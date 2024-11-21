// 2445 º° Âï±â - 8 / 11.3
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int pad = n * 2, star = 0;

	int tmp = n;
	while (tmp--) {
		star += 2;
		pad -= 2;
		for (int i = 0; i < star/2; i++) {
			printf("*");
		}
		for (int i = 0; i < pad; i++) {
			printf(" ");
		}
		for (int i = 0; i < star/2; i++) {
			printf("*");
		}
		printf("\n");

	}
	tmp = n;
	while (--tmp) {
		star -= 2;
		pad += 2;
		for (int i = 0; i < star / 2; i++) {
			printf("*");
		}
		for (int i = 0; i < pad; i++) {
			printf(" ");
		}
		for (int i = 0; i < star / 2; i++) {
			printf("*");
		}
		printf("\n");
	}

	return 0;
}