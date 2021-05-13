#include <iostream>
using namespace std;

int main() {
    // Get processes and resources
    int num_processes, num_resources;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of resources: ";
    cin >> num_resources;

    // Declare the total number of instances and available instances of a resource
    int total_resources[num_resources];
    int available[num_resources];

    int allocation[num_processes][num_resources];
    int max_request[num_processes][num_resources];
    int need[num_processes][num_resources];

    // Enter allocated resources
    cout << "Enter the allocation:" << endl;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Max resources required
    cout << "Enter max resources required: " << endl;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> max_request[i][j];
        }
    }

    // Get available resources
    cout << "Enter number of available instances: " << endl;
    for (int i = 0; i < num_resources; i++) {
        cin >> available[num_resources];
    }

    // Compute the need
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max_request[i][j] - allocation[i][j];
        }
    }

    cout << "------------------" << endl;
    cout << "Need matrix" << endl;
    cout << "------------------" << endl;
    for (int i = 0; i < num_processes; i++) {
        cout << "P" << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cout << need[i][j] << " ";
        }
        cout << endl;
    }

    // Checking if processes are in safe state
    
    int work[num_processes];
    bool finish[num_processes];
    for (int i = 0; i < num_processes; i++) {
        work[i] = available[i];
        finish[i] = false;
    } 
        
    bool safe = true;

    for (int p_no = 0; p_no < num_processes; p_no++) {
        for (int i = 0; i < num_processes; i++) {
            if (finish[i] == false) {
                bool can_proceed = true;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > work[j]) {
                        can_proceed = false;
                        break;
                    }
                }

                if (can_proceed) {
                    finish[i] = true;
                    for (int k = 0; k < num_resources; k++) {
                        work[k] += allocation[i][k];
                    }
                }
            }
        }
    }

    // CHecking is all processes can be finished
    for (int i = 0; i < num_processes; i++) {
        if (finish[i] == false) {
            cout << "False at " << i << endl;
            safe = false;
            break;
        }
    }

    if (safe) {
        cout << "The system is in SAFE state" << endl;
    } else {
        cout << "The system is in UNSAFE state" << endl;
    }

    return 0;
}