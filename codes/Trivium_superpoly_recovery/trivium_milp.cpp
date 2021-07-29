#include "main.h"

int dn = 0;

void triviumCoreThree(GRBModel& model, vector<GRBVar>& x, int i1, int i2, int i3, int i4, int i5) {

	GRBVar y1 = model.addVar(0, 1, 0, GRB_BINARY);
	GRBVar y2 = model.addVar(0, 1, 0, GRB_BINARY);
	GRBVar y3 = model.addVar(0, 1, 0, GRB_BINARY);
	GRBVar y4 = model.addVar(0, 1, 0, GRB_BINARY);
	GRBVar y5 = model.addVar(0, 1, 0, GRB_BINARY);

	GRBVar z1 = model.addVar(0, 1, 0, GRB_BINARY);
	GRBVar z2 = model.addVar(0, 1, 0, GRB_BINARY);

	GRBVar a = model.addVar(0, 1, 0, GRB_BINARY);



	model.addConstr(y1 <= x[i1]);
	model.addConstr(z1 <= x[i1]);
	model.addConstr(y1 + z1 >= x[i1]);


	model.addConstr(y2 <= x[i2]);
	model.addConstr(z2 <= x[i2]);
	model.addConstr(y2 + z2 >= x[i2]);

	model.addConstr(y3 <= x[i3]);
	model.addConstr(a <= x[i3]);
	model.addConstr(y3 + a >= x[i3]);

	model.addConstr(y4 <= x[i4]);
	model.addConstr(a <= x[i4]);
	model.addConstr(y4 + a >= x[i4]);

	model.addConstr(y5 == x[i5] + a + z1 + z2);

	x[i1] = y1;
	x[i2] = y2;
	x[i3] = y3;
	x[i4] = y4;
	x[i5] = y5;

}

void triviumUpdate(int r0, int r1, GRBModel& model, vector<vector<GRBVar>> & s) {
	for (int r = r0; r < r1; r++) {
		vector<GRBVar> tmp = s[r];
		triviumCoreThree(model, tmp, 65, 170, 90, 91, 92);
		triviumCoreThree(model, tmp, 161, 263, 174, 175, 176);
		triviumCoreThree(model, tmp, 242, 68, 285, 286, 287);

		for (int i = 0; i < 288; i++) {
			s[r + 1][(i + 1) % 288] = tmp[i];
		}
	}
}

void triviumStateAddconstr(int r0, bitset<288> state, GRBModel & model, vector<vector<GRBVar>> & s) {
	for (int i = 0; i < 288; i++) {
		if (state[i] == 1)
			model.addConstr(s[r0][i] == 1);
		else
			model.addConstr(s[r0][i] == 0);
	}
}

void triviumInitSol(int r0, int r1, vector<bitset<288>> trail, GRBModel & model, vector<vector<GRBVar>> & s) {
	for (int r = r0; r <= r1; r++) {
		for (int i = 0; i < 288; i++) {
			if (trail[r][i] == 1)
				s[r][i].set(GRB_DoubleAttr_Start, 1);
			else
				s[r][i].set(GRB_DoubleAttr_Start, 0);
		}
	}
}

int triviumMiddle(int evalNumRounds, int n0, int threadNumber, vector<bitset<288>> trail);
int milp_model_alg(int evalNumRounds, int initRound, int n0, vector<KVpoly> pstate, bitset<M> cube, int threadNumber, bitset<288> outputbit, map<bitset<288>, int, cmpBitset<288>> *n0state, bool lt);

