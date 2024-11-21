// 11721 열 개씩 끊어 출력하기 / 10.28
#include <stdio.h>

int main() {

	char s[101] = "";
	scanf("%s", &s);
	char *ps = s;
	int cnt = 0;
	while (*ps) {
		printf("%c", *ps++);
		cnt++;
		if (cnt >= 10) {
			printf("\n");
			cnt = 0;
		}
	}

	return 0;
}