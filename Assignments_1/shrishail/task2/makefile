VPATH= src
objects= main.c create.c  print.c getindex.c insert.c display.c

output:$(objects)
	gcc -o output -include "header/header.h" $^
.PHONY:clean
clean:
	rm -f output

