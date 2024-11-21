//10810	공 넣기
//배열

#include <iostream>
#include <vector>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<int> baskets(N + 1, 0); // 바구니를 0으로 초기화

    for (int m = 0; m < M; ++m) {
        int i, j, k;
        std::cin >> i >> j >> k;
        for (int idx = i; idx <= j; ++idx) {
            baskets[idx] = k;
        }
    }

    for (int n = 1; n <= N; ++n) {
        std::cout << baskets[n] << " ";
    }

    return 0;
}
