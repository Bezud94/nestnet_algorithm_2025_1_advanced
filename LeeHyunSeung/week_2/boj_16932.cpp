/*
������ ĭ���� ����� 1�� ����̶�� �Ѵ�.
����� ũ��� ��翡 ���Ե� 1�� �����̴�.

�迭�� ĭ �ϳ��� �ٲ㼭 ���� �� �ִ� ����� �ִ� ũ�⸦ ���ض�.

��κ��� ��쿡�� 0�� 1�� �ٲ�߰ڳ�.
�ִ� ũ���� ����� ������ �ϴϱ� 1�� 0���� �ٲٸ� ������ ũ�⿡ 1 �̻��� ���ظ� �ְ� �ǰ���.

�� ū ����� ������ �ϴϱ� �����ϸ� �̹� �����ϴ� ��翡 ������ 0�� 1�� �ٲ�� �Ѵ�.

0�� 1�� ������ �ϳ� �̻����� ������ ���� ����ǹǷ� ���ܴ� ����.


n, m: �迭�� ũ�� (2 <= n, m <= 1000).
arr: �迭. (n, m)�� ũ�⸦ ������.

possible: �迭. arr���� ���� �ٲ� ���� ��ǥ�� �����Ѵ�.

1. n, m �Է�
2. arr �Է�
3. arr Ž�� (n * m)
	a. ���� 1�� ���ҿ� ���� ������ 0�� ��ǥ�� possible�� ����

Ž���� �� �� count ���� �����صд�. �⺻���� 1.
visited �迭�� Ž�� ���� �湮�� ���Ҹ� �����Ѵ�. �⺻���� 0.
Ž���� ���ҵ��� ���� visited �迭���� count�� �����Ѵ�.
���ҵ��� ������ ���� �迭 area�� �����Ѵ�. �ε����� count.
�� �� Ž���� ��ĥ ������ count ���� 1 �ø���.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
int arr[1000][1000];
int visited[1000][1000] = { 0, };
int area[100001] = { 0, };

vector<pair<int, int>> possible;

bool is_added(vector<int>, int);

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> arr[i][j];
	
	queue<pair<int, int>> q;
	pair<int, int> cur;
	int dx[4] = { -1, 1, 0, 0 };
	int dy[4] = { 0, 0, -1, 1 };
	int shape_count = 1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (visited[i][j])
				continue;
			if (arr[i][j] < 1)
				continue;

			int area_size = 1;

			q.push({ i, j });
			visited[i][j] = shape_count;
			while (!q.empty()) {
				cur = q.front(); q.pop();
				for (int dir = 0; dir < 4; dir++) {
					int nx = cur.first + dx[dir];
					int ny = cur.second + dy[dir];

					if (nx < 0 || nx >= n || ny < 0 || ny >= m)
						continue;
					if (visited[nx][ny])
						continue;
					if (arr[nx][ny] < 1) {
						if (arr[nx][ny] == 0) {
							possible.push_back({ nx, ny });
							arr[nx][ny] = -1;
						}
						continue;
					}
					q.push({ nx, ny });
					visited[nx][ny] = shape_count;

					area_size++;
				}
			}
			area[shape_count] = area_size;

			shape_count++;
		}
	}
	
	int ans = 0;

	for (int i = 0; i < possible.size(); i++) {
		vector<int> already_added;
		int value = 1;

		cur = possible[i];
		for (int dir = 0; dir < 4; dir++) {
			int nx = cur.first + dx[dir];
			int ny = cur.second + dy[dir];

			if (nx < 0 || nx >= n || ny < 0 || ny >= m)
				continue;
			if (visited[nx][ny] < 1)
				continue;
			if (is_added(already_added, visited[nx][ny]))
				continue;

			value += area[visited[nx][ny]];
			already_added.push_back(visited[nx][ny]);
		}
		
		if (value > ans)
			ans = value;
	}

	cout << ans << endl;
}

bool is_added(vector<int> list, int value) {
	for (int i = 0; i < list.size(); i++) {
		if (list[i] == value)
			return true;
	}
	return false;
}