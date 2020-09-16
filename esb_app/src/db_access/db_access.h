
#ifndef _DB_ACCESS_H
#define _DB_ACCESS_H


#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

#define HOST         "localhost"
#define USER         "raja"	
#define PASSWD       "Kucharla@1"
#define DB           "esb_db"
#define PORT         0
#define UNIX_SOCKET  NULL
#define FLAG         CLIENT_MULTI_STATEMENTS

#define VALID 1
#define INVALID -1


int insert_into_esb_request(char *sender_id, char *dest_id,
char *message_type, char *reference_id, char *message_id,
char *received_on, char *data_location, char *status, char *status_details);

int finish_with_error(MYSQL *con);

int select_active_route (char *sender, char *destination, char *message_type) ;

int select_transport_config(int route_id);

int select_transform_config(int route_id);

int check_new_request(int id);

int change_available_to_taken(int id);

int change_taken_to_done(int id);

int get_route_id (char *sender, char *destination, char *message_type);

int get_transform_key(int route_id, char *transform_key);

int get_emailId(int route_id, char *transport_key);

int get_transport_value(int route_id, char *transport_value);

int add_payload(char Payload_value[], int route_id, char *transport_key);

#endif
