/*************************************
* ��������� �������� ���������     *
* ������������ ��������� �1          *
* ������ ������� ������� ����� ��-51 *
* ��������� ���������               *
*************************************/

#include <stdio.h>
#pragma warning(disable : 4996)

#define max_len 4

const int Nmax = 1e2 + 17; // ������������ ����� �����, ����������� �� �������

char g_s[Nmax][Nmax] = { 0 }; // ������� �������� �����
char g_i[Nmax][Nmax * Nmax] = { 0 }; // ������� ������������ �����

void output(int&, int&); // ��������� �������

int main(void)
{
	freopen("input1.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int m; // ʳ������ �����
	int n; // ʳ������ ������

	scanf_s("%d %d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		int v, u;
		scanf_s("%d %d", &v, &u);

		g_s[v][u] += 1;

		if (v != u)
		{
			g_i[v][i] = -1;
			g_i[u][i] = 1;
		}
		else g_i[v][i] = 2;

	}

	output(n, m);
}

void output(int &n, int &m)
{
	printf("Adjacency matrix:\n");

	for (int i = 0; i<max_len - 3; i++) printf(" ");
	printf("V\\V |");
	for (int i = 1; i <= n; i++) printf("%*d |", max_len, i);
	printf("\n");
	for (int i = (max_len + 2)*(n + 1); i>0; i--) printf("-");
	printf("\n");

	for (int i = 1; i <= n; i++, printf("\n")) {
		printf("%*d |", max_len, i);
		for (int z = 1; z <= n; z++) printf("%*d |", max_len, g_s[i][z]);
		printf("\n");
		for (int i = (max_len + 2)*(n + 1); i>0; i--) printf("-");
	}


	printf("\nIncidence matrix:\n");
	for (int i = 0; i<max_len - 3; i++) printf(" ");
	printf("V\\E |");
	for (int i = 1; i <= m; i++) printf("%*d |", max_len, i);
	printf("\n");
	for (int i = (max_len + 2)*(m + 1); i>0; i--) printf("-");
	printf("\n");

	for (int i = 1; i <= n; i++, printf("\n")) {
		printf("%*d |", max_len, i);
		for (int z = 1; z <= m; z++) printf("%*d |", max_len, g_i[i][z]);
		printf("\n");
		for (int i = (max_len + 2)*(m + 1); i>0; i--) printf("-");
	}
}