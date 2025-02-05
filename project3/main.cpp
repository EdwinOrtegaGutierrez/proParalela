#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

using namespace std;

class OperacionesMatriciales {
private:
    vector<int> matriz;
    static const int maxSize = 100;

public:
    OperacionesMatriciales() { srand(time(0) + omp_get_thread_num()); }

    vector<int> crearMatrizAleatoriaOpenMP() {
        while (matriz.size() < maxSize) {
            int randomNum = rand() % 100 + 1;
            
            #pragma omp critical
            {
                if (find(matriz.begin(), matriz.end(), randomNum) == matriz.end()) {
                    matriz.push_back(randomNum);
                }
            }
        }
        return matriz;
    }
};

int main() {
    OperacionesMatriciales operaciones;
    vector<int> matrizGenerada = operaciones.crearMatrizAleatoriaOpenMP();

    cout << "Matriz generada: " << matrizGenerada.size() << endl;
    for (size_t i = 0; i < matrizGenerada.size(); i++) {
        cout << matrizGenerada[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl; // Formato de 10x10
    }

    return 0;
}
