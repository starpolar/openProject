//10807	개수 세기
//배열

#include <iostream>
using namespace std;
#include <vector>

int main() {
	int n;
	cin >> n;

	vector<int> x(n);
	for (int i = 0; i < n; i++) {
		cin >> x[i];
	}

	int v;
	cin >> v;

	int count = 0;
	for (int i = 0; i < n; i++) {
		if (x[i] == v) {
			count++;
		}
	}

	cout << count << '\n';

	return 0;
}