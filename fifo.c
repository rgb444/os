#include <stdio.h>
#define MAX_FRAMES 3
#define MAX_PAGES 20

int findPageInFrames(int frames[], int n, int page)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] == page)
        {
            return i;
        }
    }
    return -1;
}

void printFrames(int frames[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

void fcfsPageReplacement(int pages[], int n)
{
    int frames[MAX_FRAMES] = {-1, -1, -1};
    int pageFaults = 0, index = 0;

    printf("\nFCFS Page Replacement:\n");
    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        if (findPageInFrames(frames, MAX_FRAMES, page) == -1)
        {
            frames[index] = page;
            index = (index + 1) % MAX_FRAMES;
            pageFaults++;
            printf("Page %d caused a page fault. Frames: ", page);
        }
        else
        {
            printf("Page %d already in frames. Frames: ", page);
        }
        printFrames(frames, MAX_FRAMES);
    }
    printf("Total Page Faults (FCFS): %d\n", pageFaults);
}

int main()
{
    int pages[MAX_PAGES], n;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    fcfsPageReplacement(pages, n);

    return 0;
}
