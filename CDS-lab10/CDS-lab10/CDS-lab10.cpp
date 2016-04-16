#include <stdio.h>
#include <vector>
#include <stack>
using namespace std;

const int Nmax = 1e2;

int g[Nmax][Nmax] = { 0 };
int rang[Nmax] = { 0 };

int main(void)
{

	freopen("input1.txt", "r", stdin);

	int n, m;
	scanf("%d%d", &n, &m);

	while (m--)
	{
		int from, to;
		scanf("%d%d", &from, &to);
		g[from][to]++; 
	}

	for (int i = 1; i <= n; i++)
		for (int z = 1; z <= n; z++)
			rang[i] += g[i][z];

	int v1 = -1;
	int v2 = -1;
	bool bad = false;

	for (int i = 1; i <= n; i++)
			if (rang[i] % 2)
				if (v1 == -1) v1 = i;
				else if (v2 == -1) v2 = i;
				else bad = true;

	if (v2 != -1)
	{
		g[v1][v2]++;
		g[v2][v1]++;
	}

	int start = 1;
	while (rang[start] == 0) start++;

	stack <int> st;
	st.push(start);
	vector <int> res;

	while (!st.empty())
	{
		int v = st.top();
		int i;

		for (i = 1; i <= n; i++) if (g[v][i]) break;

		if (i == n + 1)
		{
			res.push_back(v);
			st.pop();
		}
		else 
		{
			g[v][i]--;
			g[i][v]--;
			st.push(i);
		}
	}

	if (v2 != -1)
		for (int i = 0; i+1 < res.size(); i++)
			if ((res[i] == v1 && res[i + 1] == v2) || (res[i] == v2 && res[i + 1] == v1))
			{
				vector <int> res2;
				for (int z = i + 1; z < res.size(); z++) res2.push_back(res[z]);
				for (int z = 1; z <= i; z++) res2.push_back(res[z]);
				res = res2;
				break;
			}

	for (int i = 1; i <= n; i++)
		for (int z = 1; z <= n; z++)
			if (g[i][z]) bad = true;

	if (bad) printf("Graf is bad.\n");
	else if (v2 == -1)
	{
		printf("Euler circle:\n");
		for (int i = 0; i < res.size(); i++) printf("%d ", res[i]);
	}
	else
	{
		printf("Euler path:\n");
		for (int i = 0; i < res.size(); i++) printf("%d ", res[i]);
	}
}