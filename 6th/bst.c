// bst.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

struct node {
	int data, height;
	struct node *lchild, *rchild;
};
typedef struct node Node;

Node* insertNode(Node* temp, int data, int height) {
	if (temp == NULL) {
		temp = (Node *)malloc(sizeof(Node));
		temp->rchild = NULL;
		temp->lchild = NULL;
		temp->data = data;
		temp->height = height;
	}
	else if (temp->data<=data) {
		temp->rchild = insertNode(temp->rchild, data, ++height);
	}
	else {
		temp->lchild = insertNode(temp->lchild, data, ++height);
	}
	return temp;
}

void traverse(Node* temp) {
	if (temp != NULL) {
		traverse(temp->lchild);
		if (temp->lchild == NULL && temp->rchild == NULL) {
			printf("%d %d\n", temp->data, temp->height);
		}
		traverse(temp->rchild);
	}
}

int main() {
	Node *root = NULL;
	int num, data, i;
	scanf("%d", &num);
	for (i = 0; i<num; i++) {
		scanf("%d", &data);
		root = insertNode(root, data, 1);
	}
	traverse(root);
	return 0;
}

