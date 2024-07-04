// 최소 힙 사용.
#include <cstdio>
#include <queue>
#include <vector>

int main() {
    int N;
    scanf("%d", &N);

    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    for (int i = 0; i < N; ++i) {
        int x;
        scanf("%d", &x);

        if (x == 0) {
            if (minHeap.empty()) {
                printf("0\n");
            } else {
                printf("%d\n", minHeap.top());
                minHeap.pop();
            }
        } else {
            minHeap.push(x);
        }
    }

    return 0;
}