#include<stdio.h>
#include<stdlib.h>

#include"bmd.h"

void xml2json(char *Payload)
	{
		char *filename= "Payload.json";
		FILE *file;
	    	file = fopen(filename,"w");
	    	
	    	if(file == NULL) 
	    	{
			printf("file opening failed");
			exit(0);
	    	}
	    	
	    	
	    	fprintf(file,"{\n \"Payload\":\"%s\"\n}",Payload);
	    	
	    	printf("\nPayload json File created\n");
	   	
	    	fclose(file);
	    	
	    	//return strdup(filename);
	}

/*int main()
{
	bmd b;
	b=parse_bmd_xml("bmd.xml");
	char *payload=b.payload;
	//char payload[]="How to integrate";
	xml2json(payload);
	return 0;	
}
*/