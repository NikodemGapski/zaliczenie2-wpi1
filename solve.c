#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int max(int a, int b) {
	return a < b ? b : a;
}
int min(int a, int b) {
	return a < b ? a : b;
}

// whether start <= a < end
int in_range(int a, int start, int end) {
	return start <= a && a < end;
}
// find the first 3 motels of different types starting at start and incrementing by increment
void find_3_different(int n, int type[], int start, int increment, int res[]) {
	res[0] = res[1] = start;
	while(in_range(res[1], 0, n) && type[res[1]] == type[res[0]]) res[1] += increment;
	res[2] = res[1];
	while(in_range(res[2], 0, n) && (type[res[2]] == type[res[0]] || type[res[2]] == type[res[1]])) res[2] += increment;
}

// calculate the result for MIN
int calculate_min(int n, int type[], int dist[]) {
	int res = __INT_MAX__;
	int prev3[3] = {0, -1, -1};
	int next3[3];
	// 1.1. Find the first 3 different motels after i = 1
	find_3_different(n, type, 2, 1, next3);

	// 1.2. Catepillar method on the middle motel [ O(n) ]
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

				if(type[a] == type[b] || type[a] == type[i] || type[b] == type[i]) continue; // some motels are of the same type
				res = min(res, max(dist[i] - dist[a], dist[b] - dist[i]));
			}
		}
	}
	return res;
}

// calculate the result for MAX
int calculate_max(int n, int type[], int dist[]) {
	int res = -1;
	// 2.1. Find the first 3 different motels [ O(n) ]
	int first3[3];
	find_3_different(n, type, 0, 1, first3);
	// 2.2. Find the last 3 different motels [ O(n) ]
	int last3[3];
	find_3_different(n, type, n - 1, -1, last3);

	if(first3[2] == n || last3[2] == -1) return -1; // no 3 different motels found

	// 2.3. For each found pair look for the maximum middle-point [ O(9n) = O(n) ]
	for(int a_i = 0; a_i < 3; ++a_i) {
		int a = first3[a_i];
		for(int b_i = 0; b_i < 3; ++b_i) {
			int b = last3[b_i];
			if(type[a] == type[b]) continue; // they are of the same type
			for(int i = a + 1; i < b; ++i) { // for each motel in between update the maximum result if the triple is correct
				if(type[i] == type[a] || type[i] == type[b]) continue;
				res = max(res, min(dist[i] - dist[a], dist[b] - dist[i]));
			}
		}
	}
	return res;
}

int main() {
	// INPUT
	int n; assert(scanf("%d", &n));
	int *type, *dist;
	type = (int*)malloc((size_t)n * sizeof(int));
	dist = (int*)malloc((size_t)n * sizeof(int));
	for(int i = 0; i < n; ++i) {
		assert(scanf("%d%d", type + i, dist + i));
	}

	// CALCULATE
	int min_d = calculate_min(n, type, dist);
	int max_d = calculate_max(n, type, dist);

	// PRINT
	if(max_d == -1) {
		printf("0 0\n");
		return 0;
	}
	printf("%d %d\n", min_d, max_d);
}