#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<int, vector<int>, greater<int>> minHeap;

    // 카드 묶음을 최소 힙에 넣기
    for (int i = 0; i < n; ++i) {
        int card;
        cin >> card;
        minHeap.push(card);
    }

    int totalCost = 0;

    // 카드 묶음을 합치는 과정
    while (minHeap.size() > 1) {
        // 가장 작은 두 카드 묶음 꺼내기
        int first = minHeap.top();
        minHeap.pop();
        int second = minHeap.top();
        minHeap.pop();

        // 두 카드 묶음을 합친 비용 계산
        int cost = first + second;
        totalCost += cost;

        // 합친 카드 묶음을 다시 최소 힙에 넣기
        minHeap.push(cost);
    }

    cout << totalCost << endl;

    return 0;
}
