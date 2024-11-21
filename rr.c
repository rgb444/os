#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

void roundRobin(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0, completed = 0, queue[n], front = 0, rear = 0;
    int visited[n];

    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        processes[i].remainingTime = processes[i].burstTime;
    }

    queue[rear++] = 0;
    visited[0] = 1;

    while (completed < n) {
        int i = queue[front++];
        if (front == n) front = 0;

        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        if (processes[i].remainingTime > timeQuantum) {
            processes[i].remainingTime -= timeQuantum;
            currentTime += timeQuantum;
        } else {
            currentTime += processes[i].remainingTime;
            processes[i].remainingTime = 0;
            processes[i].completionTime = currentTime;
            processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
            processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
            completed++;
        }

        for (int j = 0; j < n; j++) {
            if (j != i && !visited[j] && processes[j].arrivalTime <= currentTime && processes[j].remainingTime > 0) {
                queue[rear++] = j;
                if (rear == n) rear = 0;
                visited[j] = 1;
            }
        }

        if (processes[i].remainingTime > 0) {
            queue[rear++] = i;
            if (rear == n) rear = 0;
        }
    }
}

void displayProcesses(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\n+-----+---------+-------+---------+------------+------------+\n");
    printf("| PID | Arrival | Burst | Waiting | Turnaround | Completion |\n");
    printf("+-----+---------+-------+---------+------------+------------+\n");

    for (int i = 0; i < n; i++) {
        printf("| %-3d | %-7d | %-5d | %-7d | %-10d | %-10d |\n", 
               processes[i].pid, 
               processes[i].arrivalTime, 
               processes[i].burstTime, 
               processes[i].waitingTime, 
               processes[i].turnaroundTime, 
               processes[i].completionTime);

        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("+-----+---------+-------+---------+------------+------------+\n");
    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes:");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("\nEnter details for Process %d:\n", i + 1);
        printf("Arrival Time:");
        scanf("%d", &processes[i].arrivalTime);
        printf("Burst Time:");
        scanf("%d", &processes[i].burstTime);
    }

    printf("\nEnter the Time Quantum:");
    scanf("%d", &timeQuantum);

    roundRobin(processes, n, timeQuantum);
    displayProcesses(processes, n);

    return 0;
}
