
// @authors Kucharla Rajashekhar and Vinay Prabhakar

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<mysql.h>


#include"db_access.h"

#define STRING_SIZE 1000


int get_route_id (char *sender, char *destination, char *message_type) {
   

    MYSQL *conn =mysql_init(NULL);
    if(conn==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        //exit(1);
        return INVALID;
    }
    if(mysql_real_connect(conn, HOST, USER, PASSWD, DB, PORT, UNIX_SOCKET, FLAG)==NULL)
    {
        printf("Failed to connect MySQL Server %s. Error: %s\n", HOST, mysql_error(conn));
    }
    
    int return_value;
    char quer[STRING_SIZE];

    //Prepareing select statement

    return_value = snprintf(quer,STRING_SIZE,"SELECT route_id FROM routes WHERE sender='%s'\
     AND destination='%s' AND message_type='%s' ",sender, destination, message_type);
    char query[return_value+1];
    return_value = snprintf(query,return_value+1,"SELECT route_id FROM routes WHERE sender='%s' \
     AND destination='%s' AND message_type='%s'  ",sender, destination, message_type);
    if(mysql_query(conn,query))
    {
       printf("Failed to connect MySQL Server %s. Error: %s\n", HOST, mysql_error(conn));
    }

    //storing the result from select query in result

    MYSQL_RES  *result=mysql_store_result(conn);
    if(result==NULL)
    {
      printf("Failed to connect MySQL Server %s. Error: %s\n", HOST, mysql_error(conn));
    }

    // Total no.of fiels in the result

    int num_fields=mysql_num_fields(result);
    MYSQL_ROW row;
    unsigned int r_id;
    row = mysql_fetch_row(result);
    if(row==NULL) {
          return INVALID;
          printf("row\n");
    }
    else {
        for(int i=0;i<num_fields;i++) {
                if(row[i]==NULL) {
                return INVALID;
                 }
             r_id = atoi(row[i]);
        }
    }
   
    mysql_free_result(result);
    mysql_close(conn);
    return r_id;

}
