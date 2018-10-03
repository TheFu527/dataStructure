#include<stdio.h>

void readMatrix(int(*matrix)[10], int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			scanf("%d", &matrix[i][j]);
		}
	}
	scanf("%*c");
}

void add(int(*matrixA)[10], int(*matrixB)[10], int size) {
	int i,j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			matrixA[i][j] += matrixB[i][j];
		}
	}
}

void sub(int(*matrixA)[10], int(*matrixB)[10], int size) {
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			matrixA[i][j] -= matrixB[i][j];
		}
	}
}

void operation(int(*matrix)[10], int size) {
	char opt;
	int matrixB[10][10];
	opt = getchar();
	while (opt != '#') {
		readMatrix(matrixB, size);
		if (opt == '+') {
			add(matrix, matrixB, size);
		}
		else {
			sub(matrix, matrixB, size);
		}
		opt = getchar();
	}
}

int main()
{
	int matrixA[10][10];
	int i, j;
	int size;
	scanf("%d", &size);
	readMatrix(matrixA, size);
	operation(matrixA, size);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			printf("%5d", matrixA[i][j]);
		}
		printf("\n");
	}
	return 0;
}

