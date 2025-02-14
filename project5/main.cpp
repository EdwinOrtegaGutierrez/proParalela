#include <iostream>
#include <omp.h>
#include "Banco.h"

using namespace std; 

void realizarOperaciones(Banco &banco, int numOperaciones) {
    #pragma omp parallel for
    for (int i = 0; i < numOperaciones; i++) {
        int operacion = rand() % 3; // 0 = depositar, 1 = retirar, 2 = consultar saldo
        int cantidad = (rand() % 100) + 1;

        switch (operacion) {
            case 0:
                banco.depositar(cantidad);
                break;
            case 1:
                banco.retirar(cantidad);
                break;
            case 2:
                banco.consultarSaldo();
                break;
        }
    }
}

int main() {
    cout << "Integrantes:" << endl;
    cout << "* Ayala Reyes Arely Daniela" << endl;
    cout << "* Ortega Gutierrez Edwin Omar" << endl;
    cout << "* Topete Sarabia Manuel Alejandro" << endl;

    srand(time(nullptr));
    const int numHilos = 4;
    const int saldoInicial = 500;
    const int numOperacionesPorHilo = 4;
    
    Banco banco(saldoInicial);
    omp_set_num_threads(numHilos);

    double inicio = omp_get_wtime();

    #pragma omp parallel
    {
        realizarOperaciones(banco, numOperacionesPorHilo);
    }

    double fin = omp_get_wtime();
    std::cout << "Tiempo de ejecución: " << (fin - inicio) << " segundos." << std::endl;

    cout << "Integrantes:" << endl;
    cout << "* Ayala Reyes Arely Daniela" << endl;
    cout << "* Ortega Gutierrez Edwin Omar" << endl;
    cout << "* Topete Sarabia Manuel Alejandro" << endl;
    return 0;
}