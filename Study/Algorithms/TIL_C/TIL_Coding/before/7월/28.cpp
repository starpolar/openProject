//10951	A + B - 4
//반복문

#include <iostream>
using namespace std;

int main() {
	int a, b;
	for (; ;) {
		if (cin >> a >> b) {
			cout << a + b << '\n';
		}
		else {
			break;
		}
	}
	
	return 0;
}