#include <stdio.h>

int main() { // 2675	���ڿ� �ݺ� / ���ڿ�
	int t = 1;
	scanf("%d", &t);

	for (int i = 0; i < t; i++) {
		int cnt = 3;
		char s[21] = "ABC", buf[161] = { 0 };
		scanf("%d %s", &cnt, s); // Q : �迭�� �����͸� ���ص� �Ǵ� ������?

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