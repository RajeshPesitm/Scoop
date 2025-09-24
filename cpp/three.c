#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <unistd.h>

#define TOTAL_WORDS 1000
#define BATCH_SIZE 100
#define BUFFER_SIZE 10
#define SLEEP_SECONDS 5

const char *fruits[] = {"apple", "banana", "mango", "grape", "orange"};
int num_fruits = sizeof(fruits) / sizeof(fruits[0]);

// Shared buffer
char *buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Synchronization tools
sem_t empty_slots, filled_slots;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Counters
int apple_count = 0, mango_count = 0, grape_count = 0;

void *producer(void *arg) {
    srand(time(NULL) + pthread_self());  // Random seed

    for (int i = 1; i <= TOTAL_WORDS; i++) {
        const char *fruit = fruits[rand() % num_fruits];

        sem_wait(&empty_slots);            // Wait for an empty slot
        pthread_mutex_lock(&mutex);        // Lock buffer access

        // Add fruit to buffer
        buffer[in] = strdup(fruit);        // Duplicate string to store safely
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);      // Unlock buffer
        sem_post(&filled_slots);           // Signal that a new item is available

        if (i % BATCH_SIZE == 0) {
            printf("👷 Producer: Generated %d fruits, sleeping %d seconds...\n", i, SLEEP_SECONDS);
            sleep(SLEEP_SECONDS);
        }
    }

    return NULL;
}

void *consumer(void *arg) {
    for (int i = 1; i <= TOTAL_WORDS; i++) {
        sem_wait(&filled_slots);           // Wait for an available item
        pthread_mutex_lock(&mutex);        // Lock buffer access

        // Remove fruit from buffer
        char *fruit = buffer[out];
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);      // Unlock buffer
        sem_post(&empty_slots);            // Signal that a slot is free

        // Count fruits
        if (strcmp(fruit, "apple") == 0) apple_count++;
        else if (strcmp(fruit, "mango") == 0) mango_count++;
        else if (strcmp(fruit, "grape") == 0) grape_count++;

        free(fruit);  // Free memory allocated by strdup
    }

    printf("👨 Consumer: Counted %d apples, %d mangoes, %d grapes.\n",
           apple_count, mango_count, grape_count);

    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores
    sem_init(&empty_slots, 0, BUFFER_SIZE);  // Buffer starts empty
    sem_init(&filled_slots, 0, 0);           // No items produced yet

    // Create threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&empty_slots);
    sem_destroy(&filled_slots);
    pthread_mutex_destroy(&mutex);

    printf("✅ Done.\n");
    return 0;
}
