CC = gcc
FFLAGS = -Wall -fopenmp -lm
LFLAGS = -lgomp
OBJECTS = matrix.o main.o

main.exe:  $(OBJECTS)
	$(CC) $(FFLAGS) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exe output*.txt *.out *.err

