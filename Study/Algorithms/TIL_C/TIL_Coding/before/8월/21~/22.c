#include <stdio.h>
#include <string.h>

int main() { // 2941	크로아티아 알파벳 / 심화 1
	char s[101];
	scanf("%s", &s);

	int cnt = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] == 'l' && s[i + 1] == 'j') {
			cnt++;
			if (i + 1 == strlen(s) - 1) {
				break;
			}
			i++;
		}
		else if (s[i] == 'n' && s[i + 1] == 'j') {
			cnt++;
			if (i + 1 == strlen(s) - 1) {
				break;
			}
			i++;
		}
		else if (s[i] == 'd' && s[i + 1] == 'z' && s[i + 2] == '=') {
			cnt++;
			if (i + 2 == strlen(s) - 1) {
				break;
			}
			i++;
		}
		else if (s[i] == '=' || s[i] == '-') {}
		else cnt++;
	}

	printf("%d", cnt);

	return 0;
}