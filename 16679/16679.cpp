#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_DICE_NUM 21
#define MAX_TASK_NUM 1002

struct dice_struct {

	int dice_num = 0;							//총 주사위 개수
	int target = 0;								//합산 목표 값

	int max_p_count = 0;						//최대 확률일때의 target을 넘는 경우의 수
	int throw_dice_num = 0;						//최대 확률을 위해 던져야할 주사위 수

	int dice_value[MAX_DICE_NUM] = { 0, };		//각 주사위의 값
	int throw_dice[MAX_DICE_NUM] = { 0, };		//던질 주사위 표시

	int sort_dice_value[MAX_DICE_NUM] = { 0, }; //각 주사위값 정렬

};

long long table[MAX_DICE_NUM][MAX_DICE_NUM*6];

void sorting_dice(int T_num);
int compare(const void* a, const void* b);
int dice_sum(int t, int n);
int check_probability_per_dice_num(int n, int k, int sum);
long long check_count_per_dice_num_and_k(int n, int k);

struct dice_struct T[MAX_TASK_NUM];
long long count = 0;

int main() {
	int T_num = 0;
	long long max_count = 0;
	int max_p_dice_num = 1;
	long long count = 0;
	//입력
	scanf_s("%d", &T_num); // 테스트 케이스
	for (int i = 0; i < T_num; i++) {
		scanf_s("%d %d", &T[i].dice_num, &T[i].target); //주사위개수, 목표값 입력받기
		for (int j = 0; j < T[i].dice_num; j++) {
			scanf_s("%d", &T[i].dice_value[j]); //주사위 각 수 입력받기
		}
	}

	//sort_dice_value 정렬
	sorting_dice(T_num);

	for (int i = 0; i < T_num; i++) {
		max_count = 0;
		max_p_dice_num = 1;

		//이미 주사위 합이 타겟을 넘었을때
		if (T[i].target <= dice_sum(i, T[i].dice_num)) {
			long long res = 1;

			for (int i2 = 0; i2 < T[i].dice_num; i2++) // 6에 n승을 하고 출력
				res *= 6;
			printf("%lld\n", res);

			for (int i2 = 0; i2 < T[i].dice_num; i2++) { // 모든 주사위 0으로 출력
				if (i2 != 0)
					printf(" ");
				printf("%d",0);
			}
		}

		//주사위 합이 타켓을 못 넘을때
		else {
			for (int j = 1; j < T[i].dice_num + 1; j++) {// 주사위를 한개씩 던짐.
				//check_probability_per_dice_num(j, T[i].target, dice_sum(i, T[i].dice_num) - dice_sum(i, j));
				count = check_count_per_dice_num_and_k(j, T[i].target - (dice_sum(i, T[i].dice_num)-dice_sum(i, j)) );
				int a = j - max_p_dice_num;
				if ( (long long)(max_count*pow(6.0,a)) < count) {
					max_count = count;
					max_p_dice_num = j;
				}
				count = 0;
			}

			long long res2 = 1;
			for (int i2 = 0; i2 < T[i].dice_num - max_p_dice_num; i2++)
				res2 *= 6;
			printf("%lld\n", (long long)max_count * res2);

			for (int k = 0; k < max_p_dice_num; k++) //서치를 통해 굴려야하는 주사위의 위치를 체크
			{
				for (int k2 = 0; k2 < T[i].dice_num; k2++) {
					if ((T[i].sort_dice_value[k] == T[i].dice_value[k2]) && (T[i].throw_dice[k2] == 0)) {
						T[i].throw_dice[k2] = 1;
						break;
					}
				}
			}

			for (int k = 0; k < T[i].dice_num; k++) { // 1 0 1 0 찍기
				if (k != 0)
					printf(" ");
				if (T[i].throw_dice[k])
					printf("1");
				else
					printf("0");
			}
		}
		if(i!=T_num-1)
			printf("\n");
	}

	return 0;
}

int compare(const void* a, const void* b) {
	int num1 = *(int*)a;
	int num2 = *(int*)b;

	if (num1 < num2)
		return -1;
	if (num1 > num2)   
		return 1;

	return 0;
}

void sorting_dice(int T_num) {

	for (int i = 0; i < T_num; i++) {
		for (int j = 0; j < T[i].dice_num; j++) {
			T[i].sort_dice_value[j] = T[i].dice_value[j];
		}
		qsort(T[i].sort_dice_value, T[i].dice_num, sizeof(int), compare);
	}
}

int dice_sum(int t, int n) {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		sum += T[t].sort_dice_value[i];
	}
	return sum;
}
/*
int check_probability_per_dice_num(int n, int k, int sum) {
	//n : 굴려야하는 주사위 개수
	//k : 넘어야하는 목표값
	//sum : 현재 주사위 합

	if (sum >= k && n == 0) {
		count++;
		return 0;
	}
	else if (n == 0)
		return 0;
	else if (n != 0 && sum >= k) {
		count += (long long)(pow(6.0, n));
		return 0;
	}

	for (int i = 1; i < 7; i++) {
		check_probability_per_dice_num(n - 1, k, sum + i);
	}
	return 0;
}*/


long long check_count_per_dice_num_and_k(int n, int k) {
	long long count = 0;
	memset(table, 0, sizeof(table));

	for (int i = 1; i <= 6; i++)
		table[1][i] = 1;

	for (int var_n = 2; var_n <= n; var_n++) {
		for (int var_k = var_n; var_k <= (var_n * 6); var_k++)
		{
			if (var_k - 6 >= 1) {
				for (int i = var_k - 1; i >= var_k - 6; i--)
					table[var_n][var_k] += table[var_n - 1][i];
			}
			else {
				for (int i = var_n - 1; i <= var_k - 1; i++)
					table[var_n][var_k] += table[var_n - 1][i];
			}
		}
	}


	for (int i = k; i <= n * 6; i++)
		count += table[n][i];

	return count;
}
