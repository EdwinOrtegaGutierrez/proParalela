#ifndef RELLENO_H
#define RELLENO_H

#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

#define ARRAY_SIZE 10

using namespace std;

class MPIManager {
private:
    int rank, size;
    int numbers[ARRAY_SIZE];

    bool is_unique(int num, int count) {
        for (int i = 0; i < count; i++) {
            if (numbers[i] == num) {
                return false; // No es único
            }
        }
        return true;
    }

public:
    MPIManager() {
        MPI_Init(NULL, NULL);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
        srand(time(NULL) + rank); // Semilla única

        MPI_Barrier(MPI_COMM_WORLD);

        if (rank == 0) { 
            cout << "--- Inicio del programa ---" << endl;
            cout << "* Ayala Reyes Arely Daniela" << endl;
            cout << "* Ortega Gutierrez Edwin Omar" << endl;
            cout << "* Topete Sarabia Manuel Alejandro" << endl;
        }
        
        MPI_Barrier(MPI_COMM_WORLD);
    }

    ~MPIManager() {
        MPI_Barrier(MPI_COMM_WORLD);

        MPI_Finalize();

        if (rank == 0) { 
            cout << "--- Fin del programa ---" << endl;
            cout << "* Ayala Reyes Arely Daniela" << endl;
            cout << "* Ortega Gutierrez Edwin Omar" << endl;
            cout << "* Topete Sarabia Manuel Alejandro" << endl;
        }


        MPI_Barrier(MPI_COMM_WORLD);
    }

    void generate_numbers() {
        int count = 0;
        while (count < ARRAY_SIZE) {
            int num = rand() % 100;
            if (is_unique(num, count)) {
                numbers[count] = num;
                count++;
            }
            cout << "Proceso " << rank << ": " << (count * 100) / ARRAY_SIZE << "% completado\n";
        }
    }

    void print_numbers() {
        cout << "Proceso " << rank << " - Números generados: ";
        for (int i = 0; i < ARRAY_SIZE; i++) {
            cout << numbers[i] << " ";
        }
        cout << endl;
    }
};

#endif // RELLENO_H
