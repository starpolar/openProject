// 25314	코딩은 체육과목 입니다
// 반복문

#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;

    int count = N / 4;  // N을 4로 나눈 몫이 "long"의 반복 횟수
    for (int i = 0; i < count; ++i) {
        cout << "long ";
    }
    cout << "int" << endl;

    return 0;
}

/* 
#include <cstdio>
#include <string>
using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    string total;
    n = n / 4;
    printf("a %s", total);
    for (int i = 0; i < n; i++) {
        total = total + "long ";
        printf("b %s %d\n", total, i);
    }
    printf("%sint", total);

    return 0;
}
 */