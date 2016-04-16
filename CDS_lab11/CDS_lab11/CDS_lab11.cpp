#include <stdio.h>
#include <vector>
#include <algorithm>
using std::vector;
using std::pair;

const int Nmax = 17; // !!!!!! Don`t make it bigger !!!!!!!!!
const int INF = 1e9;

double d[Nmax][1 << Nmax];
double g[Nmax][Nmax] = { 0 };

void distance(int& n)
{
	for (int i = 0; i < n; i++)
		for (int z = i+1; z < n; z++)
			g[i][z] = g[z][i] = INF;
}

double findCheapest(int v, int mask, int& n)
{
	if (d[v][mask] != INF)
		return d[v][mask];

	for (int i = 0; i < n; i++)
		if (g[v][i] != INF && ((mask & (1<<i)) != 0) )
			d[v][mask] = std::min(d[v][mask], findCheapest(i, mask - (1 << i), n) + g[v][i]);
	
	return d[v][mask];
}

double travellingSalesmanProblem(int start, int& n)
{
	for (int i = 0; i < n; i++)
		for (int mask = 0; mask < (1 << n); mask++)
			d[i][mask] = INF;

	d[start][0] = 0;
	return findCheapest(start, (1 << n) - 1, n);
}

void printfPath(int start, int& n)
{
	int mask = (1 << n) - (1 << start);
	vector <int> path;
	path.push_back(start);

	while (mask != 0)
		for (int i = 0; i < n; i++)
			if (g[start][i] != INF && ((mask & (1 << i)) != 0) && d[start][mask] == d[i][mask - (1 << i)] + g[start][i])
			{
				path.push_back(i);
				start = i;
				mask -= (1 << i);
			}

	for (int i = 0; i < path.size() - 1; i++) printf("%d ", path[i] + 1);
}

void printfPath(int &n)
{
	int start = n - 1;
	int mask = (1 << n) - 1;
	vector <int> path;
	path.push_back(start);

	while (mask != 0)
		for (int i = 0; i < n; i++)
			if (g[start][i] != INF && ((mask & (1 << i)) != 0) && d[start][mask] == d[i][mask - (1 << i)] + g[start][i])
			{
				path.push_back(i);
				start = i;
				mask -= (1 << i);
			}

	for (int i = 1; i < path.size(); i++) printf("%d ", path[i] + 1);
}

int main(void)
{
	const int start = 0;

	freopen("input2.txt", "r", stdin);

	int n, m;
	scanf("%d%d", &n, &m);

	distance(n);

	for (int i = 0; i < m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);

		x--; y--;
		g[x][y] = 1;
 	}


	double weight = travellingSalesmanProblem(start, n);
	
	if (weight != INF) {
		printf("Hamiltonian circle:\n");
		printfPath(start, n);
	}
	else
	{
		for (int i = 0; i < n; i++)
			g[i][n] = g[n][i] = 1;

		n++;
		weight = travellingSalesmanProblem(n-1, n);
		if (weight == INF) printf("No hamiltonian path or circle.");
		else
		{
			printf("Hamiltonian path:\n");
			printfPath(n);
		}
	}

}