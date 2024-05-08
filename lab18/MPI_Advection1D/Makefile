# $ISUHPC/lectures/lecture23/codes/MPI_Advection1D/Makefile
CC = mpicxx
FFLAGS = -O3 -Wall -std=c++14
LFLAGS =
OBJECTS = vector.o main.o

main.exe:  $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe

%.o: %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) *.exe *.png *.data slurm*
