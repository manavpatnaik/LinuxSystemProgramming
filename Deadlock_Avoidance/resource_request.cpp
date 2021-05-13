#include <iostream>
using namespace std;

int main() {
    int num_processes, num_resources;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of resources: ";
    cin >> num_resources;

    int total_resources[num_resources];
    int available[num_resources];

    int allocation[num_processes][num_resources];
    int max_request[num_processes][num_resources];
    int need[num_processes][num_resources];
    int request[num_processes][num_resources];

    // Enter allocated resources
    cout << "Enter the allocation:" << endl;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> allocation[i][j];
        }
    }

    // Max resources required
    cout << "Enter max resources required:" << endl;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> max_request[i][j];
        }
    }

    // Compute the need
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max_request[i][j] - allocation[i][j];
        }
    }

    cout << "Enter the resources required by each of the processess:" << endl;
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            cin >> request[i][j];
        }
    }

    // Deadlock avoidance check
    int less_than_need = 0;
    int less_than_available = 0;
    for (int i = 0; i < num_processes; i++) {
        // i => process number
        less_than_need = 0;
        less_than_available = 0;
        for (int j = 0; j < num_resources; j++) {
            if (request[i][j] <= need[i][j]) {
                less_than_need++;
            }
        }

        if (less_than_need == num_resources) {
            for (int j = 0; j < num_resources; j++) {
                if (request[i][j] <= available[j]) {
                    less_than_available++;
                }
            }
            if (less_than_available == num_resources) {
                // The request is less than need and the available, so it doesnt cause deadlock
                for (int k = 0; k < num_resources; k++) {
                    // i => Process number, k => corresponding resource
                    available[k] = available[k] - request[i][k];
                    allocation[i][k] = allocation[i][k] + request[i][k];
                    need[i][k] = need[i][k] - request[i][k];
                }
            } else {
                cout << "Process " << i << " is waiting for resources." << endl;
                continue;
            }
        } else {
            cout << "Exited: Process requested more resources than its max claim" << endl;
            break;
        }
    }
}