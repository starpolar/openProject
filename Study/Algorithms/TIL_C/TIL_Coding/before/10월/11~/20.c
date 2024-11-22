// 1267 핸드폰 요금 / 10.20
#include <stdio.h>

int main() {

	// Y 요금제 : 30초마다 10원
	// M 요금제 : 60초마다 15원

	int n;
	scanf("%d", &n);

	int pee, y = 0, m = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &pee);
		y += ((pee / 30) + 1) * 10;
		m += ((pee / 60) + 1) * 15;
	}

	if (y > m) {
		printf("M %d", m);
	}
	else if (y == m) {
		printf("Y M %d", m);
	}
	else {
		printf("Y %d", y);
	}

	return 0;
}