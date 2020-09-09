OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
cflags = gcc -c -g -Wall -Werror -std=c99 
out : $(OBJECTS)
	gcc -o out $(OBJECTS) $(libl) $(libm)
main.o : main.c bmd.h	
	$(cflags) main.c
xmljson.o : xmljson.c bmd.h
	$(cflags) xmljson.c
validation.o : validation.c bmd.h
	$(cflags) validation.c  $(libm)
db_access.o : db_access.c bmd.h 
	$(cflags) db_access.c $(libm) 
parsing.o : parsing.c bmd.h
	$(cflags) parsing.c $(libl) 

clean:
	rm -f out $(OBJECTS)






