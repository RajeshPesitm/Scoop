// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define BASE_PRICE 100000
#define MIN_DEVIATION 500
#define MAX_DEVIATION 1000
#define ITERATIONS 20
#define FIFO_NAME "goldrate"

int main() {
    srand(time(NULL));
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd < 0) {
        perror("Failed to open FIFO for writing");
        exit(1);
    }

    int currentPrice = BASE_PRICE;

    for (int i = 0; i < ITERATIONS; i++) {
        int deviation = (rand() % (MAX_DEVIATION - MIN_DEVIATION + 1)) + MIN_DEVIATION;
        int direction = rand() % 2 == 0 ? 1 : -1;  // +1 or -1
        currentPrice += direction * deviation;

        // Optional: Prevent price going below ₹1 (just sanity)
        if (currentPrice < 1) currentPrice = 1;

        dprintf(fd, "%d\n", currentPrice);
        printf("💰 Writer: New gold rate → ₹%d (%s₹%d)\n", currentPrice,
               direction > 0 ? "+" : "-", deviation);

        sleep(1);
    }

    close(fd);
    printf("✅ Writer: Finished sending gold rates.\n");
    return 0;
}
