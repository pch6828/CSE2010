#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//typedefinition to make Stack

typedef struct Node* PtrToNode;
typedef PtrToNode Stack;

struct Node{
	int number;
	PtrToNode next;
};

void push(int x, Stack s);
void pop(Stack s, FILE* fp2);
Stack make(Stack s);

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	int cnt;
	fscanf(fp1, "%d", &cnt);
	
	Stack s = make(s);
	while(cnt--){
		char cmd[5];
		fscanf(fp1, "%s", cmd);
		if(strcmp(cmd, "push")==0){
			int n;
			fscanf(fp1, "%d", &n);
			push(n, s);
		}else{
			pop(s, fp2);
		}
	}
	fclose(fp1);
	fclose(fp2);
}

//make empty stack
Stack make(Stack s){
	s = (Stack)malloc(sizeof(struct Node));
	s->next = NULL;
	return s;
}

//push x into stack s
void push(int x, Stack s){
	PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
	temp->next = s->next;
	temp->number = x;
	s->next = temp;
}

//pop top of the stack, if stack is empty, print "Empty"
void pop(Stack s, FILE* fp2){
	if(s->next == NULL){
		fprintf(fp2, "Empty\n");
		return;
	}

	PtrToNode temp = s->next;
	s->next = s->next->next;
	fprintf(fp2, "%d\n", temp->number);
	free(temp);
}
