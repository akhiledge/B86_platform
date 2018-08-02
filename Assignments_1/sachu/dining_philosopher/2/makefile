VPATH = source
files = main.c philosopher_fun.c fork_acquire.c check_for_fork.c fork_release.c 

objects = main.o philosopher_fun.o fork_acquire.o check_for_fork.o fork_release.o

dining_exe : $(objects)
	gcc -o $@ -Wall $^ -pthread

$(objects) : $(files)
	gcc -c $^ -include "source/header/dining_header.h" -Wall

clean:
	rm dining_exe *.o
