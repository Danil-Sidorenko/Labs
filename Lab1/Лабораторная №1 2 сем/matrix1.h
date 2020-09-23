#pragma once

void Load_Matrix_From_File(const char* filename, int** matrix, int size);

int Get_Number_Of_Matrix_Colomns(FILE *p);

int Get_Number_Of_Matrix_Lines(FILE *p);

int Matrix_Check(const char* filename);

void Matrix_Console_Output(int **matrix, int size);

void Matrix_Console_Input(int** matrix, int size);

void Get_Random_Matrix(int **matrix, int size);

long long Get_Det_Of_Matrix(int** matrix, int size);

void Get_Cofactor_Of_Element(int** main_matrix, int size, int line, int colomn, int** minor);