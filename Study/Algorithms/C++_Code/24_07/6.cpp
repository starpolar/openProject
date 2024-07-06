// 11286 절댓값 힙

#include <cstdio>
#include <queue>
#include <vector>
#include <cmath>

using namespace std;

// 사용자 정의 비교 함수
struct compare {
    bool operator()(const int &a, const int &b) {
        if (abs(a) == abs(b)) {
            return a > b; // 절댓값이 같으면 원래 값이 작은 것이 우선
        }
        return abs(a) > abs(b); // 절댓값이 작은 것이 우선
    }
};

int main() {
    int N;
    scanf("%d", &N);

    priority_queue<int, vector<int>, compare> pq;

    for (int i = 0; i < N; ++i) {
        int x;
        scanf("%d", &x);
        if (x == 0) {
            if (pq.empty()) {
                printf("0\n");
            } else {
                printf("%d\n", pq.top());
                pq.pop();
            }
        } else {
            pq.push(x);
        }
    }

    return 0;
}