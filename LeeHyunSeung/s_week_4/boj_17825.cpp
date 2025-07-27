#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// �� ĭ�� ����
int score[33] = {
	0,
	2, 4, 6, 8, 10,
	12, 14, 16, 18, 20,
	22, 24, 26, 28, 30,
	32, 34, 36, 38, 40,
	13, 16, 19,
	22, 24,
	28, 27, 26,
	25,
	30, 35,
	0
};
// �� ĭ�� ���� ĭ (������ ȭ��ǥ)
// (����: 5 -> 21, 10 -> 24, 15 -> 26)
int map[33] = {
	1,
	2, 3, 4, 5, 6,
	7, 8, 9, 10, 11,
	12, 13, 14, 15, 16,
	17, 18, 19, 20, 32,
	22, 23, 29,
	25, 29,
	27, 28, 29,
	30,
	31, 20,
};
// Ư�� �̵� ĭ
int special[33];

short visited[11][33][33][33][33];

int main() {
	// �Է�
	int move[10];

	for (int i = 0; i < 10; i++) {
		scanf("%d", &move[i]);
	}

	// Ư�� �̵� ĭ ����
	special[5] = 21;
	special[10] = 24;
	special[15] = 26;
	
	// first: ȸ��, second: ���� ��ġ (����)
	queue<pair<int, vector<int>>> q;
	pair<int, vector<int>> cur;

	int ans = 0;

	q.push({ 0, {0, 0, 0, 0} });
	visited[0][0][0][0][0] = 0;

	while (!q.empty()) {
		cur = q.front(); q.pop();

		if (cur.first == 10) {
			if (ans < visited[10][cur.second[0]][cur.second[1]][cur.second[2]][cur.second[3]]) {
				ans = visited[10][cur.second[0]][cur.second[1]][cur.second[2]][cur.second[3]];
			}
			continue;
		}

		// 4���� �� ��� �̵����Ѻ���
		int move_amount = move[cur.first];

		for (int i = 0; i < 4; i++) {
			// �̵�
			vector<int> nx = cur.second;
			int new_score = visited[cur.first][nx[0]][nx[1]][nx[2]][nx[3]];

			if (nx[i] == 32)
				continue;
			if (special[nx[i]]) {
				nx[i] = special[nx[i]];
				for (int j = 1; j < move_amount; j++) {
					nx[i] = map[nx[i]]; 
					if (nx[i] == 32)
						break;
				}
			}
			else {
				for (int j = 0; j < move_amount; j++) {
					nx[i] = map[nx[i]];
					if (nx[i] == 32)
						break;
				}
			}

			// ��ȿ�� �������� Ȯ��
			bool is_wrong = false;
			if (nx[i] != 32) {
				for (int j = 0; j < 4; j++) {
					if (j == i)
						continue;

					if (nx[i] == nx[j]) {
						is_wrong = true;
						break;
					}
				}
				if (is_wrong)
					continue;
			}

			new_score += score[nx[i]];

			sort(nx.begin(), nx.end());

			if (new_score > visited[cur.first + 1][nx[0]][nx[1]][nx[2]][nx[3]]) {
				q.push({ cur.first + 1, nx });
				visited[cur.first + 1][nx[0]][nx[1]][nx[2]][nx[3]] = new_score;
			}
		}
	}

	printf("%d\n", ans);
}