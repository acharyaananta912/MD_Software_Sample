CC=mpicc
FFLAGS=-O2 -Wall


mc_pi: mpi_mc_pi.c
	$(CC) $(FFLAGS) -o main mpi_mc_pi.c -lm 

clean:
	rm -f main *.txt *.out

