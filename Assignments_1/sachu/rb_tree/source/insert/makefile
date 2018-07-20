VPATH = insert display delete

files = check_parent.c  insert_element.c check_uncle.c  left_rotate_from_gp.c right_rotate_from_gp.c create_node.c  left_rotate_from_parent.c  right_rotate_from_parent.c find_root.c rbt_main.c display_tree.c delete_element.c find_min.c

objects =check_parent.o  insert_element.o check_uncle.o  left_rotate_from_gp.o right_rotate_from_gp.o create_node.o  left_rotate_from_parent.o  right_rotate_from_parent.o find_root.o rbt_main.o display_tree.o delete_element.o find_min.o

rbt_exe : $(objects)
	gcc -o $@ -Wall $^

$(objects) : $(files)
	gcc -c -include "./rbt_header.h" $^ -Wall

clean :
	rm *.o rbt_exe

