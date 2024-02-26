CC = gcc
FFLAGS = -O3
LFLAGS =
OBJECTS = main.o fraction_add.o fraction_subtract.o fraction_multiply.o fraction_divide.o \
	  get_prime_factors.o \
	  fraction_reduce.o \
	  make_proper_fraction.o
.PHONY: clean help

output.txt: main.exe
	./main.exe > output.txt

main.exe: $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe -lm

%.o: %.c
	$(CC) $(FFLAGS) -c $< 

clean:
	rm -f $(OBJECTS) main.exe output.txt

help:
	@echo "Valid targets:"
	@echo " main.exe"
	@echo " main.o"
	@echo " fraction_add.o"
	@echo " fraction_subtract.o"
	@echo " fraction_multiply.o"
	@echo " fraction_divide.o"
	@echo " get_prime_factors.o"
	@echo " fraction_reduce.o"
	@echo " make_proper_fraction.o"
	@echo " clean: removes *.o, *.txt, and *.exe files"
