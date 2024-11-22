//10813	공 바꾸기
//배열

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> x(N, 0);
    
    for (int i = 0; i < N; i++) {
        x[i] = i + 1;
    }
    
    for (int i = 0; i < M; i++) {
        int a, b, tmp;
        cin >> a >> b;
        a -= 1;
        b -= 1;

        tmp = x[a];
        x[a] = x[b];
        x[b] = tmp;
    }

    for (int i = 0; i < N; i++) {
        cout << x[i] << ' ';
    }

    return 0;
}