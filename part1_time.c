//Part 1 by Sunny Mei, Time
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
int main() {

	int child; //Holds info for fork status
	child = fork();
	pid_t pid;//for parent 
	if (child == 0)//enter child fork
		{
			time_t current_time;//generate dummy time data
			char* time;//will hold dummy time
			time = ctime(&current_time);
			printf("\nYes father, my ID is %d, and the current time is...\n",getpid());	
			execl("/bin/date", "date", 0, (char*) NULL);//First arg is the file path name, 2nd is arg 0 which holds the info.
			//These info will be passed into another c file as args, Null is required at the end
			printf("\nSorry daddy %d, I lost my watch\n But mom said the time is \n %s",getppid(),time);
			//child will print the above out in case any errors.
			return 0;
		}	
	else//parent process
		{	int status;
			printf("\nI am your father, please tell me the time. My ID is %d\n", getpid());
			pid = waitpid(child, &status,0);
			printf("\nThank you my %dth son\n",pid);
		}
	return 0;
} 
