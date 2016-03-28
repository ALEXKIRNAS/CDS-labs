#include <iostream>
const int NotUsed = system("color F0");

int g[110][110];

void dei(int s, int f, int n) {

	__int64 dis[110], u, i, index, count;
	bool vis[110] = { 0 };
	for (i = 0; i<110; i++) { dis[i] = INT_MAX; vis[i] = 0; }
	dis[s] = 0;
	for (count = 0; count < n - 1; count++) {
		int min = INT_MAX;
		for (i = 0; i<n; i++) if (!vis[i] && dis[i]<min) { min = dis[i]; index = i; }
		u = index;
		vis[u] = 1;
		for (i = 0; i<n; i++) if (!vis[i] && g[u][i] && dis[u] != INT_MAX && dis[u] + g[u][i]<dis[i]) dis[i] = dis[u] + g[u][i];
	}
	if (dis[f] != INT_MAX) printf("%d", dis[f]);
	else printf("-1");
}

int main() {
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w+", stdout);
	int n, s, f, i, j;
	scanf("%d%d%d", &n, &s, &f);
	for (i = 0; i<n; i++) for (j = 0; j<n; j++) {
		scanf("%d", &g[i][j]);
		if (g[i][j]<0) g[i][j] = INT_MAX;
	}
	dei(s - 1, f - 1, n);
	printf("\n");
}