#include <iostream>
#include "relleno.h"


using namespace std;
int main(int argc, char **argv) {
    MPIManager mpi;
    mpi.generate_numbers();
    mpi.print_numbers();
return EXIT_SUCCESS;
}

//mpicxx -o mpi_program main.cpp COMPILAR 
//mpirun -np 4 ./mpi_program EJECUTAR CON 4 HILOS (SE PUEDEN CAMBIAR A MAS O MENOS SEGUN EL CASO)