#ifndef OPERACIONES_VECTOR_H
#define OPERACIONES_VECTOR_H

#include <vector>
#include <cstdlib>
#include <omp.h>
#include <ctime>
#include <stdio.h>

using namespace std;

class OperacionesVector {
private:
    vector<int> datos;

public:
    // Constructor que crea el arreglo automáticamente
    OperacionesVector() {
        srand(time(NULL)); 
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

    void ImprimirDatos() {
        printf("Datos del vector:\n");
        for (size_t i = 0; i < datos.size(); i++) {
            printf("%d ", datos[i]);
            if ((i + 1) % 10 == 0) printf("\n"); // Salto de línea cada 10 elementos
        }
        printf("\n");
    }
    


    int Sumatoria() {
        int suma = 0;
        #pragma omp parallel for reduction(+:suma)
        for (int i = 0; i < datos.size(); i++) {
            suma += datos[i];
        }
        return suma;
    }

    double Promedio() {
        if (datos.empty()) return 0.0;
        int suma = Sumatoria();
        return static_cast<double>(suma) / datos.size();
    }
    // Métodos pendientes 
    int Maximo() {
        if (datos.empty()) return 0;

        int max = datos[0];

        #pragma omp parallel for reduction(max:max)
        for (int i = 0; i < datos.size(); i++) {
            if (datos[i] > max) max = datos[i];
        }

        return max;
    }

    int Minimo() {
        if (datos.empty()) return 0;

        int min = datos[0];

        #pragma omp parallel for reduction(min:min)
        for (int i = 0; i < datos.size(); i++) {
            if (datos[i] < min) min = datos[i];
        }

        return min;
    }

    // Obtener referencia al vector
    vector<int>& GetDatos() {
        return datos;
    }
};

#endif // OPERACIONES_VECTOR_H
