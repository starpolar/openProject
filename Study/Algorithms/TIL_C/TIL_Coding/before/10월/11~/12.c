// ���, ����� �Ҽ� 2 / 10.12
// 11866	 �似Ǫ�� ���� 0
#include <stdio.h>

int main() {

	int n = 7, k = 3;
	scanf("%d %d", &n, &k);

	int arr[1000] = { 0 };
	for (int i = 0; i < n; i++) {
		arr[i] = i + 1;
	} // ���� �Է� ���ϰ� 0 �� 1�� ���� ������� �����ϰ�
	// reIdx�� ���ŵ� ���� ���ļ� while���� �ϳ� ���� ���� �ִ�.

	int res[1002] = { 0 };
	int reIdx=0,idx = -1,cnt=0;
	int tmp = n;
	while (tmp--) {
		cnt = 0;
		while (1) {
			idx++;
			if (idx >= n) {
				idx = 0;
			}
			if (arr[idx] != 0) {
				cnt++;
				if (cnt == k) {
					res[reIdx++] = arr[idx];
					arr[idx] = 0;
					break;
				}
			}
		}
	}

	printf("<");
	for (int i = 0; i < n; i++) {
		printf("%d", res[i]);
		if (res[i + 1]) {
			printf(", ");
		} // res �迭�� �۰� �����ؼ� ��������.
		// �Ʒ�ó�� ���������� �ϳ��������� ����ص� ��.
		/*if (i != n - 1) {
			printf(", ");
		}*/
	}
	printf(">");

	return 0;
}