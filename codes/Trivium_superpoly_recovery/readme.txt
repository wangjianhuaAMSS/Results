This source code recovers superpolies for Trivium. 

This code is written by C++ with Gurobi API. 

Therefore, to compile and run this code, you need to install Gurobi Optimizer in advance. 

You need to change some options in Makefile according to your Gurobi Optimizer version and your operating system.

If you already complete the above operations, you just run
+++
 make
+++

After compile, if you want to try the superpoly recovery of cube $I_1$ or $I_5$(refer to the paper) for 840-round or 841-round Trivium, you just run
+++
	./a.out -i[1 or 5] -r [840 or 841] -t [option : thread number]
+++

Note that this code does not return the answer quickly, and it depends on the performance of your computer. 

