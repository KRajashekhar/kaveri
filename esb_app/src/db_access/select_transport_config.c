#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<mysql.h>


#include"db_access.h"

#define STRING_SIZE 1000


int select_transport_config(int route_id) {

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
    
   //Preparing select string
   
    int return_value;
    char quer[STRING_SIZE];
    return_value = snprintf(quer,STRING_SIZE,"SELECT * \
     FROM transport_config WHERE route_id=%d",route_id);
    char query[return_value+1];
    return_value=snprintf(query,return_value+1,"SELECT *\
     FROM transport_config WHERE route_id=%d",route_id);
    if(mysql_query(conn,query))
    {
        return finish_with_error(conn);
    }
    MYSQL_RES *result = mysql_store_result(conn);
    if(result==NULL)
    {  
        
        return finish_with_error(conn);
    }

    int num_fields=mysql_num_fields(result);
    MYSQL_ROW row;
    row=mysql_fetch_row(result);
    if(row==NULL) {
          
          return INVALID;
    }
    else {
        for(int i=0;i<num_fields;i++){

            if(row[i]==NULL) {
                return INVALID;
            }
        }
    }
    while((row=mysql_fetch_row(result)))
        {
            for(int i=0;i<num_fields;i++)
            {
                if(row[i]==NULL)
                {
                    return INVALID;
                }
            }
        }
    mysql_free_result(result);
    mysql_close(conn);
     
     return VALID;
}