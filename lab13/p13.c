#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

void mergesort_recursive(int* arr, int l, int r, FILE* fp2);
void mergesort_iterative(int* arr, int size, FILE* fp2);
void merge(int* arr, int l, int mid, int r);

int main()
{
	FILE* fp1 = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");

	int size;
	fscanf(fp1, "%d", &size);

	int* arr1 = (int*)malloc(sizeof(int) * size);
	int* arr2 = (int*)malloc(sizeof(int) * size);
	fprintf(fp2, "input :\n");
	for (int i = 0; i < size; i++) {
		fscanf(fp1, "%d", &arr1[i]);
		fprintf(fp2, "%d ", arr1[i]);
		arr2[i] = arr1[i];
	}
	fprintf(fp2, "\n\niterative :\n");
	mergesort_iterative(arr2, size, fp2);
	fprintf(fp2, "\n\nrecursive :\n");
	mergesort_recursive(arr1, 0, size - 1, fp2);
}

void mergesort_recursive(int* arr, int l, int r, FILE* fp2) {
	if (l >= r) {
		return;
	}
	int mid = (l + r) / 2;

	mergesort_recursive(arr, l, mid, fp2);
	mergesort_recursive(arr, mid + 1, r, fp2);
	merge(arr, l, mid, r);
	int i;
	for (i = l; i <= r; i++) {
		fprintf(fp2, "%d ", arr[i]);
	}
	fprintf(fp2, "\n");
}

void merge(int* arr, int l, int mid, int r) {
	int* sorted = malloc(sizeof(int) * (r + 1));
	int i = l;
	int j = mid + 1;
	int k = l;

	while (i <= mid && j <= r) {
		if (arr[i] < arr[j]) {
			sorted[k++] = arr[i++];
		}
		else {
			sorted[k++] = arr[j++];
		}
	}

	if (i > mid) {
		for (int i = j; i <= r; i++) {
			sorted[k++] = arr[i];
		}
	}
	if (j > r) {
		for (int j = i; j <= mid; j++) {
			sorted[k++] = arr[j];
		}
	}
	for (int i = l; i <= r; i++) {
		arr[i] = sorted[i];
	}
}

void mergesort_iterative(int* arr, int size, FILE* fp2) {
	int l = 0, r = size - 1;
	for (int i = 2; i <= r * 2; i *= 2) {
		l = 0;
		for (int j = l; j <= r; j += i) {
			int left = j, right = j + i - 1;
			if (right >= size) {
				right = size - 1;
			}
			int mid = left + i / 2 - 1;
			merge(arr, left, mid, right);
			for (int k = left; k <= right; k++) {
				fprintf(fp2, "%d ", arr[k]);
			}
			fprintf(fp2, "\n");
		}
	}
}
