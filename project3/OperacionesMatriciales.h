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
    static const int N = 10;
    static const int maxSize = N * N;

public:
    OperacionesMatriciales() { srand(time(0) + rand()); }

    vector<int> crearMatrizAleatoriaOpenMP() {
        vector<int> nuevaMatriz(maxSize);
        #pragma omp parallel
        {
            int id = omp_get_thread_num();
            int num_hilos = omp_get_num_threads();
            srand(time(0) + id);
            
            #pragma omp for
            for (int i = 0; i < maxSize; i++) {
                nuevaMatriz[i] = rand() % 1000 + 1;
                printf("Hilo %d generó la posición %d.\n", id, i); // Imprimir lo que hace cada hilo
            }
        }
        return nuevaMatriz;
    }

    void verMatriz(const vector<int>& m) {
        cout << "Matriz generada: " << endl;
        for (size_t i = 0; i < m.size(); i++) {
            cout << m[i] << " ";
            if ((i + 1) % N == 0) cout << endl; // Formato de 10x10
        }
    }

    vector<int> sumarMatricesOpenMP(const vector<int>& matrizA, const vector<int>& matrizB) {
        vector<int> resultado(maxSize);
        #pragma omp parallel for
        for (int i = 0; i < maxSize; i++) {
            resultado[i] = matrizA[i] + matrizB[i];
            printf("Hilo %d sumó la posición %d.\n", omp_get_thread_num(), i); // Imprimir lo que hace cada hilo
        }
        return resultado;
    }
    
    vector<int> restarMatricesOpenMP(const vector<int>& matrizA, const vector<int>& matrizB) {
        vector<int> resultado(maxSize);
        #pragma omp parallel for
        for (int i = 0; i < maxSize; i++) {
            resultado[i] = matrizA[i] - matrizB[i];
            printf("Hilo %d restó la posición %d.\n", omp_get_thread_num(), i); // Imprimir lo que hace cada hilo
        }
        return resultado;
    }

    vector<int> multiplicarMatricesOpenMP(const vector<int>& matrizA, const vector<int>& matrizB) {
        vector<int> resultado(maxSize, 0); // Matriz resultado (inicializada en 0)
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; i++) { // Filas de A
            for (int j = 0; j < N; j++) { // Columnas de B
                int suma = 0;
                for (int k = 0; k < N; k++) { // Multiplicación fila A * columna B
                    suma += matrizA[i * N + k] * matrizB[k * N + j];
                }
                resultado[i * N + j] = suma;
                printf("Hilo %d calculó la posición (%d, %d).\n", omp_get_thread_num(), i, j); // Imprimir lo que hace cada hilo
            }
        }
        return resultado;
    }

    vector<int> transponerMatrizOpenMP(const vector<int>& matriz) {
        vector<int> resultado(maxSize);
        #pragma omp parallel for collapse(2)
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                resultado[j * N + i] = matriz[i * N + j];
                printf("Hilo %d transpuso la posición (%d, %d).\n", omp_get_thread_num(), i, j); // Imprimir lo que hace cada hilo
            }
        }
        return resultado;
    }

};

#endif // OPERACIONES_MATRICIALES_H
