#include <stdio.h>

struct process {
    int name;
    int arrival;
    int burst;
    int tat;
    int waiting;
} arr;

int main() {
    int n;
    float avgtt = 0;
    float avgwait = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process arr[n];

    for (int i = 0; i < n; i++) {
        printf("Enter process number: ");
        scanf("%d", &arr[i].name);
        printf("Enter arrival time: ");
        scanf("%d", &arr[i].arrival);
        printf("Enter burst time: ");
        scanf("%d", &arr[i].burst);
    }

    printf("Process\t Arrival\t Burst\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t  %d\t   %d\n", arr[i].name, arr[i].arrival, arr[i].burst);
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            struct process temp;
            if (arr[i].arrival > arr[j].arrival) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    printf("Processes sorted in ascending order of arrival time:\n");
    printf("Process\t Arrival\t Burst\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t  %d\t   %d\n", arr[i].name, arr[i].arrival, arr[i].burst);
    }

    arr[0].tat = arr[0].arrival + arr[0].burst;
    for (int i = 1; i < n; i++) {
        if (arr[i - 1].tat >= arr[i].arrival) {
            arr[i].tat = arr[i - 1].tat + arr[i].burst;
        } else {
            arr[i].tat = arr[i].arrival + arr[i].burst;
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i].tat = arr[i].tat - arr[i].arrival;
        arr[i].waiting = arr[i].tat - arr[i].burst;
        avgtt += arr[i].tat;
        avgwait += arr[i].waiting;
    }

    avgtt = avgtt / n;
    avgwait = avgwait / n;

    printf("Process\t Arrival\t Burst\t Turnaround Time\t Waiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t  %d\t  %d\t  %d\t  %d\n", arr[i].name, arr[i].arrival, arr[i].burst, arr[i].tat, arr[i].waiting);
    }

    printf("Average Turnaround Time: %f\n", avgtt);
    printf("Average Waiting Time: %f\n", avgwait);

    return 0;
}
