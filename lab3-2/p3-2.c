#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//typedefinition to make Queue

typedef struct Node* PtrToNode;
typedef PtrToNode Queue;

struct Node{
	int size;
        int number;
        PtrToNode next;
};

void push(int x, Queue s, FILE* fp2);
void pop(Queue s, FILE* fp2);
Queue make(Queue s);

int main(){
        FILE* fp1 = fopen("input.txt", "r");
        FILE* fp2 = fopen("output.txt", "w");

        int cnt;
        fscanf(fp1, "%d", &cnt);

        Queue s = make(s);
        while(cnt--){
                char cmd[5];
                fscanf(fp1, "%s", cmd);
                if(strcmp(cmd, "enQ")==0){
                        int n;
                        fscanf(fp1, "%d", &n);
                        push(n, s, fp2);
                }else{
                        pop(s, fp2);
                }
        }
	fclose(fp1);
	fclose(fp2);
}

//make empty Queue
Queue make(Queue s){
        s = (Queue)malloc(sizeof(struct Node));
        s->next = NULL;
	s->size = 0;
        return s;
}

//push x into Queue s, if Queue is full, print "Full"
void push(int x, Queue s, FILE* fp2){
        PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
        PtrToNode a = s;
	temp->next = NULL;
	temp->number = x;
	if(s->size == 100){
		fprintf(fp2, "Full\n");
		return;
	}
	while(a->next!=NULL){
		a = a->next;
	}
	a->next = temp;
	s->size++;
}

//pop front of the Queue, if Queue is empty, print "Empty"
void pop(Queue s, FILE* fp2){
        if(s->next == NULL){
                fprintf(fp2, "Empty\n");
                return;
        }

        PtrToNode temp = s->next;
        s->next = s->next->next;
        fprintf(fp2, "%d\n", temp->number);
        free(temp);
	s->size--;
}
    
