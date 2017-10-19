//Process 1 by Sunny Mei
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int main (int argc,char *argv[])
{
	int createfile1;//Will handle the file we need to create
	int createfile2;	
	int checkdes1;//Will check if file existence for des1
	int checkdes2;//Will check for des2
	// Check file existence
	checkdes1 = access ("destination1.txt", F_OK);
	checkdes2 = access ("destination2.txt", F_OK);

	if (checkdes1 == 0)
		printf ("\n destination1.txt exists, no need to make a new one\n");
	else
	{
		createfile1 = open("destination1.txt", O_RDWR | O_CREAT,S_IRWXU);//S_IRWXU mode for read write execute
		//File not found, will make a new file. Enables read and write
		printf ("\n destination1.txt does not exists, need to make one\n");
		close(createfile1);
	}


	if (checkdes2 == 0)
		printf ("\n destination2.txt exists, no need to make a new one\n");
	else
	{
		createfile2 = open("destination2.txt", O_RDWR | O_CREAT,S_IRWXU);
		//File not found, will make a new file. Enables read and write
		printf ("\n destination2.txt does not exists, need to make one\n");
		close(createfile2);
	}
	system("ls -l");
	return 0;
}

