/*************************************
* Компютерні дискретні структури     *
* Лабораторний практикум №1          *
* Роботу виконав студент групи ІП-51 *
* Зарічковий Олександр               *
*************************************/

#include <stdio.h>
#pragma warning(disable : 4996)

#define max_len 4

const int Nmax = 1e2 + 17; // Максимальний розмір графу, допустимого на обробку

char g_s[Nmax][Nmax] = { 0 }; // Матриця суміжності графу
char g_i[Nmax][Nmax * Nmax] = { 0 }; // Матриця інцидентності графу

void output(int&, int&); // Виведення матриць

int main(void)
{
	freopen("input1.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	int m; // Кількість ребер
	int n; // Кількість вершин

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