#include<stdio.h>
#include<stdlib.h>
#include"file.h"
#include"text.h"
void main(int argc, char *argv[])
{
	int choice;
	if (argc > 1)
	{		
		for (int i = 1; i < argc; i++)
		{
			File_Check(argv[i]);
			Streamline_Text(argv[i]);
		}
	}
	else
	{
		char **filename;
		int num_of_files;
		printf("Choose how to enter file names: (1) via the console (2) From a file filename.txt\n: ");
		scanf_s("%d", &choice);
		if (choice == 1)
		{
			printf_s("Specify the number of files that the program will need to process (The minimum allowed number of files is 1)\n: ");
			scanf_s("%d", &num_of_files);
			while ((getchar()) != '\n');
			if (num_of_files < 1)
			{
				printf_s("Sorry, you entered an incorrect value. The minimum allowed number of files is 1. Try again!\n");
				system("pause");
				exit(0);
			}
			printf_s("Enter the file names\n");
			filename = (char**)malloc(num_of_files * sizeof(char*));
			for (int i = 0; i < num_of_files; i++)
			{
				filename[i] = (char*)malloc(255 * sizeof(char));
				printf(": ");
				gets_s(filename[i], 255);
			}
			system("cls");
			for (int i = 0; i < num_of_files; i++)
			{
				File_Check(filename[i]);
				Streamline_Text(filename[i]);
			}
		}
		else if (choice == 2)
		{
			FILE *F;  
			File_Check("filenames.txt");
			fopen_s(&F, "filenames.txt", "r");
			num_of_files = Get_Number_Of_Lines(F);
			fseek(F, 0, SEEK_SET);
			filename = (char**)malloc(num_of_files * sizeof(char*));
			for (int i = 0; i < num_of_files; i++)
			{
				filename[i] = (char*)malloc(255 * sizeof(char));
				fgets(filename[i], 255,F);
				File_Check(filename[i]);
				Streamline_Text(filename[i]);
			}
			fclose(F);
		}
		else
		{
			printf("There is no such option. Try again!\n");
			system("pause");
			exit(0);
		}
		for (int i = 0; i < num_of_files; i++)
		{
			free(filename[i]);
		}
		free(filename);
	}
	
	system("pause");
	exit(0);
}