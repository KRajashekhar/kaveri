#include<stdio.h>
#include<stdlib.h>
#include<libxml/parser.h>
#include<libxml/tree.h>
#include<string.h>
#include "mysql/mysql.h"
#define STRING_SIZE 1000

#define INSERT "INSERT INTO                                  \
esb_request(sender_id,dest_id,message_type,reference_id,     \
message_id,data_location,status,status_details)              \
VALUES(?,?,?,?,?,?,?,?)"




void finish_with_error(MYSQL *conn)
{
	fprintf(stderr, "%s \n", mysql_error(conn));
	//mysql_close(conn);
	exit(1);
}

void insert_to_esb_request(char **sender_id,char **dest_id,
char **message_type,char **reference_id,char **message_id, 
char **data_location, char **status,char **status_details) {

MYSQL_STMT    *stmt;
MYSQL_BIND    bind[8];
my_ulonglong  affected_rows;

char          sender_id_data[STRING_SIZE];
char          dest_id_data[STRING_SIZE];
char          message_type_data[STRING_SIZE];
char          reference_id_data[STRING_SIZE];
char          message_id_data[STRING_SIZE];
char          data_location_data[STRING_SIZE];
char          status_data[STRING_SIZE];
char          status_details_data[STRING_SIZE];
unsigned long str_length[8];



MYSQL *conn=mysql_init(NULL);


	 if (conn == NULL)
	  {
	     finish_with_error(conn);
	  }
  
  	 mysql_real_connect(conn,"localhost","root","prabhakars 589b","esb_db",0,NULL,0);
  	 stmt = mysql_stmt_init(conn);
if (!stmt) {
  fprintf(stderr, " mysql_stmt_init(), out of memory\n");
  exit(0);
}

if (mysql_stmt_prepare(stmt, INSERT, strlen(INSERT))) {
  fprintf(stderr, " mysql_stmt_prepare(), INSERT failed\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
}
fprintf(stdout, " prepare, INSERT successful\n");

memset(bind, 0, sizeof(bind));

bind[0].buffer_type= MYSQL_TYPE_STRING;
bind[0].buffer= (char *)&sender_id_data;
bind[0].is_null= 0;
bind[0].length= &str_length[0];
bind[0].buffer_length= STRING_SIZE;



bind[1].buffer_type= MYSQL_TYPE_STRING;
bind[1].buffer= (char *)dest_id_data;
bind[1].buffer_length= STRING_SIZE;
bind[1].is_null= 0;
bind[1].length= &str_length[1];


bind[2].buffer_type= MYSQL_TYPE_STRING;
bind[2].buffer= (char *)&message_type_data;
bind[2].is_null= 0;
bind[2].buffer_length= STRING_SIZE;
bind[2].length= &str_length[2];


bind[3].buffer_type= MYSQL_TYPE_STRING;
bind[3].buffer= (char *)&reference_id_data;
bind[3].is_null= 0;
bind[3].buffer_length= STRING_SIZE;
bind[3].length= &str_length[3];


bind[4].buffer_type= MYSQL_TYPE_STRING;
bind[4].buffer= (char *)&message_id_data;
bind[4].is_null= 0;
bind[4].buffer_length= STRING_SIZE;
bind[4].length= &str_length[4];


bind[5].buffer_type= MYSQL_TYPE_STRING;
bind[5].buffer= (char *)&data_location_data;
bind[5].is_null= 0;
bind[5].buffer_length= STRING_SIZE;
bind[5].length= &str_length[5];


bind[6].buffer_type= MYSQL_TYPE_STRING;
bind[6].buffer= (char *)&status_data;
bind[6].is_null= 0;
bind[6].buffer_length= STRING_SIZE;
bind[6].length= &str_length[6];


bind[7].buffer_type= MYSQL_TYPE_STRING;
bind[7].buffer= (char *)&status_details_data;
bind[7].is_null= 0;
bind[7].buffer_length= STRING_SIZE;
bind[7].length= &str_length[7];



strncpy(sender_id_data,*sender_id, STRING_SIZE);
str_length[0]= strlen(sender_id_data);
strncpy(dest_id_data,*dest_id, STRING_SIZE);
str_length[1]=strlen(dest_id_data);
strncpy(message_type_data,*message_type,STRING_SIZE);        
str_length[2]=strlen(message_type_data);
strncpy(reference_id_data,*reference_id,STRING_SIZE);        
str_length[3]=strlen(reference_id_data);
strncpy(message_id_data,*message_id,STRING_SIZE);        
str_length[4]=strlen(message_id_data);
strncpy(data_location_data,*data_location,STRING_SIZE);        
str_length[5]=strlen(data_location_data);
strncpy(status_data,*status,STRING_SIZE);        
str_length[6]=strlen(status_data);
strncpy(status_details_data,*status_details,STRING_SIZE);        
str_length[7]=strlen(status_details_data);


if (mysql_stmt_execute(stmt)) {
  fprintf(stderr, " mysql_stmt_execute, failed\n");
  fprintf(stderr, " [%d]%s\n",mysql_stmt_errno(stmt),
  mysql_stmt_error(stmt));
  exit(0);
}


affected_rows= mysql_stmt_affected_rows(stmt);
fprintf(stdout, " total affected rows(insert 2): %lu\n",
                (unsigned long) affected_rows);


if (affected_rows != 1) {
  fprintf(stderr, " invalid affected rows by MySQL\n");
  exit(0);
}


if (mysql_stmt_close(stmt)) {
  fprintf(stderr, " failed while closing the statement\n");
  fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
  exit(0);
} printf("connection id: %ld\n", mysql_thread_id(conn));

  mysql_close(conn);
}

int main() {
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
 
 	
	
	


  char *s,*d,*mt,*rid,*mid,*dl,*st,*std;
  s=arrayvalue[0]; d = arrayvalue[1]; mt = arrayvalue[2]; mid = arrayvalue[3];
  dl =arrayvalue[4]; st =arrayvalue[5]; std=arrayvalue[6];
  rid =arrayvalue[7];
 insert_to_esb_request(&s,&d,&mt,&rid,&mid,&dl,&st,&std);
 return 0;
 
  fprintf(stdout,"... \n");
	 return 0;
}


