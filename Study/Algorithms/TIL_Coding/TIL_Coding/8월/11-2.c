#include <stdio.h>

int main() { //11720	숫자의 합 / 문자열
	int n;
	scanf("%d", &n);

	char c[101] = { 0 };
	scanf("%s", &c);

	int sum = 0;
	for (int i = 0; i < n; i++) {
		c[i] = c[i] - '0';
		sum += c[i];
	}

	printf("%d", sum);

	return 0;
}