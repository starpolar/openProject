#include <stdio.h>

int main() { // 2675	문자열 반복 / 문자열
	int t = 1;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		int cnt = 3;
		char s[21] = "ABC", buf[161] = { 0 };
		scanf("%d %s", &cnt, s); // Q : 배열은 포인터를 안해도 되는 이유는?

		int bufIdx = 0;
		for (int i = 0; i < strlen(s); i++) {
			for (int j = 0; j < cnt; j++) {
				buf[bufIdx++] = s[i];
			}
		}
		printf("%s\n", buf);
	}

	return 0;
}