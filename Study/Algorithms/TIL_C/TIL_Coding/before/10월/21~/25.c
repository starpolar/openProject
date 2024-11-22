// 10872 팩토리얼 / 10.25
#include <stdio.h>

int main() {

	// 팩토리얼 : 1부터 n까지의 자연수 곱.
	int n;
	scanf("%d", &n);

	if (n == 0) {
		printf("1");
		return 0;
	}

	int mul = 1;
	for (int i = 1; i <= n; i++) {
		mul *= i;
	}
	printf("%d", mul);

	return 0;
}