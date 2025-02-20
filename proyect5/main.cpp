#include "FuerzaBruta.h"

int main() {

    cout << "Integrantes:" << endl;
    cout << "* Ayala Reyes Arely Daniela" << endl;
    cout << "* Ortega Gutierrez Edwin Omar" << endl;
    cout << "* Topete Sarabia Manuel Alejandro" << endl;

    int numHilos = omp_get_max_threads();
    cout << "Iniciando la búsqueda con " << numHilos << " hilos..." << endl;
    FuerzaBruta::fuerzaBruta(numHilos);
    cout << "Búsqueda finalizada." << endl;

    return 0;
}
  
    

