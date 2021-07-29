#include "main.h"




int main(int argc, char const* argv[]) {
	clock_t start, end;
	start = clock();
	srand((int)time(0));
	int cube_i = -1;
	int cube_n;
	int target_round;
	int threadNumber;
	bitset<80> cube;


	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-i")) cube_i = atoi(argv[i + 1]);
		if (!strcmp(argv[i], "-r")) target_round = atoi(argv[i + 1]);
    	if (!strcmp(argv[i], "-t")) threadNumber = atoi(argv[i + 1]);
	}
	if (cube_i == 1) {
		int cube_index[39] = { 0, 2, 4, 6, 7, 9, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 39;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
	}
	else if (cube_i == 2) {
		int cube_index[39] = { 0, 2, 4, 6, 8, 9, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 39;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
	}
	else if (cube_i == 3) {
		int cube_index[40] = { 0, 1, 2, 4, 6, 8, 9, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 40;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
	}
	else if (cube_i == 4) {
		int cube_index[44] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 21, 23, 25, 28, 30, 32, 34, 36, 38, 40, 43, 45, 47, 49, 51, 53, 55, 58, 60, 62, 64, 66, 68, 70, 73, 75, 77, 79};
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
	}
	else if (cube_i == 5) {
		int cube_index[44] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 21, 23, 26, 28, 30, 32, 34, 36, 38, 41, 43, 45, 47, 49, 51, 53, 56, 58, 60, 62, 64, 66, 68, 71, 73, 75, 77, 79};
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
	}
	else if (cube_i == 6) {
		int cube_index[44] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
	}
	else if (cube_i == 7) {
		int cube_index[44] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 22, 24, 26, 28, 30, 32, 34, 37, 39, 41, 43, 45, 47, 49, 52, 54, 56, 58, 60, 62, 64, 67, 69, 71, 73, 75, 77, 79 };
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
	}
	else {
		cout << "Please input again!" << endl;
		return(1);
	}
	
	
	
	vector<int> divround, target;
	KVpoly spoly;
	ofstream spolyFile;
	string str = "spoly" + to_string(cube_i) + "_" + to_string(target_round) + ".txt";
	spolyFile.open(str.c_str());
	
	divround.push_back(target_round);
	divround.push_back(200);


	vector<KVpoly> state0(288),state1(288);
	vector<Kpoly> k_fun;
	trivium_simplify_poly(state0, k_fun, 0);
	trivium_simplify_poly(state1, k_fun, 200);
	target.push_back(65);
	target.push_back(92);
	target.push_back(161);
	target.push_back(176);
	target.push_back(242);
	target.push_back(287);
	if (recovery_superpoly(0, 200, threadNumber, cube, divround, state0, state1, target, spoly) == 1) {
		cout << spoly << endl;
        spolyFile << spoly << endl;
	}
    spolyFile.close();
	end = clock();
	cout << "total running time is " << double(end - start) / CLOCKS_PER_SEC << "sec" << endl;
	return 0;
}
