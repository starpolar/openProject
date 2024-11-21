// ����, ť, �� / 10.17
// 24511 queuestack
#include <stdio.h>
#define dequeMAX 200001

int main() {

	// 1 2 3 4 �� �ڷᱸ���� �ƴ�
	// 1�� �ϳ��� �ڷᱸ�� 2�� �ϳ��� �ڷᱸ�� ������ ���δ�.
	// �Է°� �ϳ����� ��ü �ڷᱸ���� ��� push pop �ϰ� �� ���� ���� ��� ���

	int n;
	scanf("%d", &n);
	int aArr[100000] = { 0 };
	int aTmp, i, idx=0;
	for (i = 0; i < n; i++) {
		scanf("%d", &aTmp);
		if (!aTmp) {
			aArr[idx++] = i; //idx�� que�� ������ �Ǹ�, �迭�� que�� ��ġ�� ����.
		}
	}

	int deque[dequeMAX] = { 0 }, head= dequeMAX/2, tail=dequeMAX/2;
	int aValTmp = 0, setIdx ,curIdx=0;
	setIdx = aArr[curIdx];
	for (i = 0; i < n; i++) {
		scanf("%d", &aValTmp);
		if (idx == 0) {
			continue;
		}
		if (i == setIdx) {
			deque[tail++] = aValTmp;
			//printf("tail : %d\n", deque[tail - 1]);

			setIdx = aArr[++curIdx];

			/*aArr[curIdx++] = aValTmp;
			setIdx = aArr[curIdx];*/
		}
	}

	int m, c;
	scanf("%d", &m);
	for (i = 0; i < m; i++) { // deque�� ���� que�� �־��⿡ ���⵵ m���� ���� ����.
		scanf("%d", &c);
		deque[--head] = c;
		printf("%d ", deque[--tail]);
	}


	//int pop=0;
	//while (m--) { // �ð� ���⵵�� O(.. m*que����)�� �ȴ�.
	//	scanf("%d", &c);
	//	pop = c;
	//	for (i = 0; i < idx; i++) { // 0�� ������ŭ �� �����ϰ�
	//		pop = aArr[i];
	//		aArr[i] = c;
	//		c = pop;
	//	}
	//	printf("[ ");
	//	for (i = 0; i < idx; i++) {
	//		printf("%d, ", aArr[i]);
	//	}
	//	printf(" ]");
	//	printf("%d ", pop);
	//}

	return 0;
} // �ð� ���⵵ O(n+n+m) �̴�.