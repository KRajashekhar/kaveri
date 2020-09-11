#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<mysql/mysql.h>
#include<libxml/parser.h>
#include<libxml/tree.h>



#include"bmd.h"
#define MAX_STRING 200
#define MAX_SIZE 5242880
#define VALID 1
#define INVALID -1


int finish_with_error(MYSQL *conn)
{
    fprintf(stderr,"%s\n",mysql_error(conn));
    mysql_close(conn);
    return INVALID;
}

int is_bmd_complete(bmd b) {
   bmd_envelop envelop = b.envelop;

   // checking message_id 
   if(envelop.message_id == NULL) {

       fprintf(stderr,"message_id not present\n");
       return INVALID;
   }

   // message_type

   if(envelop.message_type == NULL) {
        fprintf(stderr,"message_type is not present\n");
        return INVALID;
   }

    //sender_id
    if(envelop.sender_id == NULL) {
        fprintf(stderr,"sender_id is not present\n");
        return INVALID;
    }

    //destination_id
    if(envelop.destination_id == NULL) {
        fprintf(stderr,"destination_id is not present\n");
        return INVALID;
    }

    //received_on
    if(envelop.received_on == NULL) {
        fprintf(stderr,"received_on is not present\n");
        return INVALID;
    }

    //signature
    if(envelop.signature == NULL) {
        fprintf(stderr, "signature is not present\n");
        return INVALID;
    }

    //reference_id
    if(envelop.reference_id == NULL) {
        fprintf(stderr, "reference_id is not present\n");
        return INVALID;
    }

    //user_properties
    if(envelop.user_properties == NULL) {
        fprintf(stderr, "user_properties is not present\n");
        return INVALID;
    }

    //payload
    if(b.payload == NULL) {
        fprintf(stderr, "payload is not present\n");
        return INVALID;
    }


    return VALID;
   
   
}


// finding the root_id
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


// checking config_value and config_key from transport_config table;

int check_transport_config_table(int r_id) {
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
    return_value = snprintf(quer,MAX_STRING,"select config_key and config_value from transport_config where route_id=%d",r_id);
    char query[return_value+1];
    return_value=snprintf(query,return_value+1,"select config_key and config_value from transport_config where route_id=%d",r_id);
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




int is_bmd_valid(bmd b)
{
     // 1 => VALID, -1 => INVALID
      bmd_envelop envelop = b.envelop;
    

    // checking whether bmd is complete or not
    if(is_bmd_complete(b) == INVALID)
    {
        fprintf(stderr,"BMD is incomplete\n");
        return INVALID;
    }  

    // checking the size of the payload
    size_t size = strlen(b.payload); 
    size = size+1;
    if(size > MAX_SIZE ) {
      fprintf(stderr, "Payload size is greater than 5MB\n");
      return INVALID;

    }
    
    //route_id
    int r_id = get_root_id(envelop.sender_id, envelop.message_type, envelop.destination_id);
    if(r_id == INVALID) {
        fprintf(stderr,"There is no route_id corresponding to bmd file\n");
        return INVALID;
    }
    
    //transform_config_table
    if(check_transform_config_table(r_id) == INVALID) {

        fprintf(stderr, "Either config_value or config_key or both corresponding to route_id not present in transform_config table \n");
        return INVALID;
    }
    
    //transport_config_table
    if(check_transport_config_table(r_id)  == INVALID) {
        fprintf(stderr,"Either config_value or config_key or both corressponding to route_id not present in transport_config table \n");
        return INVALID;
    }
    
  return VALID;
}

/*int main()
{
    bmd b;
    b=parse_bmd_xml("bmd.xml");
   // db_access(b);
    int ans;
    ans =is_bmd_valid(b);
    printf("%d\n",ans);
    xml2json(b.payload);
}
*/