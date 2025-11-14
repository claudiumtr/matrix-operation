/*
 * Tema 2 ASC
 * 2021 Spring
 */
#include "utils.h"
#include "cblas.h"

/* 
 * Add your BLAS implementation here
 */

double* my_solver(int N, double *A, double *B) {

	double *AB = calloc(N * N, sizeof(double));

	for(int i = 0; i < N * N; i++)
		AB[i] = B[i];

	// in AB o sa se afle B
	
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasNoTrans, CblasNonUnit, N, N, 1, A, N, AB, N);

	// in AB o sa se afle A * B

	double *ABB = calloc(N * N, sizeof(double));
	
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N, N, N, 1, AB, N, B, N, 1, ABB, N);

	// in ABB o sa se afle A * B * B'
	
	double *AA = calloc(N * N, sizeof(double));
	
	for(int i = 0; i < N * N; i++)
		AA[i] = A[i];
	//
	cblas_dtrmm(CblasRowMajor, CblasLeft, CblasUpper, CblasTrans, CblasNonUnit, N, N, 1, A, N, AA, N);

	// in AA o sa se afle A' * A

	double *res = calloc(N * N, sizeof(double));

	for (int i = 0; i < N * N; i++){
		res[i] = ABB[i] + AA[i];
	}

	// in res o sa se afle A * B * B' + A' * A
	
	free(AB);
	free(ABB);
	free(AA);

	return res;
	}
