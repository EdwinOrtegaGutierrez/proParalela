#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>
#include <string>
#include <chrono>

__global__ void contarPalabras(int* indices, int n, int* conteo, int totalPalabrasUnicas) {
    int tid = threadIdx.x + blockIdx.x * blockDim.x;
    int totalThreads = gridDim.x * blockDim.x;

    for (int i = tid; i < n; i += totalThreads) {
        int index = indices[i];
        atomicAdd(&conteo[index], 1);  // acceso seguro
    }
}

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

    int total = palabras.size();

    // Mapear palabras únicas a índices
    std::unordered_map<std::string, int> mapa;
    std::vector<std::string> palabrasUnicas;
    int idx = 0;
    std::vector<int> palabrasIdx(total);

    for (int i = 0; i < total; ++i) {
        if (mapa.find(palabras[i]) == mapa.end()) {
            mapa[palabras[i]] = idx++;
            palabrasUnicas.push_back(palabras[i]);
        }
        palabrasIdx[i] = mapa[palabras[i]];
    }

    int totalUnicas = palabrasUnicas.size();

    // Reservar memoria en GPU
    int* d_indices;
    int* d_conteo;

    cudaMalloc((void**)&d_indices, total * sizeof(int));
    cudaMalloc((void**)&d_conteo, totalUnicas * sizeof(int));
    cudaMemset(d_conteo, 0, totalUnicas * sizeof(int));
    cudaMemcpy(d_indices, palabrasIdx.data(), total * sizeof(int), cudaMemcpyHostToDevice);

    // Medir tiempo
    auto inicio = std::chrono::high_resolution_clock::now();

    // Lanzar kernel
    int threadsPorBloque = 256;
    int bloques = (total + threadsPorBloque - 1) / threadsPorBloque;
    contarPalabras<<<bloques, threadsPorBloque>>>(d_indices, total, d_conteo, totalUnicas);

    cudaDeviceSynchronize();

    auto fin = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = fin - inicio;

    // Copiar resultados
    std::vector<int> conteo(totalUnicas);
    cudaMemcpy(conteo.data(), d_conteo, totalUnicas * sizeof(int), cudaMemcpyDeviceToHost);

    // Mostrar resultados
    for (int i = 0; i < totalUnicas; ++i) {
        std::cout << palabrasUnicas[i] << ": " << conteo[i] << "\n";
    }

    std::cout << "\nTiempo de conteo (CUDA): " << duracion.count() << " segundos\n";

    // Liberar memoria
    cudaFree(d_indices);
    cudaFree(d_conteo);

    return 0;
}
