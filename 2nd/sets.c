// sets.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>

int main()
{
	int boolean[999] = { 0 };
	int setA[99];
	int setB[99];
	int result[99];
	int i=0;
	int queue = 1;
	do {
		scanf("%d", &setA[i]);
	} while (setA[i++] != -1);
	i = 0;
	do {
		scanf("%d", &setB[i]);
	} while (setB[i++] != -1);
	
	for (i = 0; setA[i] != -1; i++) {
		boolean[setA[i]] = queue;
		queue++;
	}
	queue--;
	for (i = 0; setB[i] != -1; i++) {
		boolean[setB[i]] = 0;

	}
	int flag = 0;
	int j = 0;
	while (queue!=0) {
		for (i = 1; i < 999; i++) {
			if (boolean[i] == queue) {
				result[j] = i;
				j++;
				queue--;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			queue--;
		}
		flag = 0;
	}
	j--;
	for (i = j; i >= 0; i--) {
		printf("%d ", result[i]);
	}
	return 0;
}
	