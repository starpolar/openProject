// 10872 ���丮�� / 10.25
#include <stdio.h>

int main() {

	// ���丮�� : 1���� n������ �ڿ��� ��.
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