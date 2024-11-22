#include <stdio.h>
// 브루트 포스 / 9.26
int main() {//1018	체스판 다시 칠하기
	int n, m;
	scanf("%d %d", &n, &m);

	char board[51][51];
	for (int i = 0; i < n; i++) {
		scanf("%s", board[i]);
	}

	int min_changes = 64; // 최대로 다시 칠해야 할 경우의 수는 64칸 전부 다시 칠하는 경우
	// 두 가지 체스판 패턴
	char pattern1[2] = { 'B', 'W' };
	char pattern2[2] = { 'W', 'B' };

	for (int i = 0; i <= n - 8; i++) {
		for (int j = 0; j <= m - 8; j++) {
			int changes1 = 0; // 첫 번째 패턴 (B로 시작하는 체스판)
			int changes2 = 0; // 두 번째 패턴 (W로 시작하는 체스판)

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
			// 두 가지 경우 중 최소값을 선택
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

	// ! W일때 B일때 두가지 경우의 수를 모두 따져서 최솟값을 만들어야 했기에..
	// 처음 로직부터 엇나감.
	
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
	for (int i = 0; i <= n - 8; i++) { // 8x8을 잘라낼 횟수.
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