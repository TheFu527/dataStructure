#include <stdio.h>

double jieCheng(int n) {
	double result = 1.0;
	int i;
	for (i = 1; i < n; i++) {
		result *= i;
	}
	return result;
}

double jiShuChengFa(int n) {
	double result = 1.0;
	int i;
	for (i = 1; i <= n; i++) {
		result *= (2 * i - 1);
	}
	return result;
}

int main()
{
	double e;
	int n = 2;
	scanf("%lf", &e);
	double piDiv = 1.0 + (jieCheng(n) / jiShuChengFa(n));
	double pi = piDiv * 2;
	double temp = 2.0;
	n++;
	while (pi - temp >= e) {
		temp = piDiv * 2;
		piDiv += (jieCheng(n) / jiShuChengFa(n));
		pi = piDiv * 2;
		n++;
	}
	printf("%d %8.7lf", n-1, pi);
    return 0;
}

