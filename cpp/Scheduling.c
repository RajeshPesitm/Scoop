#include<stdio.h>

  int endTime,i,smallest;
  int count,j,n,time,remain,flag=0,time_quantum;
  int wait_time=0,turnaround_time=0,at[10],bt[10],rt[10];

void RR();
void SRTF();

int main()
{
  int choice;

  printf("Enter Total Process:\t ");
  scanf("%d",&n);
  remain=n;
  for(count=0;count<n;count++)
  {
    printf("Enter Arrival Time and Burst Time for Process Process Number %d :",count+1);
    scanf("%d",&at[count]);
    scanf("%d",&bt[count]);
    rt[count]=bt[count];
  }
  tryagain:
  printf("Scheduling Alogrithms:\n\n1) Round Robin 2) Shortest Remaining Time First(SRTF) 3) Exit\n");
  scanf("%d",&choice);
  switch(choice)
  {
	  case 1:RR();
			 break;
	  case 2:SRTF();
			 break;
	  case 3:return 0;
	  default:printf("wrong choice Try again!!!");
	          goto tryagain;
  }
}

 void RR()
{
    wait_time = 0;
    turnaround_time = 0;
    printf("Enter Time Quantum:\t");
    scanf("%d", &time_quantum);
    printf("\n\nProcess\t|Turnaround Time|Waiting Time\n\n");

    time = 0;
    count = 0;
    remain = n;
    
    while(remain != 0)
    {
        if(rt[count] > 0 && at[count] <= time)
        {
            if(rt[count] <= time_quantum)
            {
                time += rt[count];
                rt[count] = 0;
                remain--;
                printf("P[%d]\t|\t%d\t|\t%d\n", count+1, time - at[count], time - at[count] - bt[count]);
                wait_time += time - at[count] - bt[count];
                turnaround_time += time - at[count];
            }
            else
            {
                rt[count] -= time_quantum;
                time += time_quantum;
            }
        }

        // Find next process which is arrived and not completed
        int next = (count + 1) % n;
        int found = 0;
        for(int i=0; i<n; i++)
        {
            if(rt[next] > 0 && at[next] <= time)
            {
                found = 1;
                break;
            }
            next = (next + 1) % n;
        }

        if(found)
            count = next;
        else
            time++; // No process ready, increase time to simulate idle CPU
    }
    printf("\nAverage Waiting Time= %f\n", wait_time*1.0/n);
    printf("Avg Turnaround Time = %f\n", turnaround_time*1.0/n);
}


void SRTF()
{
    int complete = 0, time = 0;
    int min_index;
    int min_remaining;
    int flag;
    int endTime;

    wait_time = 0;
    turnaround_time = 0;

    int remaining_time[10];
    for(int i = 0; i < n; i++)
        remaining_time[i] = rt[i]; // copy burst times (or remaining times)

    printf("\n\nProcess\t|Turnaround Time| Waiting Time\n\n");

    while(complete != n)
    {
        min_remaining = 1e9;  // large number to find min
        min_index = -1;
        flag = 0;

        for(int i = 0; i < n; i++)
        {
            if(at[i] <= time && remaining_time[i] > 0 && remaining_time[i] < min_remaining)
            {
                min_remaining = remaining_time[i];
                min_index = i;
                flag = 1;
            }
        }

        if(flag == 0)
        {
            // No process is ready to execute at this time; CPU idle
            time++;
            continue;
        }

        // Execute the process for 1 unit
        remaining_time[min_index]--;

        // If process is finished
        if(remaining_time[min_index] == 0)
        {
            complete++;
            endTime = time + 1;
            int turnaround = endTime - at[min_index];
            int waiting = turnaround - bt[min_index];

            printf("P[%d]\t|\t%d\t|\t%d\n", min_index + 1, turnaround, waiting);

            wait_time += waiting;
            turnaround_time += turnaround;
        }
        time++;
    }

    printf("\nAverage waiting time = %f\n", (float)wait_time / n);
    printf("Average turnaround time = %f\n", (float)turnaround_time / n);
}
