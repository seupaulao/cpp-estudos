all: basico.out

basico.out: basico.o
	 gcc -o $@ $<

basico.o: basico.c
	 gcc -c $<
     
clean:
	 rm basico.o basico.out
