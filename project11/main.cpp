#include "FuerzaBruta.h"

// Define the global variables
bool found = false;
bool stop = false;
vector<string> cloneKeys;

vector<string> splitKey(const string& key, int num_processes) {
    vector<string> sub_keys;
    int part_size = KEY_LENGTH / num_processes;
    int remainder = KEY_LENGTH % num_processes;
    int start = 0;

    for (int i = 0; i < num_processes; ++i) {
        int length = part_size + (i < remainder ? 1 : 0);
        sub_keys.push_back(key.substr(start, length));
        start += length;
    }
    return sub_keys;
}

bool verifyKey(const string& key_part, const string& target_part) {
    return key_part == target_part;
}

void bruteForceSearch(const string& sub_target, int process_id, int num_processes) {
    size_t charset_size = charset.size();
    size_t total_combinations = 1;

    for (size_t i = 0; i < sub_target.size(); ++i) {
        total_combinations *= charset_size;
    }

    if (process_id == 0) {
        cloneKeys.resize(num_processes);
    }

    // Calculate workload distribution
    size_t chunk_size = total_combinations / num_processes;
    size_t remainder = total_combinations % num_processes;
    size_t start = process_id * chunk_size + (process_id < remainder ? process_id : remainder);
    size_t end = start + chunk_size + (process_id < remainder ? 1 : 0);

    for (size_t i = start; i < end; ++i) {
        // Check for stop signal
        int stop_flag;
        MPI_Iprobe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stop_flag, MPI_STATUS_IGNORE);
        if (stop_flag) {
            int stop_signal;
            MPI_Recv(&stop_signal, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (stop_signal) break;
        }

        string key(sub_target.size(), ' ');
        size_t index = i;

        for (int j = sub_target.size() - 1; j >= 0; --j) {
            key[j] = charset[index % charset_size];
            index /= charset_size;
        }

        if (verifyKey(key, sub_target)) {
            found = true;
            cloneKeys[process_id] = key;

            // Broadcast found status to all processes
            int found_int = found ? 1 : 0;
            MPI_Bcast(&found_int, 1, MPI_INT, process_id, MPI_COMM_WORLD);
            found = (found_int == 1);
            
            if (key == target_key) {
                stop = true;
                // Send stop signal to all processes
                int stop_signal = 1;
                for (int dest = 0; dest < num_processes; ++dest) {
                    if (dest != process_id) {
                        MPI_Send(&stop_signal, 1, MPI_INT, dest, 0, MPI_COMM_WORLD);
                    }
                }
                break;
            }
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
}