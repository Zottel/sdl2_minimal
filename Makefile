
all: example

include $(wildcard *.d)
#include $(wildcard lib/*.d)

ECHO :=
CXX := clang++
CXXFLAGS := -std=c++11 \
            --write-dependencies
CXXLDFLAGS := -lSDL2

#%: %.cpp $(wildcard lib/*.cpp) Makefile
%: %.cpp Makefile
	$(ECHO)$(CXX) $(CXXFLAGS) $(filter %.cpp, $^) $(CXXLDFLAGS) -o $@
