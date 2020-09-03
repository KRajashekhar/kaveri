#include<stdio.h>
#include<stdlib.h>

//gcc -Wall -I/usr/include/libxml2 -o main main.c -lxml2 `mysql_config --cflags --libs`


#include "parsing1.h"
#include "db_access1.h"
int main() {
bmd b;

b = parse_bmd_xml("bmd.xml") ;
//printf("%s\n",b.payload);
queue_the_request(b);
return 0;
}
