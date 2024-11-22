// 4153 직각삼각형 / 10.27
#include <stdio.h>

int main() {

	int a, b, c, tmp;
	while (1) {
		scanf("%d %d %d", &a, &b, &c);

		if (c < a) {
			tmp = a;
			a = c;
			c = tmp;
		}
		else if (c < b) {
			tmp = b;
			b = c;
			c = tmp;
		}

		if (a == 0 && b == 0 & c == 0) {
			break;
		}
		else if (a * a + b * b == c * c) {
			printf("right\n");
		}
		else {
			printf("wrong\n");
		}
	}

	return 0;
}

/*// 10250 ACM 호텔 / 10.27
#include <stdio.h>

int main() {

	int t;
	scanf("%d", &t);

	int h, w, n;
	while (t--) {
		scanf("%d %d %d", &h, &w, &n);
		int curh = 0, curw = 1;
		while (n--) {
			curh++;
			if (curh > h) {
				curh = 1;
				curw++;
			}
		}
		if (curw < 10) {
			printf("%d0%d\n", curh, curw);
		}
		else {
			printf("%d%d\n", curh, curw);
		}
	}

	return 0;
}*/