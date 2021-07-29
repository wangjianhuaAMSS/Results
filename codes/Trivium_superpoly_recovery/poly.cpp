#include "main.h"

/*istream & operator>>(istream &in, Vmono & vmono) {
	int value;
	for (int k = 0; k < M; k++) {
		in >> value;
		if (value == 1)
			vmono.v[k] = 1;
		else
			vmono.v[k] = 0;
	}
	return in;
}*/

istream & operator>>(istream &in, Vmono & vmono) {
	int i;
	char c;
	in >> c;
	if (c == 'v') {
		while (c == 'v') {
			in >> i;
			if (i < M)
				vmono.v[i] = 1;
			else
				cout << "i out of range." << endl;
			in >> c;
		}
	}
	else if (c != '1') {
		cout << "input correct vmono." << endl;
	}
	return in;
}


ostream & operator <<(ostream &out, Vmono &vmono) {
	if (vmono.v.count() > 0) {
		for (int k = 0; k < M; k++) {
			if (vmono.v[k] == 1) {
				out << "v" << k;
			}
		}
	}
	else {
		out << "1";
	}
	return out;
}


ostream & operator <<(ostream &out, const Vmono &vmono) {
	if (vmono.v.count() > 0) {
		for (int k = 0; k < M; k++) {
			if (vmono.v[k] == 1) {
				out << "v" << k;
			}
		}
	}
	else {
		out << "1";
	}
	return out;
}



Vmono operator*(const Vmono &vm1, const Vmono &vm2) {
	Vmono vm;
	vm.v = vm1.v | vm2.v;
	return vm;
}

/*istream & operator>>(istream &in, Kmono & kmono) {
	int value;
	for (int k = 0; k < N; k++) {
		in >> value;
		if (value == 1)
			kmono.k[k] = 1;
		else
			kmono.k[k] = 0;
	}
	return in;
}
*/

istream & operator>>(istream &in, Kmono & kmono) {
	int i;
	char c;
	in >> c;
	if (c == 'k') {
		while (c == 'k') {
			in >> i;
			if (i < N)
				kmono.k[i] = 1;
			else
				cout << "i out of range." << endl;
			in >> c;
		}
	}
	else if (c != '1') {
		cout << "input correct kmono." << endl;
	}
	return in;
}


ostream & operator <<(ostream &out, Kmono &kmono) {
	if (kmono.k.count() > 0) {
		for (int k = 0; k < N; k++) {
			if (kmono.k[k] == 1) {
				out << "k" << k;
			}
		}
	}
	else {
		out << "1";
	}
	return out;
}


ostream & operator <<(ostream &out, const Kmono &kmono) {
	if (kmono.k.count() > 0) {
		for (int k = 0; k < N; k++) {
			if (kmono.k[k] == 1) {
				out << "k" << k;
			}
		}
	}
	else {
		out << "1";
	}
	return out;
}



Kmono operator*(const Kmono &km1, const Kmono &km2) {
	Kmono km;
	km.k = km1.k | km2.k;
	return km;
}


ostream & operator <<(ostream &out, Kpoly &kpoly) {
	int size = kpoly.p.size();
	if (size > 0) {
		int i = 0;
		auto it = kpoly.p.begin();
		while (it != kpoly.p.end()) {
			i++;
			if (i != size) {
				out << *it << "+";
			}
			else
				out << *it;
			it++;
		}
	}
	else
		out << "0";
	return out;
}


/*istream & operator >>(istream &in, Kpoly & kpoly) {
	int termNum;
	in >> termNum;
	kpoly.p.clear();
	for (int i = 0; i < termNum; i++){
		Kmono km;
		in >> km;
		kpoly.p.insert(km);
	}
	return(in);
}*/

istream & operator >>(istream &in, Kpoly & kpoly) {
	kpoly.p.clear();
	char c = '+';
	int i;
	while (c == '+') {
		in >> c;
		//cout << c;
		if (c == 'k') {
			Kmono km;
			while (c == 'k') {
				in >> i;
				if (i < N)
					km.k[i] = 1;
				else
					cout << "i out of range." << endl;
				in >> c;
			}
			if (kpoly.p.count(km) == 0)
				kpoly.p.insert(km);
			else
				kpoly.p.erase(km);
		}
		else if (c == '1') {
			Kmono km;
			if (kpoly.p.count(km) == 0)
				kpoly.p.insert(km);
			else
				kpoly.p.erase(km);
			in >> c;
			
		}
		else if (c == '0') {
			in >> c;
		}
		else {
			cout << "input correct kpoly." << endl;
		}
	}
	return(in);
}


