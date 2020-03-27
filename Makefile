TEST = test.o
BENCHMARK = benchmark.o
DEFINES = NONE # PTREE for tree printing
CXX = c++
TESTSRC = src/test.cpp
BENCHSRC = src/benchmark.cpp
CXXFLAGS = -std=c++17 -Wall -Wextra
IFLAGS = -I include

all: $(TEST) $(BENCHMARK)

$(TEST): $(TESTSRC)
	$(CXX) -g $< -o $(TEST) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)

$(BENCHMARK): $(BENCHSRC)
	$(CXX) -g $< -o $(BENCHMARK) $(CXXFLAGS) $(IFLAGS) $(DFLAGS)
clean: 
	@rm -fr *.o docs/html docs/latex

.PHONY: all docs clean
