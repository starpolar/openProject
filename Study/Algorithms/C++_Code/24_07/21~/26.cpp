/* 
2439	별 찍기 - 2
반복문
 */

#include <iostream>
using namespace std;

int main() {
    int n;    cin >> n;
    
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k <)

        for (int j = 0; j <= i; j++) {
            cout << '*';
        }
        cout << '\n';
    }

    return 0;
}

/* #include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    for(int i = 1; i <= n; i++) {
        // 공백 출력
        for(int j = 1; j <= n - i; j++) {
            cout << " ";
        }
        // 별 출력
        for(int k = 1; k <= i; k++) {
            cout << "*";
        }
        // 줄바꿈
        cout << endl;
    }
    
    return 0;
}
 */