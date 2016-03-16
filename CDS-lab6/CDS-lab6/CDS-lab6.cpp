/*************************************
* Компютерні дискретні структури     *
* Лабораторний практикум №5          *
* Роботу виконав студент групи ІП-51 *
* Зарічковий Олександр               *
*************************************/

#include <stdio.h>
#include <vector>
#pragma warning(disable : 4996)
const int NotUsed = system("color F0");
using std::vector;

const int Nmax = 1e2 + 17; // Максимальний розмір графу, допустимого на обробку
vector <int> g[Nmax]; // Граф
vector <int> gr[Nmax]; // Обернени граф
vector <char> visit; // Чи відвідана вершина
vector <int> order; // Порядок виходу 
vector <vector<int>> components; // Компоненти сильної звязності
vector <int> component; // Поточно компонента связності

void dfs1(int); // Обхід в глубину для визначення порядку виходу
void dfs2(int); // Пошук компонентів сильної звязності

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