#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función para crear una porción de una matriz aleatoria
void crearPorcionMatrizAleatoria(int* porcion, int elementosPorProceso, int semilla) {
    srand(semilla); // Establecer la semilla
    for (int i = 0; i < elementosPorProceso; i++) {
        porcion[i] = rand() % 100; // Números aleatorios entre 0 y 99
    }
}

// Función para imprimir una matriz
void imprimirMatriz(int* matriz, int filas, int columnas) {
    cout << "Matriz:" << endl;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            cout << matriz[i * columnas + j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int numProcesos, rangoProceso;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcesos);
    MPI_Comm_rank(MPI_COMM_WORLD, &rangoProceso);

    int filas = 4, columnas = 4;
    int totalElementos = filas * columnas;
    int elementosPorProceso = totalElementos / numProcesos;

    int* matrizA = nullptr;
    int* matrizB = nullptr;
    int* porcionA = new int[elementosPorProceso];
    int* porcionB = new int[elementosPorProceso];

    // El proceso 0 inicializa las matrices completas
    if (rangoProceso == 0) {
        matrizA = new int[totalElementos];
        matrizB = new int[totalElementos];
    }

    int opcion;
    do {
        if (rangoProceso == 0) {            
            cout << "--- Integrantes ---" << endl;
            cout << "* Ayala Reyes Arely Daniela" << endl;
            cout << "* Ortega Gutierrez Edwin Omar" << endl;
            cout << "* Topete Sarabia Manuel Alejandro" << endl;
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

        // Transmitimos la opción seleccionada a todos los procesos
        MPI_Bcast(&opcion, 1, MPI_INT, 0, MPI_COMM_WORLD);

        double tiempoInicio, tiempoFin;

        switch (opcion) {
            case 1: { // Crear matrices aleatorias
                tiempoInicio = MPI_Wtime();

                // Cada proceso genera su porción de las matrices
                int semillaA = time(NULL) + rangoProceso;
                int semillaB = time(NULL) + rangoProceso + 1000;
                cout << "Proceso " << rangoProceso << " está generando su porción de las matrices..." << endl;
                crearPorcionMatrizAleatoria(porcionA, elementosPorProceso, semillaA);
                crearPorcionMatrizAleatoria(porcionB, elementosPorProceso, semillaB);

                // Recolectamos las porciones en el proceso 0
                MPI_Gather(porcionA, elementosPorProceso, MPI_INT, matrizA, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Gather(porcionB, elementosPorProceso, MPI_INT, matrizB, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);

                if (rangoProceso == 0) {
                    cout << "Matrices generadas en " << tiempoFin - tiempoInicio << " segundos." << endl;
                    cout << "Matriz A:" << endl;
                    imprimirMatriz(matrizA, filas, columnas);
                    cout << "Matriz B:" << endl;
                    imprimirMatriz(matrizB, filas, columnas);
                }
                break;
            }

            case 2: { // Sumar matrices
                tiempoInicio = MPI_Wtime();

                // Distribuimos las matrices A y B a todos los procesos
                MPI_Scatter(matrizA, elementosPorProceso, MPI_INT, porcionA, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Scatter(matrizB, elementosPorProceso, MPI_INT, porcionB, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                // Cada proceso suma su porción
                cout << "Proceso " << rangoProceso << " está sumando su porción de las matrices..." << endl;
                int* porcionResultado = new int[elementosPorProceso];
                for (int i = 0; i < elementosPorProceso; i++) {
                    porcionResultado[i] = porcionA[i] + porcionB[i];
                }

                // Recolectamos los resultados en el proceso 0
                int* resultado = nullptr;
                if (rangoProceso == 0) {
                    resultado = new int[totalElementos];
                }
                MPI_Gather(porcionResultado, elementosPorProceso, MPI_INT, resultado, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);

                if (rangoProceso == 0) {
                    cout << "Matriz Resultado (A + B):" << endl;
                    imprimirMatriz(resultado, filas, columnas);
                    cout << "Tiempo de ejecución: " << tiempoFin - tiempoInicio << " segundos." << endl;
                    delete[] resultado;
                }
                delete[] porcionResultado;
                break;
            }

            case 3: { // Restar matrices
                tiempoInicio = MPI_Wtime();

                // Distribuimos las matrices A y B a todos los procesos
                MPI_Scatter(matrizA, elementosPorProceso, MPI_INT, porcionA, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Scatter(matrizB, elementosPorProceso, MPI_INT, porcionB, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                // Cada proceso resta su porción
                cout << "Proceso " << rangoProceso << " está restando su porción de las matrices..." << endl;
                int* porcionResultadoResta = new int[elementosPorProceso];
                for (int i = 0; i < elementosPorProceso; i++) {
                    porcionResultadoResta[i] = porcionA[i] - porcionB[i];
                }

                // Recolectamos los resultados en el proceso 0
                int* resultadoResta = nullptr;
                if (rangoProceso == 0) {
                    resultadoResta = new int[totalElementos];
                }
                MPI_Gather(porcionResultadoResta, elementosPorProceso, MPI_INT, resultadoResta, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);

                if (rangoProceso == 0) {
                    cout << "Matriz Resultado (A - B):" << endl;
                    imprimirMatriz(resultadoResta, filas, columnas);
                    cout << "Tiempo de ejecución: " << tiempoFin - tiempoInicio << " segundos." << endl;
                    delete[] resultadoResta;
                }
                delete[] porcionResultadoResta;
                break;
            }

            case 4: { // Multiplicar matrices (elemento por elemento)
                tiempoInicio = MPI_Wtime();

                // Distribuimos las matrices A y B a todos los procesos
                MPI_Scatter(matrizA, elementosPorProceso, MPI_INT, porcionA, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Scatter(matrizB, elementosPorProceso, MPI_INT, porcionB, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                // Cada proceso multiplica su porción
                cout << "Proceso " << rangoProceso << " está multiplicando su porción de las matrices..." << endl;
                int* porcionResultadoMultiplicacion = new int[elementosPorProceso];
                for (int i = 0; i < elementosPorProceso; i++) {
                    porcionResultadoMultiplicacion[i] = porcionA[i] * porcionB[i];
                }

                // Recolectamos los resultados en el proceso 0
                int* resultadoMultiplicacion = nullptr;
                if (rangoProceso == 0) {
                    resultadoMultiplicacion = new int[totalElementos];
                }
                MPI_Gather(porcionResultadoMultiplicacion, elementosPorProceso, MPI_INT, resultadoMultiplicacion, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);

                if (rangoProceso == 0) {
                    cout << "Matriz Resultado (A * B):" << endl;
                    imprimirMatriz(resultadoMultiplicacion, filas, columnas);
                    cout << "Tiempo de ejecución: " << tiempoFin - tiempoInicio << " segundos." << endl;
                    delete[] resultadoMultiplicacion;
                }
                delete[] porcionResultadoMultiplicacion;
                break;
            }

            case 5: { // Transponer matrices
                tiempoInicio = MPI_Wtime();

                // Distribuimos las matrices A y B a todos los procesos
                MPI_Scatter(matrizA, elementosPorProceso, MPI_INT, porcionA, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Scatter(matrizB, elementosPorProceso, MPI_INT, porcionB, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                // Cada proceso transpone su porción
                cout << "Proceso " << rangoProceso << " está transponiendo su porción de las matrices..." << endl;
                int* transpuestaA = new int[totalElementos];
                int* transpuestaB = new int[totalElementos];
                for (int i = 0; i < elementosPorProceso; i++) {
                    int fila = (rangoProceso * elementosPorProceso + i) / columnas;
                    int col = (rangoProceso * elementosPorProceso + i) % columnas;
                    transpuestaA[col * filas + fila] = porcionA[i];
                    transpuestaB[col * filas + fila] = porcionB[i];
                }

                // Recolectamos los resultados en el proceso 0
                int* transpuestaAFinal = nullptr;
                int* transpuestaBFinal = nullptr;
                if (rangoProceso == 0) {
                    transpuestaAFinal = new int[totalElementos];
                    transpuestaBFinal = new int[totalElementos];
                }
                MPI_Gather(transpuestaA, elementosPorProceso, MPI_INT, transpuestaAFinal, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);
                MPI_Gather(transpuestaB, elementosPorProceso, MPI_INT, transpuestaBFinal, elementosPorProceso, MPI_INT, 0, MPI_COMM_WORLD);

                tiempoFin = MPI_Wtime();
                MPI_Barrier(MPI_COMM_WORLD);

                if (rangoProceso == 0) {
                    cout << "Transpuesta de A:" << endl;
                    imprimirMatriz(transpuestaAFinal, columnas, filas);
                    cout << "Transpuesta de B:" << endl;
                    imprimirMatriz(transpuestaBFinal, columnas, filas);
                    cout << "Tiempo de ejecución: " << tiempoFin - tiempoInicio << " segundos." << endl;
                    delete[] transpuestaAFinal;
                    delete[] transpuestaBFinal;
                }
                delete[] transpuestaA;
                delete[] transpuestaB;
                break;
            }

            case 6: // Salir
                if (rangoProceso == 0) {
                    cout << "Saliendo del programa...\n" << endl;
                    cout << "--- Integrantes ---" << endl;
                    cout << "* Ayala Reyes Arely Daniela" << endl;
                    cout << "* Ortega Gutierrez Edwin Omar" << endl;
                    cout << "* Topete Sarabia Manuel Alejandro" << endl;
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

    // Liberar memoria
    delete[] porcionA;
    delete[] porcionB;
    if (rangoProceso == 0) {
        delete[] matrizA;
        delete[] matrizB;
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}