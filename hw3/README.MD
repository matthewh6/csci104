## HW 3

 - Name: Matthew Hong
 - Email: hongmm@usc.edu

### Programming Problem Notes

Compiling the Code:
Enter docker container (ch start csci104 -> ch shell csci104) or use Codio and navigate to hw3/
llrec-test
(1) Run make to compile and link all files for the recurisve linked list problems

(2) Enter ./llrec-test llrec-test<n>.in in your terminal to pass in inputs and test the function calls

(3) Run make valgrind to check for memory loss/leaks

stack.h
(1) Enter g++ -g -Wall -std=c++11 -c stack.h stack-test.cpp in your terminal to create a stack-test.o object

(2) Enter g++ -g -Wall -std=c++11 -o stack-test stack-test.o to create the executable stack-test

(3) Run the test by entering ./stack-test in your terminal

(4) Enter `valgrind --tool=memcheck --leak-check=yes ./stack-test1 to check for memory loss/leaks

heap.h
to compile code
(1) make

to check that heap.h passes all test cases
(2) make test

Design Choices/Notes:
used a vector as the container for the heap due to its dynamic sizing capabilities and push_back efficiency
used 0-based indexing to simplify initialization

Navigate to hw3/logicsim by entering cd logicsim
(1) Run make to compile and link all files for the logicsim visualizations

(2) Enter ./logicsim <input>.txt > my_<input>.uml in the terminal to generate a UML file based on input file's events

(3) Enter java -jar plantuml.jar my_<input>.uml to generate a PNG image of the command gates under the name my_<input>.png

: single_and, single_or, single_not, exclusive_or

executing logisim on exclusive_or.txt,

(1) make

(2) ./logicsim exclusive_or.txt > my_exc_or.uml

(3) java -jar plantuml.jar my_exc.uml
