#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// u: ������ ������� ��ǥ �ε���
// v: ������ �������� ��ǥ �ε���
// dist: ������ ����
struct Edge {
	int u;
	int v;
	double dist;
};

bool greaterDist(Edge, Edge);

int n, m;
int x[1000], y[1000];
vector<Edge> edge;
int vertex[1000];

int main() {
	scanf("%d %d", &n, &m);

	// �� ����� ��ǥ �Է�
	for (int i = 0; i < n; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}
	// ����� ��� �� �Է�
	for (int i = 0; i < m; i++) {
		int mx, my;
		scanf("%d %d", &mx, &my);
		mx--; my--;
		// u < v �����ϵ��� �Ҵ��ϱ�
		if (mx < my)
			edge.push_back({ mx, my, 0 });
		else
			edge.push_back({ my, mx, 0 });

	}
	sort(edge.begin(), edge.end(), greaterDist);
	
	// �Ÿ� ���� ���� - ������ �׷����ϱ� u < v�� ��츸 ����
	int m_index = 0;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			// �̹� ����Ǿ����� �˻�
			if (m_index < m && edge[m_index].u == i && edge[m_index].v == j) {
				m_index++;
				continue;
			}

			long long dx = x[i] - x[j];
			long long dy = y[i] - y[j];
			edge.push_back({ i, j, sqrt(dx * dx + dy * dy) });
		}
	}

	// �Ÿ��� ���� ������������ ����
	sort(edge.begin(), edge.end(), greaterDist);

	// ũ�罺Į �˰���
	double ans = 0;
	for (int i = 0; i < n; i++)
		vertex[i] = i;
	for (int i = 0; i < edge.size(); i++) {
		if (vertex[edge[i].u] != vertex[edge[i].v]) {
			ans += edge[i].dist;

			int set = vertex[edge[i].v];
			for (int j = 0; j < n; j++)
				if (vertex[j] == set)
					vertex[j] = vertex[edge[i].u];
		}
	}

	printf("%.2lf\n", ans);
}

bool greaterDist(Edge e1, Edge e2) {
	if (e1.dist == e2.dist) {
		if (e1.u == e2.u)
			return e1.v < e1.v;
		else
			return e1.u < e2.u;
	}
	else
		return e1.dist < e2.dist;
}