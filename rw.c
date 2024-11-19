#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdint.h>
#include<unistd.h>

#define R 5
#define W 5
int readcount;
int writecount;

sem_t y,z;
pthread_mutex_t x;
sem_t wsem,rsem;
int s=5;
void *reader1(void *a);
void *writer1(void *a);
//void *reader2(void *a);
//void *writer2(void *a);
int main()
{
	int i,op;
	pthread_t thread_read[R],thread_write[W];
	pthread_mutex_init(&x,NULL);

	sem_init(&wsem,0,1);
	sem_init(&y,0,1);
	sem_init(&rsem,0,1);
	sem_init(&z,0,1);

	do{
		printf("Menu: 1.Readers have priority 2:exit");
		scanf("%d",&op);
		if(op==1)
		{ 
			readcount = 0;
				for(i=0;i<W;i++)
				{
					pthread_create(&thread_write[i],NULL,*writer1,(void *) (intptr_t) i);
				}
				for(i=0;i<R;i++)
				{
					pthread_create(&thread_read[i],NULL,*reader1,(void *) (intptr_t) i);
				}
				for(i=0;i<W;i++)
				{
					pthread_join(thread_write[i],NULL);
				}
				for(i=0;i<R;i++)
				{
					pthread_join(thread_read[i],NULL);
				}
		}
		else
		{
			break;
		}
	}while(op!=2);
}
void *reader1(void *a)
{
	int r = (intptr_t) a;
	int i=0;
	while(i<5){
		pthread_mutex_lock(&x);
		readcount++;
		if(readcount == 1)
			sem_wait(&wsem);
		pthread_mutex_unlock(&x);
		printf("\t\t Reader %d is reading : %d \n",r,s);
		pthread_mutex_lock(&x);
		readcount--;
		if(readcount==0)
			sem_post(&wsem);
		pthread_mutex_unlock(&x);
		sleep(rand() % 10);
		i++;
	}
}

void *writer1(void *a){
	int w = (intptr_t) a;
	int i=0;
	while(i<2){
		sem_wait(&wsem);
		s+=5;
		printf("Writer %d is writing : %d \n",w,s);
		sem_post(&wsem);
		sleep(rand() % 10);
		i++;
	}
}
