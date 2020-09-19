#ifndef DATABASE 
#define DATABASE 

#define INSERT_IN_ESB_REQUEST  "INSERT INTO esb_request(sender_id,dest_id,message_type,reference_id,message_id,received_on,status) VALUES ('%s','%s','%s','%s','%s','%s','%s')"
#define SELECT_ACTIVE_ROUTE "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'  AND is_active=b'1'"
#define SELECT_TRANSPORT_CONFIG "SELECT * FROM transport_config WHERE route_id='%d'"
#define SELECT_TRANSFORM_CONFIG "SELECT * FROM transform_config WHERE route_id='%d'"

#define CHECK_NEW_REQUEST "SELECT * FROM esb_request WHERE status = 'available' AND id='%d' LIMIT 1" 

#define AVAILABLE_TO_TAKEN "UPDATE esb_request SET status = 'taken'  WHERE id='%d'"  
#define TAKEN_TO_DONE "UPDATE esb_request SET status = 'done'  WHERE id='%d'"
#define STATUS_TO_ERROR "UPDATE esb_request SET status = 'error'  WHERE id='%d'"

#define GET_routeid "SELECT route_id FROM routes WHERE sender = '%s' AND destination = '%s' AND message_type= '%s'"
#define GET_transformkey "SELECT config_key FROM transform_config WHERE route_id='%d'"
#define GET_transportkey "SELECT config_key FROM transport_config WHERE route_id='%d'"
#define GET_transportvalue "SELECT config_value FROM transport_config WHERE route_id='%d'"

#define server "localhost"
#define user "splunk_user"
#define password "password"
#define database "esb_db"
#define port 3306


#endif
