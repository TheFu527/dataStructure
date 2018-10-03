// tail.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	FILE *fileIn;
	char fileName[100];
	int n = 10;
	int i = 0;
	int maxLine = 0;
	char buff[1024][1024];
	if (argc == 3 && argv[1][0] == '-') {
		n = atoi(argv[1] + 1);
		strcpy(fileName, argv[2]);
	}
	else if (argc == 2) {
		strcpy(fileName, argv[1]);
	}
	fileIn = fopen(fileName, "r");
	while (fgets(buff[i], 1024, fileIn) != NULL) {
		i++;
		maxLine = i;
	}
	for (i = 0; i < n; i++) {
		printf("%s", buff[maxLine - n + i]);
	}
	
	return 0;
}

