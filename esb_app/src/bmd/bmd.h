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
int is_bmd_valid(bmd b);
void xml2json(char Pay[],char Sender[]);
int get_filesize(char filename[]);
char *get_filecontents (char filename[]);
char* xmltojson(char Pay[]);
int send_mail(char *to,char *file_path);
int check_transform(char type[], int route_id, char* transport_key, char* transport_value, char* SENDER);
void HTTP_Json_transform(int route_id, char* transport_key, char *SENDER);
int Apply_tranport_service(char URL[], char transport_service[]);

//bmd *parse_bmd_xml(char *);
//bmd *process_xml(char *);
//int check_if_string_is_guid(const unsigned char *value);
//bmd_envelop *extract_envelop(char *bmd_xml);
//payload *extract_payload(char *bmd_xml);

#endif
