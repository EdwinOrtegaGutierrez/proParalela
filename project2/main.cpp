#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>

using namespace std;

class RandomArray {
    private:
        vector<int> array;
        static const int maxSize = 10;
    
    public:
        RandomArray() { srand(time(0) + omp_get_thread_num()); }

        void fillArray() {
            while (array.size() < maxSize) {
                int randomNum = rand() % 100 + 1;
                
                #pragma omp critical
                {
                    if (find(array.begin(), array.end(), randomNum) == array.end()) {
                        array.push_back(randomNum);
                        cout << "Hilo " << omp_get_thread_num() << " - Progreso: " << (array.size() * 10) << "% completado." << endl;
                    }
                }
            }
        }

        void printArray() const {
            #pragma omp critical
            {
                cout << "Hilo " << omp_get_thread_num() << " - Arreglo final: ";
                #pragma opm for
                for (int num : array) {
                    cout << num << " ";
                }
                cout << endl;
            }
        }
};

int main() {
    cout << "Integrantes:" << endl;
    cout << "* Ayala Reyes Arely Daniela" << endl;
    cout << "* Ortega Gutierrez Edwin Omar" << endl;
    cout << "* Topete Sarabia Manuel Alejandro" << endl;

    #pragma omp parallel
    {   
        RandomArray randomArray;
        
        #pragma omp critical
        {
            cout << "\nIniciando con el hilo: " << omp_get_thread_num() << "\n" << endl;
        }

        for (int i = 0; i < 4; i++) {
            randomArray.fillArray();
        }
        
        randomArray.printArray();
    }

    cout << "\nIntegrantes:" << endl;
    cout << "* Ayala Reyes Arely Daniela" << endl;
    cout << "* Ortega Gutierrez Edwin Omar" << endl;
    cout << "* Topete Sarabia Manuel Alejandro" << endl;

    return 0;
}
