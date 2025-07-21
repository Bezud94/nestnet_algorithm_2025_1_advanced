#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

// �� ���Ұ� ��� ���տ� ���� �ִ��� ����
int facebook[1000000] = { 0, };
// �� ���տ� ��� ���Ұ� ���� �ִ��� ����
vector<int> where[1000001];

int main() {
	int test;

	scanf("%d", &test);

	for (int t = 1; t <= test; t++) {
		// �ʱ�ȭ
		for (int i = 0; i < 1000001; i++) {
			where[i] = vector<int>();
		}
		memset(facebook, 0, sizeof(facebook));

		// �Է�
		int n, k, m;
		int x, y;

		scanf("%d", &n);
		scanf("%d", &k);

		int index = 1;

		for (int i = 0; i < k; i++) {
			scanf("%d %d", &x, &y);

			// �� �� �׷��� ����
			if (!facebook[x] && !facebook[y]) {
				facebook[x] = index;
				facebook[y] = index;

				where[index].push_back(x);
				where[index].push_back(y);

				index++;
			}
			// x�� �׷��� ����
			else if (!facebook[x]) {
				facebook[x] = facebook[y];
				where[facebook[y]].push_back(x);
			}
			// y�� �׷��� ����
			else if (!facebook[y]) {
				facebook[y] = facebook[x];
				where[facebook[x]].push_back(y);
			}
			// �� �� �׷��� �ִ� - ���� �ٸ���
			else {
				if (facebook[x] != facebook[y]) {
					int change = facebook[y];
					
					for (int j = 0; j < where[change].size(); j++) {
						facebook[where[change][j]] = facebook[x];
						where[facebook[x]].push_back(where[change][j]);
					}
					where[change] = vector<int>();
				}
			}
		}

		// Ȯ��
		scanf("%d", &m);

		printf("Scenario %d:\n", t);
		for (int i = 0; i < m; i++) {
			scanf("%d %d", &x, &y);

			if (x == y || (facebook[x] && facebook[y] && facebook[x] == facebook[y])) {
				printf("1\n");
			}
			else {
				printf("0\n");
			}
		}

		printf("\n");
	}
}