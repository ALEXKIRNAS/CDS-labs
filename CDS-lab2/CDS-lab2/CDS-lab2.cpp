/*************************************
* Компютерні дискретні структури     *
* Лабораторний практикум №2          *
* Роботу виконав студент групи ІП-51 *
* Зарічковий Олександр               *
*************************************/

#include <stdio.h>
#include <locale.h>
#include <algorithm>
#pragma warning(disable : 4996)

const int point = 1; // Точка для якої виводяться яруси в підзадачі 3
const int Nmax = 1e2 + 17; // Максимальний розмір графу, допустимого на обробку
const int inf = 1e3; // Нескінченна відстань

int g_s[Nmax][Nmax] = { 0 }; // Матриця суміжності
int g_e[Nmax][2] = { 0 }; // Матриця півстепенів заходу і виходу
bool loop[Nmax] = { 0 }; // Признак петлі

void output1(int&); // Вивід підзадачі 1
void output2(int&); // Вивід підзадачі 2
void output3(int&); // Вивід підзадачі 3

int main(void)
{
	setlocale(LC_CTYPE, "RUSSIAN");

	freopen("input2.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);

	int m; // Кількість ребер
	int n; // Кількість вершин
	int v, u; // Вершини

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
	printf("Пiвстепенi входу:\n");
	for (int i = 1; i <= n; i++) printf("%3d - %3d\n", i, g_e[i][1]);

	printf("\nПiвстепенi виходу:\n");
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
		printf("Граф однорiдний.\n");
		printf("Степень однорiдностi: %3d\n\n", g_e[1][0]);
	}
	else printf("Граф не однорiдний.\n\n");
}

void output2(int& n)
{
	bool f = 1;
	printf("Cписок висячх вершин:\n");
	for (int i = 1; i <= n; i++) if (g_e[i][0] + g_e[i][1] == 1)
	{
		printf("%d ", i);
		f = 0;
	}
	if (f) printf("Висячi вершини вiдсутнi.\n");
	printf("\n\n");

	printf("Список iзольованих вершин:\n");
	f = 1;
	for (int i = 1; i <= n; i++) if (g_e[i][0] + g_e[i][1] == 0)
	{
		printf("%d ", i);
		f = 0;
	}
	if (f) printf("Iзольованi вершини вiдсутнi.\n");
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


			int v_e[Nmax] = { 0 }; // ексцентриситети кожної вершини
			for (int i = 1; i <= n; i++)
			{
				for (int z = 1; z <= n; z++) if (g_s[i][z] != inf) v_e[i] = std::max(v_e[i], g_s[i][z]);
				//v_e[i] = std::max(v_e[i], int(loop[i]));
			}

			int d = 0; // Діаметри графу
			int r = inf; // Радіус графу

			for (int i = 1; i <= n; i++)
			{
				d = std::max(d, v_e[i]);
				r = std::min(r, v_e[i]);
			}

			printf("Радiус графа - %d.\n", r);
			printf("Дiаметр графа - %d.\n", d);

			printf("Центр графу:\n");
			for (int i = 1; i <= n; i++) if (v_e[i] == r) printf("%d ", i);
			printf("\n\n");

			printf("Яруси точки %d:\n", point);
			bool f = 1;
			for (int i = 0; f; i++)
			{
				f = 0;
				int z;
				for (z = 1; z <= n; z++) if (g_s[point][z] == i) { f = 1; break; }
				if (f)
				{
					printf("Ярус рiвня %d:", i);
					for (; z <= n; z++) if (g_s[point][z] == i) printf(" %d", z);
					printf("\n");
				}
			}
}