class Milp_cb : public GRBCallback
{
public:
	int evalNumRounds;
	int initRound;
	int n0;
	map<bitset<288>, int, cmpBitset<288>> cbstate;
	vector<vector<GRBVar>> s;
	map<bitset<288>, int, cmpBitset<288>>* n0state;
	int threadNumber;
public:
	Milp_cb(int xevalNumRounds, int xinitRound, int xn0, map<bitset<288>, int, cmpBitset<288>> &xcbstate, vector<vector<GRBVar>> xs, map<bitset<288>, int, cmpBitset<288>>* xn0state, int xthreadNumber) {
		evalNumRounds = xevalNumRounds;
		initRound = xinitRound;
		n0 = xn0;
		cbstate = xcbstate;
		s = xs;
		n0state = xn0state;
		threadNumber = xthreadNumber;
	}
protected:
	void callback() {
		try {
			if (where == GRB_CB_MIPSOL) {
				vector<bitset<288>> trail(evalNumRounds + 1);
				for (int r = initRound; r <= evalNumRounds; r++) {
					for (int i = 0; i < 288; i++) {
						if (round(getSolution(s[r][i])) == 1) trail[r][i] = 1;
						else trail[r][i] = 0;
					}
				}

				/*for (int i = 0; i < 288; i++) {
					if (round(getSolution(s[200][i])) == 1) {
						cout << i << ": ";
						auto it = x[i].begin();
						while (it != x[i].end()) {
							if (round(getSolution((*it).second)) == 1) {
								cout << (*it).first << " ";
							}
							it++;
						}
					}
				}
				cout << endl;*/

				GRBLinExpr addCon = 0.0;
				for (int i = 0; i < 288; i++) {
					if (trail[n0][i] == 1) {
						//cout << i << " ";
						addCon += (1 - s[n0][i]);
					}
					else {
						addCon += s[n0][i];
					}
				}
				GRBLinExpr addCon1 = 0.0;
				for (int i = 0; i < 288; i++) {
					addCon1 += s[n0][i];
				}
				//cout << endl;

				if (cbstate.count(trail[n0]) == 0) {
					
					cbstate[trail[n0]] = triviumMiddle(evalNumRounds, n0, threadNumber, trail);
					if (cbstate[trail[n0]] > 0) {
						if (cbstate[trail[n0]] % 2 == 1) {
							(*n0state)[trail[n0]]++;
							cout << (*n0state).size() << endl;
							if ((*n0state).size() > BOUND) { //prevent out of memory
								addLazy(addCon1 == 0); //stop optimize
							}
							else {
								addLazy(addCon >= 1);
							}
						}	
						else
							addLazy(addCon >= 1);
					}
					else {
						exit(0);
					}
				}
				else {
					addLazy(addCon >= 1);
				}
			}
			else if (where == GRB_CB_MESSAGE) {
				// Message callback
				string msg = getStringInfo(GRB_CB_MSG_STRING);
				cout << msg << flush;
			}
		}
		catch (GRBException e) {
			cerr << "Error number: " << e.getErrorCode() << endl;
			cerr << e.getMessage() << endl;
		}
		catch (...) {
			cout << "Error during callback" << endl;
		}
	}
};

int milp_model_alg(int evalNumRounds, int initRound, int n0, vector<KVpoly> pstate, bitset<M> cube, int threadNumber, bitset<288> outputbit, map<bitset<288>, int, cmpBitset<288>> *n0state, bool tl) {

	cout << endl;
	cout << "++++++++++++++++++++++++++++" << endl;
	cout << initRound << " round -- " << evalNumRounds << " round" << endl;

	try {
		// Create the environment
		GRBEnv env = GRBEnv();

		env.set(GRB_IntParam_LogToConsole, 0);
		env.set(GRB_IntParam_Threads, threadNumber);
		env.set(GRB_IntParam_MIPFocus, 3);
		env.set(GRB_StringParam_LogFile, "log_trivium.txt");


		env.set(GRB_IntParam_PoolSearchMode, 2);
		env.set(GRB_IntParam_PoolSolutions, 20000000);
		env.set(GRB_DoubleParam_PoolGap, GRB_INFINITY);
		env.set(GRB_IntParam_LazyConstraints, 1);

		if (tl == 1) {
			env.set(GRB_DoubleParam_TimeLimit, TIMELIMIT);
		}

		// Create the model
		GRBModel model = GRBModel(env);

		// Create variables
		vector<map<Vmono, GRBVar, cmpVmono>> x(288);
		vector<vector<GRBVar>> s(evalNumRounds + 1, vector<GRBVar>(288));

		//IV var constraints
		vector<GRBLinExpr> v_num(M, 0.0);

		//objective : sum of N0-round states
		GRBLinExpr ssum = 0;

		//N0-round states
		for (int i = 0; i < 288; i++) {
			auto it = pstate[i].p.begin();
			GRBLinExpr pisum = 0.0; //i-th state
			while (it != pstate[i].p.end()) {
				x[i][(*it).first] = model.addVar(0, 1, 0, GRB_BINARY);
				for (int j = 0; j < M; j++) {
					if ((*it).first.v[j] == 1)
						v_num[j] += x[i][(*it).first];
				}
				pisum += x[i][(*it).first];
				it++;
			}
			s[initRound][i] = model.addVar(0, 1, 0, GRB_BINARY);
			ssum += s[initRound][i];
			model.addConstr(pisum == s[initRound][i]);
		}

		//set objective
		model.setObjective(ssum);

		//cube iv constraints
		for (int j = 0; j < M; j++) {
			if (cube[j] == 1) {
				model.addConstr(v_num[j] >= 1);
				//cout << j << endl;
			}
		}

		triviumUpdate(initRound, evalNumRounds, model, s);

		// Output constraint
		triviumStateAddconstr(evalNumRounds, outputbit, model, s);


		model.update();
		map<bitset<288>, int, cmpBitset<288>> cbstate;
		Milp_cb cb = Milp_cb(evalNumRounds, initRound, n0, cbstate, s, n0state, threadNumber);
		model.setCallback(&cb);
		model.optimize();

		double dulation = model.get(GRB_DoubleAttr_Runtime);
		cout << dulation << "sec" << endl;

		int mstatus = model.get(GRB_IntAttr_Status);
		
		if (mstatus == GRB_TIME_LIMIT) {
			return(2);
		}
		else {
			int solCount = model.get(GRB_IntAttr_SolCount);
			if (solCount > 0) {
				exit(0);
			}
			else {
				if ((*n0state).size() > BOUND) {
					return(0);
				}
				else
					return(1);
			}
		}

		

	}
	catch (GRBException e) {
		cerr << "Error code = " << e.getErrorCode() << endl;
		cerr << e.getMessage() << endl;
		return(0);
	}
	catch (...) {
		cerr << "Exception during optimization" << endl;
		return(0);
	}
}


