// find.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#include <string.h>

/* compute hash value for string */

#define NHASH  3001

#define MULT  37

unsigned int hash(char *str)
{

	unsigned int h = 0;
	char *p;
	for (p = str; *p != '\0'; p++) {
		h = MULT*h + *p;
	}
	return h % NHASH;
}

void shunXu(char findWord[],char dic[][100],int size) {
	int i;
	int flag = 0;
	for (i = 0; i < size; i++) {
		if (strcmp(findWord, dic[i]) == 0) {
			flag = 1;
			break;
		}
		if (strcmp(findWord, dic[i]) < 0) {
			break;
		}
	}
	printf("%d %d", flag, i+1);
}

void zheBan(char findWord[], char dic[][100], int size) {
	int low = 0, high = size - 1, mid;
	int flag = 0;
	int num = 0;
	while (low <= high) {
		num++;
		mid = low + (high - low) / 2;
		if (strcmp(findWord, dic[mid]) == 0) {
			flag = 1;
			break;
		}
		if (strcmp(findWord, dic[mid]) > 0) {
			low = mid + 1;
		}
		if (strcmp(findWord, dic[mid]) < 0) {
			high = mid - 1;
		}
	}
	printf("%d %d", flag, num);
}

int suoYin(char findWord[], char dic[][100], int size) {
	int i, j;
	int indexNum[27];
	char indexChar[27]="abcdefghijklmnopqrstuvwxyz";
	j = 0;
	for (i = 0; i < size; i++) {
		while (indexChar[j] < dic[i][0]&&j<26) {
			indexNum[j] = -1;
			j++;
		}
		if (indexChar[j] == dic[i][0]) {
			indexNum[j] = i;
			j++;
		}
	}
	indexNum[26] = size;
	int low, high, mid;
	int flag1 = 1;
	for (i = 0; i < 26; i++) {
		if (findWord[0] == indexChar[i]) {
			if (indexNum[i] == -1) {
				flag1 = 0;
			}
			else {
				low = indexNum[i];
				if (indexNum[i + 1] == -1) {
					high = indexNum[i + 2] - 1;
				}
				else {
					high = indexNum[i + 1] - 1;
				}
			}
			break;
		}
	}
	if (flag1 == 1) {
		int flag = 0;
		int num = 0;
		while (low <= high) {
			num++;
			mid = low + (high - low) / 2;
			if (strcmp(findWord, dic[mid]) == 0) {
				flag = 1;
				break;
			}
			if (strcmp(findWord, dic[mid]) > 0) {
				low = mid + 1;
			}
			if (strcmp(findWord, dic[mid]) < 0) {
				high = mid - 1;
			}
		}
		printf("%d %d", flag, num);
	}
	else {
		printf("0 0");
	}


	return 0;
}

void hashWay(char findWord[], char dic[][100], int size) {
	int i;
	int flag = 0;
	int num = 0;
	int findKey = hash(findWord);
	for (i = 0; i < size; i++) {
		if (hash(dic[i]) == findKey) {
			num++;
			if (strcmp(findWord, dic[i]) == 0) {
				flag = 1;
				break;
			}
			if (strcmp(findWord, dic[i]) < 0) {
				break;
			}
		}
	}
	printf("%d %d", flag, num);
	
}

int main()
{
	FILE *file;
	char dic[3500][100];
	//char buff[100];
	char findWord[100];
	int i=0;
	int size;
	int type;
	int wordLen;
	file = fopen("dictionary3000.txt", "r");
	while (fscanf(file, "%s", dic[i]) != EOF) {
		i++;
	}
	size = i;
	fclose(file);
	scanf("%s %d", findWord, &type);
	switch (type)
	{
	case 1://OK 8 fail 1
		shunXu(findWord, dic, size);
		break;
	case 2://OK 6 fail 4 3
		zheBan(findWord, dic, size);
		break;
	case 3://OK 7 fail 5
		suoYin(findWord, dic, size);
		break;
	case 4://fail 2 9
		hashWay(findWord, dic, size);
		break;
	default:
		break;
	}
	
	
	//for (i = 0; i < size; i++) {
	//	printf("%s\n", dic[i]);
	//}



	return 0;
}

