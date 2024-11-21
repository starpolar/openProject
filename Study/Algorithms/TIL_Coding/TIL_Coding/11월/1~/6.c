// 2523 º° Âï±â - 13 / 11.6
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int cnt = n, star =0;
	while (cnt--) {
		star++;
		for (int i = 0; i < star; i++) {
			printf("*");
		}
		printf("\n");
	}
	cnt = n - 1;
	while (cnt--) {
		star--;
		for (int i = 0; i < star; i++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}