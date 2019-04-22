#include <stdio.h>

#define MAX 1000001

int arr[MAX] = { 0, };
int N, sort_arr[MAX];

void merge(int a[], int start, int mid, int end) {
	int s = start;
	int e = mid + 1;
	int arr_s = start;

	while (e<=end && s<=mid) {
		if (a[s] <= a[e]) {
			sort_arr[arr_s] = a[s];
			s++;
		}
		else {
			sort_arr[arr_s] = a[e];
			e++;
		}
		arr_s++;
	}

	if (s > mid) {
		for (int i = e; i <= end; i++) {
			sort_arr[arr_s] = a[i];
			arr_s++;
		}
	}
	else {
		for (int i = s; i <= mid; i++) {
			sort_arr[arr_s] = a[i];
			arr_s++;
		}
	}
	for (int i = start; i <= end; i++)
		a[i] = sort_arr[i];

}

void mergeSort(int a[], int start, int end) {
	if (start < end) {
		int middle = (start + end) / 2;
		mergeSort(a, start, middle);
		mergeSort(a, middle + 1, end);
		merge(a, start, middle, end);
	}
}

int main() {
	int i;

	scanf_s("%d", &N);

	for (i = 0; i < N; i++) {
		scanf_s("%d", &arr[i]);
	}

	mergeSort(arr, 0, N - 1);

	for (i = 0; i < N; i++) {
		printf("%d\n", arr[i]);
	}

	return 0;
}