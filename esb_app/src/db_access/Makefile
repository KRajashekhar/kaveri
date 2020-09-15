OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
cflags = gcc -c -g -Wall -Werror -std=gnu11 
out : $(OBJECTS)
	gcc -o out $(OBJECTS)  $(libm)
main.o : main.c db_access.h
	$(cflags) main.c $(libm)
get_route_id.o  : get_route_id.c db_access.h
	$(cflags) get_route_id.c $(libm)
taken_to_done.o : taken_to_done.c db_access.h
	$(cflags) taken_to_done.c $(libm)
available_to_taken.o : available_to_taken.c db_access.h
	$(cflags) available_to_taken.c $(libm);
check_new_request.o : check_new_request.c db_access.h
	$(cflags) check_new_request.c $(libm)
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