#include <stdio.h>
#include <string.h>

#define MAXCNT 1000001

int main() { // 2675	문자열 반복 / 문자열
	int cnt = 0;
	char s[MAXCNT] = { 0 };
	//scanf("%s", &s); // 말고 fgets 로. 근데 입출력 형식에 stdin? 예제는 FILE stream.
	fgets(s, MAXCNT, stdin);
	int length = strlen(s) - 1;
	for (int i = 0; i < length; i++) {
		char tmp = s[i];
		if ((s[i] == ' ' && i == 0) || (s[i] == ' ' && i == length - 1)) {
		}
		else
			if (s[i] == ' ') {
				cnt++;
			}
	}

	printf("%d", ++cnt);

	return 0;
}