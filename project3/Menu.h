#ifndef MENU_H
#define MENU_H

#include <iostream>
#include "OperacionesMatriciales.h"
#include <omp.h>

using namespace std;

class Menu {
public:
    void mostrarMenu() {
        OperacionesMatriciales om;
        int opcion;
        
        do {
            cout << "\n--- MENU DE OPERACIONES MATRICIALES ---" << endl;
            cout << "1. Crear matrices aleatorias" << endl;
            cout << "2. Sumar matrices" << endl;
            cout << "3. Restar matrices" << endl;
            cout << "4. Multiplicar matrices" << endl;
            cout << "5. Transponer matriz" << endl;
            cout << "6. Salir" << endl;
            cout << "Seleccione una opcion: ";
            cin >> opcion;
            
            switch (opcion) {
                case 1: {
                    vector<int> matriz = om.crearMatrizAleatoriaOpenMP();
                    om.verMatriz(matriz);
                    break;
                }
                case 2: {
                    vector<int> matrizA = om.crearMatrizAleatoriaOpenMP();
                    vector<int> matrizB = om.crearMatrizAleatoriaOpenMP();
                    
                    cout << "\nMatriz A:" << endl;
                    om.verMatriz(matrizA);
                    
                    cout << "\nMatriz B:" << endl;
                    om.verMatriz(matrizB);
                    
                    vector<int> resultado = om.sumarMatricesOpenMP(matrizA, matrizB);
                    
                    cout << "\nResultado de la suma:" << endl;
                    om.verMatriz(resultado);
                    break;
                }
                case 3: {
                    vector<int> matrizA = om.crearMatrizAleatoriaOpenMP();
                    vector<int> matrizB = om.crearMatrizAleatoriaOpenMP();
                    
                    cout << "\nMatriz A:" << endl;
                    om.verMatriz(matrizA);
                    
                    cout << "\nMatriz B:" << endl;
                    om.verMatriz(matrizB);
                    
                    vector<int> resultado = om.restarMatricesOpenMP(matrizA, matrizB);
                    
                    cout << "\nResultado de la resta (Pueden generarse valores negativos):" << endl;
                    //Dada la naturaleza de los numeros tan grandes podemos tener casos como 200-500 donde el resultado sera -300
                    om.verMatriz(resultado);
                    break;
                }
                case 4:{
                    vector<int> matrizA = om.crearMatrizAleatoriaOpenMP();
                    vector<int> matrizB = om.crearMatrizAleatoriaOpenMP();

                    cout << "\nMatriz A:" << endl;
                    om.verMatriz(matrizA);

                    cout << "\nMatriz B:" << endl;
                    om.verMatriz(matrizB);

                    vector<int> resultado = om.multiplicarMatricesOpenMP(matrizA, matrizB);

                    cout << "\nResultado de la multiplicación:" << endl;
                    om.verMatriz(resultado);
                    break;
                }
                case 5:
                    cout << "Operacion de transposicion de matriz aun no implementada." << endl;
                    break;
                case 6:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Opcion invalida, intente de nuevo." << endl;
                    break;
            }
        } while (opcion != 6);
    }
};

#endif

