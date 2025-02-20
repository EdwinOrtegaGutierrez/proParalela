#include <iostream>
#include "FuerzaBruta.h"

using namespace std;

volatile bool found = false;
string cloneKey = "";

int main() {
    cout << "Integrantes:" << endl;
    cout << "* Ayala Reyes Arely Daniela" << endl;
    cout << "* Ortega Gutierrez Edwin Omar" << endl;
    cout << "* Topete Sarabia Manuel Alejandro" << endl;

    int num_threads = omp_get_max_threads();
    vector<string> sub_keys = splitKey(target_key, num_threads);

    double start_time = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < num_threads; ++i) {
        bruteForceSearch(sub_keys[i], i);
    }

    double end_time = omp_get_wtime();

    // Esperar hasta que todos los hilos terminen y verificar la clave completa
    #pragma omp flush(cloneKeys)
    
    // Verificar si alguna subclave encontrada corresponde a la clave original
    bool found_key = false;
    for (const string& key : cloneKeys) {
        if (key == target_key) {
            found_key = true;
            break;
        }
    }
    
    for (size_t i = 0; i < cloneKeys.size(); i++)
    {
        cloneKey += cloneKeys[i];
    }
    if(cloneKey == target_key){
        cout << "¡La clave original fue encontrada!\n";
        cout << "Clave encontrada: " << cloneKey << endl;
        cout << "Clave original: " << target_key << endl;
    }

    cout << "Tiempo de ejecución: " << (end_time - start_time) << " segundos.\n";
    return 0;
}
