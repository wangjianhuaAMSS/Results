#include "main.h"

int trivium_index[3][5] = { {65, 92, 170, 90, 91}, {161, 176, 263, 174, 175}, {242, 287, 68, 285, 286} };
int trivium_length[3] = { 93, 84, 111 };

void trivium_default_initial_vector_degree(vector<Vdeg> &D, bitset<80> v_degree, bitset<80> k_degree, bitset<80> v_0, bitset<80> k_0, bitset<80> vd_index)
{
	for (int i = 0; i < 80; i++)
	{
		if (k_degree[i] == 1)
		{
			D[i].v[0] = 1;
		}
		else if (k_0[i] == 0)
		{
			D[i].v[0] = 0;
		}
	}

	int k = 0;
	for (int i = 93; i < 173; i++)
	{
		if (vd_index[i - 93] == 1) {
			D[i].v[1 << k] = 0;
			k++;
		}
		else if (v_degree[i - 93] == 1)
		{
			D[i].v[0] = 1;
		}
		else if (v_0[i - 93] == 0)
		{
			D[i].v[0] = 0;
		}
	}
	for (int i = 285; i < 288; i++)
	{
		D[i].v[0] = 0;
	}
	//for (int i = 0; i < 288; i++)
	//	cout << i << ":" <<  D[i] << endl;
}


Vdeg trivium_vector_deg_of_three_adjacent_terms( int k, vector<Vdeg> D, vector<Vdeg> mul_D, vector<Vdeg> three_D)
{
	Vdeg d1;
	Vdeg m1, m2, m3;
	m1 = three_D[trivium_index[k][3] - 1] * mul_D[trivium_index[k][4]];
	m2 = three_D[trivium_index[k][4]] * mul_D[trivium_index[k][3]];
	m3 = min_vector_degree(m1, m2);
	m1 = three_D[trivium_index[k][3] - 1] * three_D[trivium_index[k][3]] * three_D[trivium_index[k][4]]; 
	d1 = min_vector_degree(m3, m1);
	return(d1);
}

Vdeg trivium_vector_degree_of_mul_term(int r, int k, vector<Vdeg> D,  vector<Vdeg> mul_D, vector<Vdeg> lin_D, vector<Vdeg> three_D)
{
	Vdeg mul_d;
	Vdeg d1, d2, d3;
	if (r < trivium_length[k])
	{
		mul_d = D[trivium_index[k][3]] * D[trivium_index[k][4]];
	}
	else
	{
		d1 = trivium_vector_deg_of_three_adjacent_terms(k, D, mul_D, three_D);
		d2 = mul_D[trivium_index[k][3]] * lin_D[trivium_index[k][4]];
		d3 = lin_D[trivium_index[k][3]] * D[trivium_index[k][4]];
		mul_d = d1 + d2 + d3;
	}
	return(mul_d);
}

void trivium_vector_degree_update(int r, vector<Vdeg> &D, vector<Vdeg> &mul_D, vector<Vdeg> &lin_D, vector<Vdeg> &three_D)
{
	Vdeg mul_d[3], lin_d[3];
	for (int i = 0; i < 3; i++)
	{
		mul_d[i] = trivium_vector_degree_of_mul_term(r, i, D, mul_D, lin_D, three_D);
		lin_d[i] = D[trivium_index[i][0]] + D[trivium_index[i][1]] + D[trivium_index[i][2]];
	}
	
	for (int i = 0; i < 2; i++)
	{
		mul_D[trivium_index[i][1]] = mul_d[i];
		lin_D[trivium_index[i][1]] = lin_d[i];
		three_D[trivium_index[i][1]] = D[trivium_index[i][4]];
		D[trivium_index[i][1]] = mul_d[i] + lin_d[i];
	}
	mul_D.pop_back();  mul_D.insert(mul_D.begin(), mul_d[2]);
	lin_D.pop_back();  lin_D.insert(lin_D.begin(), lin_d[2]);
	three_D.pop_back();  three_D.insert(three_D.begin(), D[trivium_index[2][4]]);
	D.pop_back();  D.insert(D.begin(), mul_d[2] + lin_d[2]);
	
}

