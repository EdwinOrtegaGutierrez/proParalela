#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <omp.h>

std::string limpiarPalabra(const std::string& palabra) {
    std::string limpia;
    for (char c : palabra) {
        if (std::isalnum(c))
            limpia += std::tolower(c);
    }
    return limpia;
}

int main() {
    std::ifstream archivo("input.txt");
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo input.txt\n";
        return 1;
    }

    std::vector<std::string> palabras;
    std::string linea, palabra;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        while (ss >> palabra) {
            std::string limpia = limpiarPalabra(palabra);
            if (!limpia.empty())
                palabras.push_back(limpia);
        }
    }
    archivo.close();

    std::unordered_map<std::string, int> conteoGlobal;
    int n = palabras.size();

    double inicio = omp_get_wtime();

    // Crear un mapa por hilo
    int num_threads = 4;
    std::vector<std::unordered_map<std::string, int>> conteoParcial(num_threads);

    #pragma omp parallel num_threads(num_threads)
    {
        int id = omp_get_thread_num();
        int inicio = id * n / num_threads;
        int fin = (id + 1) * n / num_threads;

        for (int i = inicio; i < fin; ++i) {
            conteoParcial[id][palabras[i]]++;
        }
    }

    // Fusionar resultados
    for (const auto& parcial : conteoParcial) {
        for (const auto& par : parcial) {
            conteoGlobal[par.first] += par.second;
        }
    }

    double fin = omp_get_wtime();

    // Mostrar resultados
    for (const auto& par : conteoGlobal) {
        std::cout << par.first << ": " << par.second << "\n";
    }

    std::cout << "\nTiempo de conteo (OpenMP): " << (fin - inicio) << " segundos\n";

    return 0;
}
