#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//type definition for making BST

typedef struct TreeNode* Tree;
typedef struct TreeNode{
	int value;
	Tree left, right;
}TreeNode;

//function declaration for makeing BST
Tree insert(int x, Tree tree, FILE* fp2);
Tree delete(int x, Tree tree, FILE* fp2);
Tree find(int x, Tree tree);
Tree findmax(Tree tree);
void inorder(Tree tree, FILE* fp2);
void preorder(Tree tree, FILE* fp2);
void postorder(Tree tree, FILE* fp2);

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	char cmd[3];
	int x;
	Tree tree;
	while(fscanf(fp1, "%s", cmd)!=EOF){
		if(strcmp(cmd, "i")==0){
			fscanf(fp1, "%d", &x);
			tree = insert(x, tree, fp2);
		}else if(strcmp(cmd, "d")==0){
                        fscanf(fp1, "%d", &x);  
			delete(x, tree, fp2);
		}else if(strcmp(cmd, "f")==0){
                        fscanf(fp1, "%d", &x);  
                        Tree temp = find(x, tree);
			if(temp){
				fprintf(fp2, "%d is in the tree\n", x);
			}else{
				fprintf(fp2, "%d is not in the tree\n", x);
			}
                }else if(strcmp(cmd, "pi")==0){
			fprintf(fp2, "pi - ");  
                        inorder(tree, fp2);
			fprintf(fp2, "\n");
                }else if(strcmp(cmd, "pr")==0){
                        fprintf(fp2, "pr - ");
                        preorder(tree, fp2);
			fprintf(fp2, "\n");
                }else if(strcmp(cmd, "po")==0){
                        fprintf(fp2, "po - ");
                        postorder(tree, fp2);
			fprintf(fp2, "\n");
                }
	}
}

//insert x into BST, if x already exists, just print error message
Tree insert(int x, Tree tree, FILE* fp2){
	if(tree == NULL){
		tree = (Tree)malloc(sizeof(struct TreeNode));
		tree->value = x;
		tree->left = NULL;
		tree->right = NULL;
	}else if(tree->value > x){
		tree->left = insert(x, tree->left, fp2);
	}else if(tree->value < x){
		tree->right = insert(x, tree->right, fp2);
	}else{
		fprintf(fp2, "%d already exists.\n", x);
	}
	return tree;
}

//delete x from BST, if x doesn't exist, just print error message
Tree delete(int x, Tree tree, FILE* fp2){
	if (tree==NULL){
		fprintf(fp2, "Deletion failed. %d does not exist.\n", x);
	}else if(tree->value > x){
		tree->left = delete(x, tree->left, fp2);
	}else if(tree->value < x){
		tree->right = delete(x, tree->right, fp2);
	}else if(tree->left&&tree->right){
		Tree temp = findmax(tree->left);
		tree->value = temp->value;
		tree->left = delete(tree->value, tree->left, fp2); 
	}else{
		Tree temp = tree;
		if(tree->left==NULL){
			tree = tree->right;
		}else if(tree->right == NULL){
			tree = tree->left;
		}
		free(temp);
	}
	return tree;
}

//find x from BST, if x doesn't exist, return NULL
Tree find(int x, Tree tree){
	if(tree == NULL){
		return NULL;
	}
	if(tree->value > x){
		return find(x, tree->left);
	}else if (tree->value < x){
		return find(x, tree->right);
	}else{
		return tree;
	}
}

//find max value from BST, if tree is empty, return NULL
Tree findmax(Tree tree){
	if(!tree){
		return tree;
	}
	while(tree->right!=NULL){
		tree = tree->right;
	}
	return tree;
}

//inorder traversal function
void inorder(Tree tree, FILE* fp2){
	if(!tree){
		return;
	}else{
		inorder(tree->left, fp2);
		fprintf(fp2, "%d ", tree->value);
		inorder(tree->right, fp2);
	}
}

//preorder traversal function
void preorder(Tree tree, FILE* fp2){
        if(!tree){
                return;
        }else{
                fprintf(fp2, "%d ", tree->value);
                preorder(tree->left, fp2);
                preorder(tree->right, fp2);
        }
}

//postorder traversal function
void postorder(Tree tree, FILE* fp2){
        if(!tree){
                return;
        }else{
                postorder(tree->left, fp2);
                postorder(tree->right, fp2);
                fprintf(fp2, "%d ", tree->value);
        }
}