void trivium_output_z(int8_t *d, vector<Vdeg> D, int output_mode, int8_t max_degree);
void trivium_vector_degree_estimation(int8_t *zout, int round0, bitset<80> vd_index, bitset<80> v_degree, bitset<80> v_0, bitset<80> k_degree, bitset<80> k_0, int output_mode) {
	/*cout << "v_degree: ";
	for (int i = 0; i < 80; i++){
		if (v_degree[i] == 1)
			cout << i << " ";
	}
	cout << endl;

	cout << "v_0: ";
	for (int i = 0; i < 80; i++) {
		if (v_0[i] == 1)
			cout << i << " ";
	}
	cout << endl;
	
	cout << "vd_index: ";
	for (int i = 0; i < 80; i++) {
		if (vd_index[i] == 1)
			cout << i << " ";
	}
	cout << endl;*/
	
	int8_t max_degree = v_degree.count();
	vector<Vdeg> D, mul_D, lin_D, three_D;
	Vdeg vd;
	for (int i = 0; i < (1 << vd_index.count()); i++)
			vd.v.push_back(-128);
	for (int i = 0; i < 288; i++) {
		D.push_back(vd); mul_D.push_back(vd);
		lin_D.push_back(vd); three_D.push_back(vd);
	}
	trivium_default_initial_vector_degree(D, v_degree, k_degree, v_0, k_0, vd_index);
	for (int i = 1; i <= round0; i++)
	{
		//cout << i << endl;
		trivium_vector_degree_update(i, D, mul_D, lin_D, three_D);
		if (i == round0)
		{
			if (output_mode == 1)
				trivium_output_z(&zout[i-round0],D, 1, max_degree);
			else if (output_mode == 2)
			{
				trivium_output_z(&zout[i - round0], D, 2, max_degree);
			}
		}
		/*int8_t zo;
		if (output_mode == 1) {
			trivium_output_z(&zo,D, 1, max_degree);
			cout << i << ":" << signed(zo) << endl;

		}
		else if (output_mode == 2)
		{
			trivium_output_z(&zo, D, 2, max_degree);
			cout << i << ":" << signed(zo) << endl;
		}*/
	}
}

void trivium_output_z(int8_t *d, vector<Vdeg> D, int output_mode, int8_t max_degree)
{
	Vdeg l;
	if (output_mode == 1) {
		l = D[trivium_index[0][0]] + D[trivium_index[0][1]] + D[trivium_index[1][0]] + D[trivium_index[1][1]] + D[trivium_index[2][0]] + D[trivium_index[2][1]];
		d[0] = compute_degree(l);
	}
	else if (output_mode == 2) {
		l = D[trivium_index[0][0]] + D[trivium_index[0][1]] + D[trivium_index[1][0]] + D[trivium_index[1][1]] + D[trivium_index[2][0]] + D[trivium_index[2][1]];
		d[0] = adjusted_degree(l, max_degree);
	}

}




void set_vector_degree_index(bitset<80>& vd_index, bitset<80> v_degree, bitset<80> v_0, bitset<80> k_degree, bitset<80> k_0, int Convdn, int round0) {
	srand((int)time(0));
	for (int i = 0; i < 79; i++) {
		if (v_degree[i] == 1 && v_degree[i + 1] == 1) {
			vd_index[i] = 1;
			vd_index[i + 1] = 1;
		}
	}
	if (int(vd_index.count()) < min(Convdn, int(v_degree.count()))) {
		map<int8_t, vector<int>,greater<int8_t>> d_index;
		int8_t zout[1000];
		for (int i = 0; i < 80; i++) {
			if (v_degree[i] == 1) {
				bitset<80> c, v;
				c[i] = 1;
				trivium_vector_degree_estimation(zout, round0, v, c, v_0, k_degree, k_0, 0);
				//cout << i << ":" << signed(zout[0]) << endl;
				d_index[zout[0]].push_back(i);
			}	
		}

		auto it = d_index.begin();
		/*while (it != d_index.end()) {
			cout << signed((*it).first) << ":";
			auto id = (*it).second.begin();
			while (id != (*it).second.end()) {
				cout << (*id) << " ";
				id++;
			}
			cout << endl;
			it++;
		}
		it = d_index.begin();*/
		while (int(vd_index.count()) < min(Convdn, int(v_degree.count()))) {
			int in = rand() % (*it).second.size();
			vd_index[(*it).second[in]] = 1;
			(*it).second.erase((*it).second.begin() + in);
			if ((*it).second.size() == 0)
				it++;	
		}
	}
	else {
		vector<int> invd;
		for (int i = 0; i < 80; i++) {
			if (vd_index[i] == 1)
				invd.push_back(i);
		}
		while (int(vd_index.count()) > min(Convdn, int(v_degree.count()))) {
			int in = rand() % invd.size();
			vd_index[invd[in]] = 0;
			invd.erase(invd.begin() + in);
		}
	}
	
}



