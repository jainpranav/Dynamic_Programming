/*
 * Recursive dynamic programming algorithm to return the minimum number of 
 * multiplications of a list of n matrices. The dimensions of the matrix are 
 * read from a file that contains n+1 numbers representing the dimension of 
 * the matrices
 */
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// We can solve the problem for N-1 matrices.
#define N 100000

// Initialize values into arrays val and pos that store the minimum
// number of multiplications and the position to break the array
initialize(int n, int val[n][n], int pos[n][n]) {
	int i,j;
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			if(i == j) {
				val[i][j] = 0;
				pos[i][j] = 0;
			}
			else {
				val[i][j] = INT_MAX;
				pos[i][j] = -1;
			}
		}
	}
}

// Prints the min multiplications matrix - useful for debugging etc.
void
printMat(int n, int val[n][n]) {
	int i,j;
	printf("\n\n Printing val\n");
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
				printf("  ");
			else {
				if(val[i][j] == INT_MAX)
					printf("-- ");
				else
					printf("%d ", val[i][j]);
			}	
		}
		printf("\n");
	}
	printf("\n");
}

// Prints the position matrix - useful for debugging etc.
void
printPos(int n, int pos[n][n]) {
	int i,j;
	printf("pos matrix\n");
	for(i = 0; i < n; ++i) {
		for(j = 0; j < n; ++j) {
			if(i >= j) 
				printf("-- ");
			else
				printf("%d ",pos[i][j]);
		}
		printf("\n");
	}
}

// Prints paranthesized output - reading from the pos matrix.
void
printParan(int n, int pos[n][n], int a, int b) {
	if(a == b) {
		printf("A_%d", a);
		return;
	}
	if(a == b-1) {
		printf("A_%dA_%d", a, b);
		return;
	}

	printf("(");
	printParan(n, pos, a, pos[a][b]);
	printf(")(");
	printParan(n, pos, pos[a][b]+1, b);

	printf(")");
}

// Compute Multiplications - takes as parameters, n - the dimension of the matrix, val - the memoized min values, pos - the position where the break occurs, list - the input list of dimensions, and a, b - the val[a][b] that we want to compute.

int
computeMult(int n, int val[n][n], int pos[n][n], int list[n], int a,int b) {
	if(val[a][b] < INT_MAX)
		return val[a][b];
	
	int i, q;
	for(i = a; i < b; ++i) {
		q = computeMult(n, val, pos, list, a, i) + computeMult(n, val, pos, list, i+1, b) + list[a]*list[i+1]*list[b+1];
		if(q < val[a][b]) {
			val[a][b] = q;
			pos[a][b] = i;
		}
	}
	return val[a][b];
}

int
main(int argc, char** argv) {
	if(argc != 2) {
		printf("error\n");
		return -1;
	}

	FILE* inp = fopen(argv[1], "r");
	int list[N];
	int i,j;

	// read input
	for(i = 0; (fscanf(inp, "%d", &list[i]) == 1); ++i);

	int n = i-1;

	printf("number of matrices = %d\n", n);
	
	int val[n][n];
	int pos[n][n];

	initialize(n, val, pos);
	
	int f = computeMult(n, val, pos, list, 0, n-1);
	printf("minimum number of multiplications = %d\n",f);
	printf("\n");
	printParan(n, pos, 0,n-1);
	printf("\n");
	fclose(inp);
}
