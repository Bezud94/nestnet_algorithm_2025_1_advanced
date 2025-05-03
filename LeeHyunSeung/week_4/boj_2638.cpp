#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;

int arr[100][100] = { 0, };
int visited[100][100] = { 0, };

int main() {
	int n, m;

	scanf("%d %d", &n, &m);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			scanf("%d", &arr[i][j]);
		}
	}

	queue<pair<int, int>> q;
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };

	int ans = 0;
	int cheese_count;
	do {
		// �ʱ�ȭ
		queue<pair<int, int>> del;
		cheese_count = 0;
		memset(visited, 0, sizeof(visited));

		// Ž�� ������: { 0, 0 }
		// �������� �� �����ڸ����� ġ� ������ �ʴ´�.
		q.push({ 0, 0 });
		visited[0][0] = -1;

		// BFS
		pair<int, int> cur;
		while (!q.empty()) {
			cur = q.front(); q.pop();

			for (int dir = 0; dir < 4; dir++) {
				int nx = cur.first + dx[dir];
				int ny = cur.second + dy[dir];

				if (nx < 0 || nx >= n || ny < 0 || ny >= m)
					continue;
				// �ٱ��� �´��� ġ��
				if (arr[nx][ny] == 1) {
					visited[nx][ny]++;
					cheese_count++;
					// �� �� �̻� �´�� �ִٸ� ���� ���ÿ� �߰��Ѵ�.
					// �ߺ��� ���� ���� 2�� ���� ���ÿ� �߰��Ѵ�.
					if (visited[nx][ny] == 2)
						del.push({ nx, ny });
				}
				if (visited[nx][ny])
					continue;

				q.push({ nx, ny });
				visited[nx][ny] = -1;
			}
		}

		// ġ�� ����
		while (!del.empty()) {
			cur = del.front(); del.pop();
			arr[cur.first][cur.second] = 0;
		}

		ans++;
	} while (cheese_count);

	// ans���� 1�� ���ش�.
	// ġ� �� ���ְ� �� ��, ġ� �ִ��� �� ���� �� ���� �����̴�.
	printf("%d\n", ans - 1);
}