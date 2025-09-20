#include <stdio.h>

int n, time_quantum;
int at[10], bt[10];

void RR();
void SRTF();

int main() {
    int choice;

    printf("Enter Total Processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
    }

    while (1) {
        printf("\nScheduling Algorithms:\n1) Round Robin\n2) Shortest Remaining Time First (SRTF)\n3) Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: RR(); break;
            case 2: SRTF(); break;
            case 3: return 0;
            default: printf("Invalid choice. Try again!\n");
        }
    }

    return 0;
}

// Round Robin Implementation
void RR() {
    int rt[10], wt = 0, tat = 0;
    int time = 0, remain = n;
    int flag = 0;

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    printf("Enter Time Quantum: ");
    scanf("%d", &time_quantum);

    printf("\nProcess\t| Turnaround Time | Waiting Time\n");

    int completed[10] = {0}; // Track completed processes

    while (remain > 0) {
        flag = 0;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                if (rt[i] <= time_quantum) {
                    time += rt[i];
                    rt[i] = 0;
                    flag = 1;

                    int turnaround = time - at[i];
                    int waiting = turnaround - bt[i];

                    if (waiting < 0) waiting = 0;

                    printf("P[%d]   \t|\t%d\t|\t%d\n", i + 1, turnaround, waiting);

                    wt += waiting;
                    tat += turnaround;
                    remain--;
                } else {
                    rt[i] -= time_quantum;
                    time += time_quantum;
                    flag = 1;
                }
            }
        }

        if (!flag) {
            time++; // If no process is ready, advance time
        }
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)tat / n);
}

// Shortest Remaining Time First (Preemptive)
void SRTF() {
    int rt[10], wt = 0, tat = 0;
    int time = 0, remain = 0, endTime;
    int smallest;

    for (int i = 0; i < n; i++)
        rt[i] = bt[i];

    printf("\nProcess\t| Turnaround Time | Waiting Time\n");

    rt[9] = 9999; // sentinel

    while (remain != n) {
        smallest = 9;

        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0) {
                smallest = i;
            }
        }

        rt[smallest]--;
        time++;

        if (rt[smallest] == 0) {
            remain++;
            endTime = time;

            int turnaround = endTime - at[smallest];
            int waiting = turnaround - bt[smallest];

            if (waiting < 0) waiting = 0;

            printf("P[%d]   \t|\t%d\t|\t%d\n", smallest + 1, turnaround, waiting);

            wt += waiting;
            tat += turnaround;
        }
    }

    printf("\nAverage Waiting Time = %.2f\n", (float)wt / n);
    printf("Average Turnaround Time = %.2f\n", (float)tat / n);
}
