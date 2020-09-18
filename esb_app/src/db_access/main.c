
// @authors Kucharla Rajashekhar and Vinay Prabhakar

#include<stdio.h>
#include<stdlib.h>


#include "db_access.h"



int main(void) {

    insert_into_esb_request("A9ECAEF2-107A-4452-9553-043B6D25386E","6393F82F-4687-433D-AA23-1966330381FE","CreditReport","INV-PROFILE-889712","A9ECAEF2-107A-4452-9553-043B6D25386E","2020-08-02T05:18:00+0000", "bmd.xml","available","It is available" );
   int route_id = select_active_route("756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport");
   printf("result form route_id is : %d\n",route_id);
   int success = select_transport_config(route_id);
   printf("result form transport is : %d\n",success);
   success = select_transform_config(route_id);
   printf("result from transform is : %d\n",success);
   success = check_new_request(19);
   printf("result from check new_request is : %d\n",success);
   success = change_available_to_taken(19);
   printf("result from change_available_to_taken is : %d\n",success);
     success = change_taken_to_done(19);
   printf("result from change_taken_to_done is : %d\n",success);
   route_id = get_route_id("756E2EAA-1D5B-4BC0-ACC4-4CEB669408DA","6393F82F-4687-433D-AA23-1966330381FE","CreditReport");
   printf("result from get_route_id is : %d\n",route_id);
   char  transform_key[50] = "   ";
   success = get_transform_key(1,transform_key);
   printf("result form get_transform_key is :%d   %s and \n",success,transform_key);
   char transport_key[50] = " ";
   success = get_transform_key(1,transport_key);
   printf("result form get_emailId is :%d   %s and \n",success,transport_key);
   char transport_value[50] = " ";
   success = get_transport_value(1,transport_value);
   printf("result from get_transport_value is : %d   %s ans \n",success,transport_value);
   char Payload_value[] = " shekhar ";
   success = add_payload(Payload_value, 1, transport_key);
   printf("result form add_payload is : %d  %s and",success,transport_key );
    success = change_status_to_error(19);
   printf("result from stutus_to_error is : %d\n",success);
   
   return 0;
} 
