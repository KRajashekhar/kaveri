#include<stdio.h>
#include<libxml/parser.h>
#include<stdlib.h>
#include<string.h>
#include "../bmd/bmd.h"
#include "transform.h"
#include "transport.h"

//creating a json file and returning path of file

char * payload_to_json(bmd *bmd_file) {
	char bmd_name[20]; //create file name of json  as per bmd name
	char file[50];
	 sprintf(file,"../bmd/Payload.json",bmd_file->envelop.message_id);
	 
	 char *payload=bmd_file->payload;
	 FILE *fp;
	 fp=fopen(file,"w");
	 if(fp==NULL)
	 {
	 	printf("could not open file");
	 	exit(0);
	 	}
	 	
	 //write into json file
	 fprintf(fp,"{\n\"Payload\":\"%s\"\n}",payload);
	 
	 //close file now
	 fclose(fp);
	 //return file
	 
	 return strdup(file);
	 }
	 
char* payload_to_xml(bmd *bmd_file) {
	char bmd_name[20]; //file name should be same as bmd name
	char file[50]; 
	sprintf(file,"../bmd/Payload.json",bmd_file->envelop.message_id);
	
	char *payload=bmd_file->payload;
	FILE *fp;
	fp=fopen(file,"w");
	if(fp==NULL)
	{
		printf("could not open file");
		exit(0);
	}
	
	//now wirte into xml file like version and all
	char *version="<?xml version=\"1.0\"encoding=\"UTF-8\"?>";
	char *style="<?xml-stylesheet typ'text/xsl'?>";
	fprintf(fp,"%s\n%s\n<payload>%s</payload>",version,style,payload);
	//close the file
	fclose(fp);
	return strdup (file);
	
	}
	
	
	int main() {
		bmd *file=parse_bmd_xml("../bmd/bmd.xml");
		char *xml_path=payload_to_xml(file);
		char *json_path=payload_to_json(file);
		send_email("testmailv1@gmail.com",json_path);
		printf("%s %s",json_path,xml_path);
		}
		
	
