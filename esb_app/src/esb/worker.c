#include <stdio.h>
#include <unistd.h>
#include "esb.h"
#include "../bmd/bmd.h"
#include<mysql/mysql.h>
#include<string.h>
#include "../bmd/db.h"
#

int fetch_new_request_from_db(int id)
{
    /** 
     * TODO: query the DB for this, and populate the 
     * request pointer with the requests.
     */
     printf("Checking for new requests in  esb_requests table");
     if(check_new_request(id)>=1)
     
     {
     	printf("\nFound a new request");
    
    	return 1;
     }
     else
     {
     	printf("\n no new request found");
     	return 0;
     	}
     	
    
     // 1 => OK, 0 => Failed
}

/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requets(void *vargp)
{
    // Step 1: Open a DB connection
    
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    conn=mysql_init(NULL);
    
    if(!mysql_real_connect(conn,server,user,password,database ,0,NULL,0))
    {
    	printf("Failed to connect ot MYSQL server");
    	}
    	
    int i = 0;
    while (i < 99)
    {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
         
         int ID;
         char SENDER[50];
         char DEST[50];
         char MTYPE[50];
         //checking the rows with status available
         
         mysql_query(conn,"select id,sender_id,dest_id,message_type from esb_request where status ='availabale' order by id");
         res=mysql_store_result(conn);
         int fields=mysql_num_fields(res);
         printf("Entries in the table esb_request with status =available \n");
         while(row=mysql_fetch_result(res))
         {
         	for(int i=0;i<4;i++)
         	{
         		printf("%s ",row[i]?row[i]:"NULL");
         		switch(i){
         			case 0:
         				ID=atoi(row[i]);
         				break;
         			case 1:
         				strcpy(SENDER,row[i]);
         				break;
         			case 2:
         				strcpy(DEST,row[i]);
         			case 3:
         				strcpy(MTYPE,row[i]);
         				break;
         				};
         	}
         	printf("\n");
         }
         mysql_free_result(res);	
        bmd *req;
        /**
         * Step 3:
         */
        if (fetch_new_request_from_db(ID))
        {
            /**
              * Found a new request, so we will now process it.
              * See the ESB specs to find out what needs to be done
              * in this step. Basically, you will be doing:
              * 1. Find if there is any transformation to be applied to
              *    the payload before transporting it to destination.
              * 2. If needed, transform the request.
              * 3. Transport the transformed data to destination.
              * 4. Update the status of the request in esb_requests table
              *    to mark it as done (or error) depending on the outcomes
              *    of this step.
              * 5. Cleanup
              */
            printf("Applying transformation and transporting steps.\n");
            int route_id=get_route_id(SENDER,DEST,MTYPE);
            //getting the config key fot transformation
            char transform_key[50];
            get_transform_key(route_id,transform_key);
            printf("\n transform key - %s\n", transform_key);
            
            //if transformation is required
            char transport_key[50];
            check_transform(transform_key,route_id,transport_key);
            printf("trasnport key - %s\n", transport_key);
            
            //getting the service value
            char transport_value[50];
            get_transport_value(route_id,transport_value);
            printf(" transport value - %s\n",transport_value);
            
            //applying transport service
            Apply_transport_service(transport_key,transport_value);
            
            //checking and updating
            
        }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
}


