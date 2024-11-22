//Process P1
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
	char s1[300],s2[300];
	int num,fd1,fd2,byt;
	//printf("producer");
	mknod(FIFO_NAME1,S_IFIFO | 0666,0);
	mknod(FIFO_NAME2,S_IFIFO | 0666,0);
	printf("waiting for consumer ...\n");
	fd1 = open(FIFO_NAME1,O_WRONLY);
	fd2 = open(FIFO_NAME2,O_RDONLY);
	printf("got a consumer -- type some stuff\n");
	gets(s1);
	if((num = write(fd1,s1,strlen(s1)))==-1)
		perror("write");
	else
	{
		printf("speak:wrote %d bytes to file1\n",num);

		byt=read(fd2,s2,300);
		s2[byt]='\0';
		printf("%s\n",s2);
	}
	close(fd1);
	close(fd2);
	return 0;
}

//Process P2
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
	char s[300],vowel[20],send[200];
	int num,fd1,fd2,sig,k=0,i,wordcnt=1,charcnt=0,linecnt=0;
	FILE *fp;
	fp=fopen("fifo.txt","w");
	mknod(FIFO_NAME1,S_IFIFO | 0666,0);
	mknod(FIFO_NAME2,S_IFIFO | 0666,0);
	printf("waiting for producers...\n");
	fd1=open(FIFO_NAME1,O_RDONLY);
	fd2=open(FIFO_NAME2,O_WRONLY);
	printf("Got a producer");

	if((num=read(fd1,s,300))==-1)
		perror("read");
	else {
		s[num]='\0';
		printf("tick:read %d bytes : \"%s\"\n",num,s);
		k=0;
		vowel[0]='\0';
		wordcnt=1;
		for(int i=0;i<num;i++)
		{
			if((s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'))
			{
				vowel[k]=s[i];
				k++;
			}
			if(s[i] == ' '  && s[i+1] != ' '){
				wordcnt++;
			}
			if(s[i]=='.'&&(s[i+1]==' '||s[i+1]=='\0')){
				linecnt++;
			}
			else if(s[i]!='.'&&s[i]!=' ')
			charcnt++;
		}
		vowel[k]='\0';
		sprintf(send,"for the given sentence the word count is %d \n vowelcount is %d \n char count is %d \n lines are %d \n ",wordcnt,k,charcnt,linecnt);
		fprintf(fp,"%s",send);

		//strcat(send,vowel);
		if(sig==write
				(fd2,send,strlen(send))!=-1)
				printf("\n written successfully to file 2");
		else
		printf("\n error in writing to file2");
	}

	close(fd1);
	close(fd2);
	fclose(fp);
	return 0;
}

//cc file.c
//./a.out
// Explanation =>
// This code demonstrates Inter-Process Communication (IPC) between two processes using named pipes (FIFOs). There are two processes, Producer (P1) and Consumer (P2), communicating via two named pipes (comm_pipe1 and comm_pipe2). The producer sends a string to the consumer, and the consumer processes it by counting words, vowels, characters, and lines, then sends the results back to the producer.

// Process 1 (Producer - P1):
// FIFO Creation:
// The producer creates two named pipes (comm_pipe1 and comm_pipe2) using mknod.
// Write to FIFO1:
// The producer waits for the consumer to be ready. Once the consumer is connected, the producer reads a string from the user using gets().
// The string is written to the named pipe comm_pipe1 using write().
// Read from FIFO2:
// The producer then waits for the consumer's response from comm_pipe2. After receiving the response, it prints the message from the consumer.
// Close FDs:
// Finally, the producer closes the file descriptors (fd1 and fd2).
// Process 2 (Consumer - P2):
// FIFO Creation:
// Similar to the producer, the consumer creates the same named pipes (comm_pipe1 and comm_pipe2).
// Read from FIFO1:
// The consumer waits for the producer to send a string through comm_pipe1. It reads this string and processes it.
// String Processing:
// The consumer counts:
// Words: The number of words in the string.
// Vowels: The vowels in the string (a, e, i, o, u).
// Characters: Non-space characters.
// Lines: The number of lines based on periods ('.').
// Write to FIFO2:
// The processed information (word count, vowel count, character count, and line count) is formatted and written to comm_pipe2, which the producer reads.
// Additionally, the consumer logs this information into a file (fifo.txt).
// Close FDs:
// The consumer closes the file descriptors and the file itself (fp).
// Key Functions:
// mknod():
// Creates named pipes (FIFOs) with read and write permissions.
// open():
// Opens the named pipes for reading and writing.
// write() and read():
// Used for communication between the producer and consumer through the pipes.
// sprintf():
// Formats the result string before writing it to the pipe.
// Compilation and Execution:
// Compilation: cc file.c
// Execution: ./a.out
// This will run the producer-consumer communication process.
// Explanation of the Output:
// Producer: Waits for user input, sends it to the consumer, and then receives the processed result.
// Consumer: Processes the input, counts the words, vowels, characters, and lines, and sends the results back to the producer. It also logs the information to a file.
// Issues in Code:
// Use of gets(): gets() is unsafe because it doesn't prevent buffer overflow. It's recommended to use fgets() instead.
// sig variable: The sig variable is not initialized or used properly, and it seems like an incomplete condition for writing to fd2. The condition if(sig==write(fd2,send,strlen(send))!=-1) is incorrect and should be fixed.
// File Descriptors: mknod() is used to create named pipes, but it would be better to use mkfifo() which is more portable and recommended for FIFO creation in modern systems.
// This code demonstrates a basic interaction between two processes using named pipes, where the producer sends data, and the consumer processes and returns the result.






