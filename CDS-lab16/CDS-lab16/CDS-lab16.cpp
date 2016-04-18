#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

const int Nmax = 1e2 + 17;
const int INF = 1e9;

int graph[Nmax][Nmax] = { 0 };
int flow[Nmax][Nmax] = { 0 };
vector <char> visit;
int s, t;
int n, m;
bool flag = true;

int dfs(int v, int minFlow)
{
	visit[v] = true;

	if (v == t)
	{
		flag = true;
		return minFlow;
	}

	for (int i = 1; i <= n; i++)
		if (graph[v][i] != 0 && visit[i] == 0)
			if (graph[v][i] > 0 && graph[v][i] - flow[v][i] > 0)
			{
				int delta = dfs(i, min(minFlow, graph[v][i] - flow[v][i]));
				flow[v][i] += delta;
				if(flag) return delta;
			}
			else if (graph[v][i] < 0 && flow[i][v] > 0)
			{
				int delta = dfs(i, min(minFlow, flow[i][v]));
				flow[i][v] -= delta;
				if(flag) return delta;
			}

	return 0;
}

int main(void)
{
	freopen("input3.txt", "r", stdin);

	scanf("%d%d", &n, &m);

	while (m--)
	{
		int x, y, weight;
		scanf("%d%d%d", &x, &y, &weight);
		graph[x][y] = weight;
		graph[y][x] = -weight;
	}

	for (int i = 1; i <= n; i++) 
	{
		int plus = 0;
		int minus = 0;
		for (int z = 1; z <= n; z++)
			if (graph[i][z] > 0) minus++;
			else if (graph[i][z] < 0) plus++;

		if (plus == 0 && minus != 0) s = i;
		if (minus == 0 && plus != 0) t = i;
	}

	int totalFlow = 0;

	do
	{
		visit.assign(n + 1, 0);
		flag = false;
		int delta = dfs(s, INF);
		totalFlow += delta;
		if (delta == 0 || !flag) break;
	} while (true);

	printf("Flow: %d", totalFlow);
}