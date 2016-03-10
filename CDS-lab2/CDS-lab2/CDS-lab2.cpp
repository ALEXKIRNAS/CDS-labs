/*************************************
* ��������� �������� ���������     *
* ������������ ��������� �2          *
* ������ ������� ������� ����� ��-51 *
* ��������� ���������               *
*************************************/

#include <stdio.h>
#include <locale.h>
#include <algorithm>
#pragma warning(disable : 4996)

const int point = 1; // ����� ��� ��� ���������� ����� � �������� 3
const int Nmax = 1e2 + 17; // ������������ ����� �����, ����������� �� �������
const int inf = 1e3; // ���������� �������

int g_s[Nmax][Nmax] = { 0 }; // ������� ��������
int g_e[Nmax][2] = { 0 }; // ������� ��������� ������ � ������
bool loop[Nmax] = { 0 }; // ������� ����

void output1(int&); // ���� �������� 1
void output2(int&); // ���� �������� 2
void output3(int&); // ���� �������� 3

int main(void)
{
	setlocale(LC_CTYPE, "RUSSIAN");

	freopen("input2.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int m; // ʳ������ �����
	int n; // ʳ������ ������
	int v, u; // �������

	scanf_s("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
	{
		scanf_s("%d%d", &v, &u);

		g_e[v][0]++;
		g_e[u][1]++;

		g_s[v][u] = 1;
		if (v == u) loop[v] = 1;
	}

	output1(n);
	output2(n);
	output3(n);
}

void output1(int& n)
{
	printf("�i�������i �����:\n");
	for (int i = 1; i <= n; i++) printf("%3d - %3d\n", i, g_e[i][1]);

	printf("\n�i�������i ������:\n");
	for (int i = 1; i <= n; i++) printf("%3d - %3d\n", i, g_e[i][0]);

	bool f = 1;
	for (int i = 2; i <= n; i++)
		if (g_e[i][0] != g_e[i - 1][0] || g_e[i][0] != g_e[i][1])
		{
			f = 0;
			break;
		}

	if (f)
	{
		printf("���� �����i����.\n");
		printf("������� �����i�����i: %3d\n\n", g_e[1][0]);
	}
	else printf("���� �� �����i����.\n\n");
}

void output2(int& n)
{
	bool f = 1;
	printf("C����� ������ ������:\n");
	for (int i = 1; i <= n; i++) if (g_e[i][0] + g_e[i][1] == 1)
	{
		printf("%d ", i);
		f = 0;
	}
	if (f) printf("�����i ������� �i�����i.\n");
	printf("\n\n");

	printf("������ i���������� ������:\n");
	f = 1;
	for (int i = 1; i <= n; i++) if (g_e[i][0] + g_e[i][1] == 0)
	{
		printf("%d ", i);
		f = 0;
	}
	if (f) printf("I��������i ������� �i�����i.\n");
	printf("\n\n");
}

void output3(int& n)
{
	for (int i = 1; i <= n; i++)
		for (int z = 1; z <= n; z++)
			if (i == z) g_s[i][z] = 0;
			else if (!g_s[i][z]) g_s[i][z] = inf;

			for (int i = 1; i <= n; i++)
				for (int z = 1; z <= n; z++)
					for (int k = 1; k <= n; k++)
						g_s[i][z] = std::min(g_s[i][z], g_s[i][k] + g_s[k][z]);


			int v_e[Nmax] = { 0 }; // ��������������� ����� �������
			for (int i = 1; i <= n; i++)
			{
				for (int z = 1; z <= n; z++) if (g_s[i][z] != inf) v_e[i] = std::max(v_e[i], g_s[i][z]);
				//v_e[i] = std::max(v_e[i], int(loop[i]));
			}

			int d = 0; // ĳ������ �����
			int r = inf; // ����� �����

			for (int i = 1; i <= n; i++)
			{
				d = std::max(d, v_e[i]);
				r = std::min(r, v_e[i]);
			}

			printf("���i�� ����� - %d.\n", r);
			printf("�i����� ����� - %d.\n", d);

			printf("����� �����:\n");
			for (int i = 1; i <= n; i++) if (v_e[i] == r) printf("%d ", i);
			printf("\n\n");

			printf("����� ����� %d:\n", point);
			bool f = 1;
			for (int i = 0; f; i++)
			{
				f = 0;
				int z;
				for (z = 1; z <= n; z++) if (g_s[point][z] == i) { f = 1; break; }
				if (f)
				{
					printf("���� �i��� %d:", i);
					for (; z <= n; z++) if (g_s[point][z] == i) printf(" %d", z);
					printf("\n");
				}
			}
}