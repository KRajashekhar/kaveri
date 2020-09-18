
// @authors Kucharla Rajashekhar and Vinay Prabhakar

#include<stdio.h>
///#include "../bmd/bmd.h"
#ifndef ESB_H
#define ESB_H

// task tag

typedef struct task
	{
		int id;
		char *sender;
		char *destination;
		char *message_type;
		char *data_location;
		int processing_attempts;
	} task_t;
	
int process_esb_request(char* bmd_file_path);
//int insert_in_esb_request(BMD *);
//int select_active_route(const unsigned char *Sender, const unsigned char *Destination, const unsigned char *MessageType);
//int select_transport_config(int route_id);
//int select_transform_config(int route_id);

#endif
