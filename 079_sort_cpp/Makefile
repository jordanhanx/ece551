CCFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
sortLines: sort.o
	g++ -o sortLines $(CCFLAGS) $^

%.o: %.cpp
	g++ -c $(CCFLAGS) $<

clean:
	rm -f *.o  *~ sortLines
