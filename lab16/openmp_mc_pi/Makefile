CC=gcc
CFLAGS=-Wall

mc_pi: openmp_mc_pi.c
	$(CC) $(CFLAGS) -o openmp_mc_pi.exe openmp_mc_pi.c -lm -fopenmp

clean:
	rm -f *.exe *.txt *.out

