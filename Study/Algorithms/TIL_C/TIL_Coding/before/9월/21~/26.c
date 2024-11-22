#include <stdio.h>
// ���Ʈ ���� / 9.26
int main() {//1018	ü���� �ٽ� ĥ�ϱ�
	int n, m;
	scanf("%d %d", &n, &m);

	char board[51][51];
	for (int i = 0; i < n; i++) {
		scanf("%s", board[i]);
	}

	int min_changes = 64; // �ִ�� �ٽ� ĥ�ؾ� �� ����� ���� 64ĭ ���� �ٽ� ĥ�ϴ� ���
	// �� ���� ü���� ����
	char pattern1[2] = { 'B', 'W' };
	char pattern2[2] = { 'W', 'B' };

	for (int i = 0; i <= n - 8; i++) {
		for (int j = 0; j <= m - 8; j++) {
			int changes1 = 0; // ù ��° ���� (B�� �����ϴ� ü����)
			int changes2 = 0; // �� ��° ���� (W�� �����ϴ� ü����)

			for (int x = 0; x < 8; x++) {
				for (int y = 0; y < 8; y++) {
					if (board[i + x][j + y] != pattern1[(x + y) % 2]) {
						changes1++;
					}
					if (board[i + x][j + y] != pattern2[(x + y) % 2]) {
						changes2++;
					}
				}
			}
			// �� ���� ��� �� �ּҰ��� ����
			if (min_changes > changes1) {
				min_changes = changes1;
			}
			if (min_changes > changes2) {
				min_changes = changes2;
			}
		}
	}

	printf("%d\n", min_changes);
	return 0;

	// ! W�϶� B�϶� �ΰ��� ����� ���� ��� ������ �ּڰ��� ������ �߱⿡..
	// ó�� �������� ������.
	
	// 2���� �迭�� ������ �����ϰ�
	// 2���� �迭�� ������� 8x8�� �߶� �����ϴµ�,
	// ó�� ���� B�϶� �������� W���� Ȯ���ϰ�
	// x�� 2 �̻��̰� y�� 1�϶� x-1(����)�� ���� �ٸ��� Ȯ���ϰ� cnt++(�ٽ� ĥ ����)
	// �������� resCnt(�ٽ� ĥ�� �ּڰ�)���� cnt�� ���� ������ resCnt = cnt
	// ������ resCnt ������ cnt�� ���� Ŀ���� break
	// �׷� resCnt ���� �ִ�ġ�� 64�� �ʱ�ȭ�ϰ�, ���� �������� resCnt�� ���.

	int n, m;
	scanf("%d %d", &n, &m);
	char arr[51][51] = { 0 };

	for (int i = 0; i < n; i++) {
		char x[50] = { 0 };
		scanf("%s", &x);

		for (int j = 0; j < m; j++) {
			arr[i][j] = x[j];
		}
	}

	int x = 0, y = 0, cnt, resCnt = 64;
	for (int i = 0; i <= n - 8; i++) { // 8x8�� �߶� Ƚ��.
		for (int j = 0; j <= m-8; j++) {
			if (i == 1 && j == 1) {
				//printf("debug\n");
			}
			char startCh[2] = { 0 }, nextCh[2] = { 0 };
			cnt = 0;
			for (int xi = i; xi < i + 8; xi++) {
				for (int yj = j; yj < j + 8; yj++) {
					if (i == 0 && j == 5 && xi == 4) {
						//printf("debug\n");
					}
					if (startCh[0] == 0) {
						startCh[0] = arr[xi][yj];
					}
					else if (yj == j && startCh[0] != arr[xi][yj]) {
						cnt++;
					}
					/*else if (yj == j && xi != i && startCh[0] == arr[xi - 1][j]) {
						if (startCh[0] == 'B') startCh[0] = 'W';
						else if (startCh[0] == 'W') startCh[0] = 'B';
						cnt++;
					}*/

					nextCh[0] = arr[xi][yj + 1];
					if (yj == (j + 8 - 1)) {

					}
					else if (startCh[0] == nextCh[0]) {
						cnt++;
						if (nextCh[0] == 'B') startCh[0] = 'W';
						else if (nextCh[0] == 'W') startCh[0] = 'B';
					}
					else if (nextCh[0] != 0) startCh[0] = nextCh[0];
				}
			}
			if (i == 1 && j == 1) {
				//printf("debug");
			}
			if (resCnt > cnt) {
				resCnt = cnt;
			}
		}
	}

	printf("%d", resCnt);
	
	return 0;

	if (1) {
		printf("debug");
	}

}