#include"header_std.hpp"
class frac;
class vf;
class mf;

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