Kpoly operator + (const Kpoly &kpoly1, const Kpoly &kpoly2) {
	Kpoly kp;
	cmpKmono cmpK;
	set_symmetric_difference(kpoly1.p.begin(), kpoly1.p.end(), kpoly2.p.begin(), kpoly2.p.end(), insert_iterator<set<Kmono, cmpKmono>>(kp.p, kp.p.begin()), cmpK);
	return kp;
}

Kpoly operator * (const Kpoly &kpoly1, const Kpoly &kpoly2) {
	Kpoly kp;
	Kmono km;
	auto it1 = kpoly1.p.begin();
	while (it1 != kpoly1.p.end()) {
		auto it2 = kpoly2.p.begin();
		while (it2 != kpoly2.p.end()) {
			km = (*it1) * (*it2);
			if (kp.p.count(km) == 0)
				kp.p.insert(km);
			else
				kp.p.erase(km);
			it2++;
		}
		it1++;
	}
	return kp;
}


ostream & operator <<(ostream &out, KVpoly &kvp) {
	auto it = kvp.p.begin();
	int i = 0;
	if (kvp.p.size() == 0) out << "0";
	while (it != kvp.p.end()) {
		i++;
		out << (*it).first << "*";
		if ((*it).second.p.size() > 1)
			out << "(" << (*it).second << ")";
		else
			out << (*it).second;
		if (i < kvp.p.size()) {
			out << "+";
		}	
		it++;
	}
	return out;
}


istream & operator >>(istream &in, KVpoly &kvp) {
	kvp.p.clear();
	char c = '+';
	int i;
	while (c == '+') {
		in >> c;
		if (c == 'v') {
			Vmono vm;
			while (c == 'v') {
				in >> i;
				if (i < M)
					vm.v[i] = 1;
				else
					cout << "i out of range." << endl;
				in >> c;
			}
			
			Kpoly kp;
			if (c == '*') {
				in >> c;
				if (c == '(') {
					in >> kp;
					in >> c;
					kvp.p[vm] = kp + kvp.p[vm];
				}
				else {
					if (c == 'k') {
						Kmono km;
						while (c == 'k') {
							in >> i;
							if (i < N)
								km.k[i] = 1;
							else
								cout << "i out of range." << endl;
							in >> c;
						}
						kp.p.insert(km);
						kvp.p[vm] = kp + kvp.p[vm];
					}
					else if (c == '1') {
						Kmono km;
						kp.p.insert(km);
						kvp.p[vm] = kvp.p[vm] + kp;
						in >> c;
					}
					else if (c == '0') {
						in >> c;
					}
					else 
						cout << "input correct kvpoly." << endl;
				}
			}
			else
				cout << "input correct kvpoly." << endl;
		}
		else if (c == '1') {
			Vmono vm;
			in >> c;

			Kpoly kp;
			if (c == '*') {
				in >> c;
				if (c == '(') {
					in >> kp;
					in >> c;
					kvp.p[vm] = kp + kvp.p[vm];
				}
				else {
					if (c == 'k') {
						Kmono km;
						while (c == 'k') {
							in >> i;
							if (i < N)
								km.k[i] = 1;
							else
								cout << "i out of range." << endl;
							in >> c;
						}
						kp.p.insert(km);
						kvp.p[vm] = kp + kvp.p[vm];
					}
					else if (c == '1') {
						Kmono km;
						kp.p.insert(km);
						kvp.p[vm] = kvp.p[vm] + kp;
						in >> c;
					}
					else if (c == '0') {
						in >> c;
					}
					else
						cout << "input correct kvpoly." << endl;
				}
			}
			else
				cout << "input correct kvpoly." << endl;
			
		}
		else if (c == '0') {
			in >> c;
		}
		else
			cout << "input correct kvpoly." << endl;

	}	
		
	return(in);
}


