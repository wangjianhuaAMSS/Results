#include"gurobi_c++.h"
#include <string.h>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<bitset>
#include<set>
#include<algorithm>
#include<map>
#include<iomanip>
#include<utility>
#include<cmath>
#include<time.h>
#include<stdlib.h>
#include <iterator>


#ifndef __MAIN_H__
#define __MAIN_H__

//#define N 542
#define N 542
#define M 80



#define BOUND 200000 //prevent out of memory
#define TIMELIMIT 300 //time limit for optimizer


using namespace std;


template <size_t T> struct cmpBitset {
	bool operator()(const bitset<T>& a, const bitset<T>& b) const {
		for (int i = T - 1; i >= 0; i--) {
			if (a[i] < b[i])
				return true;
			else if (a[i] > b[i])
				return false;
		}
		return false;
	}
};

class Vmono {
public: bitset<M> v;
public:
	friend ostream & operator <<(ostream &out, Vmono &vmono);
	friend istream & operator>>(istream &in, Vmono & vmono);
	friend ostream & operator <<(ostream &out, const Vmono &vmono);
	friend Vmono operator*(const Vmono &vm1, const Vmono &vm2);
};

struct cmpVmono {
	bool operator()(const Vmono &vm1, const Vmono &vm2) const {
		cmpBitset<M> cmp;
		return cmp(vm1.v, vm2.v);
	}
};

class Kmono {
public: bitset<N> k;
public:
	friend ostream & operator <<(ostream &out, Kmono &kmono);
	friend istream & operator >>(istream &in, Kmono & kmono);
	friend ostream & operator <<(ostream &out, const Kmono &kmono);
	friend Kmono operator*(const Kmono &km1, const Kmono &km2);
};

struct cmpKmono {
	bool operator()(const Kmono &km1, const Kmono &km2) const {
		cmpBitset<N> cmp;
		return cmp(km1.k, km2.k);
	}
};

class Kpoly {
public: set<Kmono, cmpKmono> p;
public: 
	friend ostream & operator <<(ostream &out, Kpoly &kpoly);
	friend istream & operator >>(istream &in, Kpoly &kpoly);
	friend Kpoly operator + (const Kpoly &kpoly1, const Kpoly &kpoly2);
	friend Kpoly operator * (const Kpoly &kpoly1, const Kpoly &kpoly2);
};

class KVpoly {
public: map<Vmono, Kpoly, cmpVmono> p;
public:
	friend ostream & operator <<(ostream &out, KVpoly &kvp);
	friend istream & operator >>(istream &in, KVpoly &kvp);
	friend KVpoly operator + (const KVpoly &kvp1, const KVpoly &kvp2);
	friend KVpoly operator * (const KVpoly &kvp1, const KVpoly &kvp2);
};

void trivium_poly(vector<KVpoly>& state, int round0);
void trivium_simplify_poly(vector<KVpoly> &state, vector<Kpoly> & k_fun, int round0);
void trivium_flag_poly(bitset<80> flag, vector<KVpoly> &state, vector<KVpoly> &pstate);
int recovery_superpoly(int initRound, int n0, int threadNumber, bitset<M> cube, vector<int> divround, vector<KVpoly> state0, vector<KVpoly> state1, vector<int> target, KVpoly & spoly);

#endif
