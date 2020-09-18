
# @authors Kucharla Rajashekhar and Vinay Prabhakar

#OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
libc = -lcurl
cflags = gcc -c -g -Wall -Werror -pedantic
VPATH = ../db_access : ../http : ../email
#INCLUDE := ../db_access
out : parsing.o validation.o xmljson.o transform.o transport.o get_route_id.o\
 select_transport_config.o select_transform_config.o\
 get_emailId.o add_payload.o http_get.o email.o
	gcc -o out $^ $(libl) $(libm) $(libc)
main.o : main.c bmd.h	
	$(cflags) main.c
transport.o : transport.c bmd.h db_access.h http.h
	$(cflags) $<
transform.o : transform.c bmd.h db_access.h
	$(cflags) $< 
xmljson.o : xmljson.c bmd.h
	$(cflags) $< $(libl)
validation.o : validation.c bmd.h db_access.h
	$(cflags)  $< 
parsing.o : parsing.c bmd.h
	$(cflags)  $< $(libl) 
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
http_get.o : http_get.c http.h
	$(cflags) $< $(libc)
http_post.o : http_post.c http.h
	$(cflags) $< $(libc)
email.o : email.c email.h
	$(cflags) $< $(libc)

.PHONY : clean
clean:
	rm out parsing.o validation.o xmljson.o transform.o transport.o email.o \
	 get_route_id.o select_transport_config.o select_transform_config.o\
 get_emailId.o add_payload.o http_get.o 



