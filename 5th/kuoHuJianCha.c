// kuoHuJianCha.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>

struct KuoHu {
	char symbol;
	char lineNum;
};

int main()
{
	FILE *fileIn;
	fileIn = fopen("example.c", "r");
	char buff[1024];
	int i = 0;
	int line = 1;
	int top = 0;
	int flag = 0;
	int fall = 0;
	int correctI = 0;
	struct KuoHu kuoHu[200];
	char correct[200];
	while (fgets(buff, 1023, fileIn) != NULL) {
		if (fall == 1) {
			break;
		}
		for (i = 0; buff[i] != '\0'; i++) {
			if (buff[i] == '/'&&buff[i + 1] == '*') {
				flag = 1;
			}
			if (buff[i] == '*'&&buff[i + 1] == '/') {
				flag = 0;
			}
			if (flag == 1) {
				continue;
			}
			if (buff[i] == '/'&&buff[i + 1] == '/') {
				break;
			}
			if (buff[i] == '\"') {
				i++;
				while (buff[i] != '\"') {
					i++;
				}
				continue;
			}

			if (buff[i] == '(' || buff[i] == '{') {
				kuoHu[top].lineNum = line;
				kuoHu[top].symbol = buff[i];
				correct[correctI] = buff[i];
				correctI++;
				top++;
			}
			if (buff[i] == ')' || buff[i] == '}') {
				if ((kuoHu[top - 1].symbol == '('&&buff[i] == ')') ||
					(kuoHu[top - 1].symbol == '{'&&buff[i] == '}')) {
					correct[correctI] = buff[i];
					correctI++;
					top--;
				}
				else {
					printf("without maching '%c' at line %d", buff[i], line);
					fall = 1;
					break;
				}
			}
		}
		line++;
	}
	correct[correctI] = '\0';
	if (top != 0&&fall==0) {
		printf("without maching '%c' at line %d", kuoHu[top - 1].symbol, kuoHu[top - 1].lineNum);
	}
	else if(fall==0){
		printf("%s", correct);
	}
	fclose(fileIn);

	return 0;
}


