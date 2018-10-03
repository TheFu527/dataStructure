// sort.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>

void swap(int *p, int *q) {
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}


int selectionSort(int arr[], int len)
{
	int i, j;
	int num = 0;
	for (i = 0; i < len - 1; i++)
	{
		int min = i;
		for (j = i + 1; j < len; j++) {
			num++;
			if (arr[j] < arr[min]) {
				min = j;
			}
		}

		swap(&arr[min], &arr[i]);
	}
	return num;
}

int bubbleSort(int arr[], int len) {
	int i, j;
	int num = 0;
	int flag = 1;
	for (i = len-1; i > 0; i--) {
		if (flag == 1) {
			flag = 0;
			for (j = 0; j < i; j++) {
				num++;
				if (arr[j] > arr[j + 1]) {
					swap(&arr[j], &arr[j + 1]);
					flag = 1;
				}
			}
		}

	}
	return num;
}

int adjust(int k[], int i, int n) {
	int j, temp;
	int num = 0;
	temp = k[i];
	j = 2 * i + 1;
	while (j < n) {
		if (j < n - 1 && k[j] < k[j + 1])
			j++;
		num++;
		if (temp >= k[j])
			break;
		k[(j - 1) / 2] = k[j];
		j = 2 * j + 1;
	}
	k[(j - 1) / 2] = temp;
	return num;
}

int heapSort(int arr[], int len) {
	int i;
	int num = 0;
	for (i = len / 2 - 1; i >= 0; i--)
		num += adjust(arr, i, len);
	for (i = len - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		num += adjust(arr, 0, i);
	}
	return num;
}

int mergeNum = 0;
void merge(int arr[], int reg[], int start, int end) {
	if (start >= end)
		return;
	int len = end - start, mid = (len >> 1) + start;
	int start1 = start, end1 = mid;
	int start2 = mid + 1, end2 = end;
	merge(arr, reg, start1, end1);
	merge(arr, reg, start2, end2);
	int k = start;
	while (start1 <= end1 && start2 <= end2) {
		mergeNum++;
		reg[k++] = arr[start1] < arr[start2] ? arr[start1++] : arr[start2++];
	}
	while (start1 <= end1)
		reg[k++] = arr[start1++];
	while (start2 <= end2)
		reg[k++] = arr[start2++];
	for (k = start; k <= end; k++)
		arr[k] = reg[k];
}

int mergeSort(int arr[], int len) {
	int tmp[200];
	merge(arr, tmp, 0, len - 1);
	return mergeNum;
}

int quickNum = 0;
void quickSort(int k[], int left, int right) {
	if (left >= right) {
		return;
	}
	int i, last;
	if (left < right) {
		last = left;
		for (i = left + 1; i <= right; i++) {
			quickNum++;
			if (k[i] < k[left]) {
				swap(&k[++last], &k[i]);
			}
		}
		swap(&k[left], &k[last]);
		quickSort(k, left, last - 1);
		quickSort(k, last + 1, right);
	}
}

int main()
{
	int a[200];
	int size;
	int type;
	int i;
	int biJiaoNum = 0;
	scanf("%d %d", &size, &type);
	for (i = 0; i < size; i++) {
		scanf("%d", &a[i]);
	}
	switch (type)
	{
	case 1://OK
		biJiaoNum = selectionSort(a, size);
		break;
	case 2:
		biJiaoNum = bubbleSort(a, size);
		break;
	case 3:
		biJiaoNum = heapSort(a, size);
		break;
	case 4://OK
		biJiaoNum = mergeSort(a, size);
		break;
	case 5://OK
		quickSort(a, 0, size - 1);
		biJiaoNum = quickNum;
		break;
	default:
		break;
	}
	for (i = 0; i < size; i++) {
		printf("%d ", a[i]);
	}
	printf("\n%d", biJiaoNum);

	return 0;
}

