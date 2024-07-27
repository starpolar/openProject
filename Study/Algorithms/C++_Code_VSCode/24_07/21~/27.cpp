/*
10952	A+B - 5
¹Ýº¹¹®
*/

#include <iostream>
using namespace std;

int main() {
    for (; ;) {
        int a, b, r;
        cin >> a >> b;

        r = a + b;
        if (!r) break;
        cout << r << '\n';
    }

    return 0;
}