#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

#define FIFO_NAME1 "comm_pipe1"
#define FIFO_NAME2 "comm_pipe2"

int main()
{
    char s1[300], s2[300], s[300], vowel[20], send[200];
    int num, fd1, fd2, byt, k = 0, wordcnt = 1, charcnt = 0, linecnt = 0;
    FILE *fp;
    
    mknod(FIFO_NAME1, S_IFIFO | 0666, 0);
    mknod(FIFO_NAME2, S_IFIFO | 0666, 0);
    
    printf("Waiting for consumer...\n");
    fd1 = open(FIFO_NAME1, O_WRONLY);
    fd2 = open(FIFO_NAME2, O_RDONLY);
    printf("Got a consumer -- type some stuff\n");
    gets(s1);  // Getting input from producer
    
    if ((num = write(fd1, s1, strlen(s1))) == -1)
        perror("write");
    else
    {
        printf("Producer: wrote %d bytes to file1\n", num);
        byt = read(fd2, s2, 300);  // Consumer reads
        s2[byt] = '\0';
        printf("Consumer: %s\n", s2);
    }

    close(fd1);
    close(fd2);

    // Now process the sentence for word, vowel, char, line counts
    fp = fopen("fifo.txt", "w");
    fd1 = open(FIFO_NAME1, O_RDONLY);
    fd2 = open(FIFO_NAME2, O_WRONLY);
    printf("Waiting for producer...\n");

    if ((num = read(fd1, s, 300)) == -1)
        perror("read");
    else
    {
        s[num] = '\0';
        printf("Consumer: read %d bytes: \"%s\"\n", num, s);
        k = 0;
        vowel[0] = '\0';
        wordcnt = 1;
        for (int i = 0; i < num; i++)
        {
            if ((s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u'))
            {
                vowel[k] = s[i];
                k++;
            }
            if (s[i] == ' ' && s[i + 1] != ' ')
            {
                wordcnt++;
            }
            if (s[i] == '.' && (s[i + 1] == ' ' || s[i + 1] == '\0'))
            {
                linecnt++;
            }
            else if (s[i] != '.' && s[i] != ' ')
                charcnt++;
        }
        vowel[k] = '\0';
        sprintf(send, "For the given sentence the word count is %d \nVowel count is %d \nCharacter count is %d \nLines are %d\n", wordcnt, k, charcnt, linecnt);
        fprintf(fp, "%s", send);

        if (write(fd2, send, strlen(send)) != -1)
            printf("\nWritten successfully to file2\n");
        else
            printf("\nError in writing to file2\n");
    }

    close(fd1);
    close(fd2);
    fclose(fp);
    
    return 0;
}
