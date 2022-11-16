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
	type = (int*)malloc((long unsigned)n * sizeof(int));
	dist = (int*)malloc((long unsigned)n * sizeof(int));
	for(int i = 0; i < n; ++i) {
		scanf("%d%d", type + i, dist + i);
	}

	// CALCULATE
	int min_d = __INT_MAX__, max_d = -1;
	// (1) - FIND MIN_D
	int prev3[3] = {0, -1, -1};
	int next3[3] = {2, -1, -1};
	// 1.1. Find the first 3 different hotels after i = 1
	{
		next3[1] = next3[0] + 1;
		while(next3[1] < n && type[next3[1]] == type[next3[0]]) ++next3[1];
		next3[2] = next3[1] + 1;
		while(next3[2] < n && (type[next3[2]] == type[next3[0]] || type[next3[2]] == type[next3[1]])) ++next3[2];
	}
	// 1.2. Catepillar method on the middle hotel [ O(n) ]
	for(int i = 1; i < n - 1; ++i) {
		// update prev3
		if(type[prev3[0]] != type[i - 1]) {
			prev3[2] = prev3[1];
			prev3[1] = prev3[0];
		}
		prev3[0] = i - 1;
		// update next3
		next3[0] = i + 1;
		// (fix overlapping indices)
		while(next3[1] < n && type[next3[1]] == type[next3[0]]) ++next3[1]; // (moreover, idx <= next3[2])
		while(next3[2] < n && (type[next3[2]] == type[next3[0]] || type[next3[2]] == type[next3[1]])) ++next3[2];
		// for each pair of beginnings and endings update the minimum result if the triple is correct
		for(int a_i = 0; a_i < 3; ++a_i) {
			int a = prev3[a_i]; if(a == -1) continue; // this prev doesn't exist yet

			for(int b_i = 0; b_i < 3; ++b_i) {
				int b = next3[b_i]; if(b >= n) continue; // this next doesn't exist anymore

				if(type[a] == type[b] || type[a] == type[i] || type[b] == type[i]) continue; // some hotels are of the same type
				min_d = min(min_d, max(dist[i] - dist[a], dist[b] - dist[i]));
			}
		}
	}
	// (2) - FIND MAX_D
	// 2.1. Find the first 3 different hotels [ O(n) ]
	int first3[3];
	{
		int idx = 0;
		first3[0] = idx;
		while(idx < n && type[idx] == type[first3[0]]) ++idx;
		first3[1] = idx;
		while(idx < n && (type[idx] == type[first3[0]] || type[idx] == type[first3[1]])) ++idx;
		first3[2] = idx;
	}
	// 2.2. Find the last 3 different hotels [ O(n) ]
	int last3[3];
	{
		int idx = n - 1;
		last3[0] = idx;
		while(idx >= 0 && type[idx] == type[last3[0]]) --idx;
		last3[1] = idx;
		while(idx >= 0 && (type[idx] == type[last3[0]] || type[idx] == type[last3[1]])) --idx;
		last3[2] = idx;
	}

	if(first3[2] == n || last3[2] == -1) { // no 3 different hotels found
		printf("0 0");
		return 0;
	}
	// 2.3. For each found pair look for the maximum middle-point [ O(9n) = O(n) ]
	for(int a_i = 0; a_i < 3; ++a_i) {
		int a = first3[a_i];
		for(int b_i = 0; b_i < 3; ++b_i) {
			int b = last3[b_i];
			if(type[a] == type[b]) continue; // they are of the same type
			for(int i = a + 1; i < b; ++i) { // for each hotel in between update the maximum result if the triple is correct
				if(type[i] == type[a] || type[i] == type[b]) continue;
				max_d = max(max_d, min(dist[i] - dist[a], dist[b] - dist[i]));
			}
		}
	}

	// PRINT
	printf("%d %d\n", min_d, max_d);
}