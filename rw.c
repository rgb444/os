#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <unistd.h>

#define R 5 // Number of readers
#define W 5 // Number of writers

int readcount = 0;  // Number of active readers
int s = 5;          // Shared resource

pthread_mutex_t x;  // Mutex for reader count update
sem_t wsem;         // Semaphore for writers

// Function declarations
void *reader(void *a);
void *writer(void *a);

int main() {
    int i, op;
    pthread_t thread_read[R], thread_write[W];

    // Initialize mutex and semaphores
    pthread_mutex_init(&x, NULL);
    sem_init(&wsem, 0, 1); // Binary semaphore for writers

    do {
        printf("\nMenu:\n1. Readers have priority\n2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &op);

        if (op == 1) {
            for (i = 0; i < W; i++) {
                pthread_create(&thread_write[i], NULL, writer, (void *)(intptr_t)i);
            }
            for (i = 0; i < R; i++) {
                pthread_create(&thread_read[i], NULL, reader, (void *)(intptr_t)i);
            }

            for (i = 0; i < W; i++) {
                pthread_join(thread_write[i], NULL);
            }
            for (i = 0; i < R; i++) {
                pthread_join(thread_read[i], NULL);
            }
        } else if (op == 2) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid option. Please try again.\n");
        }
    } while (op != 2);

    // Destroy mutex and semaphores
    pthread_mutex_destroy(&x);
    sem_destroy(&wsem);

    return 0;
}

void *reader(void *a) {
    int r = (intptr_t)a; // Reader ID
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&x); // Lock to update reader count
        readcount++;
        if (readcount == 1) {
            sem_wait(&wsem); // First reader blocks writers
        }
        pthread_mutex_unlock(&x); // Unlock after updating reader count

        // Reading the shared resource
        printf("Reader %d is reading: %d\n", r, s);

        pthread_mutex_lock(&x); // Lock to update reader count
        readcount--;
        if (readcount == 0) {
            sem_post(&wsem); // Last reader unblocks writers
        }
        pthread_mutex_unlock(&x); // Unlock after updating reader count

        sleep(rand() % 3); // Simulate reading time
    }
    return NULL;
}

void *writer(void *a) {
    int w = (intptr_t)a; // Writer ID
    for (int i = 0; i < 2; i++) {
        sem_wait(&wsem); // Writer blocks other writers and readers

        // Writing to the shared resource
        s += 5;
        printf("Writer %d is writing: %d\n", w, s);

        sem_post(&wsem); // Writer unblocks others
        sleep(rand() % 3); // Simulate writing time
    }
    return NULL;
}
