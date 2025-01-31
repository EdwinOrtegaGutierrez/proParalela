#include <stdio.h>
#include <mpi.h>  

int main(int argc, char *argv[])
{
  int rank, size;

  // Inicializar MPI
  MPI_Init(&argc, &argv);

  // Obtener el rango (ID) del proceso y el tamaño total de procesos
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Imprimir el mensaje desde cada proceso
  printf("Hola Mundo desde el proceso %d de %d\n", rank, size);

  // Finalizar MPI
  MPI_Finalize();

  return 0;
}