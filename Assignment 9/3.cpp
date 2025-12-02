#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int buffer[5];
int rear = 0, front = 0;

sem_t emptySlots;
sem_t filledSlots;
sem_t mutexLock;

void* producer(void* arg) {
    for(int i = 1; i <= 10; i++) {
        sem_wait(&emptySlots);
        sem_wait(&mutexLock);

        buffer[rear] = i;
        cout << "Producer produced " << i << "\n";
        rear = (rear + 1) % 5;

        sem_post(&mutexLock);
        sem_post(&filledSlots);
    }
    return NULL;
}

void* consumer(void* arg) {
    for(int i = 1; i <= 10; i++) {
        sem_wait(&filledSlots);
        sem_wait(&mutexLock);

        int item = buffer[front];
        cout << "Consumer consumed " << item << "\n";
        front = (front + 1) % 5;

        sem_post(&mutexLock);
        sem_post(&emptySlots);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    sem_init(&emptySlots, 0, 5);
    sem_init(&filledSlots, 0, 0);
    sem_init(&mutexLock, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&filledSlots);
    sem_destroy(&mutexLock);

    return 0;
}
