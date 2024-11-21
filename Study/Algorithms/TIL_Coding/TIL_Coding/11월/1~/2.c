// 2443 º° Âï±â - 6 / 11.2
#include <stdio.h>

int main() {

	int n, m, total;
	scanf("%d", &n);
	m = n - 1;
	total = 2 * n - 1;

	int sum = n + m, cnt = 0;
	while (n--) {

		for (int i = 0; i < cnt; i++) {
			printf(" ");
		}
		for (int i = 0; i < sum; i++) {
			printf("*");
		}

		printf("\n");
		if (sum != 1) {
			sum -= 2;
			cnt++;

		}
	}

	return 0;
}