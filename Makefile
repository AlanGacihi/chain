CC=gcc
CFLAGS=-I.
DEPS = chain.h
OBJ = read.o split.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

chain: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY : clean
clean :
	-rm *.o $(objects)
