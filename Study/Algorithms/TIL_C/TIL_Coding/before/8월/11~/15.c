#include <stdio.h>
#include <string.h>

char a[1000005];

int main() { //	1152	�ܾ��� ���� �� �м�.
    int ans = 0;

    scanf("%[^\n]s", a);

    if (a[0] != ' ') ans++;

    for (int i = 1; i < strlen(a); i++)
        if (a[i - 1] == ' ' && a[i] != ' ') ans++;

    printf("%d", ans);

    return 0;
}