all:		sequencial openmp

sequencial:	sequencial.c
		@gcc -o sequencial sequencial.c -lcrypt

openmp:		openmp.c
		@gcc -o openmp openmp.c -lcrypt -fopenmp

clean:
		@rm -f sequencial openmp
