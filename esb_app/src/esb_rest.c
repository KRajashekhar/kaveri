#include <kore/kore.h>
#include <kore/http.h>


typedef struct
{
	int status;
	char *message_id;
}rest_result;

int esb_rest(struct http_request *);
rest_result get_messageID(struct http_request *);
//Receives a request
int esb_rest(struct http_request *req)
{
    printf("Received the REST request.\n");
    rest_result get_status =get_messageID(req);
    return KORE_RESULT_OK;
}
rest_result get_messageID(struct http_request *req)
{
    rest_result rs_res;
    rs_res.status=1; //1-->OK , -ve for errors

    if(req->method!=HTTP_METHOD_GET)
    {
        printf("NOT A GET");
        kore_log(LOG_ERR, "Rejecting non GET request.");
		http_response(req, 405,"Wrong Method\n", 13);
    }
    http_response(req, 200, "Processing GET REQUEST",15);
    return rs_res;  
}

