//1546	Æò±Õ
//¹è¿­

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> x(n, 0);
    int max = 0;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        x[i] = tmp;
        if (tmp > max) {
            max = tmp;
        }
    }

    double total = 0, avg = 0;
    for (int i = 0; i < n; i++) {
        total += (double)x[i] / max * 100;
    }
    avg = total / n;

    cout << avg;

    return 0;
}