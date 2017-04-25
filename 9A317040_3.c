#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> 
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>		 
#include <sys/wait.h>		
#define input 10

int fd;

void init_shmem()
{
	char *ptr;

	fd = shm_open("shmem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd == -1)
		printf("can't open shared memory area\n");
	
	if(ftruncate(fd,sizeof(char)*100) == -1)
		printf("can't limit size of the shared memory area\n");


}

void do_something_child()
{
	int n = input;
	char output[100],*ptr;

	/* Block "Collatz conjecture" begin */	
	do{
		char temp[10];

		if(n%2)
			n=3*n+1;
		else
			n=n/2;	
	
		sprintf(temp,"%d ",n);	// Convert a integer into a string
		strcat(output,temp);	// Concatenate ouput(another string) with the string 
	}while(n>1);
	/* Block "Collatz conjecture" end */

	printf("The result of child process: %s\n",output);		// Test whether output is correct


	fd = shm_open("shmem", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	
	if(fd == -1)
		printf("can't open shared memory area\n");
	
	//if(ftruncate(fd,sizeof(char)*100) == -1)
	//	printf("can't limit size of the shared memory area\n");
	

	ptr=mmap(NULL,sizeof(char)*100,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	
	if(ptr == MAP_FAILED)
		printf("can't map the shared memory area into child process's address area\n");	

	sprintf(ptr,"%s",output);	// write output into shared memory area
	shm_unlink("shmem");
}

void do_something_parent()
{

	char *ptr;

	ptr=mmap(NULL,sizeof(char)*100,PROT_READ | PROT_WRITE, MAP_SHARED,fd,0);
	
	if(ptr == MAP_FAILED)
		printf("can't map the shared memory area into child process's address area\n");	

	printf("The result in parent process: %s\n",ptr);
	
}


int main()
{

	pid_t child;

	init_shmem();	
	switch(fork())
	{
		case -1:		// if the system can't create child, then it doesn't need to continute
			printf("can't create any child\n");
			return 0;
		break;
	
		case 0:			// child process
			printf("The child is ready to be run\n");
			do_something_child();
			printf("The child has been done\n");	
		break;  
	
		default: 		// parent process
			printf("The parent is ready to be run and waits\n");
			wait(NULL); 	// waits until the child has been done	
			do_something_parent();
			shm_unlink("shmem");
			printf("The shared memory area has been removed\n");
			printf("The parent has been done\n");
		break;

	}


	return 0;
}
