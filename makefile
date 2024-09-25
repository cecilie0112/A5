WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c99 -g $(WARNING) $(ERROR) 

TESTFALGS = 

SRCS = a5.c
OBJS = $(SRCS:%.c=%.o)

a5: $(OBJS) 
	$(GCC) $(TESTFALGS) $(OBJS) -o a5 -lm

.c.o: 
	$(GCC) $(TESTFALGS) -c $*.c 

test: a5

memory: a5
	valgrind --tool=memcheck ./a5

clean: # remove all machine generated files
	rm -f a5 *.o output? *~