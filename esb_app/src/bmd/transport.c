#include<stdio.h>
#include<stdlib.h>
#include<string.h>

Apply_tranport_service(char URL[], char transport_service[])
{
	if(!strcmp(transport_service,"HTTP"))
	{
		printf(" HTTP service should be applied here\n");
		//passing the url
		send_http_request(URL);
		//destination service could be of any type 
	}
	else
	{
		printf("No service Found\n");
	}
	
}
