#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include"text.h"
#include<locale.h>
void Streamline_Text(char *filename)
{
	setlocale(LC_ALL, "Russian");
	printf("\nFILE: %s", filename);
	FILE *F;  fopen_s(&F,filename, "r");
	int lines = Get_Number_Of_Lines(F);
	lines = lines - 1;;
	printf("\nLINES = %d\n", lines);
	int *size = (int*)malloc(lines * sizeof(int));
	char **text = (char**)malloc(lines * sizeof(char*));
	for (int i = 0; i < lines; i++)
	{
		text[i] = (char*)malloc(255 * sizeof(char));
	}
	fseek(F, 0, SEEK_SET);

	printf("\nText before:\n====================================================================================================\n");
	for (int i = 0; i < lines; i++)
	{
		fgets(text[i], 255, F);
		size[i] = String_Size(text[i]);	
		if (i == (lines - 1)) { size[i]++;}
		fputs(text[i], stdout);
	}
	printf("====================================================================================================\n");

	char *tmp_string;
	int tmp_size;
	for (int j = 0; j < (lines-1); j++)
	{
		for (int i =0 ; i<(lines-1) ; i++)
		{
			int a = String_Size(text[i]), b = String_Size(text[i + 1]);
				if (a > b)
				{
					tmp_string = text[i+1];
					text[i+1]= text[i];
					text[i] = tmp_string;
					tmp_size = size[i + 1];
					size[i + 1] = size[i];
					size[i] = tmp_size;
				}
		}
	}
	
	printf("\nText after:\n====================================================================================================\n");
	for (int i = 0; i < lines; i++) { fputs(text[i], stdout); }
	printf("====================================================================================================\n");

	for (int i = 0; i < lines; i++)
	{
		free(text[i]);
	}
	free(text);
	free(size);
	fclose(F);
}

int Get_Number_Of_Lines(FILE *p)
{
	fseek(p, 0, SEEK_SET);
	int lines=0;
	char ch=0;
	while (!feof(p))
	{
		if ((ch = fgetc(p)) == '\n') {lines++;}
	}
	lines++;
	return lines;
}

int String_Size(char *string)
{
	int size = 0;
	while (string[size]!='\0') {size++;}
	return size;
}

