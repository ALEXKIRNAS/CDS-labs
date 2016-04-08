#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int Nmax = 1e3 + 17; // Max size of graph
const int INF = 1e9;
const int start = 1; // Starth point for way search

vector < pair <int, int> > g[Nmax]; // Graph
// 1 - weight, 2 - to

void prepare(int d[][Nmax], int path[][Nmax], int& n) {
	for (int i = 0; i <= n; i++)
		for (int z = 0; z <= n; z++) {
			d[i][z] = INF;
			path[i][z] = -1;
		}

	for (int i = 1; i < n; i++)
		d[i][i] = 0;

	for (int i = 1; i <= n; i++) {
		int size = g[i].size();
		for (int z = 0; z < size; z++)
			d[i][g[i][z].second] = g[i][z].first;
	}
}

void output(int d[][Nmax], int path[][Nmax], int& n){
	printf("Distance:\n");
	for (int i = 1; i <= n; i++, printf("\n"))
		for (int z = 1; z <= n; z++)  printf("%6d", d[i][z]);

	printf("\nPaths:\n");
	for (int z = 1; z <= n; z++, printf("\n")) {
		vector <int> way;
		int end = z;  // End point for way search

		while (path[start][end] != -1) {
			way.push_back(end);
			end = path[start][end];
		}

		for (int j = way.size() - 1; j >= 0; j--) printf("%d ", way[j]);
	}
	printf("\n\n");
}

bool Ford_Belman(vector <int>& s, int& n) {
	s.assign(n, 0);
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

	// Prepare
	int d[Nmax][Nmax];
	int path[Nmax][Nmax] = { 0 };

	prepare(d, path, n);

	// Algorithm
	for (int i = 1; i <= n; i++)
		for (int z = 1; z <= n; z++)
			for (int j = 1; j <= n; j++)
				if (d[i][z] > d[i][j] + d[j][z]) {
					d[i][z] = d[i][j] + d[j][z];
					path[i][z] = j;
				}
	
	output(d, path, n);
}

void Deijstra(int* d, int* path, int& n) {

}

void Johnson(int &n) {

	//Prepare
	vector <int> s;
	if (!Ford_Belman(s, n)) return;

	int d[Nmax][Nmax];
	int path[Nmax][Nmax];

	prepare(d, path, n);

	// Algorithm
	for (int i = 1; i <= n; i++)
		Deijstra(d[i], path[i], n);

	output(d, path, n);
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

	Floid(n);
	Johnson(n);
}