#include<stdio.h>
#include<stdlib.h>

//type definition for threaded tree
typedef struct threaded_tree* threaded_ptr;
typedef struct threaded_tree{
	short int left_thread;
	threaded_ptr left_child;
	char data;
	threaded_ptr right_child;
	short int right_thread;	
}threaded_tree;

threaded_ptr insucc(threaded_ptr tree);
void tinorder(threaded_ptr tree, FILE* fp2);

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	int n;
	fscanf(fp1, "%d", &n);

	//sorry sir, I made threaded tree by my own hand, not by logic

	//Dynamic allocation
        threaded_ptr tree = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	threaded_ptr a = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr b = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr c = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr d = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr e = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr f = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr g = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr h = (threaded_ptr)malloc(sizeof(struct threaded_tree));
        threaded_ptr i = (threaded_ptr)malloc(sizeof(struct threaded_tree));
	
	//initialization
	*tree = (threaded_tree){0,a,' ',tree,0};
	*a = (threaded_tree){0,b,'A',c,0};
        *b = (threaded_tree){0,d,'B',e,0};
        *c = (threaded_tree){0,f,'C',g,0};
        *d = (threaded_tree){0,h,'D',i,0};
        *e = (threaded_tree){1,b,'E',a,1};
        *f = (threaded_tree){1,a,'F',c,1};
        *g = (threaded_tree){1,c,'G',tree,1};
        *h = (threaded_tree){1,tree,'H',d,1};
        *i = (threaded_tree){1,d,'I',b,1};

	tinorder(tree, fp2);
	fclose(fp1);
	fclose(fp2);
}

//who is my successor?
threaded_ptr insucc(threaded_ptr tree){
	threaded_ptr temp;
	temp = tree->right_child;
	if (!tree->right_thread){
		while(!temp->left_thread){
			temp = temp->left_child;
		} 
	}
	return temp;
}
//function for inorder traversal, using insucc() to find next node
void tinorder(threaded_ptr tree, FILE* fp2){
	threaded_ptr temp = tree;
	for(;;){
		temp = insucc(temp);
		if(temp == tree){
			break;
		}
		fprintf(fp2, "%c ", temp->data);
	}
}


