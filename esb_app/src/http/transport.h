#ifndef TRANSPORT_H
#define TRANSPORT_H

typedef struct transport_config{
	char *key;
	char *value;
	} transport_t;
	
	int send_email(char *to,char *file_path);
	#endif
