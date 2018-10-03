// notation.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
int main()
{
	char priNum[100];
	char zhengShu[100];
	char xiaoShu[100];
	int i, j, k;
	int isZhengShu = 1;
	int zhiShu = 0;
	i = j = k = 0;

	scanf("%s", priNum);
	for (i = 0; priNum[i] != '\0'; i++) {
		if (priNum[i] == '.') {
			isZhengShu = 0;
			continue;
		}
		if (isZhengShu == 1) {
			zhengShu[j] = priNum[i];
			j++;
		}
		else if (isZhengShu == 0) {
			xiaoShu[k] = priNum[i];
			k++;
		}
	}
	xiaoShu[k] = zhengShu[j] = '\0';
	if (zhengShu[0] == '0') {
		for (i = 0; i < strlen(xiaoShu); i++) {
			if (xiaoShu[i] == '0') {
				zhiShu++;
			}
			if (xiaoShu[i] != '0') {
				break;
			}
		}
		zhiShu++;
		int start = i;
		printf("%c", xiaoShu[start]);
		if (xiaoShu[start + 1] != '\0') {
			printf(".");
			for (i = start + 1; i < strlen(xiaoShu); i++) {
				printf("%c", xiaoShu[i]);
			}
		}
		printf("e-%d", zhiShu);

	}
	else {
		zhiShu = strlen(zhengShu) - 1;
		printf("%c.", zhengShu[0]);
		for (i = 1; i < strlen(zhengShu); i++)
			printf("%c", zhengShu[i]);
		printf("%s", xiaoShu);
		printf("e%d", zhiShu);
	}
	return 0;
}

