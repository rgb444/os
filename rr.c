#include <stdio.h>

struct Process {
    int pid;
    int burstTime;
    int remainingTime;
    int arrivalTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
};

void roundRobin(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0, completed = 0;

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].remainingTime <= timeQuantum) {
                    currentTime += processes[i].remainingTime;
                    processes[i].remainingTime = 0;
                    processes[i].completionTime = currentTime;
                    processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
                    processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                    completed++;
                } else {
                    currentTime += timeQuantum;
                    processes[i].remainingTime -= timeQuantum;
                }
            }
        }
    }
}

void displayProcesses(struct Process processes[], int n) {
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrivalTime, processes[i].burstTime, processes[i].waitingTime, processes[i].turnaroundTime);
        totalWaitingTime += processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter the time quantum: ");
    scanf("%d", &timeQuantum);

    for (int i = 0; i < n; i++) {
        printf("Enter process %d details:\n", i + 1);
        printf("  Arrival time: ");
        scanf("%d", &processes[i].arrivalTime);
        printf("  Burst time: ");
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i + 1;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].turnaroundTime = 0;
    }

    roundRobin(processes, n, timeQuantum);
    displayProcesses(processes, n);

    return 0;
}
