//10871 X���� ���� ��
//�迭

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