// 2490 ¿∑≥Ó¿Ã / 11.5
#include <stdio.h>

int main() {
	
	int n = 3;
	int a, b, c, d, cnt=0;
	while (n--) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		cnt = 0;
		cnt += a +b+c+d;
		if (cnt == 3) {
			printf("A\n");
			continue;
		} 
		else if (cnt == 2) {
			printf("B\n");
			continue;
		}
		else if (cnt == 1) {
			printf("C\n");
			continue;
		}
		else if (cnt == 0) {
			printf("D\n");
			continue;
		}
		else if (cnt == 4) {
			printf("E\n");
			continue;
		}
	}

	return 0;
}