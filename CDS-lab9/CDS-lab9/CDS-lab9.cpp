#include <iostream>
#include <set>
#include <vector>
#include <time.h>
using namespace std;

const int Nmax = 1e2 + 17; // Max size of graph
const int INF = 1e9;
const int start = 1; // Start point for way search

vector < pair <int, int> > g[Nmax]; // Graph
// 1 - weight, 2 - to

void prepare(int d[][Nmax], int path[][Nmax], int& n) {
	for (int i = 0; i <= n; i++)
		for (int z = 0; z <= n; z++) {
			d[i][z] = INF;
			path[i][z] = i;
		}

	for (int i = 1; i <= n; i++) {
		d[i][i] = 0;
		path[i][i] = -1;
	}

	for (int i = 1; i <= n; i++) {
		int size = g[i].size();
		for (int z = 0; z < size; z++)
			d[i][g[i][z].second] = g[i][z].first;
	}
}

void output(int d[][Nmax], int path[][Nmax], int& n){
	printf("Distance:\n");
	for (int i = 1; i <= n; i++, printf("\n"))
		for (int z = 1; z <= n; z++) 
			if(d[i][z] < INF/10) printf("%6d", d[i][z]);
			else printf("%6s", "INF");

	printf("\nPaths:\n");
	for (int z = 1; z <= n; z++, printf("\n")) {
		vector <int> way;
		int end = z;  // End point for way search
		printf("%d -> %d: ", start, end);

		while (end != -1) {
			way.push_back(end);
			end = path[start][end];
		}

		for (int j = way.size() - 1; j >= 0; j--) printf("%d ", way[j]);
	}
}

bool Ford_Belman(vector <int>& s, int& n) {
	s.assign(n+1, 0);
	bool isNegativeCircul = false;

	for (int i = 0; i <= n; i++) {

		for (int j = 1; j <= n; j++) {
			int size = g[j].size();
			for (int z = 0; z < size; z++) 
				if (s[g[j][z].second] > s[j] + g[j][z].first) {
					s[g[j][z].second] = s[j] + g[j][z].first;
					if (i == n) isNegativeCircul = true;
				}
		}
	}

	return isNegativeCircul;
}

void Floid(int& n) {

	time_t clocks = clock();

	// Prepare
	int d[Nmax][Nmax];
	int path[Nmax][Nmax] = { 0 };

	prepare(d, path, n);

	// Algorithm
	for (int j = 1; j <= n; j++)
		for (int i = 1; i <= n; i++)
			for (int z = 1; z <= n; z++)
				if (d[i][z] > d[i][j] + d[j][z]) {
					d[i][z] = d[i][j] + d[j][z];
					path[i][z] = path[j][z];
				}
	
	output(d, path, n);
	clocks = clock() - clocks;

	printf("Runtime: %d ms\n\n", clocks);
}

void Deijstra(int* d, int* path, int& n, int start, vector <int>& s) {
	set < pair <int, int> > q; 

	d[start] = 0;
	path[start] = -1;
	q.insert(make_pair(0, start));
	while (!q.empty()) {
		
		int v = q.begin()->second;
		q.erase(q.begin());

		int size = g[v].size();
		for (int i = 0; i < size; i++) {
			int to = g[v][i].second;
			int len = g[v][i].first + s[v] - s[to];

			if (d[to] > d[v] + len) {
				q.erase(make_pair(d[to], to));
				d[to] = d[v] + len;
				q.insert(make_pair(d[to], to));
				path[to] = v;
			}
		}
	}
}

void Johnson(int &n) {
	time_t clocks = clock();

	//Prepare
	vector <int> s;
	if (Ford_Belman(s, n)) return;

	int d[Nmax][Nmax];
	int path[Nmax][Nmax] = { 0 };

	for (int i = 0; i <=n; i++)
		for (int z = 0; z <= n; z++) 
			d[i][z] = INF;
		

	// Algorithm
	for (int i = 1; i <= n; i++)
		Deijstra(d[i], path[i], n, i, s);

	for (int i = 1; i <= n; i++)
		for (int z = 1; z <= n; z++)
			d[i][z] = d[i][z] - s[i] + s[z];

	output(d, path, n);

	clocks = clock() - clocks;

	printf("Runtime: %d ms\n\n", clocks);
}

int main(void) {
	freopen("input.txt", "r", stdin);

	int n, m;
	cin >> n >> m;

	// Reading graph
	for (int i = 0; i < m; i++) {
		int w, from, to;
		cin >> from >> to >> w;

		g[from].push_back(make_pair(w, to));
	}

	printf("Floid:\n");
	Floid(n);

	printf("Jonson:\n");
	Johnson(n);
}