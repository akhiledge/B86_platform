.PHONY: rb_tree, clean

VPATH=source

inc=./header/rb_tree.h

obj=./objects/

objects = allocate_memory.o balance.o inorder.o insert.o\
	  left_rotate.o main.o postorder.o preorder.o right_rotate.o\
	  sibling.o user_input.o value_in_node.o


rb_tree : $(objects)
	gcc -o ./exec/rb_tree_'$(shell date)' $^ -include ./header/rb_tree.h
	mv *.o $(obj)

%.o : %.c
	gcc -c $^ -I$(inc)


clean :
	rm -f ./exec/*
