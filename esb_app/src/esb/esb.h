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
	
int queue_the_request(bmd *b,char *file_path);
int process_esb_request(char * bmd_file_path);
int fetch_new_request_from_db(task_t *request);
void *poll_database_for_new_request(void *vargp);

#endif
