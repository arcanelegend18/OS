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

void calculateRoundRobin(struct Process proc[], int n, int quantum) {
    int i;
    int currentTime = 0;
    int completed = 0;
    float totalWaitingTime = 0, totalTurnAroundTime = 0;
    int queue[n], front = 0, rear = 0;

    for (i = 0; i < n; i++) {
        queue[rear++] = i; 
    }

    while (completed != n) {
        int idx = queue[front++];
        if (front == n) front = 0; 

        if (proc[idx].remainingTime > quantum) {
            proc[idx].remainingTime -= quantum;
            currentTime += quantum;
        } else {
            currentTime += proc[idx].remainingTime;
            proc[idx].remainingTime = 0;
            completed++;
            
            proc[idx].waitingTime = currentTime - proc[idx].arrivalTime - proc[idx].burstTime;
            proc[idx].turnAroundTime = currentTime - proc[idx].arrivalTime;

            totalWaitingTime += proc[idx].waitingTime;
            totalTurnAroundTime += proc[idx].turnAroundTime;
        }

        for (i = 0; i < n; i++) {
            if (proc[i].arrivalTime <= currentTime && proc[i].remainingTime > 0 && !isInQueue(queue, front, rear, i)) {
                queue[rear++] = i;
                if (rear == n) rear = 0; 
            }
        }

        if (proc[idx].remainingTime > 0) {
            queue[rear++] = idx;
            if (rear == n) rear = 0; 
        }
    }

    printf("PID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].pid, proc[i].arrivalTime, proc[i].burstTime, proc[i].waitingTime, proc[i].turnAroundTime);
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnAroundTime / n);
}

int isInQueue(int queue[], int front, int rear, int pid) {
    for (int i = front; i != rear; i = (i + 1) % rear) {
        if (queue[i] == pid) return 1;
    }
    return 0;
}

int main() {
    int n;
    int quantum;
    int i;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

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
    calculateRoundRobin(proc, n, quantum);

    return 0;
}


