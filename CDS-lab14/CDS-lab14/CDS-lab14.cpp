#include <iostream>
#include <algorithm>

const int Nmax = 1e2 + 17;
int g[Nmax][Nmax] = { 0 };
int gColour[Nmax] = { 0 };
std::pair <int, int> rang[Nmax];
// first - count, second - number

int main(void)
{
	freopen("input1.txt", "r", stdin);

	int n, m;
	scanf("%d%d", &n, &m);

	for (int i = 0; i <= n; i++)
	{
		rang[i].first = 0;
		rang[i].second = i;
	}

	for (int i = 0; i < m; i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		g[x][y]++;
		g[y][x]++;

		rang[x].first++;
		rang[y].first++;
	}

	std::sort(rang + 1, rang + n + 1);
	std::reverse(rang + 1, rang + n + 1);

	int colour = 0;
	for (int i = 1; i <= n; i++) 
		if (gColour[rang[i].second] == 0)
		{
			gColour[rang[i].second] = ++colour;
			for (int z = i + 1; z <= n; z++)
			{
				int v = rang[z].second;
				int j;

				for (j = 1; j <= n; j++)
					if (g[v][j] && gColour[j] == colour) break;

				if (j == n + 1) gColour[v] = colour;
			}
				
		}

	printf("Colours used - %d\n", colour);
	printf("Vectex - Colour\n");
	for (int i = 1; i <= n; i++)
		printf("%6d - %d\n", i, gColour[i]);
		
}