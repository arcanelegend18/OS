#include <stdio.h>

struct Process
{
    int id;
    int burstTime;      
    int waitingTime;    
    int turnAroundTime; 
};

void calculateWaitingTime(struct Process processes[], int n)
{
    processes[0].waitingTime = 0; 

    for (int i = 1; i < n; i++)
    {
        processes[i].waitingTime = processes[i - 1].waitingTime + processes[i - 1].burstTime;
    }
}

void calculateTurnAroundTime(struct Process processes[], int n)
{
    for (int i = 0; i < n; i++)
    {
        processes[i].turnAroundTime = processes[i].waitingTime + processes[i].burstTime;
    }
}

void sortProcessesByBurstTime(struct Process processes[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (processes[i].burstTime > processes[j].burstTime)
            {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

void displayProcesses(struct Process processes[], int n)
{
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burstTime,
               processes[i].waitingTime, processes[i].turnAroundTime);
    }
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++)
    {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burstTime);
    }

    sortProcessesByBurstTime(processes, n);

    calculateWaitingTime(processes, n);
    calculateTurnAroundTime(processes, n);

    displayProcesses(processes, n);

    float totalWaitingTime = 0, totalTurnAroundTime = 0;
    for (int i = 0; i < n; i++)
    {
        totalWaitingTime += processes[i].waitingTime;
        totalTurnAroundTime += processes[i].turnAroundTime;
    }
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);

    return 0;
}    
