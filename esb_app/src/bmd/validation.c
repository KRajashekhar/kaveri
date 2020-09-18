
// @authors Kucharla Rajashekhar and Vinay Prabhakar

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<mysql/mysql.h>
#include<libxml/parser.h>
#include<libxml/tree.h>



#include"bmd.h"
#include"../db_access/db_access.h"
#define MAX_SIZE  5000000


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
    int r_id = get_route_id(envelop.sender_id, envelop.message_type, envelop.destination_id);
    if(r_id == INVALID) {
        fprintf(stderr,"There is no route_id corresponding to bmd file\n");
        return INVALID;
    }
    
    //transform_config_table
    if(select_transform_config(r_id) == INVALID) {

        fprintf(stderr, "Either config_value or config_key or both corresponding to route_id not present in transform_config table \n");
        return INVALID;
    }
    
    //transport_config_table
    if(select_transport_config(r_id)  == INVALID) {
        fprintf(stderr,"Either config_value or config_key or both corressponding to route_id not present in transport_config table \n");
        return INVALID;
    }
    
  return VALID;
}


int main()
{
    bmd b;
    b=parse_bmd_xml("bmd.xml");
   // db_access(b);
    int ans;
    ans =is_bmd_valid(b);
    printf("%d\n",ans);
    //xml2json(b.payload);
}

