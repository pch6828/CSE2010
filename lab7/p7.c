#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//fill S with 0
void init(int* S){
  	for (int i = 1;i < (sizeof(S) / sizeof(int));i++)
      		S[i] = 0;
}

//find ver.1 not path compression
int find1(int x, int* S){
   	while (S[x] > 0)
      		x = S[x];

   	return x;
}

//find ver.2 path compression
int find2(int x, int* S){
   	if (S[x] <= 0)
      		return x;

   	return S[x] = find2(S[x], S);
} 

//union disjoint set a and b
void Union(int* S, int a, int b){
   	a = find2(a, S);
   	b = find2(b, S);
   	if (S[a] > S[b])
      		S[a] = b;

   	else{
     		if (S[a] == S[b])
         		S[a]--;

      		S[b] = a;
	}
}

//print maze's shape
void PrintMaze(char** m, int n, FILE* fp2){
   	for (int i = 0;i < n;i++){
		for (int j = 0;j < n;j++)
			fprintf(fp2, "%c", m[i][j]);
      		fprintf(fp2, "\n");
   	}
}

int main(){
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	srand((unsigned int)time(NULL));

	int n;
	fscanf(fp1, "%d", &n);
	int cnt = n * n;

	int* S = (int*)malloc(sizeof(int)*(n*n + 1));
	char** maze = (char**)malloc(sizeof(char*)*(2 * n + 1));

	for (int i = 0;i < 2 * n + 1;i++){
		maze[i] = (char*)malloc(sizeof(char)*(2 * n + 1));
		for (int j = 0;j < 2 * n + 1;j++){
			if (i % 2 == 0 && j % 2 == 0){
				maze[i][j] = '+';
			}else if (i % 2 == 0){
            			maze[i][j] = '-';
			}else if (j % 2 == 0){
            			maze[i][j] = '|';
			}else{
				maze[i][j] = ' ';
			}
		}
	}
	for (int i = 0;i < 2 * n + 1;i++){
		for (int j = 0;j < 2 * n + 1;j++){
         		if (i % 2 == 0 && j % 2 == 0){
				maze[i][j] = '+';
			}else if (i % 2 == 0){
            			maze[i][j] = '-';
			}else if (j % 2 == 0){
            			maze[i][j] = '|';
			}else{
            			maze[i][j] = ' ';
			}
      		}
   	}	

   	maze[1][0] = ' ';
  	maze[2 * n - 1][2 * n] = ' ';

   	while (cnt != 1){
      		int x = rand() % (2 * n - 1) + 1;
		int y = rand() % (2 * n - 1) + 1;
		if (maze[x][y] == '-'){
         		int x1 = x - 1, x2 = x + 1;
			int a = n * (x1 - 1) / 2 + (y + 1) / 2, b = n * (x2 - 1) / 2 + (y + 1) / 2;
			if (find2(a, S) != find2(b, S)){
            			maze[x][y] = ' ';
			        Union(S, a, b);
			}
		}else if (maze[x][y] == '|'){
         		int y1 = y - 1, y2 = y + 1;
         		int a = n * (x - 1) / 2 + (y1 + 1) / 2, b = n * (x - 1) / 2 + (y2 + 1) / 2;
         		if (find2(a, S) != find2(b, S)){
            			maze[x][y] = ' ';
            			Union(S, a, b);

      			}

      		}

   		cnt = 0;
      		for (int i = 1;i <= n * n;i++){
         		if (S[i] <= 0){
            			cnt++;
			}
      		}
   	}

   	PrintMaze(maze, 2 * n + 1, fp2);
   	free(S);

   	for (int i = 0;i < 2 * n + 1;i++){
      		free(maze[i]);
	}
   	free(maze);
}

