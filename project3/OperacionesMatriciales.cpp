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
        unordered_set<int> valoresUnicos;
        vector<int> resultado;

        #pragma omp parallel
        {
            unordered_set<int> localSet;
            unsigned int seed = time(0) + omp_get_thread_num();
            
            while (localSet.size() < maxSize / omp_get_num_threads()) {
                int randomNum = rand_r(&seed) % 100 + 1;
                localSet.insert(randomNum);
            }

            #pragma omp critical
            valoresUnicos.insert(localSet.begin(), localSet.end());
        }

        resultado.assign(valoresUnicos.begin(), valoresUnicos.end());
        return resultado;
    }
};
    