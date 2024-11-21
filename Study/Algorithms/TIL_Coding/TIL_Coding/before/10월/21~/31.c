// 2441 º° Âï±â - 4 / 10.31
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int star = n, ped=0;
	while (n--) {
		for (int i = 0; i < ped; i++) {
			printf(" ");
		}
		for (int i = 0; i < star; i++) {
			printf("*");
		}
		printf("\n");
		star--;
		ped++;
	}

	return 0;
}