#ifndef MENU_H
#define MENU_H

#include <cstdio>
#include "OperacionesVector.h"

// Función para mostrar el menú
void MostrarMenu() {
    printf("\n--- Menú de Operaciones ---\n");
    printf("1. Calcular la sumatoria del vector\n");
    printf("2. Calcular el promedio del vector\n");
    printf("3. Encontrar el máximo del vector\n");
    printf("4. Encontrar el mínimo del vector\n");
    printf("5. Salir\n");
    printf("6. Test Matriz (Impresion)\n");
    printf("Seleccione una opción: ");
}

// Función para manejar la lógica del menú
void EjecutarMenu(OperacionesVector& opVector) {
    int opcion;
    do {
        MostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("La sumatoria del vector es: %d\n", opVector.Sumatoria());
                break;
            case 2:
                printf("El promedio del vector es: %.2f\n", opVector.Promedio());
                break;
            case 3:
                printf("El máximo del vector es: %d\n", opVector.Maximo());
                break;
            case 4:
                printf("El mínimo del vector es: %d\n", opVector.Minimo());
                break;
            case 5:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente nuevamente.\n");
            case 6:
            opVector.ImprimirDatos();
                   break;

        }
    } while (opcion != 5);
}

#endif // MENU_H
