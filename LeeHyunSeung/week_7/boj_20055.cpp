#include <iostream>

using namespace std;

int n, k;
int first, last;
int a[200];
bool robot[200];

inline int prev(int index) {
	return (index - 1 + n * 2) % (n * 2);
}

int main() {

	cin >> n >> k;
	for (int i = 0; i < 2 * n; i++) {
		cin >> a[i];
	}

	first = 0;
	last = n - 1;

	int step = 0;
	int count = 0;
	while (count < k) {
		step++;

		// �����̾� ��Ʈ �̵�
		first = prev(first);
		last = prev(last);

		robot[last] = false;

		// �κ� �̵�
		int index = last + 1;
		while (index != first) {
			index = prev(index);

			if (robot[index] || !a[index])
				continue;
			if (!robot[prev(index)])
				continue;

			robot[index] = true;
			robot[prev(index)] = false;
			if (!--a[index]) count++;
		}

		robot[last] = false;

		// �κ� �ø���
		if (a[first]) {
			robot[first] = true;
			if (!--a[first]) count++;
		}
	}

	cout << step << endl;
}