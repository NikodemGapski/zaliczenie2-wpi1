#include <stdio.h>
#include <stdlib.h>

int max(int a, int b) {
	return a < b ? b : a;
}
int min(int a, int b) {
	return a < b ? a : b;
}

int main() {
	// INPUT
	int n; scanf("%d", &n);
	int *type, *dist;
	type = (int*)malloc(n * sizeof(int));
	dist = (int*)malloc(n * sizeof(int));
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", type + i, dist + i);
	}

	// CALCULATE
	int min_d = __INT_MAX__, max_d = -1;
	for(int i = 0; i < n; ++i) {
		for(int j = i + 1; j < n; ++j) {
			for(int k = j + 1; k < n; ++k) {
				if(type[i] != type[j] && type[i] != type[k] && type[j] != type[k]) {
					int min_cur = max(dist[j] - dist[i], dist[k] - dist[j]);
					int max_cur = min(dist[j] - dist[i], dist[k] - dist[j]);
					min_d = min(min_d, min_cur);
					max_d = max(max_d, max_cur);
				}
			}
		}
	}
	// no triple found
	if(max_d == -1 || min_d == __INT_MAX__) {
		max_d = 0;
		min_d = 0;
	}

	printf("%d %d\n", min_d, max_d);
}