
// @authors Kucharla Rajashekhar and Vinay Prabhakar

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"bmd.h"

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

void xml2json(char Pay[],char Sender[])
	{
		char *filename = " ";
		strcpy(filename,Sender);
		strcat(filename,"Paylaod.json");
		FILE *file;
	    	file = fopen(filename,"w");
	    	
	    	if(file == NULL) 
	    	{
			printf("file opening failed");
			exit(0);
	    	}
	    	
	    	
	    	fprintf(file,"{\n \"Payload\":\"%s\"\n}",Pay);
	    	
	    	printf("\nPayload json File created\n");
	   	
	    	fclose(file);
	    	
	    	//return strdup(filename);
	}
int get_filesize(char filename[])
{
	FILE *fp;
	int size=0;
	fp=fopen(filename,"r");
	
	if(fp==NULL)
	{
		printf("File opening failed\n");
	}
	else
	{
		printf("file opened\n");
	}
	//file pointer to the end of file
	
	fseek(fp,0,2);
	size=ftell(fp);
	
	if(size>5000000)
	{
		printf("File size larger than 5 mb not allowed\n");
	}
	fclose(fp);
	
	return size;
}

char *get_filecontents (char filename[])
{
	long f_size;
	char *str_data;
	size_t file_size;
	FILE *fp=fopen(filename,"r");
	fseek(fp,0,2);
	
	//read size of file after moving pointer to the end of teh file
	f_size=ftell(fp);
	fseek(fp,0,0);
	file_size=sizeof(char) * f_size;
	str_data=malloc(file_size);
	
	//returns number of items actually read
	fread(str_data,1,f_size,fp);
	return strdup(str_data);
}
	
char* xmltojson(char Pay[])
{
	char filename[]="Payload.json";
	FILE *file;
	file=fopen(filename,"w");
	
	if(file==NULL)
	{
		printf("File opening failed\n");
		exit(0);
	}
	
	//write into json file
	fprintf(file,"{\n \"Paylaod\":\"%s\"\n}",Pay);
	
	printf("Payload json file created\n");
	
	//close the file
	fclose(file);
	
	return strdup(filename);
}
	
