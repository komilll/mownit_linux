CC=gcc
GSL_HOME=/home/kamil/mownit_linux/gsl
export LD_LIBRARY_PATH=/home/kamil/mownit_linux/gsl/lib

CFLAGS=-I$(GSL_HOME)/include
LDFLAGS=-L$(GSL_HOME)/lib -lgsl -lgslcblas -lm 

all: aproksymacja

aproksymacja: aproksymacja.o
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o
