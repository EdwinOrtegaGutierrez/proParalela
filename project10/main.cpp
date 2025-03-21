#include <mpi.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Banco {
private:
    int saldo;
    MPI_Win win; // Ventana MPI para acceso remoto al saldo

public:
    Banco() : saldo(0) {
        // Crear la ventana MPI para el saldo
        MPI_Win_create(&saldo, sizeof(int), sizeof(int), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    }

    ~Banco() {
        // No liberar la ventana MPI aquí, se hará manualmente antes de MPI_Finalize()
    }

    void liberar() {
        // Liberar la ventana MPI manualmente
        MPI_Win_free(&win);
    }

    void depositar(int cantidad, int rank) {
        // Bloquear el acceso exclusivo al saldo en el proceso 'rank'
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win);
        saldo += cantidad;
        // Desbloquear el acceso
        MPI_Win_unlock(rank, win);
    }

    void retirar(int cantidad, int rank) {
        // Bloquear el acceso exclusivo al saldo en el proceso 'rank'
        MPI_Win_lock(MPI_LOCK_EXCLUSIVE, rank, 0, win);
        if (saldo >= cantidad) {
            saldo -= cantidad;
        }
        // Desbloquear el acceso
        MPI_Win_unlock(rank, win);
    }

    int consultarSaldo(int rank) {
        int saldoActual;
        // Bloquear el acceso compartido al saldo en el proceso 'rank'
        MPI_Win_lock(MPI_LOCK_SHARED, rank, 0, win);
        saldoActual = saldo;
        // Desbloquear el acceso
        MPI_Win_unlock(rank, win);
        return saldoActual;
    }
};

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        std::cout << "* Ayala Reyes Arely Daniela" << std::endl;
        std::cout << "* Ortega Gutierrez Edwin Omar" << std::endl;
        std::cout << "* Topete Sarabia Manuel Alejandro" << std::endl;
    }

    Banco banco;
    int saldoInicial = 1000;

    // Inicializar saldo en el proceso 0 y sincronizar
    if (rank == 0) {
        banco.depositar(saldoInicial, 0);
    }
    MPI_Barrier(MPI_COMM_WORLD); // Sincronizar todos los procesos

    srand(time(NULL) + rank); // Semilla diferente para cada proceso

    double startTime = MPI_Wtime();

    for (int i = 0; i < 10; ++i) {
        int operacion = rand() % 3; // 0: depositar, 1: retirar, 2: consultar saldo
        int cantidad = rand() % 100 + 1;

        switch (operacion) {
            case 0:
                banco.depositar(cantidad, rank);
                std::cout << "Proceso " << rank << " depositó " << cantidad << std::endl;
                break;
            case 1:
                banco.retirar(cantidad, rank);
                std::cout << "Proceso " << rank << " retiró " << cantidad << std::endl;
                break;
            case 2:
                int saldo = banco.consultarSaldo(rank);
                std::cout << "Proceso " << rank << " consultó saldo: " << saldo << std::endl;
                break;
        }
    }

    double endTime = MPI_Wtime();
    double tiempoEjecucion = endTime - startTime;

    if (rank == 0) {
        std::cout << "* Ayala Reyes Arely Daniela" << std::endl;
        std::cout << "* Ortega Gutierrez Edwin Omar" << std::endl;
        std::cout << "* Topete Sarabia Manuel Alejandro" << std::endl;
        std::cout << "Tiempo de ejecución total: " << tiempoEjecucion << " segundos" << std::endl;
        std::cout << "Saldo final: " << banco.consultarSaldo(rank) << std::endl;
    }

    // Liberar la ventana MPI antes de finalizar
    banco.liberar();

    MPI_Finalize();

    return 0;
}