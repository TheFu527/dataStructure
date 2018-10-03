// queue.cpp: 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <stdio.h>
#define MAXSIZE 1000

struct Custom {
	int id;
	int arrivetime;
};

struct Custom QUEUE[MAXSIZE];
int Front, Rear, Count;

void initQueue() {
	Front = 0;
	Rear = MAXSIZE - 1;
	Count = 0;
}

void enQueue(struct Custom item) {
	Rear = (Rear + 1) % MAXSIZE;
	QUEUE[Rear] = item;
	Count++;
}

void deQueue(int clock) {
	if (Count == 0)
		return;
	else {
		printf("%d : %d\n", QUEUE[Front].id, clock - QUEUE[Front].arrivetime);
		Count--;
		Front = (Front + 1) % MAXSIZE;
		return;
	}
}

int main() {
	int i, time, clock = 0, queuenum = 3, id = 1;
	initQueue();
	scanf("%d", &time);
	int cusnum;
	for (; ; clock++) {
		if (clock<time) {
			scanf("%d", &cusnum);
			for (i = 0; i<cusnum; i++) {
				struct Custom tempcus;
				tempcus.id = id++;
				tempcus.arrivetime = clock;
				enQueue(tempcus);
			}
			if (Count >= 28) {
				queuenum = 5;
			}
			else if (Count >= 21) {
				queuenum = 4;
			}
		}
		for (i = 0; i<queuenum; i++) {
			deQueue(clock);
		}
		if ((float)Count / queuenum<7.0 && queuenum >= 4) {
			queuenum--;
		}
		if (clock >= time && Count == 0)
			break;
	}
	return 0;
}
