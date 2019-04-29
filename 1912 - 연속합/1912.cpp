#include <stdio.h>

#define MAX 100001

int N;
int arr[MAX] = { 0, };

int find_MAX() {
	int max=-1001;
	int tmp = 0;

	for (int i = 0; i < N; i++) {
		tmp += arr[i];
		if (tmp > max) {
			max = tmp;
		}
		if (tmp < 0)
			tmp = 0;
	}

	return max;
}

int main() {
	
	scanf_s("%d", &N);
	for (int i = 0; i < N; i++)
		scanf_s("%d", &arr[i]);

	printf("%d", find_MAX());

	return 0;

}