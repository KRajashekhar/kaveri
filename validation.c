#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include "parsing.h"
#include "db_access.h"
#define MAX_STRING 200


/*void finish_with_error(MYSQL *conn)
{
    fprintf(stderr,"%s\n",mysql_error(conn));
    mysql_close(conn);
    exit(1);
}*/

int is_bmd_valid(bmd b)
{
 int valid = 1; // 1 => vaild, -1 => invalid
    // TODO: Implement the validation logic here
      bmd_envelop envl = b.envelop;

     if(envl.message_id==NULL || envl.message_type==NULL || envl.sender_id==NULL || envl.destination_id==NULL || envl.received_on==NULL || envl.signature==NULL || envl.reference_id==NULL || envl.user_properties==NULL)
    {
        valid=-1;
    }

    MYSQL *conn =mysql_init(NULL);
    if(conn==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        exit(1);
    }
    if(mysql_real_connect(conn,"localhost","raja","Kucharla@1","esb_db",0,NULL,0)==NULL)
    {
        finish_with_error(conn);
    }
     
     int return_value;
     char quer[MAX_STRING];
     return_value = snprintf(quer,MAX_STRING,"select route_id from routes where sender='%s' and message_type='%s' and destination='%s'",envl.sender_id,envl.message_type,envl.destination_id);
    char query[return_value+1];
    return_value = snprintf(query,return_value+1,"select route_id from routes where sender='%s' and message_type='%s' and destination='%s'",envl.sender_id,envl.message_type,envl.destination_id);
    if(mysql_query(conn,query))
    {
        finish_with_error(conn);
    }
    MYSQL_RES  *result=mysql_store_result(conn);
    unsigned int r_id;
    if(result==NULL)
    {
        finish_with_error(conn);
    }
    int num_fields=mysql_num_fields(result);
    MYSQL_ROW row;
    while((row=mysql_fetch_row(result)))
    {
        for(int i=0;i<num_fields;i++)
        {
           
            if(row[i]==NULL)
            {
                valid=-1;
            }
             r_id=(atoi)(row[i]);
             //printf("%d\n",r_id);
            break;
        }
    }
    mysql_free_result(result);
    mysql_close(conn);
    
     MYSQL *conn1 =mysql_init(NULL);
    if(conn1==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        exit(1);
    }
    if(mysql_real_connect(conn1,"localhost","raja","Kucharla@1","esb_db",0,NULL,0)==NULL)
    {
        finish_with_error(conn1);
    }
    int return_value_1;
    char quer1[MAX_STRING];
    return_value_1 = snprintf(quer1,MAX_STRING,"select config_key and config_value from transport_config where route_id=%d",r_id);
    char query1[return_value_1+1];
    return_value_1=snprintf(query1,return_value_1+1,"select config_key and config_value from transport_config where route_id=%d",r_id);
    // printf("query1:%s\n",query1);
    if(mysql_query(conn1,query1))
    {
        finish_with_error(conn1);
    }
    MYSQL_RES *result_1 = mysql_store_result(conn1);
    if(result_1==NULL)
    {  
        
        finish_with_error(conn1);
    }
      //  printf("result_1\n");
    int num_fields_1=mysql_num_fields(result_1);
    MYSQL_ROW row_1;
    row_1=mysql_fetch_row(result_1);
    if(row_1==NULL) {
          
          valid = -1;
    }
    else {
        for(int i=0;i<num_fields_1;i++){

            if(row_1[i]==NULL) {
                valid = -1;
            }
        }
    }
    while((row_1=mysql_fetch_row(result_1)))
        {
            for(int i=0;i<num_fields_1;i++)
            {
                if(row_1[i]==NULL)
                {
                    valid=-1;
                }
        break;
            }
        }
    mysql_free_result(result_1);
    mysql_close(conn1);
    
     MYSQL *conn2 =mysql_init(NULL);
    if(conn2==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n");
        exit(1);
    }
    if(mysql_real_connect(conn2,"localhost","raja","Kucharla@1","esb_db",0,NULL,0)==NULL)
    {
        finish_with_error(conn2);
    }

    int return_value_2;
    char quer2[MAX_STRING];
    return_value_2=snprintf(quer2,MAX_STRING,"select config_key and config_value from transform_config where route_id=%d",r_id);
    char query2[return_value_2+1];
    return_value_2=snprintf(query2,return_value_2+1,"select config_key and config_value from transform_config where route_id=%d",r_id);
    // printf("query2:%s\n",query2);
    if(mysql_query(conn2,query2))
    {
        finish_with_error(conn2);
    }

    MYSQL_RES *result_2=mysql_store_result(conn2);
    if(result_2==NULL)
    {
        finish_with_error(conn2);
    }
    int num_fields_2=mysql_num_fields(result_2);
    MYSQL_ROW row_2;
    row_2 = mysql_fetch_row(result_2);
    if(row_2==NULL) {
          
          valid = -1;
    }
    else {
        for(int i=0;i<num_fields_2;i++){

            if(row_2[i]==NULL) {
                valid = -1;
            }
        }
    }
    
    while((row_2=mysql_fetch_row(result_2)))
    {
        for(int i=0;i<num_fields_2;i++)
        {
            if(row_2[i]==NULL)
            {
                valid=-1;
            }
            break;
        }
    }
    mysql_free_result(result_2);
    mysql_close(conn2);
    
  return valid;
}

int main()
{
    bmd b;
    b=parse_bmd_xml("bmd.xml");
    int ans;
    ans =is_bmd_valid(b);
    printf("%d\n",ans);
}

