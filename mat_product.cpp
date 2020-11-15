#include <iostream>
#include "mat_product.h"

using namespace std;

matrix::matrix(int m, int n) {
	this->m = m;
	this->n = n;
	mat = new float* [m];
	for (int i = 0; i < m; i++) {
		mat[i] = new float[n]();
	}
}

//brute force method
float dot_product1(const float* v1, const float* v2, size_t n) {
	float sum = 0.0f;
	for (size_t i = 0; i < n; i++)
		sum += (v1[i] * v2[i]);
	return sum;
}

float dot_product2(const float* v1, const float* v2, size_t n) {
	if (n % 8 != 0)
	{
		cerr << "The size n must be a multiple of 8." << endl;
		return 0.0f;
	}
	float sum = 0.0f;
	for (size_t i = 0; i < n; i += 8)
	{
		sum += (v1[i] * v2[i]);
		sum += (v1[i + 1] * v2[i + 1]);
		sum += (v1[i + 2] * v2[i + 2]);
		sum += (v1[i + 3] * v2[i + 3]);
		sum += (v1[i + 4] * v2[i + 4]);
		sum += (v1[i + 5] * v2[i + 5]);
		sum += (v1[i + 6] * v2[i + 6]);
		sum += (v1[i + 7] * v2[i + 7]);
	}
	return sum;
}

float dot_product3(const float* v1, const float* v2, size_t n) {
	if (n % 8 != 0)
	{
		cerr << "The size n must be a multiple of 8." << endl;
		return 0.0f;
	}

	float sum[8] = { 0 };
	__m256 a, b;
	__m256 c = _mm256_setzero_ps();
	for (size_t i = 0; i < n; i += 8) {
		a = _mm256_load_ps(v1 + i);
		b = _mm256_load_ps(v2 + i);
		c = _mm256_add_ps(c, _mm256_mul_ps(a, b));
	}
	_mm256_store_ps(sum, c);
	return { sum[0] + sum[1] + sum[2] + sum[3] + sum[4] + sum[5] + sum[6] + sum[7] };
}


//brute force matrix product
bool mat_product1(matrix m1, matrix m2) {
	matrix ans(m1.m, m2.n);
	float total = 0.0;
	if (m1.n != m2.m) {
		cerr << "The number of the first matrix's columns must equal to the second matrix's rows." << endl;
		return false;
	}

	for (int i = 0; i < ans.m; i++) {
		float* v2 = new float[m2.m];
		for (int j = 0; j < ans.n; j++) {
			for (int k = 0; k < m2.m; k++) {
				v2[k] = m2.mat[j][k];
			}
			ans.mat[i][j] = dot_product1(m1.mat[i], v2, m2.m);
			total += ans.mat[i][j];
		}
	}
	cout << "The sum of answer is " << total << endl;
	return true;
}

//8_grouped
bool mat_product2(matrix m1, matrix m2) {
	matrix ans(m1.m, m2.n);
	float total = 0.0;
	if (m1.n != m2.m) {
		cerr << "The number of the first matrix's columns must equal to the second matrix's rows." << endl;
		return false;
	}

	for (int i = 0; i < ans.m; i++) {
		float* v2 = new float[m2.m];
		for (int j = 0; j < ans.n; j++) {
			for (int k = 0; k < m2.m; k++) {
				v2[k] = m2.mat[j][k];
			}
			ans.mat[i][j] = dot_product2(m1.mat[i], v2, m2.m);
			total += ans.mat[i][j];
		}
	}
	cout << "The sum of answer is " << total << endl;
	return true;
}


bool mat_product3(matrix m1, matrix m2) {
	matrix ans(m1.m, m2.n);
	float total = 0.0;
	if (m1.n != m2.m) {
		cerr << "The number of the first matrix's columns must equal to the second matrix's rows." << endl;
		return false;
	}

	for (int i = 0; i < ans.m; i++) {
		float* v2 = new float[m2.m];
		for (int j = 0; j < ans.n; j++) {
			for (int k = 0; k < m2.m; k++) {
				v2[k] = m2.mat[j][k];
			}
			ans.mat[i][j] = dot_product3(m1.mat[i], v2, m2.m);
			total += ans.mat[i][j];
		}
	}
	cout << "The sum of answer is " << total << endl;
	return true;
}