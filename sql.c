#include <stdio.h> 
#include "mysql/mysql.h" 

void finish_with_error(MYSQL *conn)
{
  fprintf(stderr, "%s\n", mysql_error(conn));
  mysql_close(conn);
  exit(1);        
}

int main(int argc, char **argv)
{  
    
    MYSQL *conn=mysql_init(NULL);
 MYSQL_RES *res;

 
 char *server = "localhost";
 char *user = "vinay";
 char *password = "prabhakars 589b"; 
 char *database = "esb_db";  //mydb

   if (conn == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  

    //mysql_real_connect(&mysql,"localhost","user","prabhakars 589b","esb_db",0,NULL,0); 

    printf("Client version: %s",mysql_get_client_info()); 
    printf("\nServer version: %s",mysql_get_server_info(conn)); 
  if (mysql_query(conn, "select * from esb_request"))
 {
   finish_with_error(conn);
 }
 
 
  MYSQL_RES *result = mysql_store_result(conn);
  
  if (result == NULL) 
  {
      finish_with_error(conn);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  
  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
  
  mysql_free_result(result);
  mysql_close(conn);
  
  exit(0);
}

