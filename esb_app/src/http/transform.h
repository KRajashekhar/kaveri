#include<stdio.h>
#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../bmd/bmd.h"

typedef struct transform_config{
	char *key;
	char *value;
	}
	transform_t;
	
char * payload_to_json(bmd *bmd_file);

char * payload_to_xml(bmd *bmd_file);

#endif
