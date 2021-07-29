PLATFORM = mac64
CC       = gcc
CPP      = g++
CARGS    = -m64 -g -arch x86_64 -std=c++17

deps = $(shell find ./ -name "*.h")
src = $(shell find ./ -name "*.c")
srcpp = $(shell find ./ -name "*.cpp")
obj = $(src:%.c=%.o) 
objcpp = $(src:%.cpp=%.o)

out = a.out

$(out): $(srcpp) $(deps)
	$(CPP) $(CARGS) -o $(out) $(srcpp) 


