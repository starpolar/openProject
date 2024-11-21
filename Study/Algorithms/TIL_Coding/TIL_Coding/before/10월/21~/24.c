// 2476 주사위 게임 / 10.24
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);
	int num1, num2, num3, max = 0, tmp;
	while (n--) {
		scanf("%d %d %d", &num1, &num2, &num3);
		tmp = 0;
		if (num1 == num2 && num2 == num3) {
			tmp += 10000 + (num1 * 1000);
		}
		else if (num1 == num2 || num1 == num3) {
			tmp += 1000 + (num1 * 100);
		}
		else if (num2 == num3) {
			tmp += 1000 + (num2 * 100);
		}
		else {
			tmp = num1;
			if (tmp < num2) {
				tmp = num2;
			}
			if (tmp < num3) {
				tmp = num3;
			}
			tmp *= 100;
		}

		if (max < tmp) {
			max = tmp;
		}
	}
	printf("%d", max);

	return 0;
}

/*// 2460 지능형 기차 2 / 10.24
#include <stdio.h>
#define MAX 10000

int main() {

	int out, in, cur = 0, max = 0;
	for (int i = 0; i < 10; i++) {
		scanf("%d %d", &out, &in);
		cur -= out;
		if (cur < 0) {
			cur = 0;
		}
		cur += in;
		if (cur > MAX) {
			cur - MAX;
		}
		if (max < cur) {
			max = cur;
		}
	}
	printf("%d", max);

	return 0;
}*/