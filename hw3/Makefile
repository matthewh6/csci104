CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test

#-----------------------------------------------------
# ADD target(s) to build your llrec-test executable
#-----------------------------------------------------

llrec-test: llrec-test.cpp llrec.o
	$(CXX) $(CXXFLAGS) -o $@ llrec.o llrec-test.cpp

llrec.o: llrec.h llrec.cpp 
	$(CXX) $(CXXFLAGS) -o $@ -c llrec.cpp

clean:
	rm -f *.o rh llrec-test *~

.PHONY: clean 