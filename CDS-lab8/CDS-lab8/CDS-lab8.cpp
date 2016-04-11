Refactoring of code... special for her...
#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9;

struct edge 
{
	int from;
	int to;
	int weight;
};

vector <edge> graph;
vector <int> dist; // DISTANCE
vector <int> path;

void input(int&n)
{
	int m;
	edge temp;
	FILE* file = fopen("input.txt", "rt"); // REDING FROM FILE

	fscanf(file, "%d%d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		fscanf(file, "%d%d%d", &temp.from, &temp.to, &temp.weight);
		graph.push_back(temp);
	}

	fclose(file);
}

void ford_belman(int& n, int start)
{
	bool isNegativeCircul = false;
	dist.assign(n+1, INF); // ~ int dist[n];
	dist[start] = 0;
	path.assign(n+1, -1);

	for (int i = 0; i <= n; i++)
		for (int j = 0; j < graph.size(); j++)
		{
			int from = graph[j].from;
			int to = graph[j].to;
			int weight = graph[j].weight;

			if (dist[to] > dist[from] + weight)
			{
				dist[to] = dist[from] + weight;
				path[to] = from;
				if (i == n) isNegativeCircul = true;
			}
		}

	if (isNegativeCircul)
	{
		printf("Error. Negative circul in graph!\n");
		system("pause");
		exit(-1);
	}
}

void output(int& n)
{
	int start;
	int end;
	int choise;

	printf("Make choice:\n");
	printf("1. Out path and distance from point <start> to <end>;\n2. Out distance from point <start> to other points.\n");
	scanf("%d", &choise);

	if (choise == 1)
	{
		printf("Start = ");
		scanf("%d", &start);
		printf("End = ");
		scanf("%d", &end);

		ford_belman(n, start);

		printf("Distance: %d", dist[end]);

		vector <int> way;
		while (end != -1)
		{
			way.push_back(end);
			end = path[end];
		}

		printf("\nPath:\n");
		for (int i = way.size() - 1; i >= 0; i--) printf("%d ", way[i]);
	}
	else if (choise == 2)
	{
		printf("Start = ");
		scanf("%d", &start);

		ford_belman(n, start);

		printf("Distance to:\n");
		for (int i = 1; i <= n; i++) printf("%d - %d\n", i, dist[i]);
	}
	else
	{
		printf("Input error!\n");
		system("pause");
		exit(-1);
	}

	system("pause");
}

int main(void)
{
	int n;
	input(n);
	output(n);
}