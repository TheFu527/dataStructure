// monkey.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

struct Monkey
{
	int num;
	struct Monkey *next;
};

int main()
{
	int n, m, q;
	int i;
	int j;
	int king;
	struct Monkey *head, *p1, *p2;
	scanf("%d %d %d", &n, &m, &q);
	if (m == 1) {
		king = n;
	}
	else {
		p1 = (struct Monkey*)malloc(sizeof(*p1));
		p2 = p1;
		head = p1;
		p1->num = 1;
		for (i = 1; i < n; i++) {
			p1 = (struct Monkey*)malloc(sizeof(*p1));
			p1->num = i + 1;
			p2->next = p1;
			p2 = p1;
		}
		p2->next = head;
		p1 = head;
		while (p1->num != q) {
			p1 = p1->next;
		}
		for (i = 1; i < n; i++) {
			for (j = 1; j < m - 1; j++) {
				p1 = p1->next;
			}
			p2 = p1->next;
			p1->next = p2->next;
			p1 = p2->next;
		}
		king = p1->num;
	}
	printf("%d", king);
    return 0;
}

