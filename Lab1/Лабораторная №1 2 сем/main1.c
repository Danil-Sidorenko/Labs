#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"file1.h"
#include"matrix1.h"
int main()
{
	int **matrix;
	int choice;
	int size;
	printf_s(" CHOOSE ONE OF THE WAYS HOW TO LOAD THE NATRIX?:\n  (1)Load matrix via file.\n  (2)Enter matrix values via the console.\n  (3)Generate random values of the matrix.\n");
	printf_s("\n ENTER THE NUMBER OF THE METHOD YOU'VE SELECTED AND PRESS 'ENTER':");
	scanf_s("%d", &choice);
	while ((getchar()) != '\n');
	switch (choice)
	{
	case 1:
		printf("\nEnter a file name:\n");
		const char filename[200];
		gets_s(filename, 200);
		File_Check(filename);

		size = Matrix_Check(filename);
		matrix = (int**)malloc(size * sizeof(int*));
		for (int i = 0; i < size; i++) { matrix[i] = (int*)malloc(size * sizeof(int)); }
		
		Load_Matrix_From_File(filename, matrix,size);
		Matrix_Console_Output(matrix,size);
		break;
	case 2:
		printf("\nEnter matrix order:\n");
		scanf_s("%d", &size);

		matrix = (int**)malloc(size * sizeof(int*));
		for (int i = 0; i < size; i++) { matrix[i] = (int*)malloc(size * sizeof(int)); }

		Matrix_Console_Input(matrix,size);
		Matrix_Console_Output(matrix, size);
		break;
	case 3:
		srand(time(NULL));
		size = rand()%10;
		matrix = (int**)malloc(size * sizeof(int*));
		for (int i = 0; i < size; i++) { matrix[i] = (int*)malloc(size * sizeof(int)); }
		
		Get_Random_Matrix(matrix, size);
		Matrix_Console_Output(matrix, size);
		break;
	default:
		printf("\nThere is no such option. Try again.\n");
		system("pause");
		return 0;
		break;
	}
	clock_t start = clock();
	long long det = Get_Det_Of_Matrix(matrix, size);
	clock_t stop = clock();
	printf("\nDet = %lld\n", det);
	double execution_time = (double)(stop - start) * 1000.0;
	printf("Execution time in ms: %.2f\n", execution_time);

	for (int i = 0; i < (size - 1); i++) { free(matrix[i]);} free(matrix);

	system("pause");
	return 0;
}