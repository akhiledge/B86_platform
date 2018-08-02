dining : philosopher.o
	gcc  philosopher.o -o dining -pthread

philosopher.o: philosopher.c
	gcc -c $^ -Wall

clean :
	rm *.o dining
