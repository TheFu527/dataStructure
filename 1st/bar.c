#include<stdio.h>

int maxChar(int charNum[26]) {
	int i;
	int max = charNum[0];
	for (i = 1; i < 26; i++) {
		if (max < charNum[i]) {
			max = charNum[i];
		}
	}
	return max;
}

int main()
{
	int charNum[26] = {0};
	char str;
	int i,j;
	int maxCh;
	while ((str=getchar()) != EOF) {
		if (str >= 97 && str <= 122)
		{
			charNum[(int)str - 97]++;
		}
	}
	maxCh = maxChar(charNum);
	for (i = 0; i < maxCh; i++) {
		for (j = 0; j < 26; j++) {
			if (charNum[j] == (maxCh-i)) {
				printf("*");
				charNum[j]--;
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("abcdefghijklmnopqrstuvwxyz\n");
    return 0;
}

