#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//typedefinition to make Stack

typedef struct Node* PtrToNode;
typedef PtrToNode Stack;

struct Node{
	int c;
	PtrToNode next;
};

void push(int x, Stack s);
void pop(Stack s);
char top(Stack s);
Stack make(Stack s);

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	char str[101];
	fscanf(fp1, "%s", str);

	char ans[101];
	int idx = 0;

	Stack s = make(s);
	fprintf(fp2, "Infix Form : ");
	//make PostFix Form
	for(int i = 0; str[i]!='#';i++){
		fprintf(fp2, "%c", str[i]);
	
		if(str[i] >'0'&&str[i]<='9'){
			ans[idx++] = str[i];
		}else if(str[i]=='('){
			push(str[i], s);
		}else if(str[i]=='+'||str[i]=='-'){
			while(s->next!=NULL&&top(s)!='('){
				ans[idx++] = top(s);
				pop(s);
			}
			push(str[i], s);
		}else if(str[i] == '*' ||str[i]=='/'||str[i]=='%'){
                        while(s->next!=NULL&&top(s)!='('&&top(s)!='-'&&top(s)!='+'){
                                ans[idx++] = top(s);
                                pop(s);
                        }
                        push(str[i], s);
		}else if(str[i] == ')'){
                        while(s->next!=NULL&&top(s)!='('){
                                ans[idx++] = top(s);
                                pop(s);
                        }
                        pop(s);
		}
	}
	while(s->next !=NULL){
		ans[idx++] = top(s);
		pop(s);
	}
	ans[idx] = '\0';
	fprintf(fp2, "\nPostfix Form : %s\nEvaluation Result : ", ans);
	
	//Evaluate
	for(int i = 0; i < strlen(ans); i++){
		if(ans[i]>'0'&&ans[i]<='9'){
			push(ans[i]-'0', s);
		}else{
			int a = top(s);
			pop(s);
			int b = top(s);
			pop(s);

			if(ans[i]=='+'){
				push(a+b, s);
			}else if(ans[i]=='-'){
				push(b-a, s);
			}else if(ans[i]=='/'){
				push(b/a, s);
			}else if(ans[i]=='%'){
				push(b%a, s);
			}else if(ans[i]=='*'){
				push(a*b, s);
			}
		}
	}
	fprintf(fp2, "%d", top(s));	
	fclose(fp2);
	fclose(fp1);
}

//make empty stack
Stack make(Stack s){
	s = (Stack)malloc(sizeof(struct Node));
	s->next = NULL;
	return s;
}

//show top of the stack
char top(Stack s){
	return s->next->c;
}

//push x into stack s
void push(int x, Stack s){
	PtrToNode temp = (PtrToNode)malloc(sizeof(struct Node));
	temp->next = s->next;
	temp->c = x;
	s->next = temp;
}

//pop top of the stack, if stack is empty, just return
void pop(Stack s){
	if(s->next == NULL){
		return;
	}

	PtrToNode temp = s->next;
	s->next = s->next->next;
	free(temp);
}
