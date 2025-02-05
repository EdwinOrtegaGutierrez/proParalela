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
            int randomNum = rand() % 1000 + 1;
            
            if (find(matriz.begin(), matriz.end(), randomNum) == matriz.end()) {
                matriz.push_back(randomNum);
            }
        }
        return matriz;
    }

    void verMatriz(vector<int> m){
        cout << "Matriz generada: " << endl;
        for (size_t i = 0; i < m.size(); i++) {
            cout << m[i] << " ";
            if ((i + 1) % 10 == 0) cout << endl; // Formato de 10x10
        }
    }
};

int main() {
    OperacionesMatriciales om;
    vector<int> matrizGenerada = om.crearMatrizAleatoriaOpenMP();
    
    om.verMatriz(matrizGenerada);
    return 0;
}
