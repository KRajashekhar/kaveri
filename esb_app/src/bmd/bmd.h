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

/*
bmd_envelop*  extract_envelop(char * filepath);
bmd* parse_bmd_xml(char *bmd_xml_file);
char * extract_payload(char * filepath);
char * xml2json(bmd *bmd_file);
int is_bmd_valid(bmd *bmd_file);
long int find_size(char *);
*/

bmd parse_bmd_xml(char * bmd_file_path) ;
void db_access(bmd b);
int is_bmd_complete(bmd b);
int get_root_id(char *sender_id, char *message_type, char *destination_id) ;
int check_transport_config_table(int r_id);
int check_transform_config_table(int r_id);
int is_bmd_valid(bmd b);
void xml2json(char *Payload);

#endif
