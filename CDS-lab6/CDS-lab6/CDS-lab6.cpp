/*************************************
* ��������� �������� ���������     *
* ������������ ��������� �6          *
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
vector <int> gr[Nmax]; // �������� ����
vector <char> visit; // �� ������� �������
vector <int> order; // ������� ������ 
vector <vector<int>> components; // ���������� ������ ��������
vector <int> component; // ������� ���������� ��������

void dfs1(int); // ����� � ������� ��� ���������� ������� ������
void dfs2(int); // ����� ���������� ������ ��������

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
		gr[u].push_back(v);
	}

	visit.assign(n+1, 0);
	for (int i = 1; i <= n; i++)
		if(!visit[i])
			dfs1(i);

	visit.assign(n+1, 0);
	for (int i = 0; i < n; i++)
	{
		int v = order[n - 1 - i];
		if (!visit[v])
		{
			component.clear();
			dfs2(v);
			components.push_back(component);
		}
	}


	printf("Total count of components: %d\n", components.size());
	for (int i = 0; i < components.size(); i++)
	{
		printf("Component %d: ", i + 1);
		for (int z = 0; z < components[i].size(); z++) printf("%d ", components[i][z]);
		printf("\n");
	}
}

void dfs1(int v)
{
	visit[v] = 1;
	for (int i = 0; i < g[v].size(); i++)
		if (!visit[g[v][i]]) dfs1(g[v][i]);
	order.push_back(v);
}

void dfs2(int v)
{
	visit[v] = 1;
	component.push_back(v);
	for (int i = 0; i < gr[v].size(); i++)
		if (!visit[gr[v][i]]) dfs2(gr[v][i]);
}