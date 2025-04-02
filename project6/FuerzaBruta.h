#ifndef FUERZABRUTA_H
#define FUERZABRUTA_H

#include <iostream>
#include <omp.h>
#include <string>
#include <vector>

using namespace std;

// Conjunto de caracteres
const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; 
const string target_key = "7qG3wi5WBOdXMHPXxAreSlrSgHrKs7pRcyrPFXBAvhBnS999hL";  // Clave original

const int KEY_LENGTH = target_key.size();  // Longitud de la clave
extern volatile bool found;  // Indicador global para señalar que la clave ha sido encontrada
volatile bool stop = false;  // Indicar si todos los hilos deben detenerse
vector<string> cloneKeys;  // Lista para almacenar las claves encontradas

// Función que divide la clave objetivo en subclaves para que las manejen los diferentes hilos
vector<string> splitKey(const string& key, int num_threads) {
    vector<string> sub_keys;  // Vector que contendrá las subclaves
    int part_size = KEY_LENGTH / num_threads;  // Tamaño de cada subclave
    int remainder = KEY_LENGTH % num_threads;  // Distribuir el exceso de caracteres
    int start = 0;  

    // Dividir la clave en subclaves y distribuir el resto entre los primeros hilos
    for (int i = 0; i < num_threads; ++i) {
        int length = part_size + (i < remainder ? 1 : 0);  // Cada hilo recibe una longitud ajustada según el resto
        sub_keys.push_back(key.substr(start, length));  // Se agrega la subclave al vector
        start += length;  // Actualizar el índice de inicio para la siguiente subclave
    }
    return sub_keys;
}

inline bool verifyKey(const string& key_part, const string& target_part) {
    return key_part == target_part;
}

// Búsqueda a la fuerza
inline void bruteForceSearch(const string& sub_target, int thread_id) {
    size_t charset_size = charset.size();  // Tamaño del conjunto de caracteres
    size_t total_combinations = 1;  // Número total de combinaciones posibles para esta subclave

    // Combinaciones posibles para la subclave
    for (size_t i = 0; i < sub_target.size(); ++i) {
        total_combinations *= charset_size;
    }

    // dimensionar la lista de cloneKeys a numero de hilos
    #pragma omp single
    if (cloneKeys.size() < omp_get_max_threads()) {
        cloneKeys.resize(omp_get_max_threads());  // Redimensionar cloneKeys para albergar una clave por hilo
    }

    // intenta todas las combinaciones posibles para la subclave
    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < total_combinations; ++i) {
        if (stop) continue;  // Verificar si se debe detener la ejecución del hilo

        string key(sub_target.size(), ' ');  // Crear una cadena con el mismo tamaño que la subclave
        size_t index = i;  // Índice que representará la combinación actual

        // Generar la clave de la combinación actual
        for (int j = sub_target.size() - 1; j >= 0; --j) {
            key[j] = charset[index % charset_size];  // Seleccionar el carácter de acuerdo al índice
            index /= charset_size;  // Actualizar el índice para la siguiente posición
        }

        // Verificar si la clave generada coincide con la subclave objetivo
        if (verifyKey(key, sub_target)) {
            #pragma omp atomic write
            found = true;  // clave encontrada

            #pragma omp critical
            {
                // Almacenar la subclave
                cloneKeys[thread_id] = key;
            }
        }

        // Detener la ejecución si se ha encontrado la clave objetivo completa
        #pragma omp flush(cloneKeys, stop)
        if (cloneKeys[thread_id] == target_key) {
            #pragma omp atomic write
            stop = true;  // Detener todos los hilos
        }
    }
}

#endif
