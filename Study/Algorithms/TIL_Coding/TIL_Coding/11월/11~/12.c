// 2522 º° Âï±â - 12 / 11.12
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int pad = n, star = 0, cnt=n;
	while (cnt--) {
		pad--;
		star++;
		for (int i = 0; i < pad; i++) {
			printf(" ");
		}
		for (int i = 0; i < star; i++) {
			printf("*");
		}
		printf("\n");
	}

	cnt = n - 1;
	while (cnt--) {
		pad++;
		star--;
		for (int i = 0; i < pad; i++) {
			printf(" ");
		}
		for (int i = 0; i < star; i++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}