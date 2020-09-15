#include<stdio.h>
#ifndef BMD_H
#define BMD_H

struct _bmd_envelop {
    char* sender_id;
    char* destination_id;
    char* message_type;
    // TODO: Other fields
    char* reference_id;
    char* message_id;
    char * received_on;
    char * signature;
    char * user_properties;
};

typedef struct _bmd_envelop bmd_envelop;

struct _bmd{
    bmd_envelop envelop;
    char* payload;
};

typedef struct _bmd bmd;


//bmd *parse_bmd_xml(char *);
bmd *process_xml(char *);
int check_if_string_is_guid(const unsigned char *value);
bmd_envelop *extract_envelop(char *bmd_xml);
//payload *extract_payload(char *bmd_xml);

#endif
