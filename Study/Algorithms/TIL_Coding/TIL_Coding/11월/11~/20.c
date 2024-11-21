// 2875 대회 or 인턴 / 11.20
#include <stdio.h>

int main() {
	// 6 4 4 = 2 // 기존 팀에서 더 빼는거
	// 9 4 5 = 2 // 1명을 더 빼야될때 팀에서 빼는거
	// 1 2 5 = 0 // 뒤로 새는거
	// 2 3 1 = 1 // 
	// 9 6 5 = 3
	// 9 0 3 = 0
	// 9 2 3 = 2
	// 2 9 0 = 1

	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);

	if (n <= 1 || m == 0) {
		printf("0");
		return 0;
	}
	int team = n / 2;
	if (team > m) team = m;

	int rest = (m - team) + (n - team*2);
	
	int addRest = k- rest;
	if (addRest > 0) {  // 팀에서 인턴십 만큼 빼고
		if (addRest % 3 != 0) team--;
		team -= (int)(addRest / 3);
	}

	if (team <= 0) { // 나머지가 클때
		printf("0");
	}
	else {
		printf("%d", team);
	}

	return 0;
}