// find.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char data[21];
	int height;
	struct node *lchild, *rchild, *parent;
};
typedef struct node Node;

void findpos(Node* temp, char str[], Node** result) {
	if (temp == NULL) {
		return;
	}
	else if (temp != NULL) {
		findpos(temp->lchild, str, result);
		if (strcmp(str, temp->data) == 0) {
			*result = temp;
		}
		findpos(temp->rchild, str, result);
	}
}

void insertChild(Node* pos, char lchild[], char rchild[]) {
	
	if (strcmp(rchild, "NULL") != 0) {
		pos->rchild = (Node *)malloc(sizeof(Node));
		strcpy(pos->rchild->data, rchild);
		pos->rchild->height = pos->height + 1;
		pos->rchild->lchild = pos->rchild->rchild = NULL;
		pos->rchild->parent = pos;
	}

	if (strcmp(lchild, "NULL") != 0) {
		pos->lchild = (Node *)malloc(sizeof(Node));
		strcpy(pos->lchild->data, lchild);
		pos->lchild->height = pos->height + 1;
		pos->lchild->lchild = pos->lchild->rchild = NULL;
		pos->lchild->parent = pos;
	}
}

int main() {
	Node *pos = NULL;
	int num, i;
	char parent[21], lchild[21], rchild[21];
	FILE *fileIn = fopen("in.txt", "r");
	fscanf(fileIn, "%d", &num);
	fscanf(fileIn, "%s %s %s", parent, lchild, rchild);
	Node *root = (Node *)malloc(sizeof(Node));
	strcpy(root->data, parent);
	root->lchild = NULL;
	root->rchild = NULL;
	root->parent = NULL;
	root->height = 1;
	insertChild(root, lchild, rchild);
	for (i = 1; i<num; i++) {
		fscanf(fileIn, "%s %s %s", parent, lchild, rchild);
		findpos(root, parent, &pos);
		insertChild(pos, lchild, rchild);
	}

	char p1[100], p2[100];
	Node *p1Pos = NULL, *p2Pos = NULL;
	scanf("%s %s", p1, p2);
	findpos(root, p1, &p1Pos);
	findpos(root, p2, &p2Pos);
	if (p1Pos->height>p2Pos->height) {
		printf("%s %s %d", p1Pos->data, p2Pos->data, p1Pos->height - p2Pos->height);
	}
	else if (p1Pos->height<p2Pos->height) {
		printf("%s %s %d", p2Pos->data, p1Pos->data, p2Pos->height - p1Pos->height);
	}
	else {
		int h = p1Pos->height;
		while (p1Pos != p2Pos) {
			p1Pos = p1Pos->parent;
			p2Pos = p2Pos->parent;
		}
		printf("%s %s %d\n%s %s %d\n", p1Pos->data, p1, h - p1Pos->height, p1Pos->data, p2, h - p1Pos->height);
	}

	fclose(fileIn);
	return 0;
}
