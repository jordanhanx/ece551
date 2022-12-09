CPPFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3
circles: main.o circle.o point.o
	g++ -o circles $^
*.o: *.cpp point.h circle.h
	g++ $(CPPFLAGS) -c $<


.PHONY: clean
clean:
	rm -f *.o *~ circles
