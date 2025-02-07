#ifndef OPERACIONES_MATRICIALES_H
#define OPERACIONES_MATRICIALES_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

using namespace std;

class OperacionesMatriciales {
private:
    static const int maxSize = 100;

public:
    OperacionesMatriciales() { srand(time(0) + rand()); }

    vector<int> crearMatrizAleatoriaOpenMP() {
        vector<int> nuevaMatriz;
        srand(time(0) + rand()); // Reiniciar la semilla aleatoria en cada llamada

        while (nuevaMatriz.size() < maxSize) {
            int randomNum = rand() % 1000 + 1;
            
            if (find(nuevaMatriz.begin(), nuevaMatriz.end(), randomNum) == nuevaMatriz.end()) {
                nuevaMatriz.push_back(randomNum);
            }
        }
        return nuevaMatriz;
    }

    void verMatriz(const vector<int>& m) {
        cout << "Matriz generada: " << endl;
        for (size_t i = 0; i < m.size(); i++) {
            cout << m[i] << " ";
            if ((i + 1) % 10 == 0) cout << endl; // Formato de 10x10
        }
    }

    vector<int> sumarMatricesOpenMP(const vector<int>& matrizA, const vector<int>& matrizB) {
        vector<int> resultado(matrizA.size());
        #pragma omp parallel for
        for (size_t i = 0; i < matrizA.size(); i++) {
            resultado[i] = matrizA[i] + matrizB[i];
        }
        return resultado;
    }
    
    vector<int> restarMatricesOpenMP(const vector<int>& matrizA, const vector<int>& matrizB) {
        vector<int> resultado(matrizA.size());
        #pragma omp parallel for
        for (size_t i = 0; i < matrizA.size(); i++) {
            resultado[i] = matrizA[i] - matrizB[i];
        }
        return resultado;
    }

    vector<int> multiplicarMatricesOpenMP(const vector<int>& matrizA, const vector<int>& matrizB) {
        vector<int> resultado(maxSize, 0); // Matriz resultado (inicializada en 0)
        const int N = 10; // Tamaño de la matriz cuadrada 10x10

            #pragma omp parallel for collapse(2)
            for (int i = 0; i < N; i++) { // Filas de A
                for (int j = 0; j < N; j++) { // Columnas de B
                    int suma = 0;
                    for (int k = 0; k < N; k++) { // Multiplicación fila A * columna B
                        suma += matrizA[i * N + k] * matrizB[k * N + j];
                    }
                    resultado[i * N + j] = suma;
                }
            }
            return resultado;
        }

};

#endif // OPERACIONES_MATRICIALES_H
