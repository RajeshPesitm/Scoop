#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

#define FILENAME "fruits.txt"
#define TOTAL_WORDS 1000
#define BATCH_SIZE 100
#define SLEEP_SECONDS 5

const char *fruits[] = {"apple", "banana", "mango", "grape", "orange"};
int num_fruits = sizeof(fruits) / sizeof(fruits[0]);

void generate_fruits() {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) {
        perror("Child: Failed to open file for writing");
        exit(1);
    }

    srand(time(NULL) + getpid());  // Seed random generator

    for (int i = 1; i <= TOTAL_WORDS; i++) {
        int r = rand() % num_fruits;
        fprintf(fp, "%s\n", fruits[r]);

        // Flush output to file immediately to avoid buffering issues
        fflush(fp);

        // Pause every 100 words
        if (i % BATCH_SIZE == 0) {
            printf("👶 Child: Generated %d words, sleeping for %d seconds...\n", i, SLEEP_SECONDS);
            sleep(SLEEP_SECONDS);
        }
    }

    fclose(fp);
    printf("👶 Child: Finished generating %d fruit names in '%s'\n", TOTAL_WORDS, FILENAME);
}

void count_fruits() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) {
        perror("Parent: Failed to open file for reading");
        exit(1);
    }

    char word[100];
    int apple_count = 0, mango_count = 0, grapes_count=0;

    while (fgets(word, sizeof(word), fp)) {
        word[strcspn(word, "\n")] = 0;  // Remove newline
        if (strcmp(word, "apple") == 0)
            apple_count++;
        else if (strcmp(word, "mango") == 0)
            mango_count++;
        else if (strcmp(word, "grape") == 0)
            grapes_count++;
    }

    fclose(fp);
    printf("👨 Parent: Counted %d apples and %d mangoes in '%s'\n", apple_count, mango_count, FILENAME);
    printf("👨%d grapes in '%s'\n", grapes_count, FILENAME);

}

int main() {
    pid_t pid = fork();

    if (pid < 0) { //fails for both parent and
        perror("Fork failed");
        return 1; //program stops immidiatley
    }

    if (pid == 0) { //this will pass for child
        // Child process
        generate_fruits();
        exit(0);
    } else { //this will pass for parent
        // Parent process
        printf("👨 Parent: Waiting for child process %d...\n", pid);
        wait(NULL);  // Wait for child to finish
        printf("👨 Parent: Child process finished. Counting fruits...\n");
        count_fruits();
    }

    return 0;
}
