#include "OperacionesMatriciales.h"
#include <mpi.h>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int numProcesos, rangoProceso;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rangoProceso);

    OperacionesMatriciales operacionesMatrices;

    int filas = 4, columnas = 4;
    int* matrizA = new int[filas * columnas];
    int* matrizB = new int[filas * columnas];
    int* resultado = new int[filas * columnas];
    int* transpuestaA = new int[filas * columnas];
    int* transpuestaB = new int[filas * columnas];

    int opcion;
    do {
        if (rangoProceso == 0) {
            cout << "\n--- Inicio del programa ---" << endl;
            cout << "Menú de Operaciones Matriciales:" << endl;
            cout << "1. Crear matrices aleatorias" << endl;
            cout << "2. Sumar matrices" << endl;
            cout << "3. Restar matrices" << endl;
            cout << "4. Multiplicar matrices (elemento por elemento)" << endl;
            cout << "5. Transponer matrices A y B" << endl;
            cout << "6. Salir" << endl;
            cout << "Seleccione una opción: ";
            cin >> opcion;
        }

        MPI_Bcast(&opcion, 1, MPI_INT, 0, MPI_COMM_WORLD);

        double tiempoInicio, tiempoFin;

        switch (opcion) {
            case 1:
                tiempoInicio = MPI_Wtime();
                cout << "Proceso " << rangoProceso << " generando parte de las matrices..." << endl;
                operacionesMatrices.crearMatrizAleatoriaMPI(filas, columnas, matrizA, rangoProceso, numProcesos, 0);
                operacionesMatrices.crearMatrizAleatoriaMPI(filas, columnas, matrizB, rangoProceso, numProcesos, 1000);
                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);

                if (rangoProceso == 0) {
                    cout << "\nMatriz A generada:" << endl;
                    operacionesMatrices.imprimirMatriz(matrizA, filas, columnas, rangoProceso, numProcesos);
                    cout << "\nMatriz B generada:" << endl;
                    operacionesMatrices.imprimirMatriz(matrizB, filas, columnas, rangoProceso, numProcesos);
                }
                break;

            case 2:
                tiempoInicio = MPI_Wtime();
                cout << "Proceso " << rangoProceso << " sumando matrices..." << endl;
                operacionesMatrices.sumarMatricesMPI(matrizA, matrizB, resultado, (filas * columnas) / numProcesos, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);
                if (rangoProceso == 0) {
                    cout << "\nMatriz Resultado (A + B):" << endl;
                    operacionesMatrices.imprimirMatriz(resultado, filas, columnas, rangoProceso, numProcesos);
                }
                break;

            case 3:
                tiempoInicio = MPI_Wtime();
                cout << "Proceso " << rangoProceso << " restando matrices..." << endl;
                operacionesMatrices.restarMatricesMPI(matrizA, matrizB, resultado, (filas * columnas) / numProcesos, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);
                if (rangoProceso == 0) {
                    cout << "\nMatriz Resultado (A - B):" << endl;
                    operacionesMatrices.imprimirMatriz(resultado, filas, columnas, rangoProceso, numProcesos);
                }
                break;

            case 4:
                tiempoInicio = MPI_Wtime();
                cout << "Proceso " << rangoProceso << " multiplicando matrices elemento a elemento..." << endl;
                operacionesMatrices.multiplicarMatricesElementoPorElementoMPI(matrizA, matrizB, resultado, (filas * columnas) / numProcesos, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);
                if (rangoProceso == 0) {
                    cout << "\nMatriz Resultado (A * B):" << endl;
                    operacionesMatrices.imprimirMatriz(resultado, filas, columnas, rangoProceso, numProcesos);
                }
                break;

            case 5:
                tiempoInicio = MPI_Wtime();
                cout << "Proceso " << rangoProceso << " transponiendo matrices..." << endl;
                operacionesMatrices.transponerMatrizMPI(matrizA, transpuestaA, filas, columnas, rangoProceso, numProcesos);
                operacionesMatrices.transponerMatrizMPI(matrizB, transpuestaB, filas, columnas, rangoProceso, numProcesos);
                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);
                if (rangoProceso == 0) {
                    cout << "\nMatriz Transpuesta de A:" << endl;
                    operacionesMatrices.imprimirMatriz(transpuestaA, columnas, filas, rangoProceso, numProcesos);
                    cout << "\nMatriz Transpuesta de B:" << endl;
                    operacionesMatrices.imprimirMatriz(transpuestaB, columnas, filas, rangoProceso, numProcesos);
                }
                break;

            case 6:
                if (rangoProceso == 0) {
                    cout << "Saliendo del programa..." << endl;
                }
                break;

            default:
                if (rangoProceso == 0) {
                    cout << "Opción no válida. Intente de nuevo." << endl;
                }
                break;
        }

        MPI_Barrier(MPI_COMM_WORLD);

    } while (opcion != 6);

   // delete[] matrizA;
   // delete[] matrizB;
   // delete[] resultado;
   // delete[] transpuestaA;
   // delete[] transpuestaB;

    MPI_Finalize();
    return 0;
}