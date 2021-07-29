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
#include "vector_degree.h"


#ifndef __MAIN_H__
#define __MAIN_H__

//#define N 542
#define N 542
#define M 80


#define MAX_V 40 //an integer which is greater than the size of the index set of vector degree



#define Round 850

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

void trivium_vector_degree_estimation(int8_t *zout, int round0, bitset<80> vd_index, bitset<80> v_degree, bitset<80> v_0, bitset<80> k_degree, bitset<80> k_0, int output_mode);

void set_vector_degree_index(bitset<80>& vd_index, bitset<80> v_degree, bitset<80> v_0, bitset<80> k_degree, bitset<80> k_0, int Convdn, int round0);
#endif