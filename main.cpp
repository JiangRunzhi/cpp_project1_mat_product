#include <iostream>
#include <chrono>
#include "mat_product.h"
#include <cblas.h>

#include <windows.h>
using namespace std;

#define TIME_START start=std::chrono::steady_clock::now();
#define TIME_END(NAME) end=std::chrono::steady_clock::now(); \
             duration=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();\
             cout<<(NAME)\
             <<", duration = "<<duration<<"ms"<<endl;

int main(int argc, char** argv) {

	DWORD start2 = GetTickCount();
	DWORD end2 = GetTickCount();
	const int M = 2000;
	const int N = 2000;
	const int K = 2000;
	const float alpha = 1;
	const float beta = 0;
	const int lda = M;
	const int ldb = K;
	const int ldc = N;

	
	float* a1 = new float[M * K]();
	float* b1 = new float[K * N]();
	float* c1 = new float[M * N]();

	a1[M * K - 1] = 0.5;
	b1[M * K - 1] = 0.8;

	matrix *a = new matrix(M, K);
	matrix *b = new matrix(K, N);
	a->mat[M - 1][K - 1] = 0.5;
	b->mat[M - 1][K - 1] = 0.8;
	
	auto start = std::chrono::steady_clock::now();
	auto end = std::chrono::steady_clock::now();
	auto duration = 0L;

	TIME_START
	mat_product1(*a, *b);
	TIME_END("Brute")

	TIME_START
	mat_product2(*a, *b);
	TIME_END("8_grouped")

	TIME_START
	mat_product3(*a, *b);
	TIME_END("use_simd")

	start2 = GetTickCount();
	TIME_START
	cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasTrans, M, N, K, alpha, a1, lda, b1, ldb, beta, c1, ldc);
	TIME_END("OpenBLAS")
	end2 = GetTickCount();
	cout << "OpenBLAS cost time: " << end2 - start2 << " ms." << endl;

	delete a,b;

	delete a1, b1;
	float ans = 0.0;
	for (int i = 0; i < M * N; i++) {
		ans = c1[i];
	}
	cout << "The sum of answer is " << ans << endl;

	return 0;
}