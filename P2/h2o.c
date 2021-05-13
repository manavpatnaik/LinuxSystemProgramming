#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int hydrogenCount = 0, oxygenCount = 0;

pthread_mutex_t lock;
sem_t hyd_sem, oxy_sem; 
pthread_cond_t hydrogen_cond, oxygen_cond;
int numberOfMolecules = 0;

void formMolecule() {
    numberOfMolecules++;
    printf("H2O formed, count = %d\n", numberOfMolecules);
}

void* oxygen(void* args) {
    pthread_mutex_lock(&lock);
    
    sem_post(&oxy_sem);
    // Storing semaphore value in the integers
    sem_getvalue(&hyd_sem, &hydrogenCount);
    sem_getvalue(&oxy_sem, &oxygenCount);

    if (oxygenCount >= 1 && hydrogenCount >= 2) {
        // Decrementing the counting semaphore after creating molecule
        sem_wait(&hyd_sem);
        sem_wait(&hyd_sem);
        sem_wait(&oxy_sem);
        
        // Signalling the threads waiting for the cond vars
        pthread_cond_signal(&oxygen_cond);
        pthread_cond_signal(&hydrogen_cond);
        pthread_cond_signal(&hydrogen_cond);
        
        formMolecule();
    } else {
        // Wait for other threads to be created
        pthread_cond_wait(&oxygen_cond, &lock);
    }

    pthread_mutex_unlock(&lock);
}

void* hydrogen(void* args) {
    pthread_mutex_lock(&lock);
    
    sem_post(&hyd_sem);
    
    // Storing semaphore value in the integers
    sem_getvalue(&hyd_sem, &hydrogenCount);
    sem_getvalue(&oxy_sem, &oxygenCount);

    if (oxygenCount >= 1 && hydrogenCount >= 2) {
        // Decrementing the counting semaphore after creating molecule
        sem_wait(&hyd_sem);
        sem_wait(&hyd_sem);
        sem_wait(&oxy_sem);

        // Signalling the threads waiting for the cond vars
        pthread_cond_signal(&oxygen_cond);
        pthread_cond_signal(&hydrogen_cond);
        pthread_cond_signal(&hydrogen_cond);

        formMolecule();
    } else {
        // Wait for other threads to be created
        pthread_cond_wait(&hydrogen_cond, &lock);
    }

    pthread_mutex_unlock(&lock);
}

int main() {
    pthread_t oxygenThread, hydrogenThread;

    // Initializing the semaphores to 0
    sem_init(&hyd_sem, 0, 0);
    sem_init(&oxy_sem, 0, 0);
    
    // 3 molecules - 3 O, 6 H
    for (int i = 0; i < 3; i++) {
        if (pthread_create(&oxygenThread, NULL, oxygen, NULL) != 0) {
            perror("Oxygen creation failed");
        }
    }

    for(int i = 0; i < 6; i++) {
        if (pthread_create(&hydrogenThread, NULL, hydrogen, NULL) != 0) {
            perror("Hydrogen thread creation failed\n");
        }
    }

    pthread_join(oxygenThread, NULL);
    pthread_join(hydrogenThread, NULL);

    // Storing semaphore value in the integers
    sem_getvalue(&hyd_sem, &hydrogenCount);
    sem_getvalue(&oxy_sem, &oxygenCount);

    printf("--------------------------\n");
    printf("Total molecules created: %d\n", numberOfMolecules);
    printf("Remaining Molecules\n");
    printf("Oxygen: %d\n", oxygenCount);
    printf("Hydrogen: %d\n", hydrogenCount);

    return 0;
}