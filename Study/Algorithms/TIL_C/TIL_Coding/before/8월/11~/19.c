#include <stdio.h>

int main() { // 2444	별 찍기 - 7 / 심화 1
	int n, star = 1;
	scanf("%d", &n);
	int padding = n - 1, cnt = 0;

	for (int i = 0; i < n * 2 - 1; i++) {
		if (cnt == n) {
			star -= 2;
			padding++;
		}
		if (cnt >= n) {
			star -= 2;
			padding++;
			for (int _ = 0; _ < padding; _++) {
				printf("%c", ' ');
			}
			for (int _ = 0; _ < star; _++) {
				printf("%c", '*');
			}
			
		}
		else {
			for (int _ = 0; _ < padding; _++) {
				printf("%c", ' ');
			}
			for (int _ = 0; _ < star; _++) {
				printf("%c", '*');
			}
			star += 2;
			padding--;
		}
		cnt++;
		printf("\n");
	}

	return 0;
}