#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<limits.h>

//typedefinition for making HashTable
typedef struct HashTbl* HashTable;

struct HashTbl {
	int TableSize;
	int* list;
};

//function declaration for making HashTable
HashTable make(int size);
void insert(HashTable h, int value, int solution, FILE* fp2);
void delete(HashTable h, int value, int solution, FILE* fp2);
int find(HashTable h, int value, int solution);
void print(HashTable h, FILE* fp2);
int hash(int value, int size, int i, int solution);

int main()
{
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	int test;
	fscanf(fp1, "%d", &test);
	while (test--) {
		char slt[15];
		fscanf(fp1, "%s", slt);
		int solution;
		if (!strcmp(slt, "Linear")) {
			solution = 1;
		}
		else if (!strcmp(slt, "Quadratic")) {
			solution = 2;
		}
		else if (!strcmp(slt, "Double")) {
			solution = 3;
		}
		fprintf(fp2, "%s\n", slt);
		int tblsize;
		fscanf(fp1, "%d", &tblsize);
		HashTable h = make(tblsize);
		char cmd[2];
		int x;
		while (true) {
			fscanf(fp1, "%s", cmd);
			if (!strcmp(cmd, "i")) {
				fscanf(fp1, "%d", &x);
				insert(h, x, solution, fp2);
			}
			else if (!strcmp(cmd, "d")) {
				fscanf(fp1, "%d", &x);
				delete(h, x, solution, fp2);

			}
			else if (!strcmp(cmd, "f")) {
				fscanf(fp1, "%d", &x);
				int idx = find(h, x, solution);

				if (idx != -1) {
					fprintf(fp2, "%d\n", idx);
				}
				else {
					fprintf(fp2, "Not found\n");
				}
			}
			else if (!strcmp(cmd, "p")) {
				print(h, fp2);

			}
			else if (!strcmp(cmd, "q")) {
				fprintf(fp2, "\n");
				break;
			}
		}
		free(h->list);
		free(h);
	}
}

//make empty HashTable
HashTable make(int size) {
	HashTable h = (HashTable)malloc(sizeof(struct HashTbl));
	h->TableSize = size;
	h->list = (int*)malloc(sizeof(int) * size);
	int i;
	for (i = 0; i < size; i++) {
		h->list[i] = 0;
	}
	return h;
}

//insert value into HashTable, if HashTable is full, just return, if HashTable already has value, print "Already exists"
void insert(HashTable h, int value, int solution, FILE* fp2) {
	if (find(h, value, solution)!=-1) {
		fprintf(fp2, "Already exists\n");
		return;
	}

	int i = 0;
	while (h->list[hash(value, h->TableSize, i, solution)]>0) {
		i++;
		if (i >= h->TableSize) {
			return;
		}
	}
	h->list[hash(value, h->TableSize, i, solution)] = value;
	fprintf(fp2, "Inserted %d\n", value);
}

//delete value into HashTable, if HashTable doesn't have value, print "x not exists"
void delete(HashTable h, int value, int solution, FILE* fp2) {
	if (find(h, value, solution)==-1) {
		fprintf(fp2, "%d not exists\n", value);
		return;
	}
	int i = 0;
	h->list[find(h, value, solution)] = -1;
	fprintf(fp2, "Deleted %d\n", value);
}

//find value at HashTable and return its index
int find(HashTable h, int value, int solution) {
	int i = 0;
	while (h->list[hash(value, h->TableSize, i, solution)] != value && h->list[hash(value, h->TableSize, i, solution)] != 0) {
		i++;
		if (i >= h->TableSize) {
			return -1;
		}
	}
	if (h->list[hash(value, h->TableSize, i, solution)] == value) {
		return hash(value, h->TableSize, i, solution);
	}
	else {
		return -1;
	}
}

//print all components of HashTable
void print(HashTable h, FILE* fp2) {
	int i;
	for (i = 0; i < h->TableSize; i++) {
		if (h->list[i] > 0) {
			fprintf(fp2, "%d ", h->list[i]);
		}
		else {
			fprintf(fp2, "0 ");
		}
	}
	fprintf(fp2, "\n");
}

//hash function for different solution
int hash(int value, int size, int i, int solution) {
	if (solution == 1) {
		return (value % size + i) % size;
	}
	else if(solution == 2){
		return (value % size + i * i) % size;
	}
	else if (solution == 3) {
		return (value % size + i * (7 - value % 7)) % size;
	}
}
