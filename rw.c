#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdint.h>
#include <unistd.h>

#define R 5
#define W 5

int readcount = 0;

sem_t wsem;
pthread_mutex_t rmutex;

int shared_data = 5;

void *reader(void *a);
void *writer(void *a);

int main()
{
    int i, op;
    pthread_t thread_read[R], thread_write[W];
    
    pthread_mutex_init(&rmutex, NULL);
    sem_init(&wsem, 0, 1);

    do {
        printf("Menu: 1. Readers have priority 2: Exit\n");
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
        } else {
            break;
        }
    } while (op != 2);

    pthread_mutex_destroy(&rmutex);
    sem_destroy(&wsem);
    return 0;
}

void *reader(void *a)
{
    int r = (intptr_t)a;
    int i = 0;
    
    while (i < 5) {
        pthread_mutex_lock(&rmutex);
        readcount++;
        if (readcount == 1) {
            sem_wait(&wsem);
        }
        pthread_mutex_unlock(&rmutex);

        printf("\t\t Reader %d is reading: %d \n", r, shared_data);

        pthread_mutex_lock(&rmutex);
        readcount--;
        if (readcount == 0) {
            sem_post(&wsem);
        }
        pthread_mutex_unlock(&rmutex);

        sleep(rand() % 3);
        i++;
    }

    return NULL;
}

void *writer(void *a)
{
    int w = (intptr_t)a;
    int i = 0;
    
    while (i < 2) {
        sem_wait(&wsem);
        
        shared_data += 5;
        printf("Writer %d is writing: %d \n", w, shared_data);

        sem_post(&wsem);

        sleep(rand() % 3);
        i++;
    }

    return NULL;
}
