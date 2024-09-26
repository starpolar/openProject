#include <stdio.h>
// 브루트 포스 / 9.26
int main() {//1018	체스판 다시 칠하기

	// 2차원 배열에 예제를 저장하고
	// 2차원 배열을 순서대로 8x8씩 잘라서 연산하는데,
	// 처음 값이 B일땐 다음값이 W인지 확인하고
	// x가 2 이상이고 y가 1일땐 x-1(전줄)의 값과 다른지 확인하고 cnt++(다시 칠 갯수)
	// 마지막에 resCnt(다시 칠의 최솟값)보다 cnt의 값이 작으면 resCnt = cnt
	// 연산중 resCnt 값보다 cnt의 값이 커지면 break
	// 그럼 resCnt 값은 최대치인 64로 초기화하고, 로직 마지막에 resCnt값 출력.

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
	for (int i = x; i <= n-8; i++) {
		for (int j = y; j <= m-8; j++) {

			char startCh[2] = { 0 }, nextCh[2] = { 0 };
			cnt = 0;
			for (int xi = i; xi < i + 8; xi++) {
				for (int yj = j; yj < j + 8; yj++) {
					if (startCh[0] == 0) {
						startCh[0] = arr[xi][yj];
					}
					else if (yj == j && xi != i && startCh[0] == arr[xi - 1][j]) {
						cnt++;
						if (startCh[0] == 'B') startCh[0] = 'W';
						else if (startCh[0] == 'W') startCh[0] = 'B';
						continue;
					}

					nextCh[0] = arr[xi][yj + 1];
					if (startCh[0] == nextCh[0]) {
						cnt++;
						if (nextCh[0] == 'B') startCh[0] = 'W';
						else if (nextCh[0] == 'W') startCh[0] = 'B';
					}
					else if (nextCh[0] != 0) startCh[0] = nextCh[0];
				}
			}

			if (resCnt > cnt) resCnt = cnt;
			y++;
		}
		x++;
	}

	printf("%d", resCnt);
	
	/*if (1) {
		printf("debug");
	}*/

	return 0;
}