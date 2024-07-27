#include <cstdio>
#include <queue>
#include <vector>

int main() {
    int N;
    scanf("%d", &N);

    std::priority_queue<int, std::vector<int>> maxQue;
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        if (x == 0) {
            if (maxQue.empty()) {
                printf("0\n");
            } else {
                printf("%d\n", maxQue.top());
                maxQue.pop();
            }            
        } else {
            maxQue.push(x);
        }
    }

    return 0;
}