// 1173 � / 10.16
#include <stdio.h>

int main() {

	int N=3, m=50, M=60, T=10, R=20; // N : ��� m :�ּҸƹ� M : �ִ�ƹ� T : �д� ���� �ƹ� R : �д� ���� �ƹ�
	scanf("%d %d %d %d %d", &N, &m, &M, &T, &R);
	// X : ���� �ƹ�
	// X+T <= M �� � �̿� �޽� : X-R

	// ��ϴµ� �ʿ��� �ּҽð� ��, �޽Ľð� ������ �� ��ð�.


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