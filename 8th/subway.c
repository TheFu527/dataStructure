// subway.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include<stdio.h>
#include<string.h>

#define MAXNUM 512	 //地铁最大站数
#define MAXLEN 16		 //地铁站名的最大长度
#define INFINITY  32767

typedef struct _Station { //车站信息
	char sName[MAXLEN];  	//车站名
	int isChange; 		 //是否为换乘站，0-否，1-换乘
}Station;

typedef struct _Weight {
	int wei; 		//两个站间的权重，即相差站数，缺省为1
	int lno;  		//两个顶点所在的线号
}Weight;

Station station[MAXNUM];  		//地铁网络图顶点数组
Weight graph[MAXNUM][MAXNUM]; 	//网络图权重数组，邻接矩阵
int sPath[MAXNUM];				//最短路径数组
int vNum = 0; 	//实际地铁总站数
//sscanf()

void initMap() {
	FILE *fp;
	fp = fopen("bgstations.txt", "r");
	int lineNum;
	int lineNo, stationNum;
	int i, j, k, l;

	for (i = 0; i < MAXNUM; i++) {
		for (j = 0; j < MAXNUM; j++) {
			graph[i][j].wei = INFINITY;
			graph[i][j].lno = -2;
			if (i == j) {
				graph[i][j].wei = 0;
				graph[i][j].lno = 0;
			}
		}
	}
	k = 0;
	fscanf(fp, "%d", &lineNum);
	for (i = 0; i < lineNum; i++) {
		fscanf(fp, "%d %d", &lineNo, &stationNum);
		//printf("线路%d 车站量%d\n", lineNo, stationNum);
		for (j = 0; j < stationNum; j++) {
			fscanf(fp, "%s %d", &(station[k].sName), &(station[k].isChange));
			if (station[k].isChange == 1) {
				for (l = 0; l < k; l++) {
					if (strcmp(station[k].sName, station[l].sName) == 0) {
						graph[k][l].wei = graph[l][k].wei = 0;
						graph[k][l].lno = graph[l][k].lno = -1;
					}
				}
			}
			if (j == stationNum - 1 && strcmp(station[k - j].sName, station[k].sName) == 0) {
				graph[k][k - j].wei = graph[k - j][k].wei = 0;
				graph[k][k - j].lno = graph[k - j][k].lno = 0;

			}
			if (j != 0) {
				graph[k][k - 1].wei = graph[k - 1][k].wei = 1;
				graph[k][k - 1].lno = graph[k - 1][k].lno = lineNo;
			}
			graph[k][k].lno = lineNo;
			k++;
		}

	}
	vNum = k;
	fclose(fp);
}

void dijkstra(int  v0) {
	int i, j, v, minweight;
	int wfound[MAXNUM] = { 0 }; //用于标记从v0到相应顶点是否找到最短路径，0未找到，1找到
	int sWeight[MAXNUM];//v0到相应顶点最小权重数组

	for (i = 0; i < vNum; i++){  //初始化数组Sweight和Spath
		sWeight[i] = graph[v0][i].wei;
		sPath[i] = v0;
	} 
	sWeight[v0] = 0;
	wfound[v0] = 1;
	for (i = 0; i < vNum - 1; i++) {  //迭代VNUM-1次
		minweight = INFINITY;
		for (j = 0; j < vNum; j++)   //找到未标记的最小权重值顶点 
			if (!wfound[j] && (sWeight[j] < minweight)) {
				v = j;
				minweight = sWeight[v];
			}
		wfound[v] = 1;	//标记该顶点为已找到最短路径
		for (j = 0; j < vNum; j++) //找到未标记顶点且其权值大于v的权值+(v,j)的权值，更新其权值
			if (!wfound[j] && (minweight + graph[v][j].wei < sWeight[j])) {
				sWeight[j] = minweight + graph[v][j].wei;
				sPath[j] = v;  //记录前驱顶点
			}
	}
}


int main()
{
	int i, j;
	char startStat[MAXLEN];
	char endStat[MAXLEN];
	int startNo;
	int endNo;
	initMap();
	//for (i = 0; i < vNum; i++) {
	//	for (j = i; j < vNum; j++) {
	//		if (graph[i][j].wei == 1) {
	//			printf("连接：No.%d %s-----%s\n", graph[i][j].lno, station[i].sName, station[j].sName);
	//		}
	//		if (graph[i][j].wei == 0) {
	//			printf("换乘或环路：%s-----%s\n", station[i].sName, station[j].sName);
	//		}
	//	}
	//}
	scanf("%s", &startStat);
	scanf("%s", &endStat);
	int flag1 = 0;
	int flag2 = 0;
	for (i = 0; i < vNum; i++) {
		if (strcmp(startStat, station[i].sName) == 0) {
			startNo = i;
			flag1 = 1;
		}
		if (strcmp(endStat, station[i].sName) == 0) {
			endNo = i;
			flag2 = 1;
		}
		if (flag1 == 1 && flag2 == 1) {
			break;
		}
	}
	dijkstra(endNo);
	int mNum;
	i = startNo;
	mNum = 0;
	printf("%s-", station[startNo].sName);
	while (sPath[i] != endNo) {
		if (graph[i][sPath[i]].lno == -1&&mNum!=0) {
			printf("%d(%d)", graph[i][i].lno, mNum);
			printf("-%s-", station[sPath[i]].sName);
			mNum = 0;
		}
		if (graph[i][sPath[i]].lno > 0) {
			mNum++;
		}
		//printf("%s---", station[sPath[i]].sName);
		i = sPath[i];
		
	}
	mNum++;
	printf("%d(%d)", graph[i][i].lno, mNum);
	printf("-%s", station[endNo].sName);
	return 0;
}

