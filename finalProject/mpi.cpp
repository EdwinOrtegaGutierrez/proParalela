#include <mpi.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>

std::string limpiarPalabra(const std::string& palabra) {
    std::string limpia;
    for (char c : palabra) {
        if (std::isalnum(c))
            limpia += std::tolower(c);
    }
    return limpia;
}

// Serializa un mapa en un string (clave|valor|clave|valor|...)
std::string serializarMapa(const std::unordered_map<std::string, int>& mapa) {
    std::ostringstream oss;
    for (const auto& par : mapa) {
        oss << par.first << "|" << par.second << "|";
    }
    return oss.str();
}

// Deserializa un string en un mapa
std::unordered_map<std::string, int> deserializarMapa(const std::string& data) {
    std::unordered_map<std::string, int> mapa;
    std::istringstream iss(data);
    std::string token;
    while (std::getline(iss, token, '|')) {
        std::string clave = token;
        if (std::getline(iss, token, '|')) {
            int valor = std::stoi(token);
            mapa[clave] += valor;
        }
    }
    return mapa;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<std::string> todasPalabras;

    if (rank == 0) {
        std::ifstream archivo("input.txt");
        if (!archivo.is_open()) {
            std::cerr << "Error al abrir input.txt\n";
            MPI_Abort(MPI_COMM_WORLD, 1);
        }

        std::string linea, palabra;
        while (std::getline(archivo, linea)) {
            std::stringstream ss(linea);
            while (ss >> palabra) {
                std::string limpia = limpiarPalabra(palabra);
                if (!limpia.empty())
                    todasPalabras.push_back(limpia);
            }
        }
        archivo.close();
    }

    // Enviar tamaño a todos
    int totalPalabras = todasPalabras.size();
    MPI_Bcast(&totalPalabras, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular distribución
    int chunk = totalPalabras / size;
    int resto = totalPalabras % size;
    int inicio = rank * chunk + std::min(rank, resto);
    int fin = inicio + chunk + (rank < resto ? 1 : 0);
    int miTam = fin - inicio;

    std::vector<std::string> misPalabras(miTam);
    if (rank == 0) {
        for (int i = 1; i < size; ++i) {
            int start = i * chunk + std::min(i, resto);
            int end = start + chunk + (i < resto ? 1 : 0);
            int len = end - start;
            std::ostringstream oss;
            for (int j = start; j < end; ++j)
                oss << todasPalabras[j] << " ";
            std::string data = oss.str();
            int lenStr = data.size();
            MPI_Send(&lenStr, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(data.c_str(), lenStr, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
        // Copiar para proceso 0
        std::copy(todasPalabras.begin() + inicio, todasPalabras.begin() + fin, misPalabras.begin());
    } else {
        int lenStr;
        MPI_Recv(&lenStr, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::string data(lenStr, ' ');
        MPI_Recv(data.data(), lenStr, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::stringstream ss(data);
        std::string palabra;
        int i = 0;
        while (ss >> palabra && i < miTam) {
            misPalabras[i++] = palabra;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD); // Sincronización antes de medir
    double inicioTiempo = MPI_Wtime();

    // Conteo local
    std::unordered_map<std::string, int> mapaLocal;
    for (const std::string& p : misPalabras)
        mapaLocal[p]++;

    double finTiempo = MPI_Wtime();
    double duracion = finTiempo - inicioTiempo;

    // Serializar mapa local
    std::string serializado = serializarMapa(mapaLocal);
    int tam = serializado.size();

    if (rank == 0) {
        std::unordered_map<std::string, int> mapaFinal = mapaLocal;

        for (int i = 1; i < size; ++i) {
            int tamStr;
            MPI_Recv(&tamStr, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            std::string data(tamStr, ' ');
            MPI_Recv(data.data(), tamStr, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            auto mapaOtro = deserializarMapa(data);
            for (const auto& par : mapaOtro)
                mapaFinal[par.first] += par.second;
        }

        // Mostrar resultados
        for (const auto& par : mapaFinal)
            std::cout << par.first << ": " << par.second << '\n';

        std::cout << "\nTiempo de conteo: " << duracion << " segundos (proceso 0)\n";
    } else {
        MPI_Send(&tam, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(serializado.c_str(), tam, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    return 0;
}
