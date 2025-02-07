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
        vector<int> matrizA, matrizB, resultado;
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
                    matrizA = om.crearMatrizAleatoriaOpenMP();
                    om.verMatriz(matrizA);
                    break;
                }
                case 2: {
                    matrizA = om.crearMatrizAleatoriaOpenMP();
                    matrizB = om.crearMatrizAleatoriaOpenMP();
                    
                    cout << "\nMatriz A (Antes de sumar):" << endl;
                    om.verMatriz(matrizA);
                    
                    cout << "\nMatriz B (Antes de sumar):" << endl;
                    om.verMatriz(matrizB);
                    
                    resultado = om.sumarMatricesOpenMP(matrizA, matrizB);
                    
                    cout << "\nResultado de la suma:" << endl;
                    om.verMatriz(resultado);
                    break;
                }
                case 3: {
                    matrizA = om.crearMatrizAleatoriaOpenMP();
                    matrizB = om.crearMatrizAleatoriaOpenMP();
                    
                    cout << "\nMatriz A (Antes de restar):" << endl;
                    om.verMatriz(matrizA);
                    
                    cout << "\nMatriz B (Antes de restar):" << endl;
                    om.verMatriz(matrizB);
                    
                    resultado = om.restarMatricesOpenMP(matrizA, matrizB);
                    
                    cout << "\nResultado de la resta:" << endl;
                    //Dada la naturaleza de los numeros tan grandes podemos tener casos como
                    // 200-500 donde el resultado sera -300
                    om.verMatriz(resultado);
                    break;
                }
                case 4: {
                    matrizA = om.crearMatrizAleatoriaOpenMP();
                    matrizB = om.crearMatrizAleatoriaOpenMP();
                    
                    cout << "\nMatriz A (Antes de multiplicar):" << endl;
                    om.verMatriz(matrizA);
                    
                    cout << "\nMatriz B (Antes de multiplicar):" << endl;
                    om.verMatriz(matrizB);

                    resultado = om.multiplicarMatricesOpenMP(matrizA, matrizB);

                    cout << "\nResultado de la multiplicación:" << endl;
                    om.verMatriz(resultado);
                    break;
                }
                case 5: {
                    matrizA = om.crearMatrizAleatoriaOpenMP();
                    
                    cout << "\nMatriz Original (Antes de transponer):" << endl;
                    om.verMatriz(matrizA);
                    
                    vector<int> transpuesta = om.transponerMatrizOpenMP(matrizA);
                    
                    cout << "\nMatriz Transpuesta:" << endl;
                    om.verMatriz(transpuesta);
                    break;
                }
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

                   