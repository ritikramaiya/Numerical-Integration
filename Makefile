FLAGS = -g -std=c++17 -Wall -Wextra -pedantic #-stdlib=libc++
MAC = -std=c++17 -stdlib=libc++

EXECUTABLE = integrate
COMMIT = 1

all: integrate

integrate: integrate.o
	g++ integrate.o -o integrate -lpthread

integrate.o: integrate.cpp 
	g++ $(FLAGS) -c integrate.cpp


valgrind:
	valgrind --tool=memcheck --leak-check=yes ./integrate
clean:
	rm -f *.o $(EXECUTABLE)