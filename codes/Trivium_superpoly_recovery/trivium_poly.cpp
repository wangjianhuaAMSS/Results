#include "main.h"

void trivium_initial_state_poly(vector<KVpoly>& state) {
	state.clear();
	Vmono vm;
	Kpoly kp;
	Kmono km;
	kp.p.insert(km);
	for (int i = 0; i < 288; i++) {
		KVpoly kvp;
		state.push_back(kvp);
	}
	for (int i = 0; i < 80; i++) {
		Vmono vm0;
		vm0.v[i] = 1;
		state[i + 93].p[vm0] = kp;
		Kmono km0;
		Kpoly kp0;
		km0.k[i] = 1;
		kp0.p.insert(km0);
		state[i].p[vm] = kp0;
	}
	state[285].p[vm] = kp;
	state[286].p[vm] = kp;
	state[287].p[vm] = kp;
}

void trivium_update_core_poly(vector<KVpoly>& state) {
	KVpoly p;
	
	p = state[90] * state[91] + state[65] + state[92] + state[170];
	state.erase(state.begin() + 92);
	state.insert(state.begin() + 92, p);

	p = state[174] * state[175] + state[161] + state[176] + state[263];
	state.erase(state.begin() + 176);
	state.insert(state.begin() + 176, p);

	p = state[285] * state[286] + state[242] + state[287] + state[68];
	state.pop_back();
	state.insert(state.begin(), p);

}

void trivium_poly(vector<KVpoly>& state, int round0) {
	trivium_initial_state_poly(state);
	for (int r = 1; r <= round0; r++) {
		trivium_update_core_poly(state);
	}
}

void transform_k_fun(KVpoly &kvp, vector<Kpoly>& k_fun) {
	auto it = kvp.p.begin();
	while (it != kvp.p.end()) {
		if (((*it).second.p.size() > 1)) {
			Kmono km;
			Kpoly kp;
			km.k[k_fun.size()] = 1;
			kp.p.insert(km);
			k_fun.push_back((*it).second);
			(*it).second = kp;	
		}
		it++;
	}
}

void trivium_init_k_fun_poly(vector<Kpoly> &k_fun) {
	for (int i = 0; i < 80; i++) {
		Kmono km;
		km.k[i] = 1;
		Kpoly kp;
		kp.p.insert(km);
		k_fun.push_back(kp);
	}
}

void trivium_simplify_poly(vector<KVpoly> &state, vector<Kpoly> & k_fun, int round0) {
	state.clear();
	k_fun.clear();
	trivium_initial_state_poly(state);
	trivium_init_k_fun_poly(k_fun);
	for (int r = 1; r <= round0; r++) {
		trivium_update_core_poly(state);
		transform_k_fun(state[0], k_fun);
		transform_k_fun(state[93], k_fun);
		transform_k_fun(state[177], k_fun);
		
	}
}

void trivium_flag_poly(bitset<80> flag, vector<KVpoly> &state, vector<KVpoly> &pstate) {
    pstate.clear();
    bitset<80> b;
    for (int i = 0; i < 288; i++) {
        pstate.push_back(state[i]);
        auto it = state[i].p.begin();
        while (it != state[i].p.end()) {
            b = (*it).first.v | flag;
            if (b != flag) {
                pstate[i].p.erase((*it).first);
            }
            it++;
        }
    }
}





