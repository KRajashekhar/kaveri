#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void check_transform(char type[], int route_id, char * transport_key, char * transport_value)
{
	if((!strcmp(type,"Json_transform")&&(!strcmp(transport_value,"HTTP")))
	{
		printf(" HTTP_Json transformation \n");
		HTTP_Json_transform(route_id,transport_key);
	}
	
	else if((!strcmp(type,"Json_transform"))&& (!strcmp(transport_value,"email")))
	{
		printf( " Email_Json transform \n");
		get_emailId(route_id,transport_key);
	}
	else
	{
		printf("No transformation needed\n");
	}
	
}

void HTTP_Json transform( int route_id , char * transport_key)
{
	chat temp[100];
	FILE *fp=fopen("Payload.json","r");
	
	int i=0;
	char c=fgetc(fp);
	while(c!=EOF)
	{
		temp[i++]=c;
		c=fgetc(fp);
	}
	temp[i]='\0';
	
	char payload[strlen(temp)];
	int k=0;
	for(int i=0;i<strlen(temp);i++)
	{
		if(temp[i]==':')
		{
			for(int j=i+2;j<strlen(temp);j++)
			{
				if(temp[j]==' " ')
				{
					break;
				}
				payload[k++]=temp[j];
			}
			break;
		}
	}
	printf("Payload is :|t %s \n",payload);
	add_payload(payload,route_id,transport_key);
}

