#include<stdio.h>
#include<stdlib.h>
//gcc -Wall -I/usr/include/libxml2 -o parsing parsing.c -lxml2
#include <libxml/parser.h>
#include <libxml/tree.h>
#include "bmd.h"


bmd parse_bmd_xml(char * bmd_file_path) 
{

    xmlDoc         *document;
    xmlNode        *root, *first_child, *node,*temp;
    char           *filename;
    
   
    filename = bmd_file_path;

    document = xmlReadFile(filename, NULL, 0);
    temp = xmlDocGetRootElement(document);
    root=xmlFirstElementChild(temp);
  
       
    char* arrayValue[8];
    int i=0;
    first_child = root->children;
    for (node = first_child; node; node = node->next) 
    {
            
      if(node->type==1)
        {
            arrayValue[i]=(char*)xmlNodeGetContent(node);
            i++;
        }
    }

    root=xmlLastElementChild(temp);
    first_child = root;
    for (node = first_child; node; node = node->next)
     {
        if(node->type==1)
        {
            arrayValue[i]=(char*)xmlNodeGetContent(node);
            i++;
        }
     }
    
   bmd_envelop envl;
   envl.message_id = arrayValue[0];
   envl.message_type = arrayValue[1];
   envl.sender_id = arrayValue[2];
   envl.destination_id = arrayValue[3];
   envl.received_on = arrayValue[4];
   envl.signature = arrayValue[5];
   envl.reference_id =arrayValue[6];
   envl.user_properties = arrayValue[7];
   
   bmd b;
   b.envelop = envl;
   b.payload = arrayValue[8];

 return b;
}

/*int main() {
 
 bmd b;
 b = parse_bmd_xml("bmd.xml");
 printf("%s\n",b.payload);
}*/