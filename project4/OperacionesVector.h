#ifndef OPERACIONES_VECTOR_H
#define OPERACIONES_VECTOR_H

#include <vector>
#include <cstdlib>
#include <omp.h>

using namespace std;

class OperacionesVector {
private:
    vector<int> datos;

public:
    // Constructor que crea el arreglo automáticamente
    OperacionesVector() {
        CrearArreglo();
    }

    // Crear un arreglo con 1000 elementos aleatorios usando OpenMP
    void CrearArreglo() {
        datos.resize(1000);
        #pragma omp parallel for
        for (int i = 0; i < 1000; i++) {
            datos[i] = rand() % 1000 + 1; // Números entre 1 y 1000
        }
    }

    // Métodos pendientes 
    int Sumatoria();
    double Promedio();
    int Maximo();
    int Minimo();

    // Obtener referencia al vector
    vector<int>& GetDatos() {
        return datos;
    }
};

#endif // OPERACIONES_VECTOR_H
