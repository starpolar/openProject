#include <stdio.h>
#include <string.h>

int main() { //1316	그룹 단어 체커 / 심화 1
	int n;
	scanf("%d", &n);
	char s[101];

	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int alphabet[26] = { 0 };
		scanf("%s", &s);
		cnt++;

		for (int i = 0; i < strlen(s); i++) {
			if (s[i] != s[i + 1]) {
				if (alphabet[s[i] - 'a']) {
					cnt--;
					break;
				}
				alphabet[s[i] - 'a']++;
			}
		}
	}

	printf("%d", cnt);

	return 0;
}