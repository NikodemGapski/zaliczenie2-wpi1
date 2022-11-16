#include <stdio.h>
#include <stdlib.h>

int less(const void* a, const void* b) {
	int aa = *(int*)a, bb = *(int*)b;
	if(aa < bb) return -1;
	if(aa == bb) return 0;
	return 1;
}

int main() {
	int seed, n, types, max_dist;
	scanf("%d%d%d%d", &seed, &n, &types, &max_dist);
	srand(seed);

	int *tab = (int*)malloc(n * sizeof(int));
	for(int i = 0; i < n; ++i) {
		tab[i] = rand() % max_dist;
	}
	qsort(tab, n, sizeof(int), less);

	printf("%d\n", n);
	int cur_type = -1;
	for(int i = 0; i < n; ++i) {
		if(cur_type == -1 || rand() % 100 < 4) {
			cur_type = rand() % types + 1;
		}
		printf("%d %d\n", cur_type, tab[i]);
	}
}