#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//typedefinition for making graph
typedef struct Graph{
	int size;
	int* node;
	int* indegree;
	int** matrix;
}_Graph;
typedef _Graph* Graph;

//function declaration for making graph
Graph CreateGraph(int* nodes, int n);
void insertEdge(Graph G, int a, int b);
void Topsort(Graph G, FILE* fp2);

//typedefinition for making queue
typedef struct Node* PtrToNode;
typedef PtrToNode Queue;
struct Node{
	int data;
	PtrToNode next;
};

//function declaration for making queue

//insertion function of Queue
void push(int x, Queue q){
	PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
	PtrToNode a = q;
	temp->next = NULL;
	temp->data = x;
	while(a->next!=NULL){
		a=a->next;
	}
	a->next = temp;
}

//deletion function of Queue
void pop(Queue q){
	PtrToNode temp = q->next;
	q->next = q->next->next;
	free(temp);
}

//return whether Queue is empty or not
bool empty(Queue q){
	return q->next==NULL;
}

//make empty Queue
Queue make(Queue q){
	q = (Queue)malloc(sizeof(struct Node));
	q->next = NULL;
	return q;
}

//return front element of Queue
int front(Queue q){
	return q->next->data;
}

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
		if(buffer=='\r'){
			fscanf(fp1, "%c", &buffer);
		}
		if(buffer=='\n'){
			break;
		}
	}
	Graph g = CreateGraph(arr, size);
        for(int i = 0; i < size; i++){
                for(int j = 0; j < size-1; j++){
                        if(arr[j] > arr[j+1]){
                                int temp = arr[j];
                                arr[j] = arr[j+1];
                                arr[j+1] = temp;
                        }
                }
        }
	Graph s = CreateGraph(arr, size);
	int a, b;
	while(fscanf(fp1, "%d-%d", &a, &b)!=EOF){
		insertEdge(g, a, b);
		insertEdge(s, a, b);
	}
	fprintf(fp2, "Adjacency Matrix\n  ");
	for(int i = 0; i < g->size; i++){
		fprintf(fp2, "%d ", g->node[i]);
	}
	fprintf(fp2, "\n");
        for(int i = 0; i < g->size; i++){
                fprintf(fp2, "%d ", g->node[i]);
		for(int j = 0; j < g->size; j++){
			fprintf(fp2, "%d ", g->matrix[i][j]);
		}
		fprintf(fp2, "\n");
        }
	fprintf(fp2, "\n\nTopSort Result : ");
	Topsort(s, fp2);
	return 0;	
}

//make no edge Graph
Graph CreateGraph(int* nodes, int n){
	Graph g = (Graph)malloc(sizeof(_Graph));
	g->size = n;
	g->node = (int*)malloc(sizeof(int)*n);
	g->indegree = (int*)malloc(sizeof(int)*n);
	g->matrix = (int**)malloc(sizeof(int*)*n);
	for(int i = 0; i < n; i++){
		g->node[i] = nodes[i];
		g->indegree[i] = 0;
		g->matrix[i] = (int*)malloc(sizeof(int)*n);
		for(int j = 0; j < n; j++){
			g->matrix[i][j] = 0;
		}
	}
	return g;
}

//insert new edge into Graph
void insertEdge(Graph g, int a, int b){
	int ra, rb;
	for(int i = 0; i < g->size; i++){
		if(g->node[i] == a){
			ra = i;
		}
		if(g->node[i] == b){
			rb = i;
		}
	}
	g->matrix[ra][rb] = 1;
	g->indegree[rb]++;
}

//topological sorting function
void Topsort(Graph g, FILE* fp2){
	Queue topo = NULL, result = NULL;
	topo = make(topo);
	result = make(result);

	for(int i = 0; i < g->size; i++){
		if(g->indegree[i]==0){
			push(i, topo);
		}
	}

	while(!empty(topo)){
		int now = front(topo);
		pop(topo);
		push(g->node[now], result);

		for(int i = 0; i < g->size; i++){
			if(g->matrix[now][i] == 1){
				g->indegree[i]--;
				if(g->indegree[i] == 0){
					push(i, topo);
				}
			}
		} 
	}

	while(!empty(result)){
		fprintf(fp2, "%d ", front(result));
		pop(result);
	}
}
