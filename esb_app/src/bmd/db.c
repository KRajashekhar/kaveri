#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../bmd/bmd.h"
#include "../bmd/db.h"

int insert_in_esb_request(bmd *bmd)
{
    int success =1; //1=>success , -ve for errors
	
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	int8_t received_temp[100]; //= "2020-08-12 05:18:00+0000";
  	int8_t received_on[100];
  	strcpy(received_temp,bmd->envelop.received_on);
  	
  	/*Changing DateTime format*/
  	int n = strlen(received_temp);
  	int j=0;
  	for(int i=0;i<=n; i++)
  	{
  		received_on[j] = received_temp[i];
  		if(received_on[i]=='T')		//test for character
		{
			received_on[i] = ' '; // change T to space
		}
		if(i==n-3)
		{
			char ch = ':';
		  	strncat(received_on, &ch, 1); 
		  	j++;			
		}
		j++;
	}

	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
		success=-1;
		return success;
	}


	/*sql query to insert in table*/
	char *status = "available";
	char query1[5000];
	char query2[5000];
	int check = 1; //checking for duplicacy
	
	sprintf(query1,INSERT_IN_ESB_REQUEST,
			bmd->envelop.sender_id,
			bmd->envelop.destination_id,
			bmd->envelop.message_type,
			bmd->envelop.reference_id,
			bmd->envelop.message_id,
			received_on
			,status);
			

	printf("\n\n%s\n\n", query1);

	if (mysql_query(conn, query1))
	{
		printf("Failed to execute query.Error: %s\n", mysql_error(conn));
		success=-1;
		return success;
	}

	res = mysql_use_result(conn);

	/*free the result*/

	mysql_free_result(res);
	mysql_close(conn);
	return success;
}
//Returns route_id if an active route exists for a given sender , destination and message type
int select_active_route(const unsigned char *Sender, const unsigned char *Destination,const unsigned char *MessageType)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Execute SQL query to fetch all table names.*/
	sprintf(query, SELECT_ACTIVE_ROUTE, Sender, Destination, MessageType);
	
	if (mysql_query(conn, query))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);
	if ((row = mysql_fetch_row(res)) != NULL)
	{
			success = atoi(row[0]);
	}
	else
	{
		success = -1;
	}

	mysql_free_result(res);
	return success;
}

int select_transport_config(int route_id)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Execute SQL query to fetch all table names.*/
	sprintf(query, SELECT_TRANSPORT_CONFIG,route_id);
	printf("%s",query);
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}
    
	res = mysql_use_result(conn);

	if (res->field_count >= 1)
	{
		success=1;
	}
	else
	{
		success = -1;
	}

	/* free results */
	mysql_free_result(res);
	return success;
}

int select_transform_config(int route_id)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	
	sprintf(query, SELECT_TRANSFORM_CONFIG,route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);
	printf("%s\n %ld\n ",query,res->row_count);
	if (res->row_count >= 1)
	{
		success=1;
	}
	else
	{
		success =-1;
	}

	/* free results */
	mysql_free_result(res);
	return success;
}


int check_new_request(int id)
{
	int success = 0;

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	
	sprintf(query, CHECK_NEW_REQUEST, id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
        int retval = mysql_num_rows(res);
	printf("\nrows:\t%d\n",retval);
	if (retval >0)
	{
		success=1;
	}
	else
	{
		success =-1;
	}

	/* free results */
	mysql_free_result(res);
	return success;
}

void change_available_to_taken(int id)
{

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	
	sprintf(query, AVAILABLE_TO_TAKEN, id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);

	/* free results */
	mysql_free_result(res);
}

//if task is completed

void change_taken_to_done(int id)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	conn=mysql_init(NULL);
	char query[5000];
	
	//connect to db
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Failed to connect to MYSQL server %s. Error : %s \n", server,mysq_error(conn));
	}
	sprintf(query,TAKEN_TO_DONE,id);
	
	if(mysql_query(conn,query))
	{
		printf("failed to execute query. Error: %s\n", mysql_error(conn));
	}
	res = mysql_store_result(conn);
	//free res 
	mysql_free_result(res);
	}	
int get_route_id(char SENDER[], char DEST[], char MTYPE[])
{

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	
	sprintf(query, GET_routeid, SENDER, DEST, MTYPE);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	int route_id = atoi(row[0]);

	/* free results */
	mysql_free_result(res);
	return route_id;
}

void get_transform_key(int route_id, char* key)
{

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/*Get transform config_value*/
	sprintf(query, GET_transformkey, route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(key,strdup(row[0]));

	/* free results */
	mysql_free_result(res);
	
}

void add_payload(char Payload_value[], int route_id, char* transport_key)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);
	
	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/* Get transform config_key */ 
	sprintf(query, GET_transportkey, route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(transport_key,row[0]);
	
	for(int i=0;i<strlen(Payload_value);i++)
	{
		char ch = Payload_value[i];
		strncat(transport_key, &ch, 1);
	}
	
	/* free results */
	mysql_free_result(res);
	
}

void gte_emailId(int route_id, char * transport_key)
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn=mysql_init(NULL);
	
	//connecting to db
	if(!mysql_real_connect(conn,server,user,password,database,0,NULL,0))
	{
		printf("Failed to connect MYSQl server %s. Error : %\n",server,mysql_error(conn));
	}
	
	//getting transform config_key
	
	sprintf(query,GET_transportkey,route_id);
	
	if(mysql_query(conn,query))
	{
	
		printf("Failed to execute query. Error %s\n", mysql_error(conn));
		}
		res=mysql_store_result(conn); //storing the result
		row=mysql_fetch_result(res); //accessing each entry
		strcpy(transport_key,row[0]);
		
		//free
		smysql_free_result(res);
	

void get_transport_value(int route_id, char* transport_value)
{

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char query[5000];
	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
	}

	/*Get transform config_value*/
	sprintf(query, GET_transportvalue, route_id);
	/* Execute SQL query.*/
	if (mysql_query(conn, query))
	{
		printf("Failed to execute query. Error: %s\n", mysql_error(conn));
	}

	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	
	strcpy(transport_value,strdup(row[0]));

	/* free results */
	mysql_free_result(res);
	
 }
}

