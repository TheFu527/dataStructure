// frequencyStatistics.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
	char word[20];
	int count;
	struct Node *next;
};

struct Node * addNode(char s[], struct Node *head) {
	struct Node *p = head;
	while (p != NULL) {
		if (!strcmp(p->word, s)) {
			p->count++;
			return head;
		}
		p = p->next;
	}
	p = (struct Node *)malloc(sizeof(struct Node));
	strcpy(p->word, s);
	p->count = 1;
	p->next = head;
	head = p;
	return head;
}

void sortWord(struct Node *head) {
	struct Node *now, *next;
	char tempword[20];
	int tempcount;
	int flag = 0;
	while (flag == 0) {
		flag = 1;
		now = head;
		next = head->next;
		while (next != NULL) {
			if (strcmp(now->word, next->word)>0) {
				strcpy(tempword, next->word);
				strcpy(next->word, now->word);
				strcpy(now->word, tempword);
				tempcount = now->count;
				now->count = next->count;
				next->count = tempcount;
				flag = 0;
			}
			now = next;
			next = next->next;
		}
	}
}


int main()
{
	FILE *fileIn;
	fileIn = fopen("article.txt", "r");
	struct Node *head = NULL;
	char word[100];
	char buff;
	int i;
	while (1) {
		buff = fgetc(fileIn);
		if (buff == EOF)
			break;
		while (!((buff >= 'a' && buff <= 'z') || (buff >= 'A' && buff <= 'Z') || buff == EOF)) {
			buff = getc(fileIn);
		}
		if (buff == EOF)
			break;
		i = 0;
		while ((buff >= 'a' && buff <= 'z') || (buff >= 'A' && buff <= 'Z')) {
			buff = tolower(buff);
			word[i] = buff;
			i++;
			buff = fgetc(fileIn);
		}
		word[i] = '\0';
		head = addNode(word, head);
	}
	sortWord(head);
	while (head != NULL) {
		printf("%s %d\n", head->word, head->count);
		head = head->next;
	}
	fclose(fileIn);
	return 0;
}

