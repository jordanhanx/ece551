CXXFLAGS = -std=gnu++98 -Wall -Werror -pedantic -ggdb3
PROGS = cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
PROG_OBJS = $(patsubst %, %.o, $(PROGS))
SRCS = $(wildcard *.cpp)
OBJS = $(filter-out $(PROG_OBJS), $(patsubst %.cpp, %.o, $(SRCS)))


all: $(PROGS)
cyoa-step%: cyoa-step%.o $(OBJS)
	g++ -o $@ $(CXXFLAGS) $^
%.o: %.cpp
	g++ -c $(CXXFLAGS) $<

.SECONDARY:
.PHNOY: clean depend
clean:
	rm -f *~ *.o $(PROGS) *.bak
depend:
	makedepend $(SRCS)

# DO NOT DELETE THIS LINE -- make depend depends on it.

book.o: book.hpp page.hpp choice.hpp key.hpp path.hpp my_str_tools.hpp
choice.o: choice.hpp key.hpp
cyoa-step1.o: book.hpp page.hpp choice.hpp key.hpp path.hpp
cyoa-step2.o: book.hpp page.hpp choice.hpp key.hpp path.hpp reader.hpp
cyoa-step3.o: book.hpp page.hpp choice.hpp key.hpp path.hpp
cyoa-step4.o: book.hpp page.hpp choice.hpp key.hpp path.hpp reader.hpp
key.o: key.hpp
my_str_tools.o: my_str_tools.hpp
page.o: page.hpp choice.hpp key.hpp
path.o: path.hpp key.hpp my_str_tools.hpp
reader.o: reader.hpp book.hpp page.hpp choice.hpp key.hpp path.hpp
reader.o: my_str_tools.hpp
