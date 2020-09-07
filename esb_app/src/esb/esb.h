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


bmd parse_bmd_xml(char * bmd_file_path) ;
//void finish_with_error(MYSQL *con);
void db_access(bmd b);
int is_bmd_valid(bmd b);
void xml2json(char *Payload);
int select_active_route(const unsigned char *Sender,const unsigned char *Destination,const unsigned char *MessageType);
int select_transport_config(int route_id);
int select_transform_config(int route_id);




#endif
