PLATFORM = mac64
HOME    = Library/gurobi911/mac64
INC      = -I/$(HOME)/include/
CC       = gcc
CPP      = g++
CARGS    = -m64 -g -arch x86_64 -std=c++17
CLIB     = -L/$(HOME)/lib -lgurobi91
CPPLIB   = -L/$(HOME)/lib -lgurobi_c++ -lgurobi91

deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.c")
srcpp = $(shell find ./ -name "*.cpp")
obj = $(src:%.c=%.o) 
objcpp = $(src:%.cpp=%.o)

out = a.out

$(out): $(srcpp) $(deps)
	$(CPP) $(CARGS) -o $(out) $(srcpp) $(INC) $(CPPLIB) -lm


