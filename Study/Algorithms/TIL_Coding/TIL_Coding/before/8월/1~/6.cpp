//10811	바구니 뒤집기
//배열

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> x(n, 0);
    for (int i = 0; i < n; i++) {
        x[i] = i + 1;
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        if (a == b) {

        }
        else {
            vector<int> y(b, 0);
            int k = 0;
            for (int j = b; a <= j; j--) {
                y[k] = x[j - 1];
                //cout << 'y' << y[k] << '\n';

                k++;
            }

            k = 0;
            for (int i = a; i <= b; i++) {
                x[i - 1] = y[k];
                //cout << 'x' << x[i - 1] << '\n';

                k++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << x[i] << ' ';
    }

    return 0;
}