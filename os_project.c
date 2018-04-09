#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
pthread_mutex_t l1;
static int c;
void *game()
{
	pthread_mutex_lock(&l1);
	printf("3 players are playing the game in the server and game no is :%d\n",++c);
	pthread_mutex_unlock(&l1);
}
int main()
{
	int *max,*alloc,*need;
	int nop,np,i,avail=3;
    printf("enter the number of players");
    scanf("%d",&np);
    nop=np/3;
    printf("game consists of %d processes\n",nop);
    max=(int *) malloc(nop*sizeof(int));
	alloc=(int *) malloc(nop*sizeof(int));
	need=(int *) malloc(nop*sizeof(int)); 
	 for(i=0;i<nop;i++)
    {
    	*(max+i)=3;
    	*(alloc+i)=0;
    	*(need+i)=*(max+i)-*(alloc+i);
	}
	
	int count=0;
	printf("available process are 3\n");
	printf("process no\tallocated\tmax\t\tneed\n");
	for(i=0;i<nop;i++)
    {
    	count++;
       printf("%2d\t\t%4d\t\t%2d\t\t%2d\n",count,*(alloc+i),*(max+i),*(need+i));
	
	}
    for(i=0;i<nop;i++)
    {
    pthread_t t1;
	pthread_create(&t1,NULL,*game,NULL);
     if((*(need+i)-avail)==0)
    	{
    	pthread_join(t1,NULL);	
		}
	}
	if((np%3)!=0)
	printf("one process can't execute as it have insufficient player of number %d\n",(np%3));
}
