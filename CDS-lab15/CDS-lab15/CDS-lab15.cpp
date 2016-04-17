#include <stdio.h>
#include <set>
#include <vector>
using std::set;
using std::vector;
using std::pair;
using std::make_pair;

const int Nmax = 1e2 + 17;
const int INF = 1e9;

set < pair<int, int> > edges;
vector < pair<int, int> > graph[Nmax];

int main(void)
{
	freopen("input1.txt", "r", stdin);

	int n, m;
	scanf("%d%d", &n, &m);
	
	while (m--)
	{
		int x, y, weight;
		scanf("%d%d%d", &x, &y, &weight);
		graph[x].push_back(make_pair(weight, y));
		graph[y].push_back(make_pair(weight, x));
	}

	vector<int> dist(n+1, INF);
	vector<char> used(n+1, 0);

	dist[1] = 0;
	edges.insert(make_pair(0, 1));

	printf("Vertex - Edge weight:\n");
	int total_weight = 0;

	for (int i = 0; i < n; i++)
	{
		int v = edges.begin()->second;
		edges.erase(edges.begin());
		used[v] = true;
		total_weight += dist[v];

		printf("%6d - %d\n", v, dist[v]);

		for (int z = 0; z < graph[v].size(); z++)
		{
			int to = graph[v][z].second;
			int weight = graph[v][z].first;
			if (dist[to] > weight && !used[to])
			{
				edges.erase(make_pair(dist[to], to));
				dist[to] = weight;
				edges.insert(make_pair(dist[to], to));
			}
		}
	}

	printf("Total weight: %d\n", total_weight);
}