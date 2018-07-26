VPATH = source object

files = main_hash.c create_database.c hash_index.c create_node.c insert.c update_count.c search_database.c update_database.c save_data.c print_list.c my_atoi.c modify_string.c

objects = main_hash.o create_database.o hash_index.o create_node.o insert.o update_count.o search_database.o update_database.o save_data.o print_list.o my_atoi.o modify_string.o

exe_hash : $(objects)
	gcc -o $@ -Wall $^
	mv *.o object

$(objects) : $(files)
	gcc -c $^ -include "header/hash.h" -Wall

clean :
	rm object/*.o exe_hash
