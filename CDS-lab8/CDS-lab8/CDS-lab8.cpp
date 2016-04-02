#include <iostream>
#include <vector>

using namespace std;

struct edge {
	int a, b, cost;
};

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w+", stdout);
	int n, m, i, z, INF = 1e7 + 7;
	vector <edge> q;
	scanf("%d%d", &n, &m);
	vector <int> d(n, INF);


	edge temp;
	for (i = 0; i<m; i++) {
		scanf("%d%d%d", &temp.a, &temp.b, &temp.cost);
		temp.a--; temp.b--;
		q.push_back(temp);
	}

	d[0] = 0;
	while (1) {
		bool f = 1;
		for (z = 0; z<m; z++) if (d[q[z].a] < INF) if (d[q[z].b] > d[q[z].a] + q[z].cost) {
			d[q[z].b] = d[q[z].a] + q[z].cost;
			f = 0;
		}
		if (f) break;
	}

	for (i = 0; i<n; i++) if (d[i] == INF) printf("%d ", 30000); else printf("%d ", d[i]);
}