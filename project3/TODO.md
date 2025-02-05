
# Actividades

## Crear una clase llamada `OperacionesMatriciales`

* Crear Matrices Aleatorias `edwin`
    * Función: crearMatrizAleatoriaOpenMP
    * Descripción: Esta función debe crear una matriz aleatoria distribuida entre los procesos OpenMP. Cada proceso genera una parte de la matriz de manera que no haya duplicados en los elementos.
* Sumar Matrices `Alejandro`
    * Función: sumarMatricesOpenMP
    * Descripción: Esta función debe sumar dos matrices distribuidas en los procesos OpenMP. Cada proceso realiza la suma de su porción de las matrices y los resultados se combinan para obtener la matriz final.
* Restar Matrices `Alejandro`
    * Función: restarMatricesOpenMP
    * Descripción: Esta función debe restar dos matrices distribuidas en los procesos OpenMP. Similar a la suma, cada proceso resta su porción de las matrices y los resultados se combinan para obtener la matriz final.
* Multiplicar Matrices `Arely`
    * Función: multiplicarMatricesOpenMP
    * Descripción: Esta función debe multiplicar dos matrices distribuidas en los procesos OpenMP. Cada proceso calcula una porción del producto de las matrices y los resultados se combinan para formar la matriz final.
* Transponer Matriz `Arely`
    * Función: transponerMatrizOpenMP
    * Descripción: Esta función debe transponer una matriz distribuida en los procesos OpenMP. Cada proceso transpone su porción de la matriz y los resultados se combinan para obtener la matriz transpuesta.

## Detalles del Main `edwin`
Crear Instancias y Variables:
1. Creen una instancia de la clase OperacionesMatriciales.
2. Declaren y creen las matrices y otras variables necesarias para las operaciones.

Menú Interactivo:
1. Desarrollen un menú interactivo utilizando un bucle do-while o while para permitir al usuario seleccionar las operaciones matriciales.
* Opciones del menú:
    * Crear matrices aleatorias.
    * Sumar matrices.
    * Restar matrices.
    * Multiplicar matrices.
    * Transponer matriz.
    * Salir del programa.

Realizar Operaciones:
* Según la opción seleccionada por el usuario, llamen a la función correspondiente de la clase OperacionesMatriciales.
* Calculen el tiempo de ejecución de cada operación utilizando omp_get_wtime().
Mostrar Resultados:
* Estructuren los resultados de salida de cada operación para que sean mostrados de manera clara y estructurada.
* Utilicen funciones de impresión para mostrar las matrices resultantes y el tiempo de ejecución.

## Ejemplo de Flujo del Main: `arely`
Instancias y variables:
```cpp
main(){

    OperacionesMatriciales operacionesMatrices;
    Matrices matrizA, matrizB; //, etc.
    
    // Menú interactivo:
    // Bucle do-while o while para mostrar y procesar el menú.
    
    // Operaciones:
    // Según la opción del usuario, llamen a funciones como operacionesMatrices.crearMatrizAleatoriaMPI(filas, columnas);
    
    // Tiempo de ejecución:
    tiempoInicio = omp_get_wtime();
    tiempoFin = omp_get_wtime();
    // Calculen y muestren tiempoEjecucion.
}
```