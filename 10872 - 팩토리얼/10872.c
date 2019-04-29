#include <stdio.h>

int main() {
	int N;
	int num = 1;

	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
		num *= i;

	printf("%d", num);

	return 0;

}