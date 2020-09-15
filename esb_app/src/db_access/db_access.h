
#ifndef _DB_ACCESS_H
#define _DB_ACCESS_H


#include<stdio.h>
#include<stdlib.h>
#include<mysql/mysql.h>

#define HOST         "localhost"
#define USER         "root"	
#define PASSWD      "prabhakars 589b"
#define DB           "esb_db"
#define PORT         0
#define UNIX_SOCKET  NULL
#define FLAG         CLIENT_MULTI_STATEMENTS


void insert_into_esb_request(char *sender_id, char *dest_id,
char *message_type, char *reference_id, char *message_id,
char *received_on, char *data_location, char *status, char *status_details);

void finish_with_error(MYSQL *con);

int change_available_to_taken(int id);

int change_taken_to_done(int id);

int get_route_id (char *sender, char *destination, char *message_type);
#endif