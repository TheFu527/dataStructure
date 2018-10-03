// ciPinTongJi.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<ctype.h>

struct node {
	char word[20];
	int count;
	struct node *lchild, *rchild;
};
typedef struct node Node;


void tolowercase(char word[]) {
	int i = 0;
	while (word[i] != '\0') {
		word[i] = tolower(word[i]);
		i++;
	}
}

Node* insert(Node *p, char word[]) {
	if (p == NULL) {
		p = (Node *)malloc(sizeof(Node));
		strcpy(p->word, word);
		p->lchild = NULL;
		p->rchild = NULL;
		p->count = 1;
	}
	else if (strcmp(p->word, word) > 0) {
		p->lchild = insert(p->lchild, word);
	}
	else if (strcmp(p->word, word) == 0) {
		p->count++;
	}
	else {
		p->rchild = insert(p->rchild, word);
	}
	return p;
}

void output(Node *node) {
	if (node != NULL) {
		output(node->lchild);
		printf("%s %d\n", node->word, node->count);
		output(node->rchild);
	}
}

int main() {
	char letter, word[20];
	int i = 0;
	Node *root;
	root = NULL;
	FILE *fileIn = fopen("article.txt", "r");
	while ((letter = fgetc(fileIn)) != EOF) {
		if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {
			while ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z')) {
				word[i] = letter;
				letter = fgetc(fileIn);
				i++;
			}
			word[i] = '\0';
			i = 0;
			tolowercase(word);
			root = insert(root, word);
		}
	}

	Node *temp = root;
	for (i = 0; i < 3; i++) {
		if (temp != NULL) {
			printf("%s", temp->word);
			if (temp->rchild != NULL && i<2) {
				printf(" ");
			}
			else {
				printf("\n");
			}
			temp = temp->rchild;
		}
	}
	output(root);

	fclose(fileIn);
	return 0;
}

