/*
This is a classic synchronization problem where 2 threads alternately print odd and even numbers in order.

Output will be like below
Odd Thread: 1
Even Thread: 2
Odd Thread: 3
Even Thread: 4
Odd Thread: 5
Even Thread: 6
Odd Thread: 7
Even Thread: 8
Odd Thread: 9
Even Thread: 10
*/

#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_NUM 10

pthread_mutex_t lock;
pthread_cond_t cond;
int number = 1;  // start with 1

void *print_odd() {
    while (true) { // This while controls the lifetime of the worker thread.
        pthread_mutex_lock(&lock);

        while (number <= MAX_NUM && number % 2 == 0) {  // This protects against spurious wakeups and rechecks condition after every wakeup (wait if it's even's turn)
            pthread_cond_wait(&cond, &lock);
        }
        
        if(number > 10) {
          pthread_cond_signal(&cond);
          pthread_mutex_unlock(&lock);
          return NULL;
        }
        
        printf("Odd Thread: %d\n", number);
        number++;

        pthread_cond_signal(&cond);  // wake up even thread
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *print_even(void *arg) {
    while (true) {
        pthread_mutex_lock(&lock);

        while (number <= MAX_NUM && number % 2 == 1) {  // wait if it's odd's turn
            pthread_cond_wait(&cond, &lock);
        }

        if(number > 10) {
          pthread_cond_signal(&cond);
          pthread_mutex_unlock(&lock);
          return NULL;
        }
        
        printf("Even Thread: %d\n", number);
        number++;

        pthread_cond_signal(&cond);  // wake up odd thread
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t odd_thread, even_thread;

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&odd_thread, NULL, print_odd, NULL);
    pthread_create(&even_thread, NULL, print_even, NULL);

    pthread_join(odd_thread, NULL);
    pthread_join(even_thread, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);

    return 0;
}
