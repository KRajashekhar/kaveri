#include <stdio.h>
#include <unistd.h>
#include "esb.h"
//#include "../bmd/bmd.h"

int fetch_new_request_from_db(task_t *request)
{
    /** 
     * TODO: query the DB for this, and populate the 
     * request pointer with the requests.
     */
    printf("Checking for new requests in esb_requests table.\n");
    request=select_new_esb_request();
    if(request!=NULL)
    {
    	return 1;
    	}
    return 0; // 1 => OK, 0 => Failed
}

/**
 * TODO: Implement the proper logic as per ESB specs.
 */
void *poll_database_for_new_requets(void *vargp)
{
    // Step 1: Open a DB connection
    int i = 0;
    while (i < 99)
    {
        i++;
        /**
         * Step 2: Query the esb_requests table to see if there
         * are any newly received BMD requets.
         */
        task_t *req;
        /**
         * Step 3:
         */
        if (fetch_new_request_from_db(&req))
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
        }
        /**
         * Sleep for polling interval duration, say, 5 second.
         * DO NOT hard code it here!
         */
        printf("Sleeping for 5 seconds.\n");
        sleep(5);
    }
}

int main()  {
	task_t *req=select_new_esb_request();
	int a=update_esb_request("done",req->id);
	printf("rc for update =%d",a);
	printf("%d",req->id);
	printf("%s",req->data_location);
	printf("%s",req->destination);
	return 0;
	}
