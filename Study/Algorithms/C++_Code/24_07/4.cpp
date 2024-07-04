#include <cstdio> // <stdio.h>를 포함하고, 연결된 헤더들을 "std"(네임스페이스)에 선언.
#include <queue> // 대기열
#include <vector> // 동적 배열을 구현한 컨테이너(그릇) 템플릿(틀) 클래스(설계도)(온갖것을 갖다붙였다..?)

int main() {
    int N;
    scanf("%d", &N);

    // 최소 힙을 만들기 위해 priority_queue(기본적으로 최소 힙.)를 사용
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    // priority(우선순위) queue(대기열)
    // vertor(배열) // greater(..보다 큰)
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
    
    /* 
    각 라이브러리에는 수 많은 알고리즘이 담겨있을것이다.
    그리고 그 알고리즘은 대단한 기법이 아닌 기본 기법으로 이루어져 있다.
    그 즉슨, 이론적인 개념을 구현하기 위해 코드화로 개발하고,
    이를 함수화로 정리한 후, 라이브러리로 만드는 과정을 걸쳤을거라 추측한다.
    즉, 필요에 의해서 알고리즘을 기본 기법으로 개발하고 그것을 추후에
    간결화(정리), 고도화(함수화), 패키징(라이브러리)로 만들었을 것이다.
    교훈은, 개발의 순서는 앞닥친 문제를 컴퓨터의 언어로 해결하는게 최우선이며,
    그 후에 고도화와 패키징 작업이 실행되는 것이다.
    */

    return 0;
}
