objects = app.c take_spoon.c put_back_spoon.c test_leftnright.c

out : $(objects)
	gcc -o $@ -I "/header.h" $(objects) -pthread

.PHONY :
	clean

clean :
	rm out
