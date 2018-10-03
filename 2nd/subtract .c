// subtract.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>
#include<string.h>

void subtract(int numA[], int numB[], int result[]) {
	int i;
	for (i = 0; i < 80; i++) {
		if (numA[i] >= numB[i]) {
			result[i] = numA[i] - numB[i];
		}
		else {
			result[i] = numA[i] - numB[i] + 10;
			numA[i + 1]--;
		}
	}
}

int bigger(int numA[], int numB[],int length) {
	int i;
	for (i = length - 1; i >= 0; i--) {
		if (numA[i] < numB[i]) {
			return 1;
		}
	}
	return 0;
}

int main()
{
	int numA[80] = { 0 };
	int numB[80] = { 0 };
	int result[81] = { 0 };
	char inputA[80];
	char inputB[80];
	int lengthA, lengthB;
	int i, j;
	int flag = 0;
	scanf("%s", inputA);
	scanf("%s", inputB);
	lengthA = strlen(inputA);
	lengthB = strlen(inputB);
	for (i = 0; inputA[i] != '\0'; i++) {
		numA[i] = (*(inputA + lengthA - (i + 1))) - '0';
	}
	for (i = 0; inputB[i] != '\0'; i++) {
		numB[i] = (*(inputB + lengthB - (i + 1))) - '0';
	}
	if (lengthA > lengthB) {
		subtract(numA, numB, result);
	}
	else if (lengthA < lengthB) {
		subtract(numB, numA, result);
		flag = 1;
	}
	else {
		flag = bigger(numA, numB, lengthA);
		if (flag == 1) {
			subtract(numB, numA, result);
		}
		else {
			subtract(numA, numB, result);
		}
	}

	if (flag == 0) {
		for (i = 79; i >= 0; i--) {
			if (result[i] != 0) {
				for (j = i; j >= 0; j--) {
					printf("%d", result[j]);
				}
				break;
			}
			else if (i == 0 && result[i] == 0) {
				printf("0");
			}
		}
	}
	else if (flag == 1) {
		printf("-");
		for (i = 79; i >= 0; i--) {
			if (result[i] != 0) {
				for (j = i; j >= 0; j--) {
					printf("%d", result[j]);
				}
				break;
			}
		}
	}


	return 0;
}

