#include"header_std.hpp"
class frac;
class vf;
class mf;

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