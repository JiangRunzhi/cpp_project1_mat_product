#pragma once
#include <cstddef>
#include <immintrin.h>

struct matrix {
	int m; //rows
	int n;//columns
	float** mat;
	matrix();
	matrix(int m, int n);
};

//brute force method
float dot_product1(const float* v1, const float* v2, size_t n);
bool mat_product1(matrix m1, matrix m2);

//8_grouped
float dot_product2(const float* v1, const float* v2, size_t n);
bool mat_product2(matrix m1, matrix m2);

//use simd
float dot_product3(const float* v1, const float* v2, size_t n);
bool mat_product3(matrix m1, matrix m2);



