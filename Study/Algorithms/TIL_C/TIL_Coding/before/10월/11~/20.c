// 1267 �ڵ��� ��� / 10.20
#include <stdio.h>

int main() {

	// Y ����� : 30�ʸ��� 10��
	// M ����� : 60�ʸ��� 15��

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