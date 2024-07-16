#include"header_std.hpp"
class frac;
class vf;
class mf;

namespace blas {
	using ul = unsigned long long;
	using l = long long;
ul __internal_get_REF(mf &A, mf &I) {
	I.resize(A.size());
	for (size_t i = 0; i < A.size(); i++) {
		I[i].resize(A[i].size());
		if (I[i].size() > i)
			I[i][i] = 1ULL;
	}
	size_t rank = 0, r_idx = 0;
	while (rank < A.size()) {
		if (A[rank][r_idx] == frac(0ULL, 1ULL)) {
			bool swapflag = false;
			for (; r_idx < A[rank].size(); r_idx++) {
				for (size_t i = rank + 1; i < A.size(); i++) {
					if (A[i][r_idx] != frac(0ULL, 1ULL)) {
						vf tmp = A[rank];
						A[rank] = A[i];
						A[i] = tmp;
						tmp = I[rank];
						I[rank] = I[i];
						I[i] = tmp;
						swapflag = true;
						break;
					}
				}
				if (swapflag) {
					break;
				}
			}
			if (r_idx >= A[rank].size()) { // if r_idx >= matrix row Num, then no rows
																		 // can be simplify
				break;
			}
		}
		if (r_idx >= A[rank].size()) {
			break;
		}
		frac div_coef = A[rank][r_idx];
		if (div_coef == frac(0ull, 1ull)) {
			break;
		}
		for (size_t i = 0; i < A[rank].size(); i++) {
			A[rank][i] = A[rank][i] / div_coef;
			I[rank][i] = I[rank][i] / div_coef;
		}
		for (size_t i = 0; i < A.size(); i++) {
			if (i == rank) {
				continue;
			}
			if (A[i][r_idx] != frac(0ull, 1ull)) {
				div_coef = A[i][r_idx];
				if (div_coef == frac(0ull, 1ull)) {
					continue;
				}
				for (size_t j = 0; j < A[i].size(); j++) {
					A[i][j] = A[i][j] - A[rank][j] * div_coef;
					I[i][j] = I[i][j] - I[rank][j] * div_coef;
				}
			}
		}
		rank++;
		r_idx++;
	}
	return rank;
}
ul invM(mf A, mf &I) { return __internal_get_REF(A, I); }
ul RANK(mf A) {
	mf I;
	return __internal_get_REF(A, I);
}
ul REF(mf &A) {
	mf I;
	return __internal_get_REF(A, I);
}
}