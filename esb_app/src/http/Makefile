
 # @uthors Kucharla Rajashekhar and Vinay Prabhakar

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))
libl = -I/usr/include/libxml2 -lxml2 
libm = `mysql_config --cflags --libs`
libc = -lcurl
cflags = gcc -c -g -Wall -Werror -pedantic
out : $(OBJECTS)
	gcc -o out $(OBJECTS) $(libc)
http_get.o : http_get.c http.h
	$(cflags) $< $(libc)
http_post.o : http_post.c http.h
	$(cflags) $< $(libc)

.PHONY : clean
clean :
	rm  out $(OBJECTS)