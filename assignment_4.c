#include <stdio.h>
#include <ctype.h>
#define MAX 10
#define INF 999

static int n;
static int cost[MAX][MAX], dist[MAX][MAX], next[MAX][MAX];

static void print_matrix(void)
{
	int i, j;

	printf("\n     ");
	for (j = 0; j < n; j++)
		printf("%4c", 'A' + j);
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%4c ", 'A' + i);
		for (j = 0; j < n; j++)
			printf("%4d", cost[i][j]);
		printf("\n");
	}
}

static void print_tables(void)
{
	int i, j;

	for (i = 0; i < n; i++) {
		printf("\nRouting table for router %c\n", 'A' + i);
		printf("Dest\tNext hop\tCost\n");
		for (j = 0; j < n; j++) {
			if (next[i][j] < 0)
				printf("%c\t-\t\t%d\n", 'A' + j, dist[i][j]);
			else
				printf("%c\t%c\t\t%d\n", 'A' + j, 'A' + next[i][j], dist[i][j]);
		}
	}
}

int main(void)
{
	int i, j, k, changed, rounds = 0, cur, hops;
	char s, d;

	printf("Enter number of nodes (max %d): ", MAX);
	scanf("%d", &n);

	printf("Enter cost matrix (%d = no direct link, 0 on diagonal):\n", INF);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			scanf("%d", &cost[i][j]);
			dist[i][j] = cost[i][j];
			next[i][j] = (cost[i][j] < INF) ? j : -1;
		}

	printf("\n===== Initial cost matrix =====");
	print_matrix();
	printf("\n===== Initial routing tables =====");
	print_tables();

	do {
		changed = 0;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				for (k = 0; k < n; k++)
					if (dist[i][j] > cost[i][k] + dist[k][j]) {
						dist[i][j] = cost[i][k] + dist[k][j];
						next[i][j] = k;
						changed = 1;
					}
		rounds++;
	} while (changed);

	printf("\n===== Final routing tables (converged after %d rounds) =====", rounds);
	print_tables();

	printf("\nEnter source and destination (e.g. A D): ");
	scanf(" %c %c", &s, &d);
	i = toupper(s) - 'A';
	j = toupper(d) - 'A';

	if (i < 0 || i >= n || j < 0 || j >= n) {
		printf("Invalid node.\n");
		return 1;
	}
	if (dist[i][j] >= INF) {
		printf("No path from %c to %c.\n", 'A' + i, 'A' + j);
		return 0;
	}

	printf("\nShortest path from %c to %c: %c", 'A' + i, 'A' + j, 'A' + i);
	cur = i;
	for (hops = 0; cur != j && hops < n; hops++) {
		cur = next[cur][j];
		printf(" -> %c", 'A' + cur);
	}
	printf("\nMinimum cost: %d\n", dist[i][j]);
	return 0;
}