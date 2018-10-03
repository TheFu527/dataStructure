// chess.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>

int judge(int chess[][21], int x, int y) {
	int i;
	int flag = 0;
	if ((chess[x][y - 1] == 0 || chess[x][y + 4] == 0) && y <= 16) {
		flag = 1;
		for (i = 1; i <= 3; i++) {
			if (chess[x][y + i] != chess[x][y]) {
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return 1;
	}
	if ((chess[x - 1][y] == 0 || chess[x + 4][y] == 0) && x <= 16) {
		flag = 1;
		for (i = 1; i <= 3; i++) {
			if (chess[x + i][y] != chess[x][y]) {
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return 1;
	}
	if ((chess[x - 1][y - 1] == 0 || chess[x + 4][y + 4] == 0) && x <= 16 && y <= 16) {
		flag = 1;
		for (i = 1; i <= 3; i++) {
			if (chess[x + i][y + i] != chess[x][y]) {
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return 1;
	}
	if ((chess[x - 1][y + 1] == 0 || chess[x + 4][y - 4] == 0) && x <= 16 && y >= 4) {
		flag = 1;
		for (i = 1; i <= 3; i++) {
			if (chess[x + i][y - i] != chess[x][y]) {
				flag = 0;
				break;
			}
		}
		if (flag == 1)
			return 1;
	}
	return 0;
}

int main()
{
	int chess[21][21];
	int i, j;
	int flag = 0;
	for (i = 0; i < 21; i++) {
		chess[i][0] = 3;
		chess[i][20] = 3;
		chess[0][i] = 3;
		chess[20][i] = 3;
	}
	for (i = 1; i <= 19; i++) {
		for (j = 1; j <= 19; j++) {
			scanf("%d", &chess[i][j]);
		}
	}
	for (i = 1; i <= 19; i++) {
		for (j = 1; j <= 19; j++) {
			if (chess[i][j] == 1 || chess[i][j] == 2) {
				flag = judge(chess, i, j);
				if (flag == 1) {
					printf("%d:%d,%d\n", chess[i][j], i, j);
					return 0;
				}
			}
		}
	}
	printf("No\n");
	return 0;
}

