CFLAGS = -Wall -Werror -pedantic -std=gnu99
test-subseq: test-subseq.o maxSeq.o
	gcc -o test-subseq $^
%.o: %.c
	gcc -c ${CFLAGS} $<
.PHONY: clean
clean:
	rm -f *~ *.o test-subseq
