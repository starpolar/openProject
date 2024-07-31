//10818	 최소, 최대
//배열

#include <iostream>
using namespace std;
#include <vector>

int main() {
	int n = 0;
	cin >> n;

	vector<int> v(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
	}

	int tmp, min = 0, max = 0;
	//cin >> tmp;
	//if (tmp < 500000) {
	//	min = tmp;
	//}
	//else {
	//	max = tmp;
	//}
	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			if (v[i] < min) {				
				min = v[i];
			}
			else if (v[i] > max) {
				max = v[i];
			}
			break;
		}
		if (v[i] < v[i + 1]) {
			if (min) {
				if (min > v[i]) {
					min = v[i];
				}
			}
			else {
				min = v[i];
			}

			if (max) {
				if (max < v[i + 1]) {
					max = v[i + 1];
				}
			}
			else {
				max = v[i + 1];
			}
		}
		else {
			if (min) {
				if (min > v[i + 1]) {
					min = v[i + 1];
				}
			}
			else {
				min = v[i + 1];
			}

			if (max) {
				if (max < v[i]) {
					max = v[i];
				}
			}
			else {
				max = v[i];
			}
		}
	}

	printf("%d %d", min, max);

	return 0;
}


//#include <iostream>
//#include <algorithm> // std::min, std::max
//using namespace std;
//
//int main() {
//	int N;
//	cin >> N;
//
//	int minValue = 1;
//	int maxValue = 1000000;
//
//	for (int i = 0; i < N; ++i) {
//		int num;
//		cin >> num;
//
//		if (num < minValue) {
//			minValue = num;
//		}
//		if (num > maxValue) {
//			maxValue = num;
//		}
//	}
//
//	cout << minValue << " " << maxValue << endl;
//	return 0;
//}