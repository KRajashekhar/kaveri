
// @authors Kucharla Rajashekhar and Vinay Prabhakar

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<mysql.h>


#include"db_access.h"

#define STRING_SIZE 1000


int get_transform_key(int route_id, char *transform_key){

MYSQL *conn =mysql_init(NULL);
    if(conn==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        //exit(1);
        return INVALID;
    }
    if(mysql_real_connect(conn, HOST, USER, PASSWD, DB, PORT, UNIX_SOCKET, FLAG)==NULL)
    {
        return finish_with_error(conn);
    }
    
    int return_value;
    char quer[STRING_SIZE];

    //Prepareing select statement

    return_value = snprintf(quer,STRING_SIZE,"SELECT config_key FROM \
     transform_config  WHERE route_id = %d ",route_id);
     
    char query[return_value+1];
    return_value = snprintf(query,return_value+1, "SELECT config_key FROM \
     transform_config  WHERE route_id = %d ",route_id);
     
    if(mysql_query(conn,query))
    {
       return finish_with_error(conn);
    }

    //storing the result from select query in result

    MYSQL_RES  *result=mysql_store_result(conn);
    if(result==NULL)
    {
       return finish_with_error(conn);
    }

    // Total no.of fiels in the result

    int num_fields=mysql_num_fields(result);
    MYSQL_ROW row;
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
                strcpy(transform_key, row[0]);
             
        }
    }
   
    mysql_free_result(result);
    mysql_close(conn);
    return VALID;

}