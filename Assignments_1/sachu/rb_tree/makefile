VPATH = source/insert source/display source/delete source/search object

files = rbt_main.c insert_element.c create_node.c check_parent.c check_uncle.c left_rotate_from_gp.c right_rotate_from_gp.c left_rotate_from_parent.c right_rotate_from_parent.c display_tree.c find_root.c delete_element.c find_min.c double_black_fix.c black_height_fix.c search_tree.c my_atoi.c

objects = rbt_main.o insert_element.o create_node.o check_parent.o check_uncle.o left_rotate_from_gp.o right_rotate_from_gp.o left_rotate_from_parent.o right_rotate_from_parent.o display_tree.o find_root.o delete_element.o find_min.o double_black_fix.o black_height_fix.o search_tree.o my_atoi.o

rbt_exe : $(objects)
	gcc -o $@ -Wall $^
		mv *.o object

$(objects):$(files)
		gcc -c $^ -include "source/header/rbt_header.h" -Wall

clean : 
		rm rbt_exe object/*.o
