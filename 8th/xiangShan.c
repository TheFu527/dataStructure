// xiangShan.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
struct Edge {
	int eNo;
	int adjvex;
	int weight;
	struct Edge *next;
};

struct Ver {
	int vNo;
	struct Edge *link;
};

struct Ver graph[1100];
int visited[1100];
int paths[1100];

void printPath(int size) {
	int i;
	for (i = 0; i < size; i++) {
		printf("%d ", paths[i]);
	}
	printf("\n");
}

void eDFS(int v, int level, int end) {
	struct Edge  *p;
	if (v == end) {
		printPath(level);
		return;
	}
	if (!visited[v]) {
		visited[v] = 1;
		for (p = graph[v].link; p != NULL; p = p->next){
			paths[level] = p->eNo;
			eDFS(p->adjvex, level + 1, end);
		}
		visited[v] = 0;
		return;
	}
	
}

void dfsTravel(int vNum) {
	int i;
	for (i = 0; i < vNum; i++) {
		visited[i] = 0;
	}
	eDFS(0, 0, vNum - 1);
}

void bulidEdge(int e, int v1, int v2) {
	struct Edge *p, *q;
	p = (struct Edge*)malloc(sizeof(struct Edge));
	p->adjvex = v2;
	p->weight = 1;
	p->eNo = e;
	p->next = NULL;
	if (!graph[v1].link) {
		graph[v1].link = p;
	}
	else {
		q = graph[v1].link;
		while (q->next) {
			q = q->next;
		}
		q->next = p;
	}
}

int main()
{
	int vNum, eNum;
	int v1, v2, e;
	int i;
	scanf("%d %d", &vNum, &eNum);
	for (i = 0; i < vNum; i++) {
		graph[i].vNo = i;
		graph[i].link = NULL;
	}
	for (i = 0; i < eNum; i++) {
		scanf("%d %d %d", &e, &v1, &v2);
		bulidEdge(e, v1, v2);
		bulidEdge(e, v2, v1);
	}
	dfsTravel(vNum);
	return 0;
}

