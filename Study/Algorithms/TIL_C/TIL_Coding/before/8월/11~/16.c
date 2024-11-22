#include <stdio.h>
#include <string.h>

int main() { // 5622 다이얼 / 문자열
	char s[16] = { 0 };
	scanf("%s", s);
	
	int cnt = 0;
	for (int i = 0; i < strlen(s); i++) {
		if (s[i] >= 'A' && s[i] <= 'C') {
			cnt += 3;
		} 
		else if (s[i] >= 'D' && s[i] <= 'F') {
			cnt += 4;
		} 
		else if (s[i] >= 'G' && s[i] <= 'I') {
			cnt += 5;
		}
		else if (s[i] >= 'J' && s[i] <= 'L') {
			cnt += 6;
		}
		else if (s[i] >= 'M' && s[i] <= 'O') {
			cnt += 7;
		}
		else if (s[i] >= 'P' && s[i] <= 'S') {
			cnt += 8;
		}
		else if (s[i] >= 'T' && s[i] <= 'V') {
			cnt += 9;
		}
		else if (s[i] >= 'W' && s[i] <= 'Z') {
			cnt += 10;
		}
	}

	printf("%d", cnt);

	return 0;
}