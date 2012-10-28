C++ := g++

all:
	$(C++) -Wall -c molto-allegro.cpp
	ar -cvq libmoltoallegro.a molto-allegro.o
	cp libmoltoallegro.a ../bin/

clean:
	rm -f *.o
	rm -f *.a
