// multi.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>
int main()
{
	char c;
	int i, j, m, n, t = 0;
	struct deg {
		int a[1000];
		int b[1000];
	}deg1, deg2, deg3;
	for (i = 0;; i++) {
		scanf("%d%d", &deg1.a[i], &deg1.b[i]);
		c = getchar();
		if (c == '\n')
			break;
	}
	m = i;
	for (i = 0;; i++)
		if (scanf("%d%d", &deg2.a[i], &deg2.b[i]) != 2)
			break;
	n = i - 1;
	for (i = 0; i <= m; i++)
		for (j = 0; j <= n; j++) {
			deg3.a[t] = deg1.a[i] * deg2.a[j];
			deg3.b[t++] = deg1.b[i] + deg2.b[j];
		}
	for (i = 0; i<t - 1; i++)
		for (j = i + 1; j<t; j++)
			if (deg3.b[i]<deg3.b[j]) {
				m = deg3.b[i];
				deg3.b[i] = deg3.b[j];
				deg3.b[j] = m;
				m = deg3.a[i];
				deg3.a[i] = deg3.a[j];
				deg3.a[j] = m;
			}
	for (i = 0; i<t - 1; i++)
		if (deg3.b[i] == deg3.b[i + 1]) {
			deg3.a[i] += deg3.a[i + 1];
			for (j = i + 1; j<t - 1; j++) {
				deg3.a[j] = deg3.a[j + 1];
				deg3.b[j] = deg3.b[j + 1];
			}
			t--;
			i--;
		}
	for (i = 0; i<t; i++)
		printf("%d %d ", deg3.a[i], deg3.b[i]);
	return 0;
}
