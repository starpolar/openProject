#include <stdio.h>
#include <string.h>

int main() { //25206	너의 평점은 / 심화 1
	int gradeCnt[9] = { 0 };
	float gradeChart[9] = { 4.5, 4.0, 3.5, 3.0, 2.5, 2.0, 1.5, 1.0, 0.0 };
	float creGraSum = 0.0;
	for (int i = 0; i < 20; i++) { // 공식 : ((credit * grade) += 20pcs) / (credit += 20pcs)
		float credit;
		char s[51], grade[5];
		scanf("%s %f #s", &s, &credit, &grade);
		
		int tmp = grade[0] - 'A' + 1;
		if (grade[1] == '+') tmp--;
		gradeCnt[tmp]++;
		creGraSum += gradeChart[tmp] * credit;
	}


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