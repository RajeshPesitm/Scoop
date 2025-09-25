// reader.c (unchanged)
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BASE_PRICE 100000
#define FIFO_NAME "goldrate"
#define BUFFER_SIZE 64

int main() {
    int fd = open(FIFO_NAME, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open FIFO for reading");
        exit(1);
    }

    FILE *fp = fdopen(fd, "r");
    char buffer[BUFFER_SIZE];
    int price;
    int count = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        price = atoi(buffer);
        int difference = price - BASE_PRICE;

        if (difference > 0) {
            printf("📈 Reader: ₹%d → Profit ₹%d\n", price, difference);
        } else if (difference < 0) {
            printf("📉 Reader: ₹%d → Loss ₹%d\n", price, -difference);
        } else {
            printf("➖ Reader: ₹%d → No Profit, No Loss\n", price);
        }

        count++;
    }

    fclose(fp);
    printf("✅ Reader: Done. Received %d updates.\n", count);
    return 0;
}
