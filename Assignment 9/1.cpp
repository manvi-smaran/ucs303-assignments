#include <iostream>
#include <pthread.h>
using namespace std;

int size = 6;
int arr[] = {1, 2, 3, 4, 5, 6};

int sumResult;
int maxResult;

void *calculateSum(void *arg){
    int sum = 0;
    for(int i = 0; i < size; i++){
        sum += arr[i];
    }
    sumResult = sum;
    pthread_exit(nullptr);
}

void *maxValue(void *arg){
    int max = arr[0];
    for(int i = 0; i < size; i++){
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    maxResult = max;
    pthread_exit(nullptr);
}

int main(){
    pthread_t thread1, thread2;
    pthread_create(&thread1, nullptr, calculateSum, nullptr);
    pthread_create(&thread2, nullptr, maxValue, nullptr);

    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);

    cout << "Sum of array elements: " << sumResult << endl;
    cout << "Max element: " << maxResult << endl;   

    return 0;
}