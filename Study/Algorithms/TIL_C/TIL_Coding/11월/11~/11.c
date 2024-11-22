// 2576 홀수 / 11.11
#include <stdio.h>

int main() {

	int n = 7, num, min=100, sum=0;
	while (n--) {
		scanf("%d", &num);

		if (!(num % 2 == 1)) continue;

		if (min > num) {
			min = num;
		}
		sum += num;
	}
	if (sum == 0) {
		printf("-1");
		return 0;
	}
	printf("%d\n%d", sum, min);

	return 0;
}


/*// 2914 저작권 / 11.11
#include <stdio.h>

int main() {

	int a, i;
	scanf("%d %d", &a, &i);

	printf("%d", --i * a + 1);

	return 0;
}*/


/*// 10162 전자레인지 / 11.11
#include <stdio.h>

int main() {

	int t, a = 0, b = 0, c = 0;
	scanf("%d", &t);

	int tmp = t / 300;
	a = tmp;
	int rest = t - (a * 300);

	tmp = rest / 60;
	b = tmp;
	rest -= (b * 60);

	tmp = rest / 10;
	c = tmp;
	rest -= (c * 10);

	if (rest != 0) {
		printf("-1");
	}
	else {
		printf("%d %d %d", a, b, c);
	}

	return 0;
}*/