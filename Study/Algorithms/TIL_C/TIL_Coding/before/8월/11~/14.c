#include <stdio.h>
#include <string.h>

#define MAXCNT 1000001

int main() { // 2675	���ڿ� �ݺ� / ���ڿ�
	int cnt = 0;
	char s[MAXCNT] = { 0 };
	//scanf("%s", &s); // ���� fgets ��. �ٵ� ����� ���Ŀ� stdin? ������ FILE stream.
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