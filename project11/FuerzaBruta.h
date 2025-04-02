#ifndef FUERZABRUTA_H
#define FUERZABRUTA_H

#include <iostream>
#include <mpi.h>
#include <string>
#include <vector>

using namespace std;

// Conjunto de caracteres
const string charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"; 
const string target_key = "7qG3wi5WBOdXMHPXxAreSlrSgHrKs7pRcyrPFXBAvhBnS999hL";  // Clave original

const int KEY_LENGTH = target_key.size();  // Longitud de la clave
extern bool found;  // Indicador global para señalar que la clave ha sido encontrada
extern bool stop;   // Indicar si todos los procesos deben detenerse
extern vector<string> cloneKeys;  // Lista para almacenar las claves encontradas

vector<string> splitKey(const string& key, int num_processes);
bool verifyKey(const string& key_part, const string& target_part);
void bruteForceSearch(const string& sub_target, int process_id, int num_processes);

#endif