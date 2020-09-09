
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


//checking config_key and config_value from trasform_config table

int check_transform_config_table(int r_id) {


    MYSQL *conn =mysql_init(NULL);
    if(conn==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
       // exit(1);
       return INVALID;
    }
    /*if(mysql_real_connect(conn2,"localhost","root","prabhakars 589b","esb_db",0,NULL,0)==NULL)
    {
        finish_with_error(conn2);
    }*/
    if(mysql_real_connect(conn,"localhost","raja","Kucharla@1","esb_db",0,NULL,0)==NULL)
    {
        return finish_with_error(conn);
    }

    int return_value;
    char quer[MAX_STRING];
    return_value=snprintf(quer,MAX_STRING,"select config_key and config_value from transform_config where route_id=%d",r_id);
    char query[return_value+1];
    return_value=snprintf(query,return_value+1,"select config_key and config_value from transform_config where route_id=%d",r_id);
    // printf("query2:%s\n",query2);
    if(mysql_query(conn,query))
    {
        return finish_with_error(conn);
    }

    MYSQL_RES *result=mysql_store_result(conn);
    if(result==NULL)
    {
        return finish_with_error(conn);
    }
    int num_fields=mysql_num_fields(result);
    MYSQL_ROW row;
    row = mysql_fetch_row(result);
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

int main()
{
	int r_id=1;
	int ans= check_transform_config_table(r_id);
	printf("%d \n",ans);
	return 0;
	}


