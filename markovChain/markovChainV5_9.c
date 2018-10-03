// markovChain.cpp: 定义控制台应用程序的入口点。
//

//V5.9 伪二次哈希探测法的开放寻址散列
//减少函数调用
//更改为数组
//减少函数间形参调用
//减少比较次数
//非二次幂


#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

#define MAXS 6300000		//全文最大字符数 文件字符数6279166
#define MAXOUT 3000000		//最大输出
#define MAXC 96				//单个单词字符数 最大95
#define MAXO 115			//前缀字符数
#define MAXH 1403641		//哈希数组 175447,350899, 701819, 1403641, 2807303, 5614657, 11229331

char buf[MAXS];				//储存文章的字符
char preArtcl[MAXOUT];		//存储预测的全文
char *predWord;				//指向预测w3的指针		
int len;					//文章总字符数
char *word1;
char *word2;
int n;						//输出文本数

							//Vector

#define MIN_LEN 1
#define EXPANED_VAL 1

typedef void *citerator;
typedef struct _cvector *cvector;

#ifndef __gnu_linux__
#define __func__ "unknown"
#define inline __forceinline
#endif

struct _cvector
{
	void *cv_pdata;
	size_t cv_len, cv_tot_len, cv_size;
};

cvector cvector_create(const size_t size)
{
	cvector cv = (cvector)malloc(sizeof(struct _cvector));

	cv->cv_pdata = malloc(MIN_LEN * size);
	cv->cv_size = size;
	cv->cv_tot_len = MIN_LEN;
	cv->cv_len = 0;

	return cv;
}

void cvector_pushback(const cvector cv, void *memb)
{
	if (cv->cv_len >= cv->cv_tot_len)
	{
		cv->cv_tot_len <<= EXPANED_VAL;
		cv->cv_pdata = realloc(cv->cv_pdata, cv->cv_tot_len * cv->cv_size);
	}

	memcpy((char *)cv->cv_pdata + cv->cv_len * cv->cv_size, memb, cv->cv_size);
	cv->cv_len++;
}

int cvector_val_at(const cvector cv, size_t index, void *memb)
{
	memcpy(memb, (char *)cv->cv_pdata + index * cv->cv_size, cv->cv_size);
	return 0;
}

//前缀的结构体
typedef struct _Value {
	char *w1;						//W1
	char *w2;						//W2
	short int predNum;					//预测单词数
	cvector prediction;				//预测
}Value;

Value hashArr[MAXH];

unsigned int BKDRHash(char *str) {
	unsigned int seedH = 1313131; // 31 131 1313 13131 131313 etc..
	unsigned int hash = 0;
	while (*str) {
		hash = hash * seedH + (*str++);
	}
	return hash;
}


double seed = 997;
double rrand() {
	double lambda = 3125.0;
	double m = 34359738337.0;
	double r;
	seed = fmod(lambda*seed, m); //要包含头文件#include <math.h>
	r = seed / m;
	return r;
}


char *linkWord(char *tail, char *w) {
	while (*w != '\0') {
		*tail = *w;
		++tail;
		++w;
	}
	*tail = ' ';
	++tail;
	*tail = '\0';
	return tail;
}

void createHash() {
	int i;
	char orign[MAXO];
	unsigned int hash;
	unsigned int hash2;
	char *w1;
	char *w2;

	for (i = 0; i < MAXH; ++i) {
		hashArr[i].predNum = -1;
	}

	i = 0;
	while (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\r' || buf[i] == '\0') {
		buf[i] = '\0';
		++i;
	}
	w1 = &buf[i];
	word1 = &buf[i];
	while (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\r' && buf[i] != '\0') {
		++i;
	}
	buf[i] = '\0';

	while (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\r' || buf[i] == '\0') {
		buf[i] = '\0';
		++i;
	}
	w2 = &buf[i];
	word2 = &buf[i];
	while (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\r' && buf[i] != '\0') {
		++i;
	}
	buf[i] = '\0';

	while (i != -1) {
		strcpy(orign, w1);
		strcat(orign, w2);

		hash = BKDRHash(orign);
		hash2 = 1 + hash % (MAXH - 1);
		hash = hash % MAXH;

		while (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\r' || buf[i] == '\0') {
			buf[i] = '\0';
			++i;
		}
		predWord = &buf[i];
		while (buf[i] != ' ' && buf[i] != '\n' && buf[i] != '\r' && buf[i] != '\0') {
			++i;
		}
		buf[i] = '\0';
		if (i == len - 1) {
			i = -1;
		}

		while ((hashArr[hash].predNum != -1)) {
			if (strcmp(w1, hashArr[hash].w1) == 0) {
				if (strcmp(w2, hashArr[hash].w2) == 0) {
					break;
				}
			}
			hash = (hash + hash2) % MAXH;
		}
		hashArr[hash].predNum += 1;
		if (hashArr[hash].predNum != 0) {
			cvector_pushback(hashArr[hash].prediction, &predWord);
		}
		else {
			hashArr[hash].w1 = w1;
			hashArr[hash].w2 = w2;
			hashArr[hash].prediction = cvector_create(sizeof(char*));
			cvector_pushback(hashArr[hash].prediction, &predWord);
		}

		w1 = w2;
		w2 = predWord;
	}

}

void markovPred() {
	int i;
	char *w1;
	char *w2;
	char orign[MAXO];
	unsigned int hash;
	unsigned int hash2;
	int wordNo;					//选取的预测词汇序号
	char *tail;

	w1 = word1;
	w2 = word2;

	tail = preArtcl;
	tail = linkWord(tail, w1);
	tail = linkWord(tail, w2);
	for (i = 0; i < n - 2; ++i) {
		strcpy(orign, w1);
		strcat(orign, w2);

		hash = BKDRHash(orign);
		hash2 = 1 + hash % (MAXH - 1);
		hash = hash % MAXH;

		while ((strcmp(w1, hashArr[hash].w1) != 0) || (strcmp(w2, hashArr[hash].w2) != 0)) {
			hash = (hash + hash2) % MAXH;
		}

		w1 = w2;
		if (hashArr[hash].predNum == 0) {
			wordNo = 0;
		}
		else {
			wordNo = (int)(rrand() * ((hashArr[hash].predNum) + 1));
		}
		cvector_val_at(hashArr[hash].prediction, wordNo, &w2);
		if (strcmp(w2, "MARKOVEND") == 0) {
			return;
		}
		tail = linkWord(tail, w2);
	}
}


int main()
{
	scanf("%d", &n);

	FILE *fp1;
	fp1 = fopen("article.txt", "r");
	len = fread(buf, 1, MAXS, fp1);
	fclose(fp1);

	int i;
	char end[12] = " MARKOVEND ";
	for (i = 0; i < 12; ++i) {
		buf[len + i] = end[i];
	}
	len += 11;
	buf[len] = '\0';

	createHash();
	markovPred();
	fp1 = fopen("markov.txt", "w");
	fwrite(preArtcl, strlen(preArtcl) - 1, 1, fp1); //数据块大小
	fclose(fp1);


	return 0;
}

