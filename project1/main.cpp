#include <iostream>
#include <omp.h>

using namespace std;

int main(int argc, char** argv){
    #pragma omp parallel
    {
        #pragma omp critical
        {
            cout << "Hola mundo paralelo desde C" << endl;
        }
    }

    cout << "Hola mundo secuencial desde C++" << endl;
    return 0;
}
