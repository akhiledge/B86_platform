VPATH=source 

objects=rbt_app.c insertion.c display.c my_atoi.c create_node.c

rbt_out:$(objects)
	gcc -o $@ -include "source/rbt_header.h" $^

.PHONY : 
	clean

clean :
	rm rbt_out
