OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
cflags = gcc -c -g -Wall -Werror -std=gnu11 
out : $(OBJECTS)
	gcc -o out $(OBJECTS) $(libl) $(libm)
insert_into_esb_request.o : insert_into_esb_request.c
	$(cflags) insert_into_esb_request.c $(libm)
clean:
	rm out $(OBJECTS)