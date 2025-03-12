#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <stdexcept>

class OperacionesVector {
private:
    std::vector<int> vector;
public:
    void CrearArreglo() {
        try {
            vector.resize(1000);
            std::iota(vector.begin(), vector.end(), 1);
            std::shuffle(vector.begin(), vector.end(), std::mt19937{std::random_device{}()});
        } catch (const std::exception &e) {
            std::cerr << "Error al crear el arreglo: " << e.what() << std::endl;
        }
    }
    
    void MostrarArreglo() {
        std::cout << "Vector generado: ";
        for (int num : vector) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
    
    int Sumatoria() {
        int local_sum = std::accumulate(vector.begin(), vector.end(), 0);
        int global_sum;
        MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        return global_sum;
    }
    
    double Promedio() {
        int global_sum = Sumatoria();
        return static_cast<double>(global_sum) / vector.size();
    }
    
    int Maximo() {
        int local_max = *std::max_element(vector.begin(), vector.end());
        int global_max;
        MPI_Reduce(&local_max, &global_max, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
        return global_max;
    }
    
    int Minimo() {
        int local_min = *std::min_element(vector.begin(), vector.end());
        int global_min;
        MPI_Reduce(&local_min, &global_min, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
        return global_min;
    }
};

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if (rank == 0) {
        std::cout << "* Ayala Reyes Arely Daniela" << std::endl;
        std::cout << "* Ortega Gutierrez Edwin Omar" << std::endl;
        std::cout << "* Topete Sarabia Manuel Alejandro" << std::endl;
    }
    
    OperacionesVector opVec;
    opVec.CrearArreglo();
    
    if (rank == 0) {
        opVec.MostrarArreglo();
    }
    
    int opcion;
    do {
        if (rank == 0) {
            std::cout << "\nMenú de operaciones:\n";
            std::cout << "1. Calcular sumatoria\n";
            std::cout << "2. Calcular promedio\n";
            std::cout << "3. Encontrar máximo y mínimo\n";
            std::cout << "4. Salir\n";
            std::cout << "Seleccione una opción: ";
            std::cin >> opcion;
        }
        
        MPI_Bcast(&opcion, 1, MPI_INT, 0, MPI_COMM_WORLD);
        
        if (opcion == 1) {
            int resultado = opVec.Sumatoria();
            if (rank == 0) {
                std::cout << "Sumatoria: " << resultado << "\n";
            }
        } else if (opcion == 2) {
            double resultado = opVec.Promedio();
            if (rank == 0) {
                std::cout << "Promedio: " << resultado << "\n";
            }
        } else if (opcion == 3) {
            int maximo = opVec.Maximo();
            int minimo = opVec.Minimo();
            if (rank == 0) {
                std::cout << "Máximo: " << maximo << ", Mínimo: " << minimo << "\n";
            }
        }
    } while (opcion != 4);
    
    if (rank == 0) {
        std::cout << "* Ayala Reyes Arely Daniela" << std::endl;
        std::cout << "* Ortega Gutierrez Edwin Omar" << std::endl;
        std::cout << "* Topete Sarabia Manuel Alejandro" << std::endl;
    }
    
    MPI_Finalize();
    return 0;
}