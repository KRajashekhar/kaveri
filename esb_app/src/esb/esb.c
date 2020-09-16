#include<stdio.h>
#include "../bmd/email.c"
//#include "esb.h"
#include "../bmd/bmd.h"
#define MAX_SIZE  5000000
#include"../db_access/db_access.h"

/**
 * TODO: This is to be implemented separately.
 */
/*bmd parse_bmd_xml(char* bmd_file_path) {
    bmd b;
    bmd_envelop envl;
    envl.sender_id = "TEST-GUID-1";
    envl.destination_id = "TEST-GUID-2";
    envl.message_type = "TEST-GUID-3";

    b.envelop = envl;
    b.payload = "Some data here";
    return b;
}*/
int is_bmd_valid(bmd b)
{
    int valid = 1; // 1 => vaild, -1 => invalid
    // TODO: Implement the validation logic here
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
    //return valid;
}

int queue_the_request(bmd *b, char *file_path)
{
    int success = 1; // 1 => OK, -1 => Error cases
    /** 
     * TODO: Insert the envelop data into esb_requests table,
     * and implement other logic for enqueueing the request
     * as specified in Theory of Operation.
     */
    // int check=insert_to_esb_request;
    return success;
}

/**
 * This is the main entry point into the ESB. 
 * It will start processing of a BMD received at the HTTP endpoint.
 */
int process_esb_request(char* bmd_file_path) {
    int status = 1; // 1 => OK, -ve => Errors
    printf("Handling the BMD %s\n", bmd_file_path);
    /** TODO: 
     * Perform the steps outlined in the Theory of Operation section of
     * the ESB specs document. Each major step should be implemented in
     * a separate module. Suitable unit tests should be created for all
     * the modules, including this one.
     */
    // Step 1:
    bmd b = parse_bmd_xml(bmd_file_path);

    // Step 2:
    if (is_bmd_valid(b) ==  -1)
    {
        //TODO: Process the error case
        printf("BMD is invalid!\n");
        status = -2;
    }
    else
    {
        // Step 3:
        //status = queue_the_request(b);
    }
    
    return status;
}
