#OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
path = ../db_access
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
cflags = gcc -I db_access -c -g -Wall -Werror -std=c99 
path = ../db_access
out : validation.o parsing.o
	gcc -o out validation.o parsing.o $(libl) $(libm)
#main.o : main.c bmd.h	\
	$(cflags) main.c\
xmljson.o : xmljson.c bmd.h\
	$(cflags) xmljson.c
validation.o : validation.c ../db_access/get_route_id.c  bmd.h ../db_access/db_access.h 
	$(cflags) validation.c ../db_access/get_route_id.c $(libm) 
parsing.o : parsing.c bmd.h
	$(cflags) parsing.c $(libl) 

clean:
	rm out $(OBJECTS)






