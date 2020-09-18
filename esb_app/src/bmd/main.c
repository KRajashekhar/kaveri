
#include<stdio.h>
#include<stdlib.h>
//gcc -Wall -I/usr/include/libxml2 -o main main.c -lxml2 `mysql_config --cflags --libs`
#include "bmd.h"

int main(void) {
bmd b;
b = parse_bmd_xml("bmd.xml") ;
printf("%s\n",b.payload);
//db_access(b);
//int *ans = is_bmd_valid(b);
//printf("%d",&ans);
//xml2json(b.payload);
return 0;
}

