#ifndef OPERACIONESMATRICIALES_H
#define OPERACIONESMATRICIALES_H

#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

class OperacionesMatriciales {
public:
    // Función para crear una matriz aleatoria distribuida entre los procesos MPI
    void crearMatrizAleatoriaMPI(int filas, int columnas, int* matriz, int rangoProceso, int numProcesos, int semillaExtra = 0) {
        int elementosPorProceso = (filas * columnas + numProcesos - 1) / numProcesos;
        int inicio = rangoProceso * elementosPorProceso;
        int fin = std::min(inicio + elementosPorProceso, filas * columnas);

        srand(time(NULL) + rangoProceso + semillaExtra);
        for (int i = inicio; i < fin; i++) {
            matriz[i] = rand() % 100;
        }
    }

    // Función para sumar dos matrices distribuidas en los procesos MPI
    void sumarMatricesMPI(int* matrizA, int* matrizB, int* resultado, int elementosPorProceso, int rangoProceso, int numProcesos) {
        for (int i = 0; i < elementosPorProceso; i++) {
            resultado[i] = matrizA[i] + matrizB[i];
        }
    }

    // Función para restar dos matrices distribuidas en los procesos MPI
    void restarMatricesMPI(int* matrizA, int* matrizB, int* resultado, int elementosPorProceso, int rangoProceso, int numProcesos) {
        for (int i = 0; i < elementosPorProceso; i++) {
            resultado[i] = matrizA[i] - matrizB[i];
        }
    }

    // Función para multiplicar dos matrices elemento por elemento
    void multiplicarMatricesElementoPorElementoMPI(int* matrizA, int* matrizB, int* resultado, int elementosPorProceso, int rangoProceso, int numProcesos) {
        for (int i = 0; i < elementosPorProceso; i++) {
            resultado[i] = matrizA[i] * matrizB[i];
        }
    }

    // Función para transponer una matriz distribuida en los procesos MPI
    void transponerMatrizMPI(int* matriz, int* transpuesta, int filas, int columnas, int rangoProceso, int numProcesos) {
        int elementosPorProceso = (filas * columnas) / numProcesos;
        int inicio = rangoProceso * elementosPorProceso;
        int fin = inicio + elementosPorProceso;

        for (int i = inicio; i < fin; i++) {
            int fila = i / columnas;
            int col = i % columnas;
            transpuesta[col * filas + fila] = matriz[i];
        }
    }

    // Función corregida para imprimir la matriz usando MPI_Gather
    void imprimirMatriz(int* matriz, int filas, int columnas, int rangoProceso, int numProcesos) {
        int elementosPorProceso = (filas * columnas) / numProcesos;
        int* matrizCompleta = nullptr;

        if (rangoProceso == 0) {
            matrizCompleta = new int[filas * columnas];
        }

        // Recolectamos los fragmentos de la matriz en el proceso 0
        MPI_Gather(matriz, elementosPorProceso, MPI_INT,
                   matrizCompleta, elementosPorProceso, MPI_INT,
                   0, MPI_COMM_WORLD);

        if (rangoProceso == 0) {
            std::cout << "Matriz:" << std::endl;
            for (int i = 0; i < filas; i++) {
                for (int j = 0; j < columnas; j++) {
                    std::cout << matrizCompleta[i * columnas + j] << "\t";
                }
                std::cout << std::endl;
            }
            std::cout << std::endl;
            delete[] matrizCompleta;
        }
    }
};

#endif // OPERACIONESMATRICIALES_H
