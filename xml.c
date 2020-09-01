#include<stdio.h>
#include<stdlib.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include "mysql/mysql.h"

void finish_with_error(MYSQL *conn)
{
fprintf(stderr, "%s \n", mysql_error(conn));
mysql_close(conn);
exit(1);
}


int main()
{
xmlDoc *doc;
xmlNode *root,*first_child,*temp,*node;
char *filename;

MYSQL *conn=mysql_init(NULL);

char *server = "localhost";
 char *user = "vinay";
 char *password = "prabhakars 589b"; 
 char *database = "esb_db"; 
 if (conn == NULL)
  {
     finish_with_error(conn);
  }
  
  mysql_real_connect(conn,"localhost","user","prabhakars 589b","esb_db",0,NULL,0);

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
 
 if(mysql_query(conn,"insert into esb_request values (arrayname[0],arrayname[1],arrayname[2],arrayname[3],arrayname[4],arrayname[5],arrayname[6],arrayname[7])")

{
finish_with_error(conn);
}
 fprintf(stdout,"... \n");
 return 0;
 }
