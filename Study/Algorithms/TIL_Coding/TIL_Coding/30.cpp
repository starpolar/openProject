//10871 X보다 작은 수
//배열

#include <iostream>
using namespace std;
#include <vector>

int main() {
	int n, x;
	cin >> n >> x;

	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		if (v[i] < x) {
			cout << v[i] << ' ';
		}
	}

	return 0;
}