// 1173 운동 / 10.16
#include <stdio.h>

int main() {

	int N=3, m=50, M=60, T=10, R=20; // N : 몇분 m :최소맥박 M : 최대맥박 T : 분당 증가 맥박 R : 분당 감소 맥박
	scanf("%d %d %d %d %d", &N, &m, &M, &T, &R);
	// X : 현재 맥박
	// X+T <= M 때 운동 이외 휴식 : X-R

	// 운동하는데 필요한 최소시간 즉, 휴식시간 제외한 실 운동시간.


	int X = m, runTime = 0, totalTime=0;
	if ((X + T) > M) {
		printf("-1");
		return 0;
	}
	while (1) {
		if (runTime == N && X <= M) {
			break;
		}
		else if ((X + T) > M) {
			X -= R;
			if (X < m) {
				X = m;
			}
		}
		else {
			X += T;
			runTime++;
		}
		totalTime++;
	}

	printf("%d", totalTime);

	return 0;
}