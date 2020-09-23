#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
void File_Check(const char* filename)
{
	FILE *in;
	errno_t err = fopen_s(&in, filename, "r");
	if (err== ENOENT)   //Check if you have access to  file
	{
		printf("\nERROR! File %s does not exist.\n", filename);
		system("pause");
		exit(1);
		
	}
	else
		if (err== EACCES) //Check if file 'in.txt' exist
		{
			printf("\nERROR! You do not have access to the file %s.\n", filename);
			system("pause");
			exit(1);
		}
		else
		{
			fseek(in, 0, SEEK_END);
			long position = ftell(in);
			if (position == 0) //Check if file 'in.txt' is empty
			{
				printf("\nERROR! File %s is empty. The programm cannnot read any values.\n", filename);
				system("pause");
				exit(1);
			}
		}
	fclose(in);
}