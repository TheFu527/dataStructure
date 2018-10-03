// telsort.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>
int main() {
	char name[50][11];
	char number[50][11];
	int n;
	int i;
	int j;
	scanf("%d", &n);
	for (i=0 ; i < n; i++) {
		scanf("%s", name[i]);
		scanf("%s", number[i]);
		number[i][10] = name[i][10] = '\0';
	}
	for (i = 0; i < n; i++) {
		for (j = i+1; j < n; j++) {
			if (strcmp(name[i],name[j])>0) {
				char temp[11];
				strcpy(temp, name[i]);
				strcpy(name[i], name[j]);
				strcpy(name[j], temp);
				strcpy(temp, number[i]);
				strcpy(number[i], number[j]);
				strcpy(number[j], temp);
			}
		}
	}
	for (i = 0; i < n; i++) {
		printf("%12s", name[i]);
		printf("%12s\n", number[i]);
	}
	//while (1);
	return 0;
}