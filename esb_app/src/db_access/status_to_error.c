#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<mysql/mysql.h>
#define __USE_XOPEN
#define _GNU_SOURCE
#include<time.h>
 #include "db_access.h"
 
 #define UPDATE_STATUS "update esb_request set status='error' where id= ?"
 
 int change_status_to_error(int id)
 {
 	MYSQL_STMT *stmt;
 	MYSQL_BIND bind[1];
 	uint64_t affected_rows;
 	int param_count;
 	int id_data;
 	
 	MYSQL *con = mysql_init(NULL);
 	if(con==NULL)
 	{
 		fprintf(stderr,"%S \n", mysql_error(con));
 		return INVALID;
 	}
 	
 	if(mysql_real_connect(con,HOST,USER,PASSWD,DB,0,UNIX_SOCKET,FLAG)==NULL)
 	{
 		printf("Failed to connect to MYSQL server %s. Error : %s\n",HOST , mysql_error(con));
 	}
 	
 	//insert query with only 1 parameter
 	
 	stmt =mysql_init(con);
 	if(!stmt)
 	{
 		fprintf(stderr,"mysql_stmt_init(),out of memory,\n");
 	return INVALID;
 	}
 	
 	if(mysql_stmt_prepare(stmt,UPDATE_STATUS,strlen(UPDATE_STATUS)))
 	{
 		fprintf(stderr,"mysql_stmt_prepare(),UPDATE failed\n");
 		fprintf(stderr, "%s\n",mysql_stmt_error(stmt));
 		return INVALID;
 	}
 	fprintf(stdout,"prepare UPDATE statement successful\n");
 	
 	//parameter count
 	
 	param_count=mysql_stmt_param_count(stmt);
 	fprintf(stdout,"total parameters in UPDATE : %d\n",param_count);
 	
 	
 	//validating 
 	if(param_count!=1)
 	{
 		fprintf(stderr,"invalid paramter count returned by mysql\n");
 		return INVALID;
 		
 	}
 //binding the parameters
 
 memset(bind ,0,sizeof(bind));
 //int parameter
 //it is a number type so no need to specify buffer_length
 
 bind[0].buffer_type=MYSQL_TYPE_LONG;
 bind[0].buffer=(char *)&id_data;
 bind[0].is_null=0;
 bind[0].length=0;
 
 //bind the buffers
 
 if(mysql_stmt_bind_param(stmt,bind))
 {
 	fprintf(stderr,"mysql_stmt_bind_param() failed\n");
 	fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
 	return INVALID;
 }
 id_data=id;
 
 affected_rows=mysql_stmt_affected_rows(stmt);
 fprintf(stdout,"total affected rows (INSERT 1) :%lu\n",(unsigned long) affected_rows);
 
 //validating
 if(affected_rows!=1)
 {
 	fprintf(stderr,"invalid affected rows by MYSQl\n");
 	return INVALID;
 }
 //closing 
 
 if(mysql_stmt_close(stmt))
 {
 	fprintf(stderr,"failed while closing statement\n");
 	fpritnf(stderr," %s\n",mysql_error(con));
 	
 	return INVALID;
 }
 //close con
 
 mysql_close(con);
 return VALID;
 }
 
