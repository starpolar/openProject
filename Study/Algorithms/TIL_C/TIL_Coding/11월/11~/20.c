// 2875 ��ȸ or ���� / 11.20
#include <stdio.h>

int main() {
	// 6 4 4 = 2 // ���� ������ �� ���°�
	// 9 4 5 = 2 // 1���� �� ���ߵɶ� ������ ���°�
	// 1 2 5 = 0 // �ڷ� ���°�
	// 2 3 1 = 1 // 
	// 9 6 5 = 3
	// 9 0 3 = 0
	// 9 2 3 = 2
	// 2 9 0 = 1

	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	if (n <= 1 || m == 0) {
		printf("0");
		return 0;
	}
	int team = n / 2;
	if (team > m) team = m;

	int rest = (m - team) + (n - team*2);
	
	int addRest = k- rest;
	if (addRest > 0) {  // ������ ���Ͻ� ��ŭ ����
		if (addRest % 3 != 0) team--;
		team -= (int)(addRest / 3);
	}

	if (team <= 0) { // �������� Ŭ��
		printf("0");
	}
	else {
		printf("%d", team);
	}

	return 0;
}