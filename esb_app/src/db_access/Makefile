OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
cflags = gcc -c -g -Wall -Werror -std=gnu11 
out : $(OBJECTS)
	gcc -o out $(OBJECTS)  $(libm)
main.o : main.c db_access.h
	$(cflags) main.c $(libm)
status_to_error.o : status_to_error.c db_access.h
	$(cflags) $< $(libm)
add_payload.o : add_payload.c db_access.h
	$(cflags) $< $(libm)
get_transport_value.o : get_transport_value.c db_access.h
	$(cflags) $< $(libm)
get_emailId.o : get_emailId.c db_access.h
	$(cflags) $< $(libm)
get_transform_key.o :get_transform_key.c db_access.h
	$(cflags) $< $(libm)
get_route_id.o  : get_route_id.c db_access.h
	$(cflags) $< $(libm)
taken_to_done.o : taken_to_done.c db_access.h
	$(cflags) $< $(libm)
available_to_taken.o : available_to_taken.c db_access.h
	$(cflags) $< $(libm);
check_new_request.o : check_new_request.c db_access.h
	$(cflags) $< $(libm)
select_transform_config.o : select_transform_config.c db_access.h
	$(cflags) $< $(libm)
select_transport_config.o : select_transport_config.c db_access.h 
	$(cflags) $< $(libm)
select_active_route.o : select_active_route.c db_access.h
	$(cflags) $< $(libm)
insert_into_esb_request.o : insert_into_esb_request.c db_access.h
	$(cflags) $< $(libm)


clean:
	rm out $(OBJECTS)