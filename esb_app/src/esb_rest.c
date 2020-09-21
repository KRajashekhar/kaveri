#include <kore/kore.h>
#include <kore/http.h>


typedef struct
{
	int success;
	char* status;
	char *message_id;
}rest_result;

int esb_rest(struct http_request *);
rest_result get_messageID(struct http_request *);

//Receives a request
int esb_rest(struct http_request *req)
{
    printf("Received the REST request.\n");
    rest_result get_messageid =get_messageID(req);
    
    if(get_messageid.success>0)
    {
       printf("Message ID: %s\n",get_messageid.message_id);
       printf("Status: %s\n",get_messageid.status);
       return KORE_RESULT_OK;
    }
    else
    {
        return KORE_RESULT_ERROR;
    }
    

    return KORE_RESULT_OK;
}
rest_result get_messageID(struct http_request *req)
{
    rest_result rs_res;
    rs_res.success=1; //1-->OK , -ve for errors
    rs_res.status="available"; 
    http_populate_get(req);
    if(req->method!=HTTP_METHOD_GET)
    {
        rs_res.success=-1;
        rs_res.status="error";
        kore_log(LOG_ERR, "Rejecting non GET request.");
		http_response(req, 405,"Wrong Method\n", 13);
        return rs_res;
    }
    http_response(req, 200, "Processing GET REQUEST",15);
    char  *out;
    //printf("%s\n\n",req->query_string);
    if(http_argument_get_string(req,"MessageID",&out))
    {
       rs_res.message_id=malloc(strlen(out)*sizeof(char)+1);
       rs_res.status=malloc(strlen(out)*sizeof(char)+1);
       strcpy(rs_res.message_id,out);
       char status_details[20];
       get_status(out, status_details);
       strcpy(rs_res.status,(char *)status_details);
    }
       else
       {
          rs_res.success=-1;
       }
       
    return rs_res;  
}
