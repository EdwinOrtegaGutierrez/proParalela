#include "OperacionesMatriciales.h"
#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int numProcesos, rangoProceso;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rangoProceso);

    OperacionesMatriciales operacionesMatrices;

    int filas = 4, columnas = 4;  // Tamaño de las matrices (4x4)
    int* matrizA = new int[filas * columnas];
    int* matrizB = new int[filas * columnas];
    int* resultado = new int[filas * columnas];
    int* transpuestaA = new int[filas * columnas];
    int* transpuestaB = new int[filas * columnas];

    int opcion;
    do {
        if (rangoProceso == 0) {
            std::cout << "Menú de Operaciones Matriciales:" << std::endl;
            std::cout << "1. Crear matrices aleatorias" << std::endl;
            std::cout << "2. Sumar matrices" << std::endl;
            std::cout << "3. Restar matrices" << std::endl;
            std::cout << "4. Multiplicar matrices (elemento por elemento)" << std::endl;
            std::cout << "5. Transponer matrices A y B" << std::endl;
            std::cout << "6. Salir" << std::endl;
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;
        }

        MPI_Bcast(&opcion, 1, MPI_INT, 0, MPI_COMM_WORLD);

        double tiempoInicio, tiempoFin;

        switch (opcion) {
            case 1:
                tiempoInicio = MPI_Wtime();
                operacionesMatrices.crearMatrizAleatoriaMPI(filas, columnas, matrizA, rangoProceso, numProcesos, 0); // Semilla base
                operacionesMatrices.crearMatrizAleatoriaMPI(filas, columnas, matrizB, rangoProceso, numProcesos, 1000); // Semilla diferente
                tiempoFin = MPI_Wtime();
                if (rangoProceso == 0) {
                    std::cout << "Matrices creadas en " << tiempoFin - tiempoInicio << " segundos." << std::endl;
                    std::cout << "Matriz A:" << std::endl;
                    operacionesMatrices.imprimirMatriz(matrizA, filas, columnas, rangoProceso, numProcesos); // Aquí se agrega 'numProcesos'
                    std::cout << "Matriz B:" << std::endl;
                    operacionesMatrices.imprimirMatriz(matrizB, filas, columnas, rangoProceso, numProcesos); // Aquí se agrega 'numProcesos'
                }
                break;

            case 2:
                tiempoInicio = MPI_Wtime();
                operacionesMatrices.sumarMatricesMPI(matrizA, matrizB, resultado, (filas * columnas) / numProcesos, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                if (rangoProceso == 0) {
                    std::cout << "Suma de matrices realizada en " << tiempoFin - tiempoInicio << " segundos." << std::endl;
                    std::cout << "Matriz Resultado (A + B):" << std::endl;
                    operacionesMatrices.imprimirMatriz(resultado, filas, columnas, rangoProceso, numProcesos); // Aquí se agrega 'numProcesos'
                }
                break;

            case 3:
                tiempoInicio = MPI_Wtime();
                operacionesMatrices.restarMatricesMPI(matrizA, matrizB, resultado, (filas * columnas) / numProcesos, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                if (rangoProceso == 0) {
                    std::cout << "Resta de matrices realizada en " << tiempoFin - tiempoInicio << " segundos." << std::endl;
                    std::cout << "Matriz Resultado (A - B):" << std::endl;
                    operacionesMatrices.imprimirMatriz(resultado, filas, columnas, rangoProceso, numProcesos); // Aquí se agrega 'numProcesos'
                }
                break;

            case 4:
                tiempoInicio = MPI_Wtime();
                operacionesMatrices.multiplicarMatricesElementoPorElementoMPI(matrizA, matrizB, resultado, (filas * columnas) / numProcesos, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                if (rangoProceso == 0) {
                    std::cout << "Multiplicación de matrices (elemento por elemento) realizada en " << tiempoFin - tiempoInicio << " segundos." << std::endl;
                    std::cout << "Matriz Resultado (A * B):" << std::endl;
                    operacionesMatrices.imprimirMatriz(resultado, filas, columnas, rangoProceso, numProcesos); // Aquí se agrega 'numProcesos'
                }
                break;

            case 5:
                tiempoInicio = MPI_Wtime();
                operacionesMatrices.transponerMatrizMPI(matrizA, transpuestaA, filas, columnas, rangoProceso, numProcesos);
                operacionesMatrices.transponerMatrizMPI(matrizB, transpuestaB, filas, columnas, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                if (rangoProceso == 0) {
                    std::cout << "Transposición de matrices realizada en " << tiempoFin - tiempoInicio << " segundos." << std::endl;
                    std::cout << "Matriz Transpuesta de A:" << std::endl;
                    operacionesMatrices.imprimirMatriz(transpuestaA, columnas, filas, rangoProceso, numProcesos); // Aquí se agrega 'numProcesos'
                    std::cout << "Matriz Transpuesta de B:" << std::endl;
                    operacionesMatrices.imprimirMatriz(transpuestaB, columnas, filas, rangoProceso, numProcesos); // Aquí se agrega 'numProcesos'
                }
                break;

            case 6:
                if (rangoProceso == 0) {
                    std::cout << "Saliendo del programa..." << std::endl;
                }
                break;

            default:
                if (rangoProceso == 0) {
                    std::cout << "Opción no válida. Intente de nuevo." << std::endl;
                }
                break;
        }

        MPI_Barrier(MPI_COMM_WORLD);

    } while (opcion != 6);

    delete[] matrizA;
    delete[] matrizB;
    delete[] resultado;
    delete[] transpuestaA;
    delete[] transpuestaB;

    MPI_Finalize();
    return 0;
}
