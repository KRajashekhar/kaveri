#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void json_transform(int route_id,char* transport_key)
 {
 	char temp[100];
 	FILE *fp=fopen("Payload.json","r");
 	int i=0;
 	char c =fgetc(fp);
 	while(c!=EOF)
 	{
 		temp[i++]=c;
 		c=fgetc(fp);
 		
 	}
 	
 	//adding null terminator at end
 	temp[i]='\0';
 	
 	int l;
 	l=strlen(temp);
 	char payload[l];
 	int k=0;
 	for(int i=0;i<l;i++)
 	{
 		if(temp[i]==':')
 		{
 			for(int j=i+2;j<strlen(temp);j++)
 			{
 				if(temp[j]==' " ')
 					break;
 				payload[k++]=temp[j];
 			}
 			break;
 		}
 	}
 	
 	printf("\n Payload - \t%s \n", payload);
 	
 	add_payload(payload,route_id,transport_key);
 	
  }
  
  void check_transform(char type[], int route_id,char *transport_key)
  {
  	if(!strcmp(type,"json_transform"))
  	{
  		printf("transformation needed \n");
  		
  		//calling the fucntion
  		json_transform(route_id,transport_key);
  	}
  	else
  	{
  		printf("Transformation not required\n");
  	}
  }
