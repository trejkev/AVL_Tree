#MakeFile
#Generates a file to define what the following commands do:
#	*make:	general compilation of the project
#	*make unittest:	compilation of unit tests
#	*make run:	executes primary program
#	*make run_unittest:executes unit tests


#Declaration of Variables

#Compiler
CC = g++

#Compiler flags
CFLAGS = -std=c++14


#Directories where files are located

# Include directory
#IDIR = -I../AVL/include

# SRC directory
#SRCDIR = ../AVL/src

# TEST directory
#TESTDIR = ../test/

#Targets requiered (executables)
OBJECTS1 = main.cpp AVL.cpp avltree_ObtainData.cpp
OBJECTS2 = test-main.cpp AVL.cpp TestFile.cpp

#*List of object to compile all .cpp files
all : $(OBJECTS1)
#	Generation command
	$(CC) $(CFLAGS) $(OBJECTS1) -o Output

unittest: $(OBJECTS2)
	$(CC) $(CFLAGS) $(OBJECTS2) -o Testing

#Execute the output of the compilation generated by make command
run: $(OBJECTS1)
	./Output

run_unittest: $(OBJECTS2)
	./Testing