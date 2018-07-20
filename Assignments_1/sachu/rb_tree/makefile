VPATH = source/insert source/display source/delete
files = rbt_main.c insert_element.c create_node.c check_parent.c check_uncle.c left_rotate_from_gp.c right_rotate_from_gp.c left_rotate_from_parent.c right_rotate_from_parent.c display_tree.c find_root.c delete_element.c find_min.c

object = rbt_main.o insert_element.o create_node.o check_parent.o check_uncle.o left_rotate_from_gp.o right_rotate_from_gp.o left_rotate_from_parent.o right_rotate_from_parent.o display_tree.o find_root.o delete_element.o find_min.o

rbt_exe : $(object)
	gcc -o $@ -Wall $^

$(object):$(files)
		gcc -c $^ -include "source/header/rbt_header.h" -Wall

clean : 
		rm rbt_exe *.o
