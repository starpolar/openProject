#include <stdio.h>
// ���Ʈ ���� / 9.27
int main() {//1436	��ȭ���� ��
    // 6660: ���� �� count = 9
    // 6661: ���� �� count = 10
    // 6662 : ���� �� count = 11
    int n;
    scanf("%d", &n);

    int count = 0;
    int num = 666;

    while (1) {
        char str[20];
        sprintf(str, "%d", num);  // ���ڸ� ���ڿ��� ��ȯ

        if (strstr(str, "666") != NULL) {  // '666'�� ���Ե� ���
            count++;
        }

        if (count == n) {  // N��° '666'�� ã���� ���
            printf("%d\n", num);
            break;
        }

        num++;  // ���� ���ڷ� ����
    }

	return 0;
}