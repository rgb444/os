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

// LRU Page Replacement Algorithm
void lruPageReplacement(int pages[], int n)
{
    int frames[MAX_FRAMES] = {-1, -1, -1};
    int recent[MAX_FRAMES] = {0, 0, 0};
    int pageFaults = 0, time = 0;

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++)
    {
        int page = pages[i];
        int pos = findPageInFrames(frames, MAX_FRAMES, page);

        if (pos == -1)
        {
            int lruIndex = 0;
            for (int j = 1; j < MAX_FRAMES; j++)
            {
                if (recent[j] < recent[lruIndex])
                {
                    lruIndex = j;
                }
            }
            frames[lruIndex] = page;
            recent[lruIndex] = ++time;
            pageFaults++;
            printf("Page %d caused a page fault. Frames: ", page);
        }
        else
        {
            recent[pos] = ++time;
            printf("Page %d already in frames. Frames: ", page);
        }

        printFrames(frames, MAX_FRAMES);
    }

    printf("Total Page Faults (LRU): %d\n", pageFaults);
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

    lruPageReplacement(pages, n);

    return 0;
}
