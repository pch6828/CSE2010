#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//type definition for creating AVLTree
struct AVLNode;
typedef struct AVLNode* Position;
typedef struct AVLNode* AVLTree;

struct AVLNode{
	int data, height;
	Position left;
	Position right;
};

//function declaration for creation AVLTree
int MAX(int a, int b);
int height(Position P);

Position Singleleftrotation(Position K2);
Position Singlerightrotation(Position K2);
Position Doubleleftrotation(Position K2);
Position Doublerightrotation(Position K2);
Position find(AVLTree tree, int x);

Position insert(AVLTree tree, int x, FILE* fp2);
void inorder(AVLTree tree, FILE* fp2);

int main(){
	FILE* fp1 = fopen("input.txt","r");
	FILE* fp2 = fopen("output.txt","w");
	int num;
	AVLTree tree = NULL;
	while(fscanf(fp1, "%d", &num)!=EOF){
		if(!find(tree, num)){
			tree = insert(tree, num, fp2);
			inorder(tree, fp2);
		}else{
			fprintf(fp2, "%d already in the tree!", num);
		}
		fprintf(fp2, "\n");
	}
}

//Since we cannot include "algorithm", I made MAX() function
int MAX(int a, int b){
	if(a>b){
		return a;
	}else{
		return b;
	}
}

//return Node's height, if Node is NULL, return -1
int height(Position P){
	if(P==NULL){
		return -1;
	}else{
		return P->height;
	}
}

//if tree's balance is broken by inserting Node to left-left, use this function
Position Singleleftrotation(Position K2){
	Position K1;
	K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = MAX(height(K2->left), height(K2->right))+1;
	K1->height = MAX(height(K1->left), height(K1->right))+1;
	return K1;
}

//if tree's balance is broken by inserting Node to right-right, use this function
Position Singlerightrotation(Position K2){
        Position K1;
        K1 = K2->right;
        K2->right = K1->left;
        K1->left = K2;
        K2->height = MAX(height(K2->left), height(K2->right))+1;
        K1->height = MAX(height(K1->left), height(K1->right))+1;
        return K1;
}

//if tree's balance is broken by inserting Node to left-right, use this function
Position Doubleleftrotation(Position K2){
	K2->left = Singlerightrotation(K2->left);
	return Singleleftrotation(K2);
}

//if tree's balance is broken by inserting Node to right-left, use this function
Position Doublerightrotation(Position K2){
        K2->right = Singleleftrotation(K2->right);
        return Singlerightrotation(K2);
}

//insert node, if node is already in the tree, print error message
//BUT, Since I used find() function, actually this won't be invoked if node is already in the tree
Position insert(AVLTree tree, int x, FILE* fp2){
	if(tree==NULL){
		tree = (AVLTree)malloc(sizeof(struct AVLNode));
		tree->data = x;
		tree->left = tree->right = NULL;
		tree->height = 0;
		return tree;
	}else if(tree->data > x){
		tree->left = insert(tree->left, x, fp2);
		if(height(tree->left) - height(tree->right) == 2){
			if(x<tree->left->data){
				tree = Singleleftrotation(tree);
			}else{
				tree = Doubleleftrotation(tree);
			}
		}
	}else if(tree->data < x){
		tree->right = insert(tree->right, x, fp2);
                if(height(tree->left) - height(tree->right) == -2){
                        if(x>tree->right->data){
                                tree = Singlerightrotation(tree);
                        }else{
                                tree = Doublerightrotation(tree);
                        }
                }

	}else{
		fprintf(fp2, "%d already in the tree!\n", x);
	}
	tree->height = MAX(height(tree->left), height(tree->right)) + 1;
	return tree;
}

//find node's address, if it cannot find, return NULL
Position find(AVLTree tree, int x){
	if(tree == NULL){
		return NULL;
	}
	else if(tree->data == x){
		return tree;
	}else if(tree->data > x){
		return find(tree->left, x);
	}else{
		return find(tree->right, x);
	}
}

//inorder traversal recursive function
void inorder(AVLTree tree, FILE* fp2){
	if(tree == NULL){
		return;
	}else{
		inorder(tree->left, fp2);
		fprintf(fp2, "%d(%d) ", tree->data, tree->height);
		inorder(tree->right, fp2);
	}
}

