#include <stdio.h>
#include <string.h>

int main() { // 1157	단어 공부 / 심화 1
	char s[1000001];
	int cntArr[26] = { 0 };
	scanf("%s", &s);

	for (int i = 0; i < strlen(s); i++) {
		if (65 <= s[i] && s[i] <= 90) {
			cntArr[s[i] - 'A']++;
		} else if (97 <= s[i] && s[i] <= 122) {
			cntArr[s[i] - 'a']++;
		}
	}

	int top = cntArr[0], topIdx = 0;
	for (int i = 1; i < 26; i++) {
		if (top < cntArr[i]) {
			top = cntArr[i];
			topIdx = i;
		}
	}

	int notAlr = 1;
	for (int i = 0; i < 26; i++) {
		if (top == cntArr[i] && i != topIdx) {
			puts("?");
			notAlr = 0;
			break;
		}
	}

	if (notAlr) printf("%c", topIdx + 'A');
	
	return 0;
}