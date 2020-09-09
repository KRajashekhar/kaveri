#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <stdio.h>
#include <mysql/mysql.h>

#include "../Testing/bmd.h"

#include "../esb/esb.h"

#include "../db_access/databse.c"


#define HOST "localhost"   //hostname
#define USER  "root"       //username
#define PASS    ""         //blank password this user
#define DB_NAME "esb_db"   //name of the database
#define PORT  3306         //port number
#define UNIX_SOCKET NULL   //unix socket
#define FLAG 0             //last parameter to mysql_real_connect

int insert_in_esb_request(char *sender_id,char *dest_id,
char *message_type,char *reference_id,char *message_id, 
char *data_location, char *status,char *status_details,char *received_on);

void finish_with_error(MYSQL *con) ;
int get_root_id.c(char *sender,char* destination,char *message_type);
int check_transform.c(int route_id);
int check_transport.c(int route_id);


#endif
