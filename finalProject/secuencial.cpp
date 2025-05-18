#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <chrono>
#include <algorithm>
#include <cctype>

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
        std::cerr << "Error al abrir el archivo.\n";
        return 1;
    }

    std::vector<std::string> palabras;
    std::string linea, palabra;

    // Leer y tokenizar el texto
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        while (ss >> palabra) {
            std::string limpia = limpiarPalabra(palabra);
            if (!limpia.empty())
                palabras.push_back(limpia);
        }
    }
    archivo.close();

    // Medir tiempo de conteo
    auto inicio = std::chrono::high_resolution_clock::now();

    std::unordered_map<std::string, int> contador;
    for (const std::string& p : palabras) {
        contador[p]++;
    }

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;

    // Mostrar resultados
    for (const auto& par : contador) {
        std::cout << par.first << ": " << par.second << '\n';
    }

    std::cout << "\nTiempo de conteo: " << duracion.count() << " segundos\n";

    return 0;
}
