VPATH=src
objects=main.c func.c
output:$(objects)
	gcc -o output -pthread -lrt -include "header/header.h" $^
.PHONY:clean
clean:
	rm -f output
