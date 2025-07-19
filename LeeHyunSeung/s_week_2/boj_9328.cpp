#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

struct P { int x; int y; };

int h, w;
char key[27];

char map[100][101];
bool visited[100][100];
queue<P> alphabet[26];
vector<P> entrance;

void OpenTheDoor(int number) {
	P cur;
	while (!alphabet[number].empty()) {
		cur = alphabet[number].front(); alphabet[number].pop();
		map[cur.x][cur.y] = '.';
		if (cur.x == 0 || cur.x == h - 1 || cur.y == 0 || cur.y == w - 1) {
			entrance.push_back({ cur.x, cur.y });
		}
	}
}

int main() {
	int t;
	
	scanf("%d", &t);

	for (int tt = 0; tt < t; tt++) {
		// �ʱ�ȭ
		for (int i = 0; i < 26; i++) {
			alphabet[i] = queue<P>();
		}
		entrance = vector<P>();

		// �Է�
		scanf("%d %d", &h, &w);

		for (int i = 0; i < h; i++) {
			scanf("%s", map[i]);
		}

		scanf("%s", key);

		// �� ��ġ Ž��
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if ('A' <= map[i][j] && map[i][j] <= 'Z') {
					alphabet[map[i][j] - 'A'].push({ i, j });
				}
			}
		}

		// ������ �ִ� Ű�� �� ����
		if (key[0] != '0') {
			int i = 0;
			while (key[i] != '\0') {
				OpenTheDoor(key[i] - 'a');
				i++;
			}
		}

		// ���� �����ڸ��� ���� �ƴ� �� Ž��
		// ����, �Ʒ���
		for (int i = 0; i < w; i++) {
			if (map[0][i] != '*' && !('A' <= map[0][i] && map[0][i] <= 'Z'))
				entrance.push_back({ 0, i });
			if (map[h - 1][i] != '*' && !('A' <= map[h - 1][i] && map[h - 1][i] <= 'Z'))
				entrance.push_back({ h - 1, i });
		}
		// ����, ������
		for (int i = 1; i < h - 1; i++) {
			if (map[i][0] != '*' && !('A' <= map[i][0] && map[i][0] <= 'Z'))
				entrance.push_back({ i, 0 });
			if (map[i][w - 1] != '*' && !('A' <= map[i][w - 1] && map[i][w - 1] <= 'Z'))
				entrance.push_back({ i, w - 1 });
		}

		int ans = 0;

		queue<P> q;
		P cur;

		int dx[4] = { -1, 1, 0, 0 };
		int dy[4] = { 0, 0, -1, 1 };

		bool doing = true;
		while (doing) {
			doing = false;

			memset(visited, false, sizeof(visited));

			for (int i = 0; i < entrance.size(); i++) {
				cur = entrance[i];
				q.push({ cur.x, cur.y });
				visited[cur.x][cur.y] = true;
			}

			while (!q.empty()) {
				cur = q.front(); q.pop();

				// ����, ���� ó��
				if (map[cur.x][cur.y] == '$') {
					doing = true;
					ans++;
					map[cur.x][cur.y] = '.';
				}
				if ('a' <= map[cur.x][cur.y] && map[cur.x][cur.y] <= 'z') {
					doing = true;
					OpenTheDoor(map[cur.x][cur.y] - 'a');
					map[cur.x][cur.y] = '.';
				}

				for (int dir = 0; dir < 4; dir++) {
					int nx = cur.x + dx[dir];
					int ny = cur.y + dy[dir];

					if (nx < 0 || nx >= h || ny < 0 || ny >= w)
						continue;
					if (visited[nx][ny])
						continue;
					if (map[nx][ny] == '*' || ('A' <= map[nx][ny] && map[nx][ny] <= 'Z'))
						continue;

					q.push({ nx, ny });
					visited[nx][ny] = true;
				}
			}
		}

		printf("%d\n", ans);
	}
}