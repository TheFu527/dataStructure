// replace.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>
#include<string.h>
#include <ctype.h>

char *strupr(char *str) {
	char *ptr = str;
	while (*ptr != '\0')
	{
		if (islower(*ptr))
			*ptr = toupper(*ptr);
		ptr++;
	}
	return str;
}

void replaceStr(char buff[], char changeFrom[], char changeTo[]) {
	char buffTemp[1024];
	char *temp;
	int i;
	strcpy(buffTemp, buff);
	strupr(buff);
	temp = strstr(buff, changeFrom);
	strcpy(buff, buffTemp);
	if (temp == NULL) {
		return;
	}
	if (strlen(changeFrom) > strlen(changeTo)) {
		for (i = 0; changeTo[i] != '\0'; i++) {
			*temp = changeTo[i];
			temp++;
		}
		while (*temp != '\0') {
			*temp = *(temp + 1);
			temp++;
		}
	}
	else if (strlen(changeFrom) == strlen(changeTo)) {
		for (i = 0; changeTo[i] != '\0'; i++) {
			*temp = changeTo[i];
			temp++;
		}
	}
	else if (strlen(changeFrom) < strlen(changeTo)) {
		char *end;
		int differ = strlen(changeTo) - strlen(changeFrom);
		end = temp;
		for (i = 0; i < strlen(temp); i++) {
			end++;
		}
		while (end != temp + strlen(changeFrom) - 1) {
			*(end + differ) = *end;
			end--;
		}
		for (i = 0; changeTo[i] != '\0'; i++) {
			*temp = changeTo[i];
			temp++;
		}
	}
	replaceStr(buff, changeFrom, changeTo);
}


int main()
{
	FILE *fileIn;
	FILE *fileOut;
	fileIn = fopen("filein.txt", "r");
	fileOut = fopen("fileout.txt", "w");
	char changeFrom[99];
	char changeTo[99];
	char buff[1024];
	scanf("%s", changeFrom);
	scanf("%s", changeTo);
	strupr(changeFrom);
	while (fgets(buff, 1024, fileIn) != NULL) {
		replaceStr(buff, changeFrom, changeTo);
		fprintf(fileOut, "%s", buff);
	}

	fclose(fileIn);
	fclose(fileOut);

	return 0;
}

