#include<stdio.h>

int main()
{
	FILE *inFile, *outFile;
	int i = 0;
	char str[99];
	char chr;
	inFile = fopen("fcopy.in", "r");
	outFile = fopen("fcopy.out", "w");
	while ((chr = fgetc(inFile)) != EOF) {
		str[i] = chr;
		i++;
	}
	str[i] = '\0';
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\t') {
			fputc(' ', outFile);
		}
		else {
			fputc(str[i], outFile);
		}
		if (str[i] == '\t' || str[i] == ' ') {
			while (str[i + 1] == '\t' || str[i + 1] == ' ') {
				i++;
			}
		}
	}
	fclose(inFile);
	fclose(outFile);
	return 0;
}

