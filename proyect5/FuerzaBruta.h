#ifndef FUERZABRUTA_H
#define FUERZABRUTA_H

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

using namespace std;

class FuerzaBruta {
public:
    static const string caracteres;
    static const int longitudClave;
    static const long long totalCombinaciones;
    static const string claveObjetivo;

    static string indiceAClave(long long indice) {
        string clave(longitudClave, ' ');
        for (int i = longitudClave - 1; i >= 0; --i) {
            clave[i] = caracteres[indice % 62];
            indice /= 62;
        }
        return clave;
    }

    static bool verificarClave(const string& clave) {
        return clave == claveObjetivo;
    }

    static void fuerzaBruta(int numHilos) {
        bool encontrada = false;
        long long intento = 0;
        long long rango = totalCombinaciones / numHilos;

        #pragma omp parallel for num_threads(numHilos) shared(encontrada, intento)
        for (long long i = 0; i < totalCombinaciones; ++i) {
            if (encontrada) continue;
            string claveGenerada = indiceAClave(i);
            
            #pragma omp atomic
            intento++;
            
            if (intento % 1000000 == 0) { // Imprime cada 1 millón de intentos, solo por las dudas y risas xd
                #pragma omp critical
                {
                    cout << "Intento: " << intento << " - Probando clave: " << claveGenerada << endl;
                }
            }
            
            if (verificarClave(claveGenerada)) {
                #pragma omp critical
                {
                    cout << "Clave encontrada: " << claveGenerada << " en intento " << intento << endl;
                    encontrada = true;
                    cout << "Integrantes:" << endl;
                    cout << "* Ayala Reyes Arely Daniela" << endl;
                    cout << "* Ortega Gutierrez Edwin Omar" << endl;
                    cout << "* Topete Sarabia Manuel Alejandro" << endl;
                }
            }
        }
    }
};

const string FuerzaBruta::caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
const int FuerzaBruta::longitudClave = 10;  //Importante aqui cambiaremos la longitud de la clave que buscaremos
const long long FuerzaBruta::totalCombinaciones = pow(62, 10);
const string FuerzaBruta::claveObjetivo = "ArelyesGei"; // Y aqui ponemos la clave que queremos buscar 

#endif  //FuerzaBruta_H (Mas bruta que fuerza XD)