int triviumMiddle(int evalNumRounds, int n0, int threadNumber, vector<bitset<288>> trail) {

	cout << endl;
	cout << "++++++++++++++++++++++++++++" << endl;
	cout << n0 << " round -- " << evalNumRounds << " round" << endl;
	//gurobi
	try {
		// Create the environment
		GRBEnv env = GRBEnv();

		// close standard output
		env.set(GRB_IntParam_LogToConsole, 0);
		env.set(GRB_IntParam_Threads, threadNumber);
		//env.set(GRB_IntParam_MIPFocus, GRB_MIPFOCUS_BESTBOUND);
		env.set(GRB_StringParam_LogFile, "log_trivium.txt");


		env.set(GRB_IntParam_PoolSearchMode, 2);
		env.set(GRB_IntParam_PoolSolutions, 20000000);
		env.set(GRB_DoubleParam_PoolGap, GRB_INFINITY);

		// Create the model
		GRBModel model = GRBModel(env);

		// Create variables
		vector<vector<GRBVar>> s(evalNumRounds + 1, vector<GRBVar>(288));

		for (int i = 0; i < 288; i++) {
			s[n0][i] = model.addVar(0, 1, 0, GRB_BINARY);
		}

		triviumUpdate(n0, evalNumRounds, model, s);

		triviumStateAddconstr(n0, trail[n0], model, s);
		triviumStateAddconstr(evalNumRounds, trail[evalNumRounds], model, s);

		triviumInitSol(n0, evalNumRounds, trail, model, s);

		// Solve
		model.update();
		model.optimize();

		int solCount = model.get(GRB_IntAttr_SolCount);
		double dulation = model.get(GRB_DoubleAttr_Runtime);

		cout << dulation << "sec" << endl;
		//
		return solCount;
	}
	catch (GRBException e) {
		cerr << "Error code = " << e.getErrorCode() << endl;
		cerr << e.getMessage() << endl;
	}
	catch (...) {
		cerr << "Exception during optimization" << endl;
	}

	return -1;
}


