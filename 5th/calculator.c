// calculator.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node* link;
};

struct Node* num;
struct Node* op;

void pushnum(int data) {
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = data;
	newnode->link = num;
	num = newnode;
}

void pushop(int data) {
	struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
	newnode->data = data;
	newnode->link = op;
	op = newnode;
}

void popnum() {
	struct Node* p = num;
	num = num->link;
	free(p);
}

void popop() {
	struct Node* p = op;
	op = op->link;
	free(p);
}

int cal(int num1, int num2, int op) {
	if (op == '+')
		return num1 + num2;
	if (op == '-')
		return num1 - num2;
	if (op == '*')
		return num1*num2;
	if (op == '/')
		return num1 / num2;
	else
		return -1;
}

int main() {
	num = NULL;
	op = NULL;
	char buff[101], numstr[5];
	int numi;
	fgets(buff, 99, stdin);
	int i;
	for (i = 0; buff[i] != '='; i++) {
		if (buff[i] >= '0' && buff[i] <= '9') {
			int j = 0;
			while (buff[i] >= '0' && buff[i] <= '9') {
				numstr[j++] = buff[i++];
			}
			numstr[j] = '\0';
			i--;
			numi = atoi(numstr);
			pushnum(numi);
		}
		else if (buff[i] == ')') {
			while (op->data != '(') {
				num->link->data = cal(num->link->data, num->data, op->data);
				popnum();
				popop();
			}
			popop();
		}
		else if (buff[i] == '+' || buff[i] == '-') {
			while (op != NULL && op->data != '(') {
				num->link->data = cal(num->link->data, num->data, op->data);
				popnum();
				popop();
			}
			pushop(buff[i]);
		}
		else if (buff[i] == '*' || buff[i] == '/') {
			while (op != NULL && op->data != '(' && !(op->data == '+' || op->data == '-')) {
				num->link->data = cal(num->link->data, num->data, op->data);
				popnum();
				popop();
			}
			pushop(buff[i]);
		}
		else if (buff[i] == '(') {
			pushop(buff[i]);
		}
	}
	while (op != NULL) {
		num->link->data = cal(num->link->data, num->data, op->data);
		popnum();
		popop();
	}
	printf("%d", num->data);
	return 0;
}
