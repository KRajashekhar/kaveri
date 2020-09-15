#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<mysql.h>


#include"db_access.h"

#define STRING_SIZE 1000


int check_new_request(int id) {

	int INVALID = 0;
        int VALID = 1;

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
    
   //Preparing select string
   
    int return_value;
    char quer[STRING_SIZE];
    return_value = snprintf(quer,STRING_SIZE,"SELECT * FROM\
     esb_request WHERE status = 'avalilable' AND id = %d LIMIT 1",id);
    char query[return_value+1];
    return_value=snprintf(query,return_value+1,"SELECT * FROM \
     esb_request WHERE status = 'available' AND id=%d LIMIT 1",id);
    if(mysql_query(conn,query))
    {
        printf("Failed to connect MySQL Server %s. Error: %s\n", HOST, mysql_error(conn));
    }
    MYSQL_RES *result = mysql_store_result(conn);
    if(result==NULL)
    {  
        
        printf("Failed to connect MySQL Server %s. Error: %s\n", HOST, mysql_error(conn));
    }
    int num_rows = mysql_num_rows(result);
    
    if(num_rows == 0) {
        return INVALID;
    }
    /*
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
    */
    mysql_free_result(result);
    mysql_close(conn);
     
     return VALID;
}
