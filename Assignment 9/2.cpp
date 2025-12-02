#include <iostream>
#include <pthread.h>
#include <semaphore.h>
using namespace std;

int sharedValue = 0;
sem_t s;

void* run1(void* arg) {
    for(int i = 0; i < 5; i++) {
        sem_wait(&s);
        int x = sharedValue;
        x++;
        sharedValue = x;
        cout << "thread1 updated value to " << sharedValue << "\n";
        sem_post(&s);
    }
    return NULL;
}

void* run2(void* arg) {
    for(int i = 0; i < 5; i++) {
        sem_wait(&s);
        int x = sharedValue;
        x++;
        sharedValue = x;
        cout << "thread2 updated value to " << sharedValue << "\n";
        sem_post(&s);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    sem_init(&s, 0, 1);

    pthread_create(&t1, NULL, run1, NULL);
    pthread_create(&t2, NULL, run2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&s);
    cout << "final value: " << sharedValue << "\n";
    return 0;
}