void triviumLast(int n2, int n1, int threadNumber, bitset<288> n2bit, map<bitset<288>, int, cmpBitset<288>> &n1bits) {

	cout << endl;
	cout << "++++++++++++++++++++++++++++" << endl;
	cout << n1 << " round -- " << n2 << " round" << endl;
	//gurobi
	try {
		// Create the environment
		GRBEnv env = GRBEnv();

		// close standard output
		env.set(GRB_IntParam_LogToConsole, 0);
		env.set(GRB_IntParam_Threads, threadNumber);
		//env.set(GRB_IntParam_MIPFocus, GRB_MIPFOCUS_BESTBOUND);
		env.set(GRB_StringParam_LogFile, "log_trivium.txt");


		env.set(GRB_IntParam_PoolSearchMode, 2);
		env.set(GRB_IntParam_PoolSolutions, 20000000);
		env.set(GRB_DoubleParam_PoolGap, GRB_INFINITY);

		// Create the model
		GRBModel model = GRBModel(env);

		// Create variables
		vector<vector<GRBVar>> s(n2 + 1, vector<GRBVar>(288));

		for (int i = 0; i < 288; i++) {
			s[n1][i] = model.addVar(0, 1, 0, GRB_BINARY);
		}

		triviumUpdate(n1, n2, model, s);

		triviumStateAddconstr(n2, n2bit, model, s);

		// Solve
		model.update();
		model.optimize();

		int solCount = model.get(GRB_IntAttr_SolCount);
		bitset<288> tmp;
		for (int i = 0; i < solCount; i++) {
			model.set(GRB_IntParam_SolutionNumber, i);
			for (int j = 0; j < 288; j++)
				if (round(s[n1][j].get(GRB_DoubleAttr_Xn)) == 1)
					tmp[j] = 1;
				else
					tmp[j] = 0;
			n1bits[tmp]++;
		}
		
		double dulation = model.get(GRB_DoubleAttr_Runtime);
		cout << dulation << "sec" << endl;
		//
	}
	catch (GRBException e) {
		cerr << "Error code = " << e.getErrorCode() << endl;
		cerr << e.getMessage() << endl;
	}
	catch (...) {
		cerr << "Exception during optimization" << endl;
	}
}


void N0_round_model(vector<KVpoly> pstate, bitset<M> cube, int threadNumber, bitset<288> piconstr, KVpoly & spoly) {
	try {
		// Create the environment
		GRBEnv env = GRBEnv();

		// close standard output
		env.set(GRB_IntParam_LogToConsole, 0);
		env.set(GRB_IntParam_Threads, threadNumber);


		env.set(GRB_StringParam_LogFile, "log_trivium.txt");
		env.set(GRB_IntParam_PoolSearchMode, 2);
		env.set(GRB_IntParam_PoolSolutions, 2000000000);
		env.set(GRB_DoubleParam_PoolGap, GRB_INFINITY);

		// Create the model
		GRBModel model = GRBModel(env);

		// Create variables
		vector<map<Vmono, GRBVar, cmpVmono>> x(288);
		vector<GRBLinExpr> v_num(M, 0.0);
		for (int i = 0; i < 288; i++) {
			auto it = pstate[i].p.begin();
			GRBLinExpr pisum = 0.0;
			while (it != pstate[i].p.end()) {
				x[i][(*it).first] = model.addVar(0, 1, 0, GRB_BINARY);
				for (int j = 0; j < M; j++) {
					if ((*it).first.v[j] == 1)
						v_num[j] += x[i][(*it).first];
				}
				pisum += x[i][(*it).first];
				it++;
			}
			if (piconstr[i] == 1) {
				model.addConstr(pisum == 1);
				//cout << i << endl;
			}
			else
				model.addConstr(pisum == 0);
		}
		for (int j = 0; j < M; j++) {
			if (cube[j] == 1) {
				model.addConstr(v_num[j] >= 1);
				//cout << j << endl;
			}
		}

		// Solve
		//model.write("trivium.lp");
		model.update();
		model.optimize();



		//
		int solCount = model.get(GRB_IntAttr_SolCount);
		double dulation = model.get(GRB_DoubleAttr_Runtime);

		cout << dulation << "sec" << endl;
		cout << solCount <<  " solutions" << endl;
		//
		// check solution limit
		if (solCount >= 2000000000) {
			cerr << "Number of solutions is too large" << endl;
			exit(0);
		}
		if (solCount == 0) {
			cout << "no solution." << endl;
		}
		bitset<M> vcube;
		for (int i = 0; i < M;i++) {
			if (cube[i] == 1)
				vcube[i] = 1;
		}
		dn = dn + solCount;
		for (int i = 0; i < solCount; i++) {
			model.set(GRB_IntParam_SolutionNumber, i);
			Kpoly kp;
			Vmono vmono;
			Kmono kmono;
			kp.p.insert(kmono); //set kp = 1
			for (int j = 0; j < 288; j++) {
				if (piconstr[j] == 1) {
					auto it = x[j].begin();
					while (it != x[j].end()) {
						if (round((*it).second.get(GRB_DoubleAttr_Xn)) == 1) {
							kp = kp * pstate[j].p[(*it).first];
							vmono = vmono * (*it).first;
							break;
						}
						it++;
					}
				}
			}
			vmono.v = vmono.v ^ vcube;
			//print_vmono(vmono);
			//print_kmono(kmono);
			spoly.p[vmono] = kp + spoly.p[vmono];
		}

	}
	catch (GRBException e) {
		cerr << "Error code = " << e.getErrorCode() << endl;
		cerr << e.getMessage() << endl;
	}
	catch (...) {
		cerr << "Exception during optimization" << endl;
	}
}



