// graphSearch.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>


int visited[200];

void dfs(int graph[][200],int vNum, int v) {
	int w;
	int j;
	printf("%d ", v);
	visited[v] = 1;
	for (j = 0; j < vNum; j++) {
		if (graph[v][j] == 1 && visited[j] == 0) {
			dfs(graph, vNum, j);
		}
	}
	
}

void dfsTravel(int graph[][200], int vNum) {
	dfs(graph, vNum, 0);
	printf("\n");
}

void bfs(int graph[][200], int vNum, int v) {
	int j;
	int queue[200];
	int front, rear;
	front = rear = -1;
	printf("%d ", v);
	visited[v] = 1;
	rear++;
	queue[rear] = v;
	while (front != rear) {
		front++;
		v = queue[front];
		for (j = 0; j < vNum; j++) {
			if (graph[v][j] == 1 && visited[j] == 0) {
				printf("%d ", j);
				visited[j] = 1;
				rear++;
				queue[rear] = j;
			}
		}
	}

}


void bfsTravel(int graph[][200], int vNum) {
	int i;
	for (i = 0; i < vNum; i++) {
		if (visited[i] == 0) {
			bfs(graph, vNum, i);
		}
	}
	printf("\n");
}

int main()
{
	int graph[200][200] = {0};
	int vNum, eNum;
	int v1, v2;
	int i, j;
	int delV;
	scanf("%d %d", &vNum, &eNum);
	for (i = 0; i < eNum; i++) {
		scanf("%d %d", &v1, &v2);
		graph[v1][v2] = graph[v2][v1] = 1;
	}
	scanf("%d", &delV);
	for (i = 0; i < vNum; i++) {
		visited[i] = 0;
	}
	dfsTravel(graph, vNum);
	for (i = 0; i < vNum; i++) {
		visited[i] = 0;
	}
	bfsTravel(graph, vNum);
	for (i = 0; i < vNum; i++) {
		graph[i][delV] = graph[delV][i] = 0;
	}
	for (i = 0; i < vNum; i++) {
		visited[i] = 0;
	}
	visited[delV] = 1;
	dfsTravel(graph, vNum);
	for (i = 0; i < vNum; i++) {
		visited[i] = 0;
	}
	visited[delV] = 1;
	bfsTravel(graph, vNum);
    return 0;
}

