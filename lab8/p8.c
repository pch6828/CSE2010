#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

//typedefinition for making max heap
struct HeapStruct{
	int capacity, size;
	int *elements;
};

typedef struct HeapStruct* Heap;

//function declaration for making max heap
Heap make(Heap h, int capacity);
int isfull(Heap h);
int ishere(Heap h, int x, int idx);
void insert(Heap h, int x, FILE* fp2);
void find(Heap h, int x, FILE* fp2);
void print(Heap h, FILE* fp2);

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	int capacity;
	fscanf(fp1, "%d", &capacity);

	Heap h = make(h, capacity);
	char cmd[2];
	
	while( fscanf(fp1, "%s", cmd)!=EOF ){
		if(!strcmp(cmd, "i")){
			int x;
			fscanf(fp1, "%d", &x);
			insert(h, x, fp2);
		}else if(!strcmp(cmd, "f")){
                        int x;
                        fscanf(fp1, "%d", &x);
                        find(h, x, fp2);
		}else if(!strcmp(cmd, "p")){
			print(h, fp2);
		}
	}
}

//make empty heap
Heap make(Heap h, int capacity){
	h = (Heap)malloc(sizeof(struct HeapStruct));
	h->capacity = capacity;
	h->elements = (int*)malloc(sizeof(int)*(capacity+1));
	h->size = 0;

	return h;
}

//check whether heap is empty
int isfull(Heap h){
	return h->size == h->capacity;
}

//check whether x is in the heap
//this function will be used in find() and insert()
int ishere(Heap h, int x, int idx){
	/*
	for(int i = 1; i <= h->size; i++){
		if(h->elements[i]==x){
			return 1;
		}
	}
	return 0;
	*/

	if(idx > h->size){
		return false;
	}else if(h->elements[idx]==x){
		return true;
	}else{
		return ishere(h, x, idx*2)||ishere(h, x, idx*2+1);
	}
}

//insert x into heap
//if heap is full, print error message
//if heap already has x, print error message
void insert(Heap h, int x, FILE* fp2){
	if(isfull(h)){
		fprintf(fp2, "heap is full\n");
		return;
	}else if(ishere(h, x, 1)){
		fprintf(fp2, "%d is already in the heap\n", x);
		return;
	}else{
		int i;
		for(i = ++h->size; i/2>0&&h->elements[i/2] < x; i/=2){
			h->elements[i] = h->elements[i/2];
		}
		h->elements[i] = x;
		fprintf(fp2, "insert %d\n", x);
	}
}

//if heap has x, print message
//if heap doesn't has x, print other message
void find(Heap h, int x, FILE* fp2){
	if(ishere(h, x, 1)){
                fprintf(fp2, "%d is in the heap\n", x);
                return;
	}else{
                fprintf(fp2, "%d is not in the heap\n", x);
                return;
	}
}

//print all of elements in heap by index order
void print(Heap h, FILE* fp2){
	for(int i = 1; i <=h->size; i++){
		fprintf(fp2, "%d ", h->elements[i]);
	}
	fprintf(fp2, "\n");
}