KVpoly operator + (const KVpoly &kvp1, const KVpoly &kvp2) {
	KVpoly kvp;
	auto it1 = kvp1.p.begin();
	auto it2 = kvp2.p.begin();
	cmpVmono cmpV;
	while (it1 != kvp1.p.end() && it2 != kvp2.p.end()) {
		if (cmpV((*it1).first, (*it2).first)) {
			kvp.p[(*it1).first] = (*it1).second;
			it1++;
		}
		else if (cmpV((*it2).first, (*it1).first)) {
			kvp.p[(*it2).first] = (*it2).second;
			it2++;
		}
		else {
			Kpoly kp = (*it1).second + (*it2).second;
			if (kp.p.size() > 0)
				kvp.p[(*it1).first] = kp;
			it1++;
			it2++;
		}
	}
	while (it1 != kvp1.p.end()) {
		kvp.p[(*it1).first] = (*it1).second;
		it1++;
	}
	while (it2 != kvp2.p.end()) {
		kvp.p[(*it2).first] = (*it2).second;
		it2++;
	}
	return kvp;
}
KVpoly operator * (const KVpoly &kvp1, const KVpoly &kvp2) {
	KVpoly kvp;
	auto it1 = kvp1.p.begin();
	
	while (it1 != kvp1.p.end()) {
		auto it2 = kvp2.p.begin();
		while (it2 != kvp2.p.end()) {
			Vmono vm = (*it1).first * (*it2).first;
			Kpoly kp = (*it1).second * (*it2).second;
			kvp.p[vm] = kp + kvp.p[vm];
			if (kvp.p[vm].p.size() == 0) {
				kvp.p.erase(vm);
			}
			it2++;
		}
		it1++;
	}
	return(kvp);
}



int subs_kpoly(bitset<N> kValue, Kpoly kp) {
	int kpvalue = 0;
	auto it = kp.p.begin();
	while (it != kp.p.end()) {
		if ((kValue | (*it).k) == kValue) {
			kpvalue = kpvalue ^ 1;
		}
		it++;
	}
	return(kpvalue);
}

void sim_kvpoly_with_0_kfun(vector<KVpoly> kvps, vector<KVpoly> &simkvps, bitset<N> key0) {
	bitset<N> key0_f;
	key0_f = key0;
	key0_f.flip();
	for (int i = 0; i < kvps.size(); i++) {
		KVpoly kvp;
		auto it = kvps[i].p.begin();
		while(it != kvps[i].p.end()) {
			Kpoly kp;
			auto its = (*it).second.p.begin();
			while (its != (*it).second.p.end()) {
				if (((*its).k & key0_f).count() == 0)
					kp.p.insert(*its);
				its++;
			}
			if (kp.p.size() > 0) {
				kvp.p[(*it).first] = kp;
			}
			it++;
		}
		simkvps[i] = kvp;
	}
}


void fprint_latex_form_kpoly(ofstream *file, Kpoly kp) {
	int size = kp.p.size();
	if (size > 0) {
		int i = 0;
		auto it = kp.p.begin();
		while (it != kp.p.end()) {
			i++;
			if ((*it).k.count() > 0) {
				for (int j = 0; j < N; j++) {
					if ((*it).k[j] == 1) {
						(*file) << "k[" << j << "]";
					}
				}
			}
			else
				(*file) << "1";
			if (i != size) {
				(*file) << " \\oplus ";
			}
			it++;
		}
	}
	else
		(*file) << "0";
}

void fprint_latex_form_vmono(ofstream *file, Vmono vm) {
	if (vm.v.count() > 0) {
		for (int k = 0; k < M; k++) {
			if (vm.v[k] == 1) {
				(*file) << "v[" << k << "]";
			}
		}
	}
	else {
		(*file) << "1";
	}
}

void fprint_latex_form_kvpoly(ofstream *file, KVpoly kvp) {
	if (kvp.p.size() == 0) (*file) << "0";
	auto it = kvp.p.begin();
	int i = 0;
	while (it != kvp.p.end()) {
		i++;
		fprint_latex_form_vmono(file, (*it).first);
		(*file) << "*";
		if ((*it).second.p.size() > 1) {
			(*file) << "(";
			fprint_latex_form_kpoly(file,(*it).second);
			(*file) << ")";
		}
		else {
			fprint_latex_form_kpoly(file,(*it).second);
		}
		if (i < kvp.p.size()) {
			(*file) << "\\oplus ";
		}	
		it++;
	}
}