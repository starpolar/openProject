//2562 최댓값
//배열

#include <iostream>
using namespace std;
#include <vector>
#include <stdio.h>

int main() {
	int x, idx, max = 0;
	for (int i = 0; i < 9; i++) {
		cin >> x;
		if (max < x) {
			max = x;
			idx = i + 1;
		}
	}
	cout << max << '\n' << idx;

	return 0;
}