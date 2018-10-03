// huffman.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node {
	char letter;
	int count;
	struct node *next, *lchild, *rchild, *parent;
};
typedef struct node Node;

struct code {
	char letter;
	char code[30];
};
typedef struct code Code;

Node *root;

Node* insert(Node *p, char letter) {
	if (p == NULL) {
		p = (Node *)malloc(sizeof(Node));
		p->letter = letter;
		p->count = 1;
		p->next = NULL;
		p->lchild = NULL;
		p->rchild = NULL;
	}
	else if (p->letter == letter) {
		p->count++;
	}
	else {
		p->next = insert(p->next, letter);
	}
	return p;
}

Node* findMin() {
	Node *result = root, *p = root->next;
	while (p != NULL) {
		if ((p->count<result->count) || (p->count == result->count && p->letter <= result->letter)) {
			result = p;
		}
		p = p->next;
	}
	if (result == root) {
		root = root->next;
	}
	else {
		p = root;
		while (p->next != result) {
			p = p->next;
		}
		p->next = result->next;
	}
	return result;
}

void merge(Node* n1, Node* n2) {
	Node* parent = (Node *)malloc(sizeof(Node));
	parent->letter = '~';
	parent->count = n1->count + n2->count;
	n1->parent = parent;
	n2->parent = parent;
	parent->lchild = n1;
	parent->rchild = n2;
	parent->next = root;
	root = parent;
}

void createHuffman(int n) {
	int i = 0;
	while (i < n - 1) {
		Node* n1 = findMin();
		Node* n2 = findMin();
		merge(n1, n2);
		i++;
	}
}

void visit(Node *node, Code code[], int i) {
	int j = 0;
	code[i].letter = node->letter;
	while (node != root) {
		if (node->parent->lchild == node)
			code[i].code[j++] = '0';
		else if (node->parent->rchild == node)
			code[i].code[j++] = '1';
		node = node->parent;
	}
	code[i].code[j] = '\0';
}

void traverse(Node *node, Code code[], int *i) {
	if (node != NULL) {
		if (node->lchild == NULL) {
			visit(node, code, *i);
			(*i)++;
		}
		traverse(node->lchild, code, i);
		traverse(node->rchild, code, i);
	}
}

void reverse(char s[]) {
	int i, j, temp;
	for (i = 0, j = strlen(s) - 1; i<j; i++, j--) {
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
	}
}

void writefile(FILE *fp1, FILE *fp2, int num) {
	Code code[10000];
	char buffer[10000] = "";
	int i = 0, j;
	traverse(root, code, &i);
	for (i = 0; i<num; i++) {
		reverse(code[i].code);
	}
	char letter;
	while ((letter = fgetc(fp1)) != EOF) {
		if (letter != '\n') {
			for (i = 0; i<num; i++) {
				if (code[i].letter == letter) {
					strcat(buffer, code[i].code);
					break;
				}
			}
		}
	}
	for (i = 0; i<num; i++) {
		if (code[i].letter == '\0') {
			strcat(buffer, code[i].code);
			break;
		}
	}
	int sp = 8 - strlen(buffer) % 8;
	if (sp != 8) {
		for (i = 0; i<sp; i++) {
			strcat(buffer, "0");
		}
	}
	int temp[9];
	char c;
	i = 0;
	while (buffer[i] != '\0') {
		temp[8] = 0;
		for (j = 0; j<8; j++, i++) {
			temp[i % 8] = buffer[i] - '0';
		}
		for (j = 0; j<8; j++) {
			temp[j] = temp[j] << (7 - j);
		}
		for (j = 0; j<8; j++) {
			temp[8] |= temp[j];
		}
		c = temp[8];
		fwrite(&c, 1, 1, fp2);
	}
}

int main() {
	char letter;
	root = NULL;
	int n = 0;
	root = insert(root, 0);
	FILE *fileIn = fopen("input.txt", "r");
	while ((letter = fgetc(fileIn)) != EOF) {
		if (letter != '\n') {
			root = insert(root, letter);
		}
	}
	Node *temp = root;
	while (temp != NULL) {
		temp = temp->next;
		n++;
	}
	fclose(fileIn);

	createHuffman(n);
	FILE *fp1, *fp2;
	fp1 = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "wb");
	writefile(fp1, fp2, n);
	fclose(fp2);
	FILE *fileIn2;
	fileIn2 = fopen("output.txt", "rb");
	int num;
	fread(&num, 1, 1, fileIn2);
	while (!feof(fileIn2)) {
		printf("%x", num);
		fread(&num, 1, 1, fileIn2);
	}

	fclose(fp1);
	fclose(fileIn2);
	return 0;
}
