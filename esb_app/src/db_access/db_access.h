
#ifndef _DB_ACCESS_H
#define _DB_ACCESS_H


#include<stdio.h>
#include<stdlib.h>



void insert_into_esb_request(char *sender_id, char *dest_id,
char *message_type, char *reference_id, char *message_id,
char *received_on, char *data_location, char *status, char *status_details);

void finish_with_error(MYSQL *con);

#endif