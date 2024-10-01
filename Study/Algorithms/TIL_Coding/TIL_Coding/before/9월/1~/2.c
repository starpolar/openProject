#include <stdio.h>

int main() {
    int t, c, cent;
    scanf("%d", &t);

    for (int i = 0; i < t; i++) {
        scanf("%d", &c);
        int cArr[4] = { 0 };

        for (int j = 0; j < 4; j++) {
            if (j == 0) cent = 25;
            else if (j == 1) cent = 10;
            else if (j == 2) cent = 5;
            else if (j == 3) cent = 1;

            cArr[j] = c / cent;
            c %= cent;
        }

        for (int _ = 0; _ < 4; _++) {
            printf("%d ", cArr[_]);
        }
    }

    return 0;
}
