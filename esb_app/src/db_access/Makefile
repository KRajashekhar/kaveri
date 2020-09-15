OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
cflags = gcc -c -g -Wall -Werror -std=gnu11 
out : $(OBJECTS)
	gcc -o out $(OBJECTS)  $(libm)
main.o : main.c db_access.h
	$(cflags) main.c $(libm)
select_transform_config.o : select_transform_config.c db_access.h
	$(cflags) select_transform_config.c $(libm)
select_transport_config.o : select_transport_config.c db_access.h 
	$(cflags) select_transport_config.c $(libm)
select_active_route.o : select_active_route.c db_access.h
	$(cflags) select_active_route.c $(libm)
insert_into_esb_request.o : insert_into_esb_request.c db_access.h
	$(cflags) insert_into_esb_request.c $(libm)
clean:
	rm out $(OBJECTS)