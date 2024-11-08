#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime; 
    int waitingTime;
    int turnAroundTime;
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

void calculatePreemptiveSJF(struct Process proc[], int n) {
    int i;
    int completed = 0, currentTime = 0, minIndex = -1;
    int minRemainingTime = 2147483647; 
    float totalWaitingTime = 0, totalTurnAroundTime = 0;
    int isProcessSelected = 0;

    while (completed != n) {
        for (i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && proc[i].remainingTime < minRemainingTime) {
                minRemainingTime = proc[i].remainingTime;
                minIndex = i;
                isProcessSelected = 1;
            }
        }

        if (isProcessSelected == 0) {
            currentTime++;
            continue;
        }

        proc[minIndex].remainingTime--;
        minRemainingTime = proc[minIndex].remainingTime;

        if (proc[minIndex].remainingTime == 0) {
            completed++;
            isProcessSelected = 0;
            minRemainingTime = 2147483647;
            
            proc[minIndex].turnAroundTime = currentTime + 1 - proc[minIndex].arrivalTime;
            proc[minIndex].waitingTime = proc[minIndex].turnAroundTime - proc[minIndex].burstTime;

            totalWaitingTime += proc[minIndex].waitingTime;
            totalTurnAroundTime += proc[minIndex].turnAroundTime;
        }

        currentTime++;
    }

    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnAroundTime);
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

int main() {
    int n;
    int i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &proc[i].arrivalTime, &proc[i].burstTime);
        proc[i].remainingTime = proc[i].burstTime; 
        proc[i].waitingTime = 0;
        proc[i].turnAroundTime = 0;
    }

    sortByArrivalTime(proc, n);
    calculatePreemptiveSJF(proc, n);

    return 0;
}


