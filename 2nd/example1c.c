// example1cNEW.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>

int calculate(char opt[], int num[]) {
	int result = 0, i = 0, j = 0, k = 0, temp;
	int newNum[100], newOpt[100];
	do {
		temp = num[i];
		while (opt[i] == '*' || opt[i] == '/') {
			if (opt[i] == '*')
				temp *= num[i + 1];
			else
				temp /= num[i + 1];
			i++;
		}
		newNum[j++] = temp;
		newOpt[k++] = opt[i++];
	} while (newOpt[k - 1] != '=');
	k = 0;
	result = newNum[0];
	while (newOpt[k] != '=') {
		if (newOpt[k] == '+') {
			result += newNum[k + 1];
		}
		else
			result -= newNum[k + 1];
		k++;
	}
	return result;
}

int main() {
	char formula[1024];
	fgets(formula, 1024, stdin);
	int i = 0, j = 0;
	while (formula[i] != '\0') {
		if (formula[i] != ' ') {
			formula[j] = formula[i];
			j++;
		}
		i++;
	}
	formula[j] = '\0';
	i = 0;
	j = 0;
	int k = 0, l = 0;
	char temp[100];
	int num[100];
	char opt[100];
	do {
		while (formula[i] >= '0'&&formula[i] <= '9') {
			temp[j++] = formula[i++];
		}
		temp[j] = '\0';
		num[k++] = atoi(temp);
		temp[0] = '\0';
		j = 0;
		opt[l++] = formula[i++];
	} while (opt[l - 1] != '=');
	printf("%d", calculate(opt, num));
	return 0;
}

