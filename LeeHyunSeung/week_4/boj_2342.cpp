/*
# ��Ģ
0: �߾�, 1: ��, 2: ��, 3: �Ʒ�, 4: ��
�� ���� ���� ������ �� �� ����. (���� ���� �ÿ��� ����)
�߾��� ���� �ٸ� �������� ������ ��:                         �� 2 �Ҹ�
�ٸ� �������� ������ �������� ������ �� (e.g. �� -> ��, ��): �� 3 �Ҹ�
�ݴ������� ������ �� (e.g. �� -> �Ʒ�):                      �� 4 �Ҹ�
���� ������ �� �� �� ���� ��:                                �� 1 �Ҹ�
*/

#include <cstdio>
#include <climits>

using namespace std;

inline int get_require(int from, int to) {
	if (from == to)
		return 1;
	else if (from == 0)
		return 2;
	else if (from - to == 2 || to - from == 2)
		return 4;
	else
		return 3;
}

struct REQ {
	int left;
	int right;
} require;

int main() {
	bool feet[5][5] = { false, };

	int ans[5][5] = { 0, };

	int move;
	bool is_first = true;
	while (1) {
		scanf("%d", &move);

		if (!move)
			break;

		if (is_first) {
			feet[move][0] = true;
			ans[move][0] = get_require(0, move);
			is_first = false;

			continue;
		}

		bool temp_feet[5][5] = { false, };
		int temp_ans[5][5] = { 0, };

		for (int left = 0; left < 5; left++) {
			for (int right = 0; right < 5; right++) {
				if (!feet[left][right])
					continue;

				if (right != move) {
					require.left = get_require(left, move);

					temp_feet[move][right] = true;

					if (!temp_ans[move][right] || ans[left][right] + require.left < temp_ans[move][right])
						temp_ans[move][right] = ans[left][right] + require.left;
				}
				if (left != move) {
					require.right = get_require(right, move);

					temp_feet[left][move] = true;

					if (!temp_ans[left][move] || ans[left][right] + require.right < temp_ans[left][move])
						temp_ans[left][move] = ans[left][right] + require.right;
				}
			}
		}
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				ans[i][j] = temp_ans[i][j];
				feet[i][j] = temp_feet[i][j];
			}
		}
	}
	int min_ans = INT_MAX;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (ans[i][j] && ans[i][j] < min_ans)
				min_ans = ans[i][j];
		}
	}

	if (min_ans == INT_MAX)
		printf("0\n");
	else 
		printf("%d\n", min_ans);
}