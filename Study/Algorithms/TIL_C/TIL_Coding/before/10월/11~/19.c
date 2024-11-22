// 2010 ÇÃ·¯±× / 10.19
#include <stdio.h>

int main() {

	int n;
	scanf("%d", &n);

	int sum = 0, tmp;
	while (n--) {
		scanf("%d", &tmp);
		if (sum != 0) {
			sum += tmp-1;
		}
		else {
			sum += tmp;
		}
	}

	printf("%d", sum);

	return 0;
}