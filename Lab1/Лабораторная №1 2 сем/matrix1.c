#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>
#include"matrix1.h"

void Load_Matrix_From_File(const char* filename, int** matrix, int size)
{
	FILE* in;
	fopen_s(&in, filename, "r");
	fseek(in, 0, SEEK_SET);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			fscanf_s(in, "%d", &matrix[i][j]);
		}
	}
	fclose(in);
}

int Get_Number_Of_Matrix_Lines(FILE* p)
{
	int n = 1;
	char c = 0;
	fseek(p, 0, SEEK_SET);
	while (!feof(p))
	{
		fscanf_s(p, "%c", &c, 1);
		if (c == '\n')
		{
			n = n + 1;
		}
	}
	fseek(p, 0, SEEK_SET);
	return n;
}

int Get_Number_Of_Matrix_Colomns(FILE* p)
{
	int m = 1;
	char c = 0;
	fseek(p, 0, SEEK_SET);
	while (c != '\n')
	{
		fscanf_s(p, "%c", &c, 1);
		if (c == ' ')
		{
			m = m + 1;
		}
	}
	fseek(p, 0, SEEK_SET);
	return m;
}

int Matrix_Check (const char* filename)
{
	FILE *p;
	fopen_s(&p, filename, "r");
	/*Checks whether the matrix contains more than one space between two elements*/
	char space[2];
	fseek(p, 0, SEEK_SET);
	space[0] = fgetc(p);
	while ((space[1] = fgetc(p)) != EOF)
	{
		if ((isspace(space[0])) && (isspace(space[1])))
		{
			printf("ERROR! The matrix  contains extra spaces inside.\n");
			system("pause");
			exit(1);
		}
		space[0] = space[1];
	}
	/*CChecks whether the matrix contains more than one minus sign with one element*/
	char minus[2];
	fseek(p, 0, SEEK_SET);
	minus[0] = fgetc(p);
	while ((minus[1] = fgetc(p)) != EOF)
	{
		if ((minus[0] == '-') && (minus[1] == '-'))
		{

			printf("ERROR! The matrix contains extra minuses inside.\n");
			system("pause");
			exit(1);
		}
		minus[0] = minus[1];
	}
	/*Checks whether the matrix contains invalid characters*/
	char ch;
	fseek(p, 0, SEEK_SET);
	while ((ch = fgetc(p)) != EOF)
	{
		if ((ch >= '0') && (ch <= '9') || (ch == 13)|| (ch == 10) || (ch == 45) || (ch == 32) || (ch == 127))
		{
		}
		else
		{
			printf("ERROR! The matrix contains invalid characters inside.\n ");
			system("pause");
			exit(1);
		}
	}
	/*Checks that the value of the elements is within the allowed value*/
	fseek(p, 0, SEEK_SET);
	while (!feof(p))
	{
		long long n;
		fscanf_s(p, "%lld", &n);
		if (n > 2147483647)
		{
			printf("ERROR! The value of some element of the matrix is too large.\n");
			system("pause");
			exit(1);
		}

	}
	fseek(p, 0, SEEK_SET);
	while (!feof(p))
	{
		long long n;
		fscanf_s(p, "%lld", &n);
		if (n < (-2147483647 - 1))
		{
			printf("ERROR! The value of some element of the matrix is too small.\n");
			system("pause");
			exit(1);
		}

	}
	/*Checks whether the matrix is set to the correct size.Also, If the size is correct, returns the size of the matrix*/
	fseek(p, 0, SEEK_SET);
	int s = 0, n = 0, m = 0;
	n = Get_Number_Of_Matrix_Lines(p);
	m = Get_Number_Of_Matrix_Colomns(p);
	while (!feof(p))
	{
		int x = 0;
		fscanf_s(p, "%d", &x);
		s++;

	}
	if (n != m)
	{
		printf("ERROR! This matrix does not have deterniant.\n");
		system("pause");
		exit(1);
	}
	else if (s != n * m)
	{
		printf("ERROR! There's not enough elements in the file for matrix.\n");
		system("pause");
		exit(1);
	}
	else
	{
		return n;
	}
	fclose(p);
}

void Matrix_Console_Input(int** matrix,int size)
{
	printf("Enter %d elements of matrix:\n", size*size);
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			scanf_s("%d", &matrix[i][j]);
		}
	}
	
}

void Matrix_Console_Output(int **matrix,int size)
{
	printf("\nThe matrix:\n");
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}

void Get_Random_Matrix(int **matrix, int size)
{
	srand(time(NULL));
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			matrix[i][j] = rand()%1000;
		}
	}
}

long long Get_Det_Of_Matrix(int** matrix, int size)
{
	long long det = 0;
	if (size == 1)
	{
		return matrix[0][0];
	}
	else if (size == 2)
	{
		return ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
	}
	else
	{
		int degree = 1;
		int** tmp_matrix = (int**)malloc((size - 1) * sizeof(int*));
		for (int i = 0; i < (size - 1); i++) { tmp_matrix[i] = (int*)malloc((size - 1) * sizeof(int)); }
		for (int j = 0; j < size; j++,degree*=(-1))
		{
			Get_Cofactor_Of_Element(matrix, size, 0, j, tmp_matrix);
			det = det + (degree * matrix[0][j] * Get_Det_Of_Matrix(tmp_matrix,(size-1)));
		}
		for (int i = 0; i < (size-1); i++) { free(tmp_matrix[i]);} free(tmp_matrix);
	}
	/*if ((long long)(det) > LLONG_MAX)
	{
		printf("\nERROR! The determinant value is too large.\n");
		system("pause");
		exit(0);
	}
	else if ((long long)(det) < LLONG_MIN)
	{
		printf("\nERROR! The determinant value is too small.\n");
		system("pause");
		exit(0);
	}*/
	return det;
}

void Get_Cofactor_Of_Element(int** main_matrix,int size, int line, int colomn, int** minor)
{
	int colomn_offset = 0, line_offset = 0;
	for (int i = 0; i < (size-1); i++)
	{
		if (i == line)
		{
			line_offset = 1;
		}
		colomn_offset = 0;
		for (int j = 0; j < (size-1); j++)
		{
			if (j == colomn)
			{
				colomn_offset = 1;
			}
			minor[i][j] = main_matrix[i + line_offset][j + colomn_offset];
		}
	}
}