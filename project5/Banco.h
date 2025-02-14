#ifndef BANCO_H
#define BANCO_H

#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

class Banco {
private:
    int saldo;
    omp_lock_t lock;

public:
    Banco(int saldoInicial) : saldo(saldoInicial) {
        omp_init_lock(&lock);
    }

    ~Banco() {
        omp_destroy_lock(&lock);
    }

    void depositar(int cantidad) {
        omp_set_lock(&lock);
        saldo += cantidad;
        std::cout << "[+] Deposito de " << cantidad << ". Saldo actual: " << saldo << std::endl;
        omp_unset_lock(&lock);
    }

    void retirar(int cantidad) {
        omp_set_lock(&lock);
        if (saldo >= cantidad) {
            saldo -= cantidad;
            std::cout << "[-] Retiro de " << cantidad << ". Saldo actual: " << saldo << std::endl;
        } else {
            std::cout << "[!] Fondos insuficientes para retirar " << cantidad << std::endl;
        }
        omp_unset_lock(&lock);
    }

    void consultarSaldo() {
        omp_set_lock(&lock);
        std::cout << "[?] Consulta de saldo. Saldo actual: " << saldo << std::endl;
        omp_unset_lock(&lock);
    }
};

#endif