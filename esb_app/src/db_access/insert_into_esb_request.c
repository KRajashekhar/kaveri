#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<mysql/mysql.h>


//require for strptime()
//#define _XOPEN_SOURCE  
#define __USE_XOPEN
#define _GNU_SOURCE
#include<time.h>


#include"db_access.h"

#define STRING_SIZE 1000

#define INSERT_INTO_ESB_REQUEST "INSERT INTO \
esb_request(sender_id, dest_id, message_type, reference_id, \
message_id, received_on, data_location, status, status_details)\
VALUES(?,?,?,?,?,?,?,?,?)"

/*int finish_with_error(MYSQL *con) {
    fprintf(stderr,"%s\n", mysql_error(con)) ;
    mysql_close(con);
   //exit(1);
   return INVALID;
}
*/


int insert_into_esb_request(char *sender_id, char *dest_id,
char *message_type, char *reference_id, char *message_id,
char *received_on, char *data_location, char *status, char *status_details) {                                   

MYSQL_STMT      *stmt;
MYSQL_BIND       bind[9];
uint64_t         affected_rows;
int              param_count;
char             sender_id_data[STRING_SIZE];
char             dest_id_data[STRING_SIZE];
char             message_type_data[STRING_SIZE];
char             referece_id_data[STRING_SIZE];
char             message_id_data[STRING_SIZE];
MYSQL_TIME       received_on_data;
char             data_location_data[STRING_SIZE];
char             status_data[STRING_SIZE];
char             status_details_data[STRING_SIZE];
unsigned long    str_length[8];
//bool             is_null;



   MYSQL *con = mysql_init(NULL);
      
  if (con == NULL) 
  {
  fprintf(stderr, "%s \n",mysql_error(con));
  //exit(1);
  return INVALID;
  }

  if(mysql_real_connect(con, HOST ,USER, PASSWD ,
        DB, 0 , UNIX_SOCKET , FLAG )==NULL) {

    return finish_with_error(con);
  }


  // Prepare an INSERT query with 9 parameters

stmt = mysql_stmt_init(con);
if(!stmt) {
    fprintf(stderr, "mysql_stmt_init(), out of memory \n");
    //exit(0);
    return INVALID;
}

if(mysql_stmt_prepare(stmt, INSERT_INTO_ESB_REQUEST, strlen(INSERT_INTO_ESB_REQUEST))) {

    fprintf(stderr, "mysql_stmt_prepare(), INSERT failed\n");
    fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    //exit(0);
    return INVALID;
}

fprintf(stdout, "prepare, INSERT successful\n");

//Get the parameter count from the statement

param_count = mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in INSERT: %d\n", param_count);


//validate parameter count
if(param_count != 9) {
    fprintf(stderr, " invalid parameter count returned by MySQL\n");
    //exit(0);
    return INVALID;
}


//Bind the data for all 9 parameters

memset(bind, 0, sizeof(bind));

//sender_id

bind[0].buffer_type   = MYSQL_TYPE_STRING;
bind[0].buffer        = (char *)&sender_id_data;
bind[0].buffer_length = STRING_SIZE;
bind[0].is_null       = 0;
bind[0].length        = &str_length[0];

//dest_id

bind[1].buffer_type   = MYSQL_TYPE_STRING;
bind[1].buffer        = (char *)&dest_id_data;
bind[1].buffer_length = STRING_SIZE;
bind[1].is_null       = 0;
bind[1].length        = &str_length[1];

//message_type

bind[2].buffer_type   = MYSQL_TYPE_STRING;
bind[2].buffer        = (char *)&message_type_data;
bind[2].buffer_length = STRING_SIZE;
bind[2].is_null       = 0;
bind[2].length        = &str_length[2];

//reference_id

bind[3].buffer_type   = MYSQL_TYPE_STRING;
bind[3].buffer        = (char *)&referece_id_data; 
bind[3].buffer_length = STRING_SIZE;
bind[3].is_null       = 0;
bind[3].length       = &str_length[3];

//message_id

bind[4].buffer_type   = MYSQL_TYPE_STRING;
bind[4].buffer        = (char *)&message_id_data;
bind[4].buffer_length = STRING_SIZE;
bind[4].is_null       = 0;
bind[4].length        = &str_length[4];

//received_on

bind[5].buffer_type   = MYSQL_TYPE_DATETIME;
bind[5].buffer        = (char *)&received_on_data;
//bind[5].buffer_length = STRING_SIZE;
bind[5].is_null       = 0;
bind[5].length        = 0;

//data_location

bind[6].buffer_type   = MYSQL_TYPE_STRING;
bind[6].buffer        = (char *)&data_location_data; 
bind[6].buffer_length = STRING_SIZE;
bind[6].is_null       = 0;
bind[6].length       = &str_length[5];

//status

bind[7].buffer_type   = MYSQL_TYPE_STRING;
bind[7].buffer        = (char *)&status_data;
bind[7].buffer_length = STRING_SIZE;
bind[7].is_null       = 0;
bind[7].length        = &str_length[6];

//status_details

bind[8].buffer_type   = MYSQL_TYPE_STRING;
bind[8].buffer        = (char *)&status_details_data;
bind[8].buffer_length = STRING_SIZE;
bind[8].is_null       = 0;
bind[8].length        = &str_length[7];

//Bind the buffers

if(mysql_stmt_bind_param(stmt, bind)) {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    //exit(0);
    return INVALID;
}

// Specify the data values for the first row

//sender_id
strncpy(sender_id_data, sender_id, STRING_SIZE);
str_length[0] = strlen(sender_id_data);

//dest_id
strncpy(dest_id_data, dest_id, STRING_SIZE);
str_length[1] = strlen(dest_id_data);

//message_type
strncpy(message_type_data, message_type, STRING_SIZE);
str_length[2] = strlen(message_type_data);

//reference_id
strncpy(referece_id_data, reference_id, STRING_SIZE);
str_length[3] = strlen(referece_id_data);

//message_id
strncpy(message_id_data, message_id, STRING_SIZE);
str_length[4] = strlen(message_id_data);

//received_on

//modifing DATETIME format
size_t len = strlen(received_on);

  char date[len+2];
  size_t i;
  for(i = 0; i < len-2 ; i++)
  {
        
   if(received_on[i] == 'T') 
   {
    date[i] = ' ';
   }
    else 
    {
      date[i] = received_on[i];
    }
  }
  date[i] = ':';
  i++;
  for(;i<(len+2);i++) 
  {
    date[i]= received_on[i-1];
  }
  date[i] = '\0';
  received_on= date;

//converting string representation of time to a time tm structure
struct tm tm;

memset(&tm, 0, sizeof(struct tm));
strptime(received_on, "%Y-%m-%e %H:%M:%S", &tm);

  /* Seconds (0-60) */
  /* Minutes (0-59) */
  /* Hours (0-23) */
  /* Day of the month (1-31) */
  /* Month (0-11) */
  /* Year - 1900 */
  /* Day of the week (0-6, Sunday = 0) */
  /* Day in the year (0-365, 1 Jan = 0) */
  /* Daylight saving time */

received_on_data.year   = tm.tm_year+1900;
received_on_data.month  = tm.tm_mon+1;
received_on_data.day    = tm.tm_mday;

received_on_data.hour   = tm.tm_hour;
received_on_data.minute = tm.tm_min;
received_on_data.second = tm.tm_sec;

// strncpy(received_on_data, received_on, STRING_SIZE);
 //str_length[5] = strlen(received_on_data);

//data_location

strncpy(data_location_data, data_location, STRING_SIZE);
str_length[5] = strlen(data_location_data);

//status

strncpy(status_data, status, STRING_SIZE);
str_length[6] = strlen(status_data);

//status_details

strncpy(status_details_data, status_details, STRING_SIZE);
str_length[7] = strlen(status_details_data);


// Execute the INSERT statement - 1

if(mysql_stmt_execute(stmt)) {
    fprintf(stderr, " mysql_stmt_execute(), 1 failed\n");
    fprintf(stderr, " %s\n", mysql_stmt_error(stmt));
    //exit(0);
    return INVALID;
}

//Get the number of affected rows

affected_rows = mysql_stmt_affected_rows(stmt);
fprintf(stdout, "total affected rows(INSERT 1): %lu\n", (unsigned long) affected_rows);

//Validate affected_rows

if(affected_rows != 1) { 
    fprintf(stderr, " invalid affected rows by MySQL \n");
    //exit(0);
    return INVALID;
}

//close the statement

if(mysql_stmt_close(stmt)) {
    //mysql_stmt_close() invalidates stmt, so cll
    //mysql_error(con) rather than mysql_stmt_error(stmt)
    fprintf(stderr, "failed while closing the statement\n");
    fprintf(stderr, "%s\n", mysql_error(con));
   // exit(0);
   return INVALID;
}

//close con
mysql_close(con);
return VALID;
}

