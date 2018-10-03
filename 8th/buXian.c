// buXian.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>

#define MAX_INT 32767

//struct Edge {
//	int eNo;
//	int adjvex;
//	int weight;
//	struct Edge *next;
//};
//
//struct Ver {
//	int vNo;
//	struct Edge *link;
//};
//
//struct Ver graph[1100];
int graph[1100][1100];
int eNo[1100][1100];
int edges[1100];

void primMST(int r,int vNum) {
	int i, j, k;
	int minWeight[1100];
	int min;
	for (i = 0; i < vNum; i++) {
		minWeight[i] = graph[r][i];
		edges[i] = r;
	}
	minWeight[r] = 0;
	for (i = 1; i < vNum; i++) {
		min = MAX_INT;
		for (j = 0, k = 0; j < vNum; j++) {
			if (minWeight[j] != 0 && minWeight[j] < min) {
				min = minWeight[j];
				k = j;
			}
		}
		minWeight[k] = 0;
		for (j = 0; j < vNum; j++) {
			if (minWeight[j] != 0 && graph[k][j] < minWeight[j]) {
				minWeight[j] = graph[k][j];
				edges[j] = k;
			}
		}
	}
}

void path(int vNum,int eNum) {
	int i, j, size;
	int edgeMST[1100];
	int wghtSum = 0;
	primMST(0, vNum);
	j = 0;
	for (i = 0; i < vNum; i++) {
		if (graph[i][edges[i]] != MAX_INT) {
			edgeMST[j] = eNo[i][edges[i]];
			wghtSum += graph[i][edges[i]];
			j++;
		}
	}
	size = j;
	int temp;
	for (i = 0; i < size; i++) {
		for (j = size - 1; j > i; j--) {
			if (edgeMST[j] < edgeMST[j - 1]) {
				temp = edgeMST[j];
				edgeMST[j] = edgeMST[j - 1];
				edgeMST[j - 1] = temp;
			}
		}
	}
	printf("%d\n", wghtSum);
	for (i = 0; i < size; i++) {
		printf("%d ", edgeMST[i]);
	}
}


//void bulidEdge(int e, int v1, int v2, int weight) {
//	struct Edge *p, *q;
//	p = (struct Edge*)malloc(sizeof(struct Edge));
//	p->adjvex = v2;
//	p->weight = weight;
//	p->eNo = e;
//	p->next = NULL;
//	if (!graph[v1].link) {
//		graph[v1].link = p;
//	}
//	else {
//		q = graph[v1].link;
//		while (q->next) {
//			q = q->next;
//		}
//		q->next = p;
//	}
//}


int main()
{
	int vNum, eNum;
	int v1, v2, e, weight;
	int i, j;
	scanf("%d %d", &vNum, &eNum);
	for (i = 0; i < vNum; i++) {
		for (j = 0; j < vNum; j++) {
			graph[i][j] = MAX_INT;
		}
	}
	for (i = 0; i < eNum; i++) {
		scanf("%d %d %d %d", &e, &v1, &v2, &weight);
		//bulidEdge(e, v1, v2, weight);
		graph[v1][v2] = graph[v2][v1] = weight;
		eNo[v1][v2] = eNo[v2][v1] = e;
	}
	path(vNum, eNum);
	return 0;
}

