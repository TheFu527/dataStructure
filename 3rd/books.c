// books.cpp: 定义控制台应用程序的入口点。
//
//
//#include "stdafx.h"
#include <stdio.h>
#include <string.h>

struct Book {
	char name[51];
	char author[21];
	char publisher[31];
	char publishYear[11];
	int isIn;
};

void sort(struct Book books[],int end) {
	int i, j;
	struct Book temp;
	for (i = 0; i < end - 1; i++) {
		for (j = i + 1; j < end; j++) {
			if (strcmp(books[i].name, books[j].name) > 0) {
				temp = books[i];
				books[i] = books[j];
				books[j] = temp;
			}				
		}
	}
}

int singleInput(struct Book books[], char buff[], int end) {
	int i;
	int j, k, l, m;
	j = k = l = m = 0;
	if (buff[0] == '\0' || buff[0] == '\n') {
		return end;
	}
	for (i = 0; buff[i] != ' '; i++) {
		books[end].name[j] = buff[i];
		j++;
	}
	for (i = i + 1; buff[i] != ' '; i++) {
		books[end].author[k] = buff[i];
		k++;
	}
	for (i = i + 1; buff[i] != ' '; i++) {
		books[end].publisher[l] = buff[i];
		l++;
	}
	for (i = i + 1; (buff[i]!='\n' && buff[i]!='\0'); i++) {
		books[end].publishYear[m] = buff[i];
		m++;
	}
	books[end].name[j] = books[end].author[k] = books[end].publisher[l] = books[end].publishYear[m] = '\0';
	books[end].isIn = 1;
	end++;
	return end;
}

int insert(struct Book books[],int end) {
	char buff[1024];
	char c;
	fgets(buff, 1024, stdin);
	end = singleInput(books, fgets(buff, 1000, stdin), end);
	sort(books, end);
	return end;
}

void search(struct Book books[],int end) {
	int i;
	char name[51];
	scanf("%s", name);
	for (i = 0; i < end; i++) {
		if (books[i].isIn == 1 && strstr(books[i].name, name) != NULL) {
			printf("%-50s%-20s%-30s%-10s\n", books[i].name, books[i].author, books[i].publisher, books[i].publishYear);
		}
	}
}

void del(struct Book books[],int end) {
	int i;
	char name[51];
	scanf("%s", name);
	for (i = 0; i < end; i++) {
		if (books[i].isIn == 1 && strstr(books[i].name, name) != NULL) {
			books[i].isIn = 0;
		}
	}
}



int main()
{
	struct Book books[1500];
	FILE *fileIn;
	FILE *fileOut;
	fileIn = fopen("books.txt", "r");
	fileOut = fopen("ordered.txt", "w");
	int chose;
	int end=0;
	int i;
	char buff[1024];
	while (fgets(buff, 1000, fileIn) != NULL) {
		end = singleInput(books, buff, end);
	}
	if (end != 0) {
		sort(books, end);
	}
	scanf("%d", &chose);
	while (chose != 0) {
		if(chose == 1){
			end = insert(books, end);
		}
		else if (chose == 2) {
			search(books, end);
		}
		else if (chose == 3) {
			del(books, end);
		}
		scanf("%d", &chose);
	}
	if (chose == 0) {
		for (i = 0; i < end; i++) {
			if (books[i].isIn == 1) {
				fprintf(fileOut,"%-50s%-20s%-30s%-10s", books[i].name, books[i].author, books[i].publisher, books[i].publishYear);
				fprintf(fileOut, "\n");
			}
		}
	}
	fclose(fileIn);
	fclose(fileOut);
	return 0;
}


