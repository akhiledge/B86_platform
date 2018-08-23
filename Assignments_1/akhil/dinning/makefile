.PHONY : dinning, clean

VPATH=source
obj=./object/
objects = main.o eating.o thinking.o internal_routinues.o regular_phil.o

dinning : $(objects)
	clang-3.5 -o ./exec/dinning_'$(shell date)' -pthread $^
	mv *.o $(obj)

clean :
	rm -f ./exec/*