int recovery_superpoly(int initRound, int n0, int threadNumber, bitset<M> cube, vector<int> divround, vector<KVpoly> state0, vector<KVpoly> state1, vector<int> target, KVpoly & spoly) {
	vector<KVpoly> pstate0, pstate1;
	map<bitset<288>, int, cmpBitset<288>> n0state;
	spoly.p.clear();
    trivium_flag_poly(cube, state0, pstate0);
    trivium_flag_poly(cube, state1, pstate1);

	cout << divround[0] << " - round" << endl;
	cout << "cube index: ";

	vector<int> cube_index(cube.count());
	int k = 0;
	for (int i = 0; i < M; i++) {
		if (cube[i] == 1) {
			cout << i << " ";
			cube_index[k] = i;
			k++;
		}
	}
	cout << endl;
	vector<map<bitset<288>, int, cmpBitset<288>>> allstatebits(divround.size());

	for (int i = 0; i < target.size(); i++) {
		bitset<288> tmp;
		tmp[target[i]] = 1;
		allstatebits[0][tmp] = 1;
		
	}
	bool lt;
	for (int i = 0; i < divround.size(); i++) {
		map <bitset<288>, int, cmpBitset<288>> tmp;
		tmp = allstatebits[i];
		auto is = tmp.begin();
		while (is != tmp.end()) {
			if ((*is).second % 2 == 1) {
			
			}
			else {
				allstatebits[i].erase((*is).first);
			}
			is++;
		}

		int siz = allstatebits[i].size();
		cout << "************" << divround[i] << " round  " << siz << "************" << endl;
		if (i < divround.size() - 2) {
			lt = 1;
		}
		else
			lt = 0;
		int ct = 0, rt;
		while (allstatebits[i].size() > 0) {
			cout << endl;
			cout << "[" << siz << " , " << ct << "]" << endl;
			ct++;
			auto it = allstatebits[i].begin();
			cout << (*it).second << endl;
			if ((*it).second % 2 == 1) {
				map<bitset<288>, int, cmpBitset<288>> n1state;
				if (i < divround.size() - 1)
					rt = milp_model_alg(divround[i], initRound, divround[i + 1], pstate0, cube, threadNumber, (*it).first, &n1state, lt);
				else
					rt = milp_model_alg(divround[i], initRound, n0, pstate0, cube, threadNumber, (*it).first, &n1state, lt);
				if (rt == 0)
					return(0);
				else if (rt == 2) {
					triviumLast(divround[i], divround[i + 1], threadNumber, (*it).first, allstatebits[i+1]);
				}
				else if (rt == 1 && n1state.size() > 0) {
					if (i < divround.size() - 1) {
						auto at = n1state.begin();
						while (at != n1state.end()) {
							if ((*at).second % 2 == 1) {
								allstatebits[i + 1][(*at).first]++;
							}
							at++;
						}
					}
					else {
						auto at = n1state.begin();
						while (at != n1state.end()) {
							if ((*at).second % 2 == 1) {
								n0state[(*at).first]++;
							}
							at++;
						}
						cout << n0state.size() << endl;
					}
					
				}
			}
			allstatebits[i].erase(it);
		}
	}
	cout << "The size of n0state is " << n0state.size() << endl;
	auto it = n0state.begin();
	while (it != n0state.end()) {
		if ((*it).second % 2 == 1)
			N0_round_model(pstate1, cube, threadNumber, (*it).first, spoly);
		it++;
	}
	cout << "total" <<  dn << " solutions" << endl;
	cout << spoly << endl;
	return 1;

}







