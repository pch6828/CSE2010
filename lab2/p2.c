#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Type Definition
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef struct
{
	int studentID;
	char* studentName;
}ElementType;

struct Node
{
	ElementType element;
	PtrToNode next;
};

//Function Declaration
int Insert(ElementType X, List L);
int Delete(int id, List L);
Position Find(int id, List L);
void PrintList(List L, FILE* fp2);

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void DeleteList(List L);

int main()
{
	List l;
	l = MakeEmpty(l);
	FILE* fp = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	
	while(1){
		char cmd;
		//Variable for checking whether print current list or not
		int chk = 0;
		
		fscanf(fp, "%c ", &cmd);
		
		if(cmd == 'i'){
			int id;
			char name1[31], name2[31];
			
			//input
			fscanf(fp, "%d%s%s", &id, name1, name2);
			
			//creating new element;
			ElementType temp;
			temp.studentID = id;
			temp.studentName = (char*)malloc(strlen(name1)+1+strlen(name2)+1);
			strcpy(temp.studentName, name1);
			strcat(temp.studentName, " ");
			strcat(temp.studentName, name2);
			
			//check whether insertion success or failed
			if(Insert(temp, l)==1){
				fprintf(fp2, "Insertion Success : %d\n", temp.studentID);
				chk = 1;
			}else{
				fprintf(fp2, "Insertion Failed. ID %d already exists.\n", temp.studentID);
			}
		}else if(cmd == 'p'){
			PrintList(l, fp2);
			DeleteList(l);
			return 0;
		}else if(cmd == 'd'){
			int id;
			fscanf(fp, "%d", &id);
			
			//check whether deletion success or failed
			if(Delete(id, l)==1){
				fprintf(fp2, "Deletion Success : %d\n", id);
				chk = 1;
			}else{
				fprintf(fp2, "Deletion Failed : Student ID %d is not in the list\n", id);
			}
		}else if(cmd == 'f'){
			int id;
			fscanf(fp, "%d", &id);
			Position P = Find(id, l);
			
			//chck whether find success or failed (if failed, P == NULL)
			if(P){
				fprintf(fp2, "Find Success : %d %s\n", P->element.studentID, P->element.studentName);
			}else{
				fprintf(fp2, "Find %d Falied. There is no student ID\n", id); 
			}
		}
		
		//Printing current list
		if(chk){
                        Position P = l->next;
                        fprintf(fp2, "Current List > ");
                        while(P!=NULL){
                                fprintf(fp2, "%d %s", P->element.studentID, P->element.studentName);
                                P = P->next;
                                if(P!=NULL){
                                        fprintf(fp2, "-");
                                }
                        }
                        fprintf(fp2, "\n");
		}
	}
	fclose(fp);
	fclose(fp2);
}

int Insert(ElementType X, List L){
	PtrToNode temp;
	temp = (List)malloc(sizeof(struct Node));
        temp->element.studentID = X.studentID;
        temp->element.studentName = (char*)malloc(strlen(X.studentName)+1);
        strcpy(temp->element.studentName, X.studentName);
        temp->next = NULL;

	if(IsEmpty(L)==1){
		L->next = temp;
	}else{
		Position P;
		P = L;
		while(P->next!=NULL){
			if(P->next->element.studentID==X.studentID){
				free(X.studentName);
				return 0;			
			}else if(P->next->element.studentID>X.studentID){
				break;
			}
			P = P->next;
		}
		temp->next = P->next;
		P->next = temp;	
	}
	return 1;
}
int Delete(int id, List L){
	Position P = L;
                while(P->next!=NULL){
                        if(P->next->element.studentID==id){
                        	List temp = P->next;
				P->next = P->next->next;
				free(temp->element.studentName);
				free(temp);
			        return 1;                      
                        }
                        P = P->next;
                }
        return 0;

}

Position Find(int id, List L){
        Position P = L;
                while(P->next!=NULL){
                        if(P->next->element.studentID==id){
                                return P->next;
                        }
                        P = P->next;
                }
        return NULL;

}
void PrintList(List L, FILE* fp2){
	Position P = L->next;
        fprintf(fp2, "-----LIST-----\n");
        while(P!=NULL){
        	fprintf(fp2, "%d %s\n", P->element.studentID, P->element.studentName);
                P = P->next;
	}
	fprintf(fp2, "--------------");
}

List MakeEmpty(List L){
	L = (List)malloc(sizeof(struct Node));
	L->next = NULL;
	return L;
}
int IsEmpty(List L){
	return L->next == NULL;
}
int IsLast(Position P, List L){
	return P->next == NULL;
}
void DeleteList(List L){
	Position P, temp;
	P = L->next;
	L->next = NULL;
	while(P!=NULL){
		temp = P->next;
		free(P->element.studentName);
		free(P);
		P = temp;
	}
}

