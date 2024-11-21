// 1547 공 / 11.19
#include <stdio.h>

int main() {

	int m;
	scanf("%d", &m);

	int x, y, tmp;
	int ball[4] = { 0 };
	ball[1] = 1;
	while (m--) {
		scanf("%d %d", &x, &y);
		if (x == y) continue;
		tmp = ball[x];
		ball[x] = ball[y];
		ball[y] = tmp;
	}

	for (int i = 0; i < 4; i++) {
		if (ball[i]) {
			if (i == 0) {
				printf("-1");
				break;
			}
			printf("%d", i);
		}
	}

	return 0;
}

/*
// 2935 소음 / 11.19
#include <stdio.h>
#include <string.h>

int main() {

	char a[101], b[101], oper[5];
	scanf("%s %s %s", &a, &oper, &b);

	int sta = strlen(a) - 1;
	int stb = strlen(b) - 1;
	if (!(strcmp(oper, "*"))) {
		int zero = sta + stb;

		printf("1");
		for (int i = 0; i < zero; i++) {
			printf("0");
		}
	}
	else { // 나는 한 배열의 포인터연산을 이용해 예외처리를 하며 출력함.
		char main[101], next[101];
		char* pa = a;
		if (strlen(a) == strlen(b)) {
			printf("2");
			pa++;
		}
		else {
			printf("1");
			pa++;
		}
		if (strlen(a) < strlen(b)) { // 스왑하지 않고 1과0이라고만 가정하고 len으로만 앞 수 먼저 출력하고
									// 다음 뒷수를 출력하는 방법도 가능함.

									// 또 배열 자체에 중간 값을 len으로 구해서 1로 바꾸고 출력해도됨.
			char tmp[101];
			strcpy(tmp, a);
			strcpy(a, b);
			strcpy(b, tmp);
		}

		int pluLen = strlen(a) - strlen(b);
		for (int i = 1; i < strlen(a); i++) {
			if (i == pluLen) {
				printf("1");
				pa++;
				continue;
			}
			printf("%c", *pa++);
		}
	}

	return 0;
}
*/

/*
// 10824 네 수 / 11.19
#include <stdio.h>
#include <string.h>

int main() {

	char a[20], b[20], c[20], d[20];
	scanf("%s %s %s %s", &a, &b, &c, &d);

	int ab, cd;
	strcat(a, b);
	ab = atoi(a);
	strcat(c, d);
	cd = atoi(c);

	printf("%d", ab + cd);
		
	return 0;
}
*/

/*
// 10992 별 찍기 - 17 / 11.16, 19
#include <stdio.h>

int main() {

	int n, last;
	scanf("%d", &n);
	last = n + (n - 1);

	int spad = n - 1, star = 1, mpad=-1;
	int cycle = n - 1;
	while (cycle--) {
		for (int i = 0; i < spad; i++) {
			printf(" ");
		}
		printf("*");
		if (mpad >= 1) {
			mpad += 2;
		}
		else {
			mpad++;
		}
		if (mpad) {
			for (int i = 0; i < mpad; i++) {
				printf(" ");
			}
			printf("*");
		}
		star++;

		spad--;
		printf("\n");
	}
	for (int i = 0; i < last; i++) {
		printf("*");
	}

	return 0;
}
*/