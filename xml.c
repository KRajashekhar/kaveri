#include <stdio.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
int main()
{
    xmlDoc         *document;
    xmlNode        *root, *first_child, *node,*temp;
    char           *filename;
    
   
    filename = "bmd.xml";

    document = xmlReadFile(filename, NULL, 0);
    temp = xmlDocGetRootElement(document);
    root=xmlFirstElementChild(temp);
  
        char* arrayName[8];
        char* arrayValue[8];
        int i=0;
        first_child = root->children;
        for (node = first_child; node; node = node->next) {
            // if(node->type==1)
            // fprintf(stdout, "\t Child is <%s>  (%i) value: \n", node->name ,node->type);
            // // temp=node;

            if(node->type==1)
            {
            // printf("%d\n",checkNamespace("MessageID",node->name));
                arrayName[i]=(char*)node->name;
                arrayValue[i]=(char*)xmlNodeGetContent(node);
                //fprintf(stdout, "attributes:<%s>\tvalue: %s\n", node->name,xmlNodeGetContent(node));
                //printf("%d: name->%s value->%s\n",i,arrayName[i],arrayValue[i]);
                i++;
            }
        }

    root=xmlLastElementChild(temp);
    first_child = root;
        for (node = first_child; node; node = node->next) {
            // if(node->type==1)
            // fprintf(stdout, "\t Child is <%s>  (%i) value: \n", node->name ,node->type);
            // // temp=node;

            if(node->type==1)
            {
            // printf("%d\n",checkNamespace("MessageID",node->name));
                arrayName[i]=(char*)node->name;
                arrayValue[i]=(char*)xmlNodeGetContent(node);
                //fprintf(stdout, "attributes:<%s>\tvalue: %s\n", node->name,xmlNodeGetContent(node));
                //printf("%d: name->%s value->%s\n",i,arrayName[i],arrayValue[i]);
                i++;
            }
        }
    // }
    int size = sizeof arrayName / sizeof arrayName[0];
    for(int i=0;i<=size;i++)
    {
        printf("%d: name->%s value->%s\n",i,arrayName[i],arrayValue[i]);
    }
    

    fprintf(stdout, "...\n");
    return 0;
}
