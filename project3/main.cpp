#include <iostream>
#include <vector>
#include "OperacionesMatriciales.h"

using namespace std;

int main() {
    OperacionesMatriciales om;
    vector<int> matrizGenerada = om.crearMatrizAleatoriaOpenMP();
    
    om.verMatriz(matrizGenerada);
    return 0;
}
