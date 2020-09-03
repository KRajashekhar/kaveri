#include "db_access1.h"
#include "parser1.h"


void finish_with_error(MYSQL *conn)
{
    fprintf(stderr,"%s\n",mysql_error(conn));
    mysql_close(conn);
    exit(1);
}

int is_bmd_valid(bmd b)
{
 int valid = 1; // 1 => vaild, -1 => invalid
    // TODO: Implement the validation logic here
      bmd_envelop envl;
     if(envl.message_id==NULL || envl.message_type==NULL || envl.sender_id==NULL || envl.destination_id==NULL || envl.received_on==NULL || envl.signature==NULL || envl.reference_id==NULL || envl.user_properties==NULL)
    {
        valid=-2;
    }

    MYSQL *conn =mysql_init(NULL);
    if(conn==NULL)
    {
        fprintf(stderr,"mysql_init() failed\n")
        exit(1);
    }
    if(mysql_real_connect(conn,"localhost","root","prabhakars 589b","esb_db",0,NULL,0)==NULL)
    {
        finish_with_error(conn);
    }
    if(mysql_query(conn,"select route_id from routes where sender==envl.sender_id"))
    {
        finish_with_error(conn);
    }
    MYSQL_RES   *result=mysql_store_result(conn);
    if(result==NULL)
    {
        finish_with_error(conn);
    }
    int num_fields=mysql_num_fields(result);
    MYSQL_ROW row;
    while((row=mysql_fetch_row(result)))
    {
        for(int i=0;i<num_fileds;i++)
        {
            if(row[i]==NULL)
            {
                valid=-2;
            }
            break;
        }
    }
    mysql_free_result(result);
    mysql_close(conn);

  

   
    
    return valid;
}

int main()
{
    printf("%d \n",valid);
}