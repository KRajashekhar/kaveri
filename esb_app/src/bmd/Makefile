OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
cflags = gcc -c -g -Wall -Werror -std=c99 
VPATH = bmd:../db_access
INCLUDE := ../db_access
out :  parsing.o validation.o get_route_id.o
	gcc -o $^ $(libl) $(libm)
#main.o : main.c bmd.h	\
	$(cflags) main.c\
xmljson.o : xmljson.c bmd.h\
	$(cflags) xmljson.c
validation.o : validation.c bmd.h db_access.h
	$(cflags) -I$(INCLUDE) validation.c  $(libm) 
parsing.o : parsing.c bmd.h
	$(cflags) -I$(INCLUDE) parsing.c $(libl) 
get_route_id.o : get_route_id.c db_access.h
	$(cflags) -I$(INCLUDE) get_route_id.c $(libm)

.PHONEY : clean
clean:
	rm out $(OBJECTS)






