#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void asc(int arr[], int n) {
  int i, j, temp;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (arr[i] > arr[j]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  printf("Ascending order arrangement: ");
  for (i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

void desc(int arr[], int n) {
  int i, j, temp;
  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      if (arr[i] < arr[j]) {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  printf("Descending order arrangement: ");
  for (i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main() {
  int n, i;
  pid_t pid;

  printf("Enter number of elements: ");
  scanf("%d", &n);
  int arr[n];
  printf("Enter array elements: ");
  for (i = 0; i < n; i++) {
    printf("\na[%d] : ", i);
    scanf("%d", &arr[i]);
  }
  printf("\n");

  pid = fork();
  if (pid < 0) {
    perror("Fork error\n");
  } else if (pid == 0) {
    printf("Child process ID: %ld\n", (long)getpid());
  } else {
    printf("Parent process ID: %ld\n", (long)getpid());
  }

  switch (pid) {
    case -1:
      printf("\nFork error\n");
      exit(-1);
    case 0:
      printf("\nChild process\n");
      asc(arr, n);
      exit(pid);
    default:
      printf("\nParent executes\n");
      desc(arr, n);
      system("ps -elf");
      exit(pid);
  }

  return 0;
}
