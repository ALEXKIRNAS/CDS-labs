/*************************************
* ��������� �������� ���������     *
* ������������ ��������� �5          *
* ������ ������� ������� ����� ��-51 *
* ��������� ���������               *
*************************************/

#include <stdio.h>
#include <vector>
#pragma warning(disable : 4996)
const int NotUsed = system("color F0");
using std::vector;

const int Nmax = 1e2 + 17; // ������������ ����� �����, ����������� �� �������
vector <int> g[Nmax]; // ����
bool visit[Nmax] = { 0 };
vector <int> TS;

void topologicalSort(int&);
void dfs(int);

int main(void)
{
	freopen("input2.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int m; // ʳ������ �����
	int n; // ʳ������ ������

	scanf_s("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int v, u;
		scanf_s("%d %d", &v, &u);
		g[v].push_back(u);
	}
	topologicalSort(n);

	printf("Topological sort:\n");
	for (int i = 0; i < TS.size(); i++)
		printf("%d ", TS[i]);
}

// ����� � ������� � ������������� ���� ������
void dfs(int v)
{
	visit[v] = 1;
	for (int i = 0; i < g[v].size(); i++)
		if (!visit[g[v][i]]) dfs(g[v][i]);
	TS.push_back(v);
}

// ���������� ����������
void topologicalSort(int& n)
{
	for (int i = 1; i <= n; i++)
		if (!visit[i]) dfs(i);
	std::reverse(TS.begin(), TS.end());
}