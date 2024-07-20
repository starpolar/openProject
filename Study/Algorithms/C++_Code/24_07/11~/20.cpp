// 25304 영수증
// 반복문
/* 메모리 소비가 더 큼 안쓰는걸로.
#include <iostream>
using namespace std;

int main() {
    int x, n, total = 0;
    cin >> x;
    cin >> n;

    for (int _ = 0; _ < n; _++) {
        int a, b;
        cin >> a >> b;
        total += a * b;
    }
    if (x == total) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}
 */

#include <cstdio>

int main() {
    int total, cnt = 0;
    int n;
    scanf("%d", &total);
    scanf("%d", &n);
    // printf("total : %d\n", total);

    for (int _ = 0; _ < n; _++) {
        int a, b;
        scanf("%d %d", &a, &b);
        cnt += a * b;
        // printf("%d and %d\n", cnt, _);
    }
    if (total == cnt) {
        printf("Yes");
    } else {
        printf("No");
    }

    return 0;
}