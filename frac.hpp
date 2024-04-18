#pragma onece
#include <cstdio>
#pragma onece
#include <cstdlib>
#pragma onece
#include <iostream>
#pragma onece
#include <sstream>
#pragma onece
#include <string>
#pragma onece
#include <vector>

using namespace std;
using ul=unsigned long long;
class frac;
class vf;
class mf;
class frac {
	using l = signed long long;
	using ul = unsigned long long;
	bool s;
	ul n, d;
	ul egcd(ul a, ul b) const {
		ul r = 1, g = a;
		if (a < b)
			a = b, b = g;
		while (r)
			r = a % b, (r) ? a = b, b = r : 0;
		return b;
	}
public:
	void in() {
		string s;
		cin >> s;
		this->in(s);
	}
	void in(string &str) {
		if (str[0] == '-') {
			this->s = true;
			str.erase(str.begin());
		} else {
			this->s = false;
		}
		string num, den;
		for (auto itr = str.begin(); itr != str.end(); itr++) {
			if (*itr == '/') {
				num = string(str.begin(), itr);
				den = string(itr + 1, str.end());
				break;
			}
		}
		istringstream iss(num), iss2(den);
		iss >> this->n;
		iss2 >> this->d;
		return;
	}
	void approx() {
		if (n == 0 || d == 0) {
			if (n == 0) {
				d = 1;
			} else {
				n = 0;
			}
			return;
		} else {
			ul g = egcd(n, d);
			n = n / g;
			d = d / g;
			return;
		}
	}
	string str() const {
		string ret;
		ret += (this->s ? "-" : " ");
		ret += to_string(this->n);
		if (this->d > 1ull) {
			ret += "/";
			ret += to_string(this->d);
		}
		return ret;
	}
	frac() : s(false), n(0ULL), d(1ULL) {}
	frac(frac::ul numerator, frac::ul denominator = 1ULL)
			: n(numerator), d(denominator) {
		s = false;
	}
	frac(const frac &f) : s(f.s), n(f.n), d(f.d) {}
	frac(const frac *f) : s(f->s), n(f->n), d(f->d) {}
	frac(frac::l numer, frac::l denom = 1LL) {
		if (denom == 0)
			denom = 1;
		s = (((numer < 0 && denom < 0) || (numer >= 0 && denom >= 0)) ? false
																																	: true);
		n = (ul)(numer >= 0 ? numer : -numer);
		d = (ul)(denom >= 0 ? denom : -denom);
	}
	bool operator==(const frac &o) {
		ul g = egcd(this->d, o.d);
		return ((this->s == o.s) && (this->n * o.d / g == this->d / g * o.n));
	}
	bool operator==(const ul o) {
		frac p;
		p.n = o;
		return *this == p;
	}
	bool operator==(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = (ul)(o < 0 ? -o : o);
		return *this == p;
	}
	bool operator!=(const frac &o) { return !(*this == o); }
	bool operator!=(const ul o) { return !(*this == o); }
	bool operator!=(const l o) { return !(*this == o); }
	bool operator>=(const frac &o) { return !(*this < o); }
	bool operator>=(const ul o) {
		frac p;
		p.n = o;
		return *this >= p;
	}
	bool operator>=(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = (o < 0 ? -o : o);
		return *this >= p;
	}
	bool operator<=(const frac &o) { return !(*this > o); }
	bool operator<=(const ul o) {
		frac p;
		p.n = o;
		return *this <= p;
	}
	bool operator<=(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = (o < 0 ? -o : o);
		return *this <= p;
	}
	bool operator>(const frac &o) {
		ul g = egcd(this->d, o.d);
		bool ret;
		if (this->s && o.s)
			ret = this->n * o.d / g < this->d / g * o.n;
		else if (this->s)
			ret = false;
		else if (o.s)
			ret = true;
		else
			ret = this->n * o.d / g > this->d / g * o.n;
		return ret;
	}
	bool operator>(const ul o) {
		frac p;
		p.n = o;
		return *this > p;
	}
	bool operator>(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = (o < 0 ? -o : o);
		return *this > p;
	}
	bool operator<(const frac &o) {
		ul g = egcd(this->d, o.d);
		bool ret;
		if (this->s && o.s)
			ret = this->n * o.d / g > this->d / g * o.n;
		else if (this->s)
			ret = true;
		else if (o.s)
			ret = false;
		else
			ret = this->n * o.d / g < this->d / g * o.n;
		return ret;
	}
	bool operator<(const ul o) {
		frac p;
		p.n = o;
		return *this < p;
	}
	bool operator<(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = (o < 0 ? -o : o);
		return *this < p;
	}
	frac operator=(const frac &o) {
		this->s = o.s;
		this->n = o.n;
		this->d = o.d;
		return *this;
	}
	frac operator=(const ul o) {
		this->s = false;
		this->n = o;
		this->d = 1ULL;
		return *this;
	}
	frac operator=(const l o) {
		this->s = (o < 0 ? true : false);
		this->n = (ul)(o < 0 ? -o : o);
		this->d = 1ULL;
		return *this;
	}
	frac operator-() const {
		frac ret(this->n, this->d);
		ret.s = !ret.s;
		return ret;
	}
	frac operator+(const frac &o) const {
		frac ret;
		ul G = egcd(this->d, o.d);
		ul xo = this->d / G * o.n;
		ul xt = this->n * o.d / G;
		ret.d = this->d * o.d / G;
		ret.s = ((this->s && o.s) || (this->s && (xt > xo)) || (o.s && (xo > xt)));
		if ((this->s && o.s) || !(this->s || o.s))
			ret.n = xo + xt;
		else if (this->s)
			ret.n = (xt > xo ? xt - xo : xo - xt);
		else if (o.s)
			ret.n = (xo > xt ? xo - xt : xt - xo);
		ret.approx();
		return ret;
	}
	frac operator+(const ul o) const {
		frac p;
		p.n = o;
		return *this + p;
	}
	frac operator+(const l o) const {
		frac p;
		p.s = (o < 0);
		p.n = (o < 0 ? -o : o);
		return *this + p;
	}
	frac operator-(const frac &o) {
		frac p;
		p.n = o.n;
		p.d = o.d;
		p.s = !o.s;
		return *this + p;
	}
	frac operator-(const ul o) {
		frac p;
		p.s = true;
		p.n = o;
		return *this + p;
	}
	frac operator-(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = (o < 0 ? -o : o);
		return *this + p;
	}
	frac operator*(const frac &o) {
		frac ret;
		if (this->n == 0 || o.n == 0) {
			ret.s = false;
			ret.n = 0ull;
			ret.d = 1ull;
		} else {
			ret.s = (this->s ^ o.s);
			ul g1 = egcd(this->n, o.d);
			ul g2 = egcd(this->d, o.n);
			ret.n = this->n / g1 * o.n / g2;
			ret.d = this->d / g2 * o.d / g1;
		}
		ret.approx();
		return ret;
	}
	frac operator*(const ul o) {
		frac p;
		p.n = o;
		return *this * p;
	}
	frac operator*(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = (o < 0 ? -o : o);
		return *this * p;
	}
	frac operator/(const frac &o) {
		frac p;
		p.s = o.s;
		p.n = o.d;
		p.d = o.n;
		return *this * p;
	}
	frac operator/(const ul o) {
		frac p;
		p.s = false;
		p.n = 1ULL;
		p.d = o;
		return *this * p;
	}
	frac operator/(const l o) {
		frac p;
		p.s = (o < 0);
		p.n = 1ULL;
		p.d = (ul)(o < 0 ? -o : o);
		return *this * p;
	}
	frac operator+=(const frac &o) { return *this = *this + o; }
	frac operator+=(const ul o) { return *this = *this + o; }
	frac operator+=(const l o) { return *this = *this + o; }
	frac operator-=(const frac &o) { return *this = *this - o; }
	frac operator-=(const ul o) { return *this = *this - o; }
	frac operator-=(const l o) { return *this = *this - o; }
	frac operator*=(const frac &o) { return *this = *this * o; }
	frac operator*=(const ul o) { return *this = *this * o; }
	frac operator*=(const l o) { return *this = *this * o; }
	frac operator/=(const frac &o) { return *this = *this / o; }
	frac operator/=(const ul o) { return *this = *this / o; }
	frac operator/=(const l o) { return *this = *this / o; }
};
class vf {
	vector<frac> elem;
public:
	void show();
	void showT();
	size_t size() const { return elem.size(); }
	frac &operator[](size_t);
	vf operator*(mf&);
	frac operator*(vf&);
	vf operator+(vf&);
	vf operator-(vf&);
	void resize(size_t new_size) { elem.resize(new_size); }
	void append(const vf);
	void append(const frac&f){elem.push_back(f);}
	vf(size_t size=3,frac init=frac(0ull,1ull)){
		elem.resize(size);
		for(size_t i=0;i<size;i++){
			elem[i]=init;
		}
	}

};
class mf {
	vector<vf> elem;
public:
	void show();
	size_t size() const { return elem.size(); }
	void resize(size_t new_size) { elem.resize(new_size); }
	void append(const vf&v){elem.push_back(v);}
	mf(size_t size=3,size_t row_size=0,frac init=frac(0ull,1ull)){
		if(row_size==0){
			row_size=size;
		}
		elem.resize(size);
		for(size_t i=0;i<size;i++){
			elem[i].resize(row_size);
			for(size_t j=0;j<row_size;j++){
				elem[i][j]=init;
			}
		}
	}
	vf &operator[](size_t);
	vf operator*(vf&);
	mf operator*(mf&);
	mf operator+(mf&);
	mf operator-(mf&);
};

