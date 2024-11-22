//3052	나머지
//배열

#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<int> x(42, 0);
    for (int i = 0; i < 10; i++) {
        int tmp;
        cin >> tmp;
        tmp %= 42;
        x[tmp] += 1;
    }

    int total = 0;
    for (int i = 0; i < 42; i++) {
        if (x[i] != 0) {
            total += 1;
        }
    }

    cout << total;

    return 0;
}