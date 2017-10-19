//Part 3 by Sunny Mei
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc,char *argv[]) {

	int child1,child2; //Holds info for fork status
	child1 = fork();//fork first child
	pid_t pid;//for parent
	char *args1[2];
	args1[0] = "Prcs_P1";
	args1[1] = NULL;
	char *args2[2];
	args2[0] = "Prcs_P2";
	args2[1] = NULL;
	if (child1 == 0)//enter child1 fork
		{	printf("\nYes father. My ID is %d\n", getpid());
			execv("./Prcs_P1.exe",args1);//executes process 1
				
		}	
	else//parent process
		{	int status;
			printf("\nI am your father. Please do P1 My ID is %d\n", getpid());
			pid = waitpid(child1, &status,0);
			
		}
	child2 = fork();//Forks after the above finishes
	if (child2 == 0)//enter child 2 fork
	{
	printf("\nYes father. My ID is %d\n", getpid());	
	execv("./Prcs_P2.exe",args2);
	}
	else//parent 2
	{
	int status1;
	printf("\nI am your father. Please do p2. My ID is %d\n", getpid());
	pid = waitpid(child2, &status1,0);			
	}
	return 0;
} 
