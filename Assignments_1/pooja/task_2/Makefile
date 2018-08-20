VPATH = source
files = main.c hash_tab_insert.c create_node_function.c hash_tab_function.c display_node.c copy_hashtab_file.c search_content.c modify_string.c
app:$(files)
	gcc -o app -include "header/header.h" -g $^
.PHONY:clean
clean:
	rm -f app
