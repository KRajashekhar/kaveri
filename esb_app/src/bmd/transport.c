
// @authors Kucharla Rajashekhar and Vinay Prabhakar

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "bmd.h"
#include "../db_access/db_access.h"
#include "../http/http.h"

static int Apply_transport_service(char URL[], char transport_service[])
{
	int status=1;
	if(!strcmp(transport_service,"HTTP"))
	{
		printf(" HTTP service should be applied here\n");
		//passing the url
		send_http_request(URL);
		//destination service could be of any type 
		return status;
	}
	else if(!strcmp(transport_service,"email"))
	{
		char filename[1000];
		printf("Enter file to be read:\t");
		scanf("%s",filename);
		printf(" email service applied \n");
		int mail_status = send_mail(URL,filename);
		if(mail_status == 0)
		{
			printf("Mail has been sent");
		}
		else
		{
			printf("Failed to send mail \n");
		}
	}
	else	
	 	{
	 		status =0;
			printf("No service Found\n");
		}
	return status;
	
}
