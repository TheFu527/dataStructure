#include<stdio.h>

int expand(char str[], char strCopy[], int i, int j) {
	int p;
	for (p = str[i - 1] + 1; p < str[i + 1]; p++) {
		strCopy[j] = p;
		j++;
	}
	return j;
}

int main()
{
	char str[199];
	char strCopy[199];
	int i, j;
	scanf("%s", str);
	for (i = 0, j = 0; str[i] != '\0'; i++) {
		if (str[i] == '-' && i != 0 && str[i + 1] != '\0') {
			if (str[i - 1] >= 65 && str[i + 1] <= 90) {
				j = expand(str, strCopy, i, j);
			}
			else if(str[i - 1] >= 97 && str[i + 1] <= 122) {
				j = expand(str, strCopy, i, j);
			}
			else if (str[i - 1] >= 48 && str[i + 1] <= 57) {
				j = expand(str, strCopy, i, j);
			}
			else {
				strCopy[j] = str[i];
				j++;
			}
		}
		else {
			strCopy[j] = str[i];
			j++;
		}
	}
	strCopy[j] = '\0';
	printf("%s", strCopy);
	return 0;
}