void vf::append(vf v){
	for(size_t i=0;i<v.size();i++)
		elem.push_back(v[i]);
}
frac &vf::operator[](size_t idx) {
	if (idx >= elem.size()) {
		cout << "Error: Index out of range in vf::operator[]" << endl;
		return elem[0];
	}
	return elem[idx];
}
vf &mf::operator[](size_t idx) {
	if (idx >= elem.size()) {
		cout << "Error: Index out of range in mf::operator[]" << endl;
		return elem[0];
	}
	return elem[idx];
}
void mf::show() {
	for (size_t i = 0; i < elem.size(); i++)
		for (size_t j = 0; j < elem[i].size(); j++)
			cout << elem[i][j].str() << " \n"[j == elem[i].size() - 1];
	return;
}
vf mf::operator*(vf &v) {
	vf ret((*this).size());
	if ((*this)[0].size() != v.size()) {
		cout << "matrix and vector size error" << endl;
		return ret;
	}
	for (size_t i = 0; i < v.size(); i++) {
		for (size_t j = 0; j < v.size(); j++) {
			ret[i] = ret[i] + (*this)[i][j] * v[j];
		}
	}
	return ret;
}
mf mf::operator*(mf &m) {
	mf ret((*this).size(),m[0].size());
	if((*this).size()!=m[0].size()||(*this)[0].size()!=m.size()){
		cout<<"matrix size error"<<endl;
	}else{
		for(size_t i=0;i<(*this).size();i++){
			for(size_t j=0;j<m[i].size();j++){
				for(size_t k=0;k<(*this).size();k++){
					ret[i][j]+=(*this)[i][k]*m[k][j];
				}
			}
		}
	}
	return ret;
}
mf mf::operator+(mf&m){
	mf ret((*this).size(),(*this)[0].size());
	if((*this).size()!=m.size()||(*this)[0].size()!=m[0].size()){
		cout<<"matrix size error"<<endl;
	}else{
		for(size_t i=0;i<m.size();i++){
			for(size_t j=0;j<m[i].size();j++){
				ret[i][j]=(*this)[i][j]+m[i][j];
			}
		}
	}
	return ret;
}
mf mf::operator-(mf&m){
	mf ret((*this).size(),(*this)[0].size());
	if((*this).size()!=m.size()||(*this)[0].size()!=m[0].size()){
		cout<<"matrix size error"<<endl;
	}else{
		for(size_t i=0;i<m.size();i++){
			for(size_t j=0;j<m[i].size();j++){
				ret[i][j]=(*this)[i][j]-m[i][j];
			}
		}
	}
	return ret;
}
void vf::show() {
	for (size_t i = 0; i < elem.size(); i++)
		cout << elem[i].str() << endl;
	return;
}
void vf::showT() {
	for (size_t i = 0; i < elem.size(); i++)
		cout << elem[i].str() << " \n"[i == (*this).size() - 1];
	return;
}
vf vf::operator*(mf&m){
		vf ret(m[0].size());
		if ((*this).size() != m.size()) {
			cout << "vector and matrix size error" << endl;
			return ret;
		}
		for (size_t i = 0; i < m.size(); i++) {
			for (size_t j = 0; j < m.size(); j++) {
				ret[i] = ret[i] + (*this)[j] * m[j][i];
			}
		}
		return ret;
}
frac vf::operator*(vf&v){
		frac ret(0ull, 1ull);
		if ((*this).size() != v.size()) {
			cout << "vector size error" << endl;
			return ret;
		}
		for (size_t i = 0; i < v.size(); i++) {
			ret = ret + (*this)[i] * v[i];
		}
		return ret;
}
vf vf::operator+(vf&v){
		vf ret(v.size());
		if((*this).size()!=v.size()){
			cout<<"vector size error"<<endl;
		}else{
			for(size_t i=0;i<v.size();i++)
				ret[i]=(*this)[i]+v[i];
		}
		return ret;
}
vf vf::operator-(vf&v){
		vf ret(v.size());
		if((*this).size()!=v.size()){
			cout<<"vector size error"<<endl;
		}else{
			for(size_t i=0;i<v.size();i++)
				ret[i]=(*this)[i]-v[i];
		}
		return ret;
}

namespace blas {
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
