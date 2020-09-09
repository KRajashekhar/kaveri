#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<mysql.h>
/*#include<libxml/parser.h>
#include<libxml/tree.h>
*/


#include"bmd.h"
#define MAX_STRING 200
#define MAX_SIZE 5242880
#define VALID 1
#define INVALID -1


int get_root_id(char *sender_id, char *message_type, char *destination_id) {
   
    MYSQL *conn =mysql_init(NULL);
    if(conn==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        //exit(1);
        return INVALID;
    }
    /*if(mysql_real_connect(conn,"localhost","root","prabhakars 589b","esb_db",0,NULL,0)==NULL)
    {
        finish_with_error(conn);
    }*/
    if(mysql_real_connect(conn,"localhost","raja","Kucharla@1","esb_db",0,NULL,0)==NULL)
    {
        return finish_with_error(conn);
    }
    
    int return_value;
    char quer[MAX_STRING];
    return_value = snprintf(quer,MAX_STRING,"select route_id from routes where sender='%s' and message_type='%s' and destination='%s'",sender_id,message_type,destination_id);
    char query[return_value+1];
    return_value = snprintf(query,return_value+1,"select route_id from routes where sender='%s' and message_type='%s' and destination='%s'",sender_id,message_type,destination_id);
    if(mysql_query(conn,query))
    {
       return finish_with_error(conn);
    }
    MYSQL_RES  *result=mysql_store_result(conn);
    if(result==NULL)
    {
        return finish_with_error(conn);
    }
    int num_fields=mysql_num_fields(result);
    MYSQL_ROW row;
    unsigned int r_id;
    row = mysql_fetch_row(result);
    if(row==NULL) {
          
          return INVALID;
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
/*
int main()
{
	//using dummy values
	
	char *s1 ='A';
	char *m1='M';
	char *d1='D';
	get_root_id(s1,m1,d1);
	return 0;
	}
	*/
