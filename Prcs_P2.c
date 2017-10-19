//Process 2 by Sunny Mei
//Using a switch statment to make things easier
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main (int argc,char *argv[])
{

	int filesize = 1292;//size of source.txt
	int incrdes1 = 100;// destination 1 will read 100 chars
	int incrdes2 = 50;//des2 will read 50 chars
	int incrlast; // will hold the amount to read for last run
	int check;// Within the special case, we either store it in des 1 or des 2. if check is = 0, des 1. if check = 1, des 2
	int amount = 100; // will hold the counter to check if we are near EOF, starts at 100
	int mod50 = filesize%incrdes2; // will determine how many char are left for the last run for reading next 50
	int mod100 = filesize%incrdes1; // will determine how many char are left for the last run for reading next 100
	int readcontents;// will hold fd of source.txt
	int opendes1; // will hold fd for des1
	int opendes2; // will hold fd for des2
	int readfile; // will hold fd for reading from source.txt
	int writetodes1; // will hold fd for writing to des1
	int writetodes2; // will hold fd for writing to des2
	char contents1[incrdes1];//holds the contents of reading from source for des1
	char contentsdes1[incrdes1];//holds the contents that will be written to des1
	char contents2[incrdes2];//holds the contents of reading from source for des2
	char contentsdes2[incrdes2];//holds the contents that will be written to des2
	readcontents = open("source.txt",O_RDONLY);//opens source.txt for reading
	opendes1 = open("destination1.txt",O_WRONLY);//opens destination1.txt for writing
	opendes2 = open("destination2.txt",O_WRONLY);//opens destination1.txt for writing
	int flag = 0;//flag for exiting the while loop
	char state = 'a';//hold the state we are in. a means we are writing to des1, b means we are writing to des2, c means special
	while(flag == 0)
	{	//start of while loop
		switch(state)
		{//inside switch statment
			case 'a':
				printf("\nWe are in state %c, writing to des1\n",state);
				readfile = read(readcontents, contents1,incrdes1);
				//reads 100 char from source.txt, stores in contents1
				printf("\nThe next %d char contains\n %s \n",incrdes1,contents1);
				//cout<<"\nThe next "<<incrdes1<<" char contains"<<"\n"<<contents1<<"end\n";
				//display what has been read
				for(int i = 0; i < incrdes1; i++)//looping through the read contents
				{
					if(contents1[i] == '1')//we want to change 1's to A's
						contentsdes1[i] = 'A';
					else
						contentsdes1[i] = contents1[i];//we leave anything else as it is	
				}
				printf("\nThe following will be stored in destination1 file\n %s \n",contentsdes1);	
				//cout<<"\nThe following will be stored in destination file\n"<<contentsdes<<"XYZ\n";
				//display what goes into des file
				writetodes1 = write(opendes1, contentsdes1, incrdes1);
				//does the writing of the modified read contents
				amount = amount + incrdes2;//we increase by incrdes2 because we will switch to case 2
				if(amount == filesize)//this was the last run
				{flag = flag + 1; break;}//exit while loop
				if(amount<filesize)
					state = 'b';//to switch to case 1 if we can still read without being at EOF
				else
				//we are near EOF, need a special case, we are switching to case 1 but amount>filesize 
				//(less than 50)
					{
						incrlast = mod50;//holds the remaining chars to read
						state = 'c';//switch to special case
						check = 1;// will write to des 2
					}
				break;
			case 'b':
				printf("We are in state %c, writing to des2\n",state);
				readfile = read(readcontents, contents2,incrdes2);
				//reads 50 char from source.txt, stores in contents2
				printf("\nThe next %d char contains\n %s \n",incrdes2,contents2);
				//cout<<"\nThe next "<<incrdes2<<" char contains"<<"\n"<<contents2<<"end\n";
				//display what has been read
				for(int i = 0; i < incrdes2; i++)//looping through the read contents
				{
					if(contents2[i] == '2')//we want to change 2's to B's
						contentsdes2[i] = 'B';
					else
						contentsdes2[i] = contents2[i];//we leave anything else as it is	
				}
				printf("\nThe following will be stored in destination2 file\n %s \n",contentsdes2);	
				//cout<<"\nThe following will be stored in destination file\n"<<contentsdes<<"XYZ\n";
				//display what goes into des file
				writetodes2 = write(opendes2, contentsdes2, incrdes2);
				//does the writing of the modified read contents
				amount = amount + incrdes1;//we increase by incrdes1 because we will switch to case a
				if(amount == filesize)//this was the last run
				{flag = flag + 1; break;}//exit while loop
				if(amount<filesize)
					state = 'a';//to switch to case a if we can still read without being at EOF
				else
				//we are near EOF, need a special case, we are switching to case a but amount>filesize 
				//(less than 100)
					{
						incrlast = mod100;//holds the remaining chars to read
						state = 'c';//switch to special case
						check = 0;// will write to des1
					}
				break;
			case 'c':
				printf("We are in state %c, writing the last run\n",state);
				if(check == 1)//we repeat state b but with incrlast
				{
				readfile = read(readcontents, contents2,incrlast);
				//reads 50 char from source.txt, stores in contents2
				printf("\nThe next %d char contains\n %s \n",incrlast,contents2);
				//cout<<"\nThe next "<<incrlast<<" char contains"<<"\n"<<contents2<<"end\n";
				//display what has been read
				for(int i = 0; i < incrlast; i++)//looping through the read contents
				{
					if(contents2[i] == '2')//we want to change 2's to B's
						contentsdes2[i] = 'B';
					else
						contentsdes2[i] = contents2[i];//we leave anything else as it is	
				}
				printf("\nThe following will be stored in destination2 file\n %s \n",contentsdes2);	
				//cout<<"\nThe following will be stored in destination file\n"<<contentsdes<<"XYZ\n";
				//display what goes into des file
				writetodes2 = write(opendes2, contentsdes2, incrlast);
				//does the writing of the modified read contents
				flag = 1;//breaks out of while loop
				}
				else// we repeat state a but with incrlast
				{
				readfile = read(readcontents, contents1,incrlast);
				//reads 100 char from source.txt, stores in contents1
				printf("\nThe next %d char contains\n %s \n",incrlast,contents1);
				//cout<<"\nThe next "<<incrlast<<" char contains"<<"\n"<<contents1<<"end\n";
				//display what has been read
				for(int i = 0; i < incrlast; i++)//looping through the read contents
				{
					if(contents1[i] == '1')//we want to change 1's to A's
						contentsdes1[i] = 'A';
					else
						contentsdes1[i] = contents1[i];//we leave anything else as it is	
				}
				printf("\nThe following will be stored in destination1 file\n %s \n",contentsdes1);	
				//cout<<"\nThe following will be stored in destination file\n"<<contentsdes<<"XYZ\n";
				//display what goes into des file
				writetodes1 = write(opendes1, contentsdes1, incrlast);
				//does the writing of the modified read contents
				flag = 1;//breaks out of while loop
				break;
				}
			default:
				printf("\nsomething went wrong\n");

		}
		close(opendes1);//close files
		close(opendes2);
		//outside switch statement
		//
	}
	return 0;
}
