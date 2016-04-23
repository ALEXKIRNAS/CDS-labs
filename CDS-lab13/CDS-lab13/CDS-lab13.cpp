#include <stdio.h>

const int Nmax = 1e3;
int rang[Nmax] = { 0 };
int count[Nmax] = { 0 };

int main(void)
{
	freopen("input4.txt", "r", stdin);
	int n, m;

	scanf("%d%d", &n, &m);

	while (m--)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		rang[x]++;
		rang[y]++;
	}

	for (int i = 1; i <= n; i++)
		count[rang[i]]++;

	for (int i = Nmax - 2; i >= 0; i--)
		count[i] += count[i + 1];

	if (count[2] > 5 || count[3] > 4) printf("Nonplanar graph");
	else printf("Planar graph");
}