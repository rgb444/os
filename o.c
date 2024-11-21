#include <stdio.h>
#define MAX_FRAMES 10
#define MAX_PAGES 30

int findPageToReplace(int frames[], int num_frames, int pages[], int current_index, int num_pages)
{
    int farthest_index = -1, pos_to_replace = -1;

    for (int i = 0; i < num_frames; i++)
    {
        int found = 0;

        for (int j = current_index + 1; j < num_pages; j++)
        {
            if (frames[i] == pages[j])
            {
                found = 1;
                if (j > farthest_index)
                {
                    farthest_index = j;
                    pos_to_replace = i;
                }
                break;
            }
        }

        if (!found)
        {
            return i;
        }
    }

    return (pos_to_replace == -1) ? 0 : pos_to_replace;
}

void printFrames(int frames[], int num_frames)
{
    for (int i = 0; i < num_frames; i++)
    {
        if (frames[i] != -1)
            printf("%d ", frames[i]);
        else
            printf("- ");
    }
    printf("\n");
}

void optimalPageReplacement(int pages[], int num_pages, int num_frames)
{
    int frames[MAX_FRAMES];
    int faults = 0, hits = 0;

    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = -1;
    }

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < num_pages; i++)
    {
        int page = pages[i];
        int flag_hit = 0;

        for (int j = 0; j < num_frames; j++)
        {
            if (frames[j] == page)
            {
                hits++;
                flag_hit = 1;
                break;
            }
        }

        if (!flag_hit)
        {
            faults++;
            int replace_index = findPageToReplace(frames, num_frames, pages, i, num_pages);
            frames[replace_index] = page;
            printf("Page %d caused a page fault. Frames: ", page);
        }
        else
        {
            printf("Page %d already in frames. Frames: ", page);
        }

        printFrames(frames, num_frames);
    }

    printf("Total Page Faults (Optimal): %d\n", faults);
    printf("Total Page Hits (Optimal): %d\n", hits);
}

int main()
{
    int pages[MAX_PAGES], num_pages, num_frames;

    printf("Enter the number of frames: ");
    scanf("%d", &num_frames);

    printf("Enter the number of pages: ");
    scanf("%d", &num_pages);

    printf("Enter the page reference sequence: ");
    for (int i = 0; i < num_pages; i++)
    {
        scanf("%d", &pages[i]);
    }

    optimalPageReplacement(pages, num_pages, num_frames);

    return 0;
}
