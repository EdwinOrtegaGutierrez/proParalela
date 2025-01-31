#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

class RandomArray {
    private:
        vector<int> array;
        static const int maxSize = 10;

    public:
        RandomArray() { srand(time(0)); }

        void fillArray() {
            while (array.size() < maxSize) {
                int randomNum = rand() % 100 + 1;
                if (count(array.begin(), array.end(), randomNum) == 0) {
                    array.push_back(randomNum);
                    cout << "Progreso: " << (array.size() * 10) << "% completado." << endl;
                }
            }
        }

        void printArray() const {
            cout << "Arreglo final: ";
            for (int num : array) cout << num << " ";
            cout << endl;
        }
};

int main() {
    RandomArray randomArray;
    randomArray.fillArray();
    randomArray.printArray();
    return 0;
}
