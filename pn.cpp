#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int waitingTime;
    int turnAroundTime;
    int completed;
};

void sortByArrivalTime(struct Process proc[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (proc[i].arrivalTime > proc[j].arrivalTime) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

void calculateNonPreemptivePriority(struct Process proc[], int n) {
    int completed = 0, currentTime = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;

    while (completed < n) {
        int idx = -1;
        int highestPriority = 2147483647;
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && !proc[i].completed && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                idx = i;
            }
        }

        if (idx != -1) {
            proc[idx].waitingTime = currentTime - proc[idx].arrivalTime;
            proc[idx].turnAroundTime = proc[idx].waitingTime + proc[idx].burstTime;
            currentTime += proc[idx].burstTime;
            proc[idx].completed = 1;
            completed++;

            totalWaitingTime += proc[idx].waitingTime;
            totalTurnAroundTime += proc[idx].turnAroundTime;
        } else {
            currentTime++;
        }
    }

    printf("PID\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].priority, proc[i].waitingTime, proc[i].turnAroundTime);
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time, burst time and priority for process %d: ", i + 1);
        scanf("%d %d %d", &proc[i].arrivalTime, &proc[i].burstTime, &proc[i].priority);
        proc[i].completed = 0;
    }

    sortByArrivalTime(proc, n);
    calculateNonPreemptivePriority(proc, n);

    return 0;
}



