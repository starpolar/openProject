#include <stdio.h>
#include <string.h>
#include <math.h>

int main() {
    char N[31];
    int B;
    scanf("%s %d", N, &B);

    int length = strlen(N);
    int result = 0;

    for (int i = 0; i < length; i++) {
        int value;
        if (N[i] >= '0' && N[i] <= '9') {
            value = N[i] - '0';
        }
        else {
            value = N[i] - 'A' + 10;
        }
        int a = result * B;
        result = a + value;
    }

    printf("%d\n", result);

    return 0;
}
