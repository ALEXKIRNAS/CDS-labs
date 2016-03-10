/*************************************
* ��������� �������� ���������     *
* ������������ ��������� �3          *
* ������ ������� ������� ����� ��-51 *
* ��������� ���������               *
*************************************/

#include <stdio.h>
#include <locale.h>
#include <algorithm>
#include <vector>
#pragma warning(disable : 4996)

const int Nmax = 1e2 + 17; // ������������ ����� �����, ����������� �� �������
const int vertex = 1; // ����� ������� ��� ��� ����������� ���������

int g_s[Nmax][Nmax] = { 0 }; // ������� ��������
bool visit[Nmax] = { 0 }; // ³����� �������
std::vector <int> way; // �������
int dfs_number = 0; // BFS-�����

void dfs(int, int&); // ����� ����� � �������
void bfs(int, int&); // ����� ����� � ������

int main(void)
{

	freopen("input3.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int m; // ʳ������ �����
	int n; // ʳ������ ������
	int v, u; // �������

	scanf_s("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf_s("%d%d", &v, &u);

		g_s[v][u] = 1;
	}

	printf("DFS:\n");
	printf("Vertex DFS-number Stack\n");
	dfs(vertex, n);

	for (int i = 0; i <= n; i++) visit[i] = 0;

	printf("\n\nBFS:\n");
	printf("Vertex BFS-number Queue\n");
	bfs(vertex, n);
}

void dfs(int v, int& n)
{
	visit[v] = 1;
	way.push_back(v);
	dfs_number++;
	printf("%-7c%-12d", 'a' + v - 1, dfs_number);
	for (int i = 0; i<way.size(); i++) printf("%c", 'a' + way[i] - 1);
	printf("\n");

	for (int i = 1; i <= n; i++) if (g_s[v][i] && !visit[i])  dfs(i, n);

	way.pop_back();
	printf("%-7c%-12c", '-', '-');
	for (int i = 0; i<way.size(); i++) printf("%c", 'a' + way[i] - 1);
	printf("\n");
}

void bfs(int v, int& n)
{
	way.clear();
	way.push_back(v);
	visit[v] = 1;
	int bfs_number = 1;

	printf("%-7c%-12d", 'a' + v - 1, bfs_number);
	for (int i = 0; i<way.size(); i++) printf("%c", 'a' + way[i] - 1);
	printf("\n");


	while (!way.empty())
	{
		v = way.front();
		for (int i = 1; i <= n; i++)
			if (!visit[i] && g_s[v][i])
			{
				way.push_back(i);
				visit[i] = 1;
				bfs_number++;
				printf("%-7c%-12d", 'a' + i - 1, bfs_number);

				for (int z = 0; z<way.size(); z++) printf("%c", way[z] - 1 + 'a');
				printf("\n");
			}

		way.erase(way.begin(), way.begin() + 1);

		printf("%-7c%-12c", '-', '-');
		for (int z = 0; z<way.size(); z++) printf("%c", way[z] - 1 + 'a');
		printf("\n");
	}
}