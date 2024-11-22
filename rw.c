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

// explanation=>
// This code implements the Reader-Writer problem with Reader Priority using threads, mutex locks, and semaphores. It allows multiple readers to read simultaneously, while writers have exclusive access to the shared resource.

// Key Components:
// Shared Resource (s):

// A variable that readers read, and writers modify.
// Reader Count (readcount):

// Tracks the number of active readers.
// Synchronization Mechanisms:

// pthread_mutex_t x: Protects readcount from concurrent updates.
// sem_t wsem: Ensures exclusive access to the shared resource for writers.
// Workflow:
// Main Program:

// Creates 5 reader threads and 5 writer threads.
// Repeatedly prompts the user with a menu:
// Option 1: Run the Reader-Writer simulation.
// Option 2: Exit the program.
// Reader Threads:

// Each reader:
// Locks the mutex to increment readcount.
// If it is the first reader, it blocks writers by waiting on wsem.
// Reads the shared resource (s) and prints its value.
// Decrements readcount. If it is the last reader, it unblocks writers by signaling wsem.
// Readers simulate some reading time by sleeping randomly.
// Writer Threads:

// Each writer:
// Waits on wsem to block readers and other writers.
// Modifies the shared resource (s) and prints the updated value.
// Signals wsem to unblock others.
// Writers simulate writing time by sleeping randomly.
// Reader-Writers Priority:
// Reader Priority:
// Readers can read concurrently.
// A writer must wait until all readers finish.
// The first reader blocks writers, and the last reader unblocks them.
// Example Execution:
// Multiple readers can read simultaneously (e.g., Reader 1 and Reader 2 reading s=5).
// Writers gain exclusive access (e.g., Writer 1 updates s=10).
// This code efficiently handles synchronization while ensuring reader priority.
