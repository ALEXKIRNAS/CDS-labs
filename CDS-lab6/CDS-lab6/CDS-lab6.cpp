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
vector <int> gr[Nmax]; // �������� ����
vector <char> visit; // �� ������� �������
vector <int> order; // ������� ������ 
vector <vector<int>> components; // ���������� ������ ��������
vector <int> component; // ������� ���������� ��������

void dfs1(int); // ����� � ������� ��� ���������� ������� ������
void dfs2(int); // ����� ���������� ������ ��������

int main(void)
{

}

void dfs1(int v)
{
	visit[v] = 1;
	for (int i = 0; i < g[v].size(); i++)
		if (!visit[g[v][i]]) dfs1(g[v][i]);
	order.push_back(v);
}