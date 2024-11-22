// 10991 º° Âï±â - 16 / 11.14
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int spad = n-1, star = 1;
	while (n--) {
		for (int i = 0; i < spad; i++) {
			printf(" ");
		}
		for (int i = 0; i < star; i++) {
			printf("*");
			printf(" ");
		}
		spad--;
		star++;
		printf("\n");
	}

	return 0;
}