//10810	�� �ֱ�
//�迭

#include <iostream>
#include <vector>

int main() {
    int N, M;
    std::cin >> N >> M;

    std::vector<int> baskets(N + 1, 0); // �ٱ��ϸ� 0���� �ʱ�ȭ

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
