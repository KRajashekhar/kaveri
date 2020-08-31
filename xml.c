#include<stdio.h>
#include<stdlib.h>
#include<libxml/parser.h>
#include<libxml/tree.h>

int main()
{
xmlDoc *doc;
xmlNode *root,*first_child,*temp,*node;
char *filename;

filename="bmd.xml";
doc=xmlReadFile(filename,NULL,0);
 temp=xmlDocGetRootElement(doc);
 root=xmlFirstElementChild(temp);
 
 char* arrayname[8];
 char *arrayvalue[8];
 int i=0;
 first_child=root->children;
 for(node=first_child;node;node=node->next)
 {
 if(node->type==XML_ELEMENT_NODE)
 {
 arrayname[i]=(char*)node->name;
 arrayvalue[i]=(char*)xmlNodeGetContent(node);
 i++;
 }
 }
 root=xmlLastElementChild(temp);
 first_child=root;
 for(node=first_child;node;node=node->next)
 {
 if(node->type==XML_ELEMENT_NODE)
 {
 
 arrayname[i]=(char*)node->name;
 arrayvalue[i]=(char*)xmlNodeGetContent(node);
 }
 }
 
 int size=sizeof arrayname/sizeof arrayname[0];
 for(int i=0;i<=size;i++)
 {
 printf("%d : name->%s value->%s \n",i,arrayname[i],arrayvalue[i]);
 }
 fprintf(stdout,"... \n");
 return 0;
 }
