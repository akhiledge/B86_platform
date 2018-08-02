.PHONY : tower, clean

VPATH=source
obj=./object/
objects = main.o tower.o

tower : $(objects)
	gcc -o ./exec/tower_'$(shell date)' $^
	mv *.o $(obj)

clean :
	rm -f ./exec/*
