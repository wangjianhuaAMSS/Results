#include "main.h"

/*Vdeg::Vdeg() {
}

Vdeg::Vdeg(int n) {
	for (int i = 0; i < n; i++) {
		v.push_back(-128);
	}
}
*/

ostream & operator << (ostream &out, Vdeg &vd) {
	auto it = vd.v.begin();
	while (it != vd.v.end()) {
		out << signed(*it) << " ";
		it++;
	}
	return(out);
}

istream & operator >> (istream &in, Vdeg &vd) {
	int8_t i8;
	in >> i8;
	vd.v.push_back(i8);
	char c;
	in >> c;
	while (c != ' ') {
		in >> i8;
		vd.v.push_back(i8);
		in >> c;
	}
	return(in);
}

Vdeg operator +(const Vdeg vd1, const Vdeg vd2) {
	Vdeg vd;
	for (int i = 0; i < vd1.v.size(); i++) {
		vd.v.push_back(max(vd1.v[i], vd2.v[i]));
	}
	return(vd);
}

Vdeg operator *(const Vdeg vd1, const Vdeg vd2) {
	Vdeg vd;
	for (int i = 0; i < vd1.v.size(); i++)
		vd.v.push_back(-128);
	for (int i = 0; i < vd1.v.size(); i++) {
		if (vd1.v[i] >= 0) {
			for (int j = 0; j < vd2.v.size(); j++) {
				if (vd2.v[j] >= 0) {
					int8_t i8 = vd1.v[i] + vd2.v[j];
					vd.v[i | j] = max(vd.v[i | j], i8);
				}
			}
		}
	}
	return(vd);
}

Vdeg min_vector_degree(Vdeg vd1, Vdeg vd2) {
	Vdeg vd;
	for (int i = 0; i < vd1.v.size(); i++) {
		vd.v.push_back(min(vd1.v[i], vd2.v[i]));
	}
	return(vd);
}

int8_t compute_degree(Vdeg vd) {
	int8_t d = -128;
	for (int i = 0; i < vd.v.size(); i++) {
		bitset<MAX_V> b(i);
		int8_t i8 = vd.v[i] + b.count();
		d = max(d, i8);
	}
	return(d);
} 

int8_t limit_degree(Vdeg vd) {
	int8_t d = -128;
	int i = vd.v.size() - 1;
	bitset<MAX_V> b(i);
	int8_t i8 = vd.v[i] + b.count();
	d = max(d, i8);
	return(d);
}

int8_t adjusted_degree(Vdeg vd, int8_t max_degree) {
	int8_t d = -128;
	bitset<MAX_V> bm(vd.v.size() - 1);
	int8_t vds = bm.count();
	for (int i = 0; i < vd.v.size(); i++) {
		bitset<MAX_V> b(i);
		int8_t i8;
		if (vd.v[i] > max_degree - vds) {
			i8 = max_degree - vds + b.count();
		}
		else {
			i8 = vd.v[i] + b.count();
		}
		d = max(d, i8);
	}
	return(d);
}