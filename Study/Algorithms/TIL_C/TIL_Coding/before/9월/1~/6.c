#include <stdio.h>

int main() {//2501	��� ���ϱ� / ���, ����� �Ҽ�
    int n, k, cnt = 0;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            cnt++;
            if (cnt == k) { // k�� ���° ����ϱ�, cnt ��, ����� ������ k��°��� ��� i�� ���.
                printf("%d", i);
                return 0;
            }
        }
    }
    printf("%d", 0);


    return 0;
}
