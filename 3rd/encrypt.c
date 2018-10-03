// encrypt.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>

void removeKey(char keys[]) {
	int flag[26] = { 0 };
	int i, j;
	j = 1;
	flag[keys[0] - 'a'] = 1;
	for (i = 1; keys[i] != '\0'; i++) {
		if (flag[keys[i] - 'a'] == 0) {
			keys[j] = keys[i];
			j++;
			flag[keys[i] - 'a'] = 1;
		}
	}
	keys[j] = '\0';	
}

void encrypt(char text[], char keys[]) {
	int i;
	for (i = 0; text[i] != '\0'; i++) {
		if (text[i] >= 'a'&&text[i] <= 'z') {
			text[i] = keys[text[i] - 'a'];
		}
	}
}

int main()
{
	char keys[51];
	int i;
	char alphabet[27]="zyxwvutsrqponmlkjihgfedcba";
	FILE *fileIn;
	FILE *fileOut;
	char buff[1024];

	fileIn = fopen("encrypt.txt", "r");
	fileOut = fopen("output.txt", "w");
	scanf("%s", keys);
	strcat(keys, alphabet);
	removeKey(keys);
	while (fgets(buff, 1024, fileIn) != NULL) {
		encrypt(buff, keys);
		fprintf(fileOut, "%s", buff);
	}
	fclose(fileIn);
	fclose(fileOut);
    return 0;
}

