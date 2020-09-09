
//gcc connect.c -o connect 'mysql_config --cflags --libs'
#include<stdio.h>
#include <string.h>
#include <mysql/mysql.h>
/*#include <libxml/parser.h>
#include <libxml/tree.h>
*/
#include "bmd.h"

#define MAX_STRING 200


void finish_with_error1(MYSQL *con) {
    fprintf(stderr,"%s\n", mysql_error(con)) ;
    mysql_close(con);
   exit(1);
}


void db_access(bmd b) 
{
    
   MYSQL *con = mysql_init(NULL);
      
  if (con == NULL) 
  {
  fprintf(stderr, "%s \n",mysql_error(con));
  exit(1);
  }

  if(mysql_real_connect(con, "localhost" ,"raja", "Kucharla@1" , "esb_db", 0 , NULL , CLIENT_MULTI_STATEMENTS )==NULL)
  {

    finish_with_error1(con);
  }
     
  bmd_envelop e = b.envelop;
  size_t len = strlen(e.received_on);

  char date[len+2];
  int i;
  for(i = 0; i <len-2 ; i++)
  {
        
   if(e.received_on[i] == 'T') 
   {
    date[i] = ' ';
   }
    else 
    {
      date[i] = e.received_on[i];
    }
  }
  date[i] = ':';
  i++;
  for(;i<(len+2);i++) 
  {
    date[i]= e.received_on[i-1];
  }
  date[i] = '\0';
  e.received_on = date;

   //Entering data into the esb_request table   
  char quer[MAX_STRING];
  int  return_value;
  return_value = snprintf(quer, MAX_STRING, "INSERT INTO esb_request (sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES ('%s','%s','%s','%s','%s','%s','available')", e.sender_id, e.destination_id, e.message_type, e.reference_id, e.message_id, e.received_on);
  char query[return_value+1];
  return_value = snprintf(query,return_value+1, "INSERT INTO esb_request (sender_id, dest_id, message_type, reference_id, message_id, received_on, status) VALUES ('%s','%s','%s','%s','%s','%s','available')", e.sender_id, e.destination_id, e.message_type, e.reference_id, e.message_id, e.received_on);
       
   
  if (mysql_query(con, query))
   {
      finish_with_error1(con);
      
    }

    //Entering data into the routes table

  return_value = snprintf(quer,MAX_STRING, "INSERT INTO routes(sender, destination, message_type, is_active) VALUES ('%s','%s','%s',B'1')",e.sender_id, e.destination_id, e.message_type);
  char query1[return_value+1];
  return_value = snprintf(query1, return_value+1,"INSERT INTO routes(sender, destination, message_type, is_active) VALUES ('%s','%s','%s',B'1')",e.sender_id, e.destination_id, e.message_type);

   if (mysql_query(con, query1)) 
   {

    finish_with_error1(con);
   }
    
     
    
   int id = mysql_insert_id(con);

   printf("The last inserted row id is: %d\n",id);
   mysql_close(con);
    

}

/*int main() {

  bmd b;
  b = parse_bmd_xml("bmd.xml");
  db_access(b);
  return 0;
}*/