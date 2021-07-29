#include<iostream>
#include<vector>
#include<stdlib.h>

using namespace std;

#ifndef __VECTOR_DEGREE_H__
#define __VECTOR_DEGREE_H__

class Vdeg{
public: vector<int8_t> v;
public: 
	//Vdeg();
	//Vdeg(int n);
	friend ostream & operator << (ostream &out, Vdeg &vd);
	friend istream & operator >> (istream &in, Vdeg &vd);
	friend Vdeg operator +(const Vdeg vd1, const Vdeg vd2);
	friend Vdeg operator *(const Vdeg vd1, const Vdeg vd2);
};

Vdeg min_vector_degree(Vdeg vd1, Vdeg vd2);

int8_t compute_degree(Vdeg vd);

int8_t limit_degree(Vdeg vd);

int8_t adjusted_degree(Vdeg vd, int8_t max_degree);

#endif