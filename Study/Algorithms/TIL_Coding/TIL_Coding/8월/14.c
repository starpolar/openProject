#include <stdio.h>
#include <string.h>

int main() { // 2675	문자열 반복 / 문자열
	int cnt = 0;
	char s[1000001] = { 0 };
	scanf("%s", &s); // 말고 fgets 로. 근데 입출력 형식에 stdin? 예제는 FILE stream.
	int length = strlen(s) - 1;
	for (int i = 0; i < length; i++) {
		if (s[0] == ' ' || s[length] == ' ') {
			cnt--;
		}
		else if (s[i] == ' ') {
			cnt++;
		}
	}

	printf("%d", cnt);

	return 0;
}