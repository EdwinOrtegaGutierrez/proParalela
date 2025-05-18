# Run secuencial 

```bash
g++ -std=c++11 -O2 secuencial.cpp -o contador_secuencial ; ./contador_secuencial
```

# Run MPI

```bash
mpic++ mpi.cpp -o contador_mpi ; mpirun -np 4 ./contador_mpi
```

# Run OpenMP

```bash
g++ -fopenmp openmp.cpp -o contador_openmp ; ./contador_openmp
```