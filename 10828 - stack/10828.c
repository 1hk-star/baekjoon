#include <stdio.h>

#define MAX 10001


void push(int i);
int pop();
int size();
int empty();
int fun_top();

int strcmp(char* s1, char* s2);
int strlen(char* s1);


char str[MAX][15];
int str_int[MAX] = { 0, };

int stack[MAX];
int top=0;


int main(void) {
	int N, i,j;
	char c;

	scanf("%d", &N);
	getchar();
	for (i = 0; i < N; i++) {
		//gets(str[i]);
		scanf("%s", str[i]);
		if (strcmp(str[i], "push")) {
			scanf("%d", &str_int[i]);
			getchar();
		}
	}
	
	for (i = 0; i < N; i++) {
		j = 0;
		if (strcmp(str[i], "push")) {
			push(str_int[i]);
		}
		else if (strcmp(str[i], "pop")) {
			printf("%d\n",pop());
		}
		else if (strcmp(str[i], "size")) {
			printf("%d\n", size());
		}
		else if (strcmp(str[i], "empty")) {
			printf("%d\n", empty());
		}
		else if (strcmp(str[i], "top")) {
			printf("%d\n", fun_top());
		}
	}


	return 0;
}

void push(int i) {
	if (top > -1) {
		stack[top] = i;
		top++;
	}
}

int pop() {
	if (top > 0)
		return stack[--top];
	else
		return -1;
}

int size() {
	return top;
}

int empty() {
	if (top < 1)
		return 1;
	else
		return 0;
}

int fun_top(){
	if (top <= 0)
		return -1;
	else
		return stack[top - 1];
}

int strcmp(char* s1, char* s2) { //있으면 1, 없으면 0
	int i ,j, cmp_count=0;
	for (i = 0; i < strlen(s1); i++) {
		for (j = 0; i < strlen(s2); j++) {
			if (s1[i+j] == s2[j]) {
				cmp_count++;
			}
			else
				break;
		}
		if (cmp_count >= strlen(s2))
			return 1;
		cmp_count = 0;
	}
	return 0;
}

int find_index(char* s1, char s2) {
	int i;
	for (i = 0; i < strlen(s1); i++) {
		if (s1[i] == s2)
			return i;
	}
	return -1;
}

int strlen(char* s1) {
	int i, count = 0;;
	for (i = 0; s1[i] != '\0'; i++)
		count++;

	return count;
}