#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define order 3

//typedefinition for making B-tree
typedef struct B_node* B_ptr;
struct B_node{
	int n_key;
	B_ptr child[order];
	int key[order-1];
};

//enum definition for making B-tree
//Success == no upkey
//InsertIt == upkey
enum Status{Success, InsertIt};

//function declaration for making B-tree
void insert(int key);
int searchPos(int, int*, int);
enum Status insert_with_upkey(B_ptr, int, int*, B_ptr*);
void inorder(B_ptr ptr, FILE* fp2);

B_ptr root = NULL;

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	
	char cmd[2];
	while(fscanf(fp1, "%s", cmd)!=EOF){
		if(!strcmp(cmd, "i")){
			int num;
			fscanf(fp1, "%d", &num);
			insert(num);
		}else if(!strcmp(cmd, "p")){
			inorder(root, fp2);
			fprintf(fp2, "\n");
		}
	}
	fclose(fp1);
	fclose(fp2);	
}

//this function just call insert_with_upkey();
//if there is upkey, then it make new root(split it);
void insert(int key){
	B_ptr newnode;
	int upkey;
	enum Status status;

	status = insert_with_upkey(root, key, &upkey, &newnode);

	if(status == InsertIt){
		B_ptr uproot = root;
		root = calloc(1, sizeof(struct B_node));
		root->n_key = 1;
		root->key[0] = upkey;
		root->child[0] = uproot;
		root->child[1] = newnode;
	}
}

//searching where Key should be inserted
int searchpos(int key, int* key_arr, int n){
        int pos = 0;
        while(pos<n&&key>key_arr[pos]){
                pos++;
        }
        return pos;
}

//this function is invoked by insert(), and this will work at almost of insertion situation
//if this return InsertIt, there is upkey
enum Status insert_with_upkey(B_ptr ptr, int key, int* upkey, B_ptr* newnode){
	B_ptr newptr, lastptr;
	int pos, i, n, splitpos, newkey, lastkey;
	enum Status status;

	if (ptr==NULL){
		*newnode = NULL;
		*upkey = key;
		return InsertIt;
	}

	n = ptr->n_key;
	pos = searchpos(key, ptr->key, n);
	status = insert_with_upkey(ptr->child[pos], key, &newkey, &newptr);

	if(status!=InsertIt){
		return status;
	}

	if(n<order-1){
		pos = searchpos(newkey, ptr->key, n);
		for(i = n; i > pos; i--){
			ptr->key[i] = ptr->key[i-1];
			ptr->child[i+1] = ptr->child[i];
		}
		ptr->key[pos] = newkey;
		ptr->child[pos+1] = newptr;
		ptr->n_key+=1;
		return Success;
	}

	if(pos == order - 1){
		lastkey = newkey;
		lastptr = newptr;
	}else{
		lastkey = ptr->key[order-2];
		lastptr = ptr->child[order-1];
		
		for(i = order-2; i > pos; i--){
			ptr->key[i] = ptr->key[i-1];
			ptr->child[i+1] = ptr->child[i];
		}
		ptr->key[pos] = newkey;
		ptr->child[pos+1] = newptr;
	}
	splitpos = (order-1)/2;
	*upkey = ptr->key[splitpos];
	*newnode = calloc(1, sizeof(struct B_node));
	
	ptr->n_key = splitpos;
	(*newnode)->n_key = order-1-splitpos;
	
	for(i = 0; i < (*newnode)->n_key; i++){
		(*newnode)->child[i] = ptr->child[i+splitpos+1];
		if(i<(*newnode)->n_key-1){
			(*newnode)->key[i] = ptr->key[i+splitpos+1];
		}else{
			(*newnode)->key[i] = lastkey;
		}
	}

	(*newnode)->child[(*newnode)->n_key] = lastptr;
	return InsertIt;
}

//inorder traversal ver. B-tree
void inorder(B_ptr ptr, FILE* fp2){
	if(ptr==NULL){
		return;
	}else{
		for(int i = 0; i < ptr->n_key;i++){
			inorder(ptr->child[i], fp2);
			fprintf(fp2, "%d ",ptr->key[i]);
		}
		inorder(ptr->child[ptr->n_key], fp2);
	}
}
