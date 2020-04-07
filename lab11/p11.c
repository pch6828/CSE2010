#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>

//typedefinition for making graph
typedef struct graph{
	int size;
	int* node;
	int* prev;
	int* distance;
	int** matrix;
}_Graph;
typedef _Graph* Graph;

//function declaration for making graph
Graph CreateGraph(int* nodes, int n);
void insertEdge(Graph g, int a, int b, int w);

//heap element definition
typedef struct{
	int dist, now, prev;
}pos;

//typedefinition for making heap
struct HeapStruct{
	int capacity, size;
	pos* elements;
};
typedef struct HeapStruct* Heap;

//function declaration for making heap;
Heap make(Heap h, int capacity);
pos deletemin(Heap h);
void insert(pos x, Heap h);
bool isempty(Heap h);

//function declaration for dijkstra algorithm
void dijkstra(Graph g, int start, int end, FILE* fp2);
void tracking(Graph g, FILE* fp2, int end);

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	int size = 0;
	int* arr = (int*)malloc(size);
	
	while(true){
		int temp;
		char buffer;
		fscanf(fp1, "%d", &temp);
		fscanf(fp1, "%c", &buffer);
		size++;
		arr = realloc(arr, size*sizeof(int));
		arr[size-1] = temp;
		if(buffer == '\r'){
			fscanf(fp1, "%c", &buffer);
		}
		if(buffer == '\n'){
			break;
		}
	}
	Graph g = CreateGraph(arr, size);
	while(true){
		int a, b, w;
		char buffer;
		fscanf(fp1, "%d-%d-%d", &a, &b, &w);
		fscanf(fp1, "%c", &buffer);
		insertEdge(g, a, b, w);
		if(buffer == '\r'){
                        fscanf(fp1, "%c", &buffer);
                }
                if(buffer == '\n'){
                        break;
                }
	}
	int start, end;
	fscanf(fp1, "%d%d", &start, &end);
	dijkstra(g, start, end, fp2);
}

//make no edge graph
Graph CreateGraph(int* nodes, int n){
	Graph g = (Graph)malloc(sizeof(_Graph));
	g->size = n;
	g->node = (int*)malloc(sizeof(int)*n);
	g->prev = (int*)malloc(sizeof(int)*n);
	g->distance = (int*)malloc(sizeof(int)*n);
	g->matrix = (int**)malloc(sizeof(int*)*n);
	for(int i = 0; i < n; i++){
		g->node[i] = nodes[i];
		g->prev[i] = -1;
		g->distance[i] = INT_MAX;
		g->matrix[i] = (int*)malloc(sizeof(int)*n);
		for(int j = 0; j < n; j++){
			g->matrix[i][j] = INT_MAX;
		}
	}
	return g;
}

//insert edge into graph
void insertEdge(Graph g, int a, int b, int w){
	int ra, rb;
	for(int i = 0; i < g->size; i++){
		if(g->node[i] == a){
			ra = i;
		}
		if(g->node[i] == b){
			rb = i;
		}
	}
	if(g->matrix[ra][rb]>w){
		g->matrix[ra][rb] = w;
	}
}

//make empty heap
Heap make(Heap h, int capacity){
	h = (Heap)malloc(sizeof(struct HeapStruct));
	h->capacity = capacity;
	h->elements = (pos*)malloc(sizeof(pos)*(capacity+1));
	h->size = 0;
	return h;
}

//delete minimum element of heap
pos deletemin(Heap h){
	int i, child;
	pos minelement, lastelement;
	minelement = h->elements[1];
	lastelement = h->elements[h->size--];

	for(i = 1; i*2 <=h->size; i = child){
		child = i*2;
		if(child!=h->size&&h->elements[child+1].dist < h->elements[child].dist){
			child++;
		}
		if(lastelement.dist>h->elements[child].dist){
			h->elements[i] = h->elements[child];
		}else{
			break;
		}
	}
	h->elements[i] = lastelement;
	return minelement;
}

//insert one element into heap
void insert(pos x, Heap h){
	int i;
	for(i = ++h->size; h->elements[i/2].dist > x.dist; i/=2){
		h->elements[i] = h->elements[i/2];
	}
	h->elements[i] = x;
}

//check whether heap is empty
bool isempty(Heap h){
	return h->size == 0;
}

//function for dijkstra algorithm
void dijkstra(Graph g, int a, int b, FILE* fp2){
        int start, end;
        for(int i = 0; i < g->size; i++){
                if(g->node[i] == a){
                        start = i;
                }
                if(g->node[i] == b){
                        end = i;
                }
        }
	//printf("%d %d", start, end);
	Heap h = NULL;
	h = make(h, 2000);
	g->distance[start] = 0;
	pos temp;
	temp.dist = 0;
	temp.now = start;
	temp.prev = -1;
	insert(temp, h);

	while(!isempty(h)){
		pos now = deletemin(h);
		g->prev[now.now] = now.prev;
		for(int i = 0; i < g->size; i++){
			if(g->matrix[now.now][i]!=INT_MAX&&g->matrix[now.now][i]+now.dist < g->distance[i]){
				g->distance[i] = g->matrix[now.now][i] + now.dist;
				temp.dist = g->distance[i];
				temp.now = i;
				temp.prev = now.now;
				insert(temp, h);
			}
		}
	}
	if(g->distance[end] == INT_MAX){
		fprintf(fp2, "no path");
	}else{
		tracking(g, fp2, end);
	}
}

//function for printion shortest path
void tracking(Graph g, FILE* fp2, int end){
	if(end==-1){
		return;
	}else{
		tracking(g, fp2, g->prev[end]);
		fprintf(fp2, "%d ", g->node[end]);
	}
}

