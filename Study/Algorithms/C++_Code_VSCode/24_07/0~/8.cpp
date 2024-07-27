#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

const int MAXN = 32000;

std::vector<int> adj[MAXN + 1]; // 인접 리스트
int indegree[MAXN + 1];    // 각 정점의 진입 차수

vector<int> topologySort(int n) {
    priority_queue<int, vector<int>, greater<int>> pq; // 최소 힙
    vector<int> result;

    // 진입 차수가 0인 정점을 우선순위 큐에 추가
    for (int i = 1; i <= n; i++) {
        if (indegree[i] == 0) {
            pq.push(i);
        }
    }

    while (!pq.empty()) {
        int curr = pq.top();
        pq.pop();
        result.push_back(curr);

        for (int next : adj[curr]) {
            indegree[next]--;
            if (indegree[next] == 0) {
                pq.push(next);
            }
        }
    }

    return result;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u].push_back(v);
        indegree[v]++;
    }

    vector<int> result = topologySort(n);

    for (int x : result) {
        printf("%d ", x);
    }
    printf("\n");

    return 0;
}


/* 
// 1766 문제집
// (최소 힙x / 배열)

#include <cstdio>
// #include <queue>
#include <vector>

int main() {
    int N, M;
    scanf("%d %d", &N, &M);

    // std::priority_queue<int, std::vector<int>, std::greater<int>> minQue;
    std::vector<int> arr;
    for (int i = 1; i < N+1; i++) {
        int x = i;
        arr.insert(x);
    }

    return 0;
} */