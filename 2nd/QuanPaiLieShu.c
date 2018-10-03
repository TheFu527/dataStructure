// QuanPaiLieShu.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>

void swap(int i, int j, int number[]) {
	int temp;
	temp = number[i];
	number[i] = number[j];
	number[j] = temp;
}

void sort(int begin, int finish, int number[]) {
	int i,j;
	for (i = begin; i < finish-1; i++) {
		for (j = i + 1; j < finish; j++) {
			if (number[i] > number[j]) {
				swap(i, j, number);
			}
		}
	}
}

void output(int number[]) {
	int i;
	for (i = 0; number[i] != 0; i++) {
		printf("%d ", number[i]);
	}
	printf("\n");
}

void quanPaiXu(int begin, int finish, int number[]) {
	int i;
	if (begin == finish-1) {
		output(number);
	}
	else {
		for (i = begin; i < finish; i++) {
			sort(begin, finish, number);
			swap(begin, i, number);
			quanPaiXu(begin + 1, finish, number);
			swap(begin, i, number);
		}
	}
}



int main()
{
	int n;
	int number[11] = { 0 };
	int i;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		number[i] = i+1;
	}
	quanPaiXu(0, n, number);
	//while (1);
	return 0;
}

