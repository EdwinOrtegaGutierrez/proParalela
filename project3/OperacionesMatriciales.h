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
};

#endif // OPERACIONES_MATRICIALES_H
