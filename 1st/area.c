#include<stdio.h>

int max(int a, int b) {
	return (a > b) ? a : b;
}
int min(int a, int b) {
	return (a < b) ? a : b;
}

int area(int aX1, int aX2, int bX1, int bX2, int aY1, int aY2, int bY1, int bY2) {
	int maxAX = max(aX1, aX2);
	int minAX = min(aX1, aX2);
	int maxBX = max(bX1, bX2);
	int minBX = min(bX1, bX2);
	int maxAY = max(aY1, aY2);
	int minAY = min(aY1, aY2);
	int maxBY = max(bY1, bY2);
	int minBY = min(bY1, bY2);

	if (min(maxAX, maxBX) - max(minAX, minBX) <= 0 || min(maxAY, maxBY) - max(minAY, minBY) <= 0)
		return 0;
	return (min(maxAX, maxBX) - max(minAX, minBX))*(min(maxAY, maxBY) - max(minAY, minBY));

}

int main()
{
	int aX1, aX2, bX1, bX2, aY1, aY2, bY1, bY2;
	scanf("%d%d%d%d", &aX1, &aY1, &aX2, &aY2);
	scanf("%d%d%d%d", &bX1, &bY1, &bX2, &bY2);
	printf("%d", area(aX1, aX2, bX1, bX2, aY1, aY2, bY1, bY2));
	return 0;
}

