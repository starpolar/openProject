// 2443 º° Âï±â - 5 / 10.30
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int ped = n - 1, star=1;
	while (n--) {
		for (int i = 0; i < ped; i++) {
			printf(" ");
		}
		ped--;

		for (int i = 0; i < star; i++) {
			printf("*");
		}
		printf("\n");
		star += 2;
	}

	return 0;
}