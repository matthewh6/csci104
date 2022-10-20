CXX := g++
CXXFLAGS := -g -Wall --std=c++11
GTESTCFLAGS := -DGTEST_HAS_PTHREAD=1  
GTESTLIBS := -lgtest -lpthread
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: heap_tests

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

heap_tests:
	$(CXX) $(CXXFLAGS) $(GTESTCFLAGS) heap_tests.cpp random_generator.cpp -o heap_tests $(GTESTLIBS)

test: heap_tests
	./heap_tests
	
valgrind: heap_tests
	$(VALGRIND) ./heap_tests

clean:
	rm -f *.o heap_tests

.PHONY: clean heap_tests