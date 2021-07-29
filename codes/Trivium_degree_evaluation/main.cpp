#include "main.h"




int main(int argc, char const* argv[]) {
	clock_t start, end;
	start = clock();
	srand((int)time(0));
	
	int cube_i = -1; 
	int cube_n;
	int target_round;
	int mode;
	bitset<80> cube, vd_index, v_0, k_degree, k_0;
	


	for (int i = 0; i < argc; i++) {
		if (!strcmp(argv[i], "-i")) cube_i = atoi(argv[i + 1]);
		if (!strcmp(argv[i], "-r")) target_round = atoi(argv[i + 1]);
    	if (!strcmp(argv[i], "-m")) mode = atoi(argv[i + 1]);
	}
	if (cube_i == 0) {
		cube_n = 80;
		for (int i = 0; i < cube_n; i++) {
			cube[i] = 1;
		}
		v_0 = cube;
		v_0.flip();
		set_vector_degree_index(vd_index, cube, v_0, k_degree, k_0, 8, 800);
	}
	else if (cube_i == 1) {
		int cube_index[39] = { 0, 2, 4, 6, 7, 9, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 39;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
		v_0 = cube;
		v_0.flip();
		vd_index[0] = 1; vd_index[2] = 1;  vd_index[4] = 1;  vd_index[6] = 1; 
		vd_index[7] = 1; vd_index[9] = 1;  //vd_index[77] = 1;
	}
	else if (cube_i == 2) {
		int cube_index[39] = { 0, 2, 4, 6, 8, 9, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 39;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
		v_0 = cube;
		v_0.flip();
		vd_index[0] = 1; vd_index[2] = 1;  vd_index[4] = 1;  vd_index[6] = 1; 
		vd_index[8] = 1; vd_index[9] = 1;  vd_index[77] = 1;
	}
	else if (cube_i == 3) {
		int cube_index[40] = { 0, 1, 2, 4, 6, 8, 9, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 40;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
		v_0 = cube;
		v_0.flip();
		vd_index[0] = 1; vd_index[1] = 1;  vd_index[2] = 1;  vd_index[4] = 1; 
		vd_index[6] = 1; vd_index[8] = 1;  vd_index[9] = 1;  vd_index[77] = 1;
	}
	else if (cube_i == 4) {
		int cube_index[44] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 21, 23, 25, 28, 30, 32, 34, 36, 38, 40, 43, 45, 47, 49, 51, 53, 55, 58, 60, 62, 64, 66, 68, 70, 73, 75, 77, 79};
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
		v_0 = cube;
		v_0.flip();
		vd_index[0] = 1; vd_index[2] = 1; vd_index[3] = 1; vd_index[4] = 1;
		vd_index[5] = 1; vd_index[6] = 1; vd_index[7] = 1; vd_index[8] = 1;
		vd_index[10] = 1;
	}
	else if (cube_i == 5) {
		int cube_index[44] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 21, 23, 26, 28, 30, 32, 34, 36, 38, 41, 43, 45, 47, 49, 51, 53, 56, 58, 60, 62, 64, 66, 68, 71, 73, 75, 77, 79};
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
		v_0 = cube;
		v_0.flip();
		vd_index[0] = 1; vd_index[2] = 1; vd_index[3] = 1; vd_index[4] = 1;
		vd_index[5] = 1; vd_index[6] = 1; vd_index[7] = 1; vd_index[8] = 1;
		vd_index[10] = 1;
	}
	else if (cube_i == 6) {
		int cube_index[44] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 21, 24, 26, 28, 30, 32, 34, 36, 39, 41, 43, 45, 47, 49, 51, 54, 56, 58, 60, 62, 64, 66, 69, 71, 73, 75, 77, 79 };
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
		v_0 = cube;
		v_0.flip();
		vd_index[0] = 1; vd_index[2] = 1; vd_index[3] = 1; vd_index[4] = 1;
		vd_index[5] = 1; vd_index[6] = 1; vd_index[7] = 1; vd_index[8] = 1;
		vd_index[10] = 1;
	}
	else if (cube_i == 7) {
		int cube_index[44] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 22, 24, 26, 28, 30, 32, 34, 37, 39, 41, 43, 45, 47, 49, 52, 54, 56, 58, 60, 62, 64, 67, 69, 71, 73, 75, 77, 79 };
		cube_n = 44;
		for (int i = 0; i < cube_n; i++) {
			cube[cube_index[i]] = 1;
		}
		v_0 = cube;
		v_0.flip();
		vd_index[0] = 1; vd_index[2] = 1; vd_index[3] = 1; vd_index[4] = 1;
		vd_index[5] = 1; vd_index[6] = 1; vd_index[7] = 1; vd_index[8] = 1;
		vd_index[10] = 1;
	}
	else {
		cout << "Please input again!" << endl;
		return(1);
	}
	

	int8_t zout[1000];

	trivium_vector_degree_estimation(zout, target_round, vd_index, cube, v_0, k_degree, k_0, mode);

	cout << "cube_I_" << cube_i << ", " << target_round << "-round" << ":" << signed(zout[0]) << endl;
	end = clock();
	cout << "total running time is " << double(end - start) / CLOCKS_PER_SEC << "sec" << endl;
	return 0;
}