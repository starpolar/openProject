//5597	���� �� ���� ��..?
//�迭

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N = 30;
    vector<int> x(N, 0);

    for (int i = 0; i < 28; i++) {
        int a;
        cin >> a;
        x[a - 1] += 1;
    }

    for (int i = 0; i < N; i++) {
        if (x[i] == 0) {
            cout << i + 1 << ' ';
        }
    }

    return 0;
}