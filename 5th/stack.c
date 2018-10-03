// stack.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *link;
};


struct Node *Top;

void push(int data) {
	struct Node *p = (struct Node*)malloc(sizeof(struct Node));
	p->data = data;
	p->link = Top;
	Top = p;
}

void pop() {
	if (Top == NULL) {
		printf("error ");
	}
	else {
		printf("%d ", Top->data);
		struct Node *p = Top;
		Top = Top->link;
		free(p);
	}
}

int main() {
	Top = NULL;
	int opt, size = 0;
	int num;
	scanf("%d", &opt);
	while (opt != -1) {
		if (opt == 1) {
			scanf("%d", &num);
			if (size == 100) {
				printf("error ");
			}
			else {
				push(num);
				size++;
			}
		}
		else {
			pop();
			size--;
		}
		scanf("%d", &opt);
	}
	return 0;
}