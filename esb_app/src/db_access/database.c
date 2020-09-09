#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmd_parser.h"
#include "database.h"

int insert_in_esb_request(BMD *bmd)
{
    int success =1; //1=>success , -ve for errors
	
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	
	int8_t received_temp[100]; //= "2020-08-12 05:18:00+0000";
  	int8_t received_on[100];
  	strcpy(received_temp,bmd->bmd_envelope->CreationDateTime);
  	
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
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
	{
		printf("Failed to connect MySQL Server %s. Error: %s\n", server, mysql_error(conn));
		success=-1;
		return success;
	}


	/*sql query to insert in table*/
	char *status = "availble";
	char query[5000];
	sprintf(query,INSERT_IN_ESB_REQUEST,
			bmd->bmd_envelop->Sender,
			bmd->bmd_envelop->Destination,
			bmd->bmd_envelop->MessageType,
			bmd->bmd_envelop->ReferenceID,
			bmd->bmd_envelop->MessageID,
			received_on
			,status);

	printf("\n\n%s\n\n", query);

	if (mysql_query(conn, query))
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
	if (res->row_count == 1)
	{
		while ((row = mysql_fetch_row(res)) != NULL)
			success = atoi(row[0]);
	}
	else
	{
		success = -1;
	}

	/* Output table name */
	// printf("MySQL Tables in mydb database:\n");
	//while ((row = mysql_fetch_row(res)) != NULL)
	//printf("%s \n", row[0]);

	/* free results */
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
	if (mysql_query(conn, query))
	{
		printf("Failed to execute quesry. Error: %s\n", mysql_error(conn));
	}

	res = mysql_use_result(conn);
	if (res->row_count >= 1)
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
