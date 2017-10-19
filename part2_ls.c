//Part 2 by Sunny Mei, Time
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {

	int child; //Holds info for fork status
	child = fork();
	pid_t pid;//for parent 
	if (child == 0)//enter child fork
		{	
			printf("\nYes father, my ID is %d. The files in this dir are...\n",getpid());
			char *args[5];//creates the array to hold the list of commands to use
			args[0] = "ls";//holds the command 
			args[1] = "-l";//to list things horizontally
			args[2] = "-S";//Sort by size
			args[3] = "-a";//shows hidden files, starts with .
			args[4] = NULL;//null needed as last arg
			execvp("ls", args);//does the command
			printf("I have failed you father.");//error message
			return 0;
		}	
	else//parent process
		{	int status;
			printf("\nI am your Father, Please tell me all the files and info in this dir. \nMy ID is %d\n",getpid());
			pid = waitpid(child, &status,0);
			printf("Thank you my %dth son.\n",pid);
		}
	return 0;
} 
