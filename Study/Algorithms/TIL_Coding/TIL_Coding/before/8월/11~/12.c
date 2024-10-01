#include <stdio.h>

int main() { // 10809	알파벳 찾기 / 문자열
	int x[26] = { 0 };
	for (int i = 0; i < 26; i++) {
		x[i] = -1;
	}

	char s[101];
	scanf("%s", &s);

	int cnt = 0;
	for (int i = 0; i < strlen(s); i++) {
		int sIdx = s[i] - 'a';
		if (x[sIdx] == -1) {
			x[sIdx] = cnt++;
		}
		else {
			cnt++;
		}
	}

	for (int i = 0; i < 26; i++) {
		printf("%d ", x[i]);
	}
	
	return 0;
}