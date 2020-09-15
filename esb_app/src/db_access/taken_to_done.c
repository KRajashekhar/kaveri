#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<mysql.h>


//require for strptime()
//#define _XOPEN_SOURCE  
#define __USE_XOPEN
#define _GNU_SOURCE
#include<time.h>


#include"db_access.h"

#define STRING_SIZE 1000

#define UPDATE_STATUS  "UPDATE esb_request \
 SET status = 'done' WHERE id = ?"

int change_taken_to_done(int id) {
    int INVALID=0;
    int VALID=1;

    MYSQL_STMT        *stmt;
    MYSQL_BIND        bind[1];
    uint64_t          affected_rows;
    int               param_count;
    int               id_data;


    MYSQL *con = mysql_init(NULL);
      
  if (con == NULL) 
  {
    fprintf(stderr, "%s \n",mysql_error(con));
    //exit(0);
    return INVALID;
  }

  if(mysql_real_connect(con, HOST ,USER, PASSWD ,
        DB, 0 , UNIX_SOCKET , FLAG )==NULL) {

    printf("Failed to connect MySQL Server %s. Error: %s\n", HOST, mysql_error(con));
  }


// Prepare an INSERT query with 1 parameters

stmt = mysql_stmt_init(con);
if(!stmt) {
    fprintf(stderr, "mysql_stmt_init(), out of memory \n");
    //exit(0);
    return INVALID;
}

if(mysql_stmt_prepare(stmt, UPDATE_STATUS, strlen(UPDATE_STATUS))) {

    fprintf(stderr, "mysql_stmt_prepare(), UPDATE failed\n");
    fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    //exit(0);
    return INVALID;
}

fprintf(stdout, "prepare, UPDATE statement successful\n");

//Get the parameter count from the statement

param_count = mysql_stmt_param_count(stmt);
fprintf(stdout, " total parameters in UPDATE: %d\n", param_count);


//validate parameter count
if(param_count != 1) {
    fprintf(stderr, " invalid parameter count returned by MySQL\n");
    //exit(0);
    return INVALID;
}

//Bind the data for 1 parameter

memset(bind, 0, sizeof(bind));

//INTEGER PARAMETER
//This is a number type so there is no need
// to specify buffer_length

bind[0].buffer_type = MYSQL_TYPE_LONG;
bind[0].buffer      = (char *)&id_data;
bind[0].is_null     = 0;
bind[0].length      = 0;

//Bind the buffers

if(mysql_stmt_bind_param(stmt, bind)) {
    fprintf(stderr, " mysql_stmt_bind_param() failed\n");
    fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    //exit(0);
    return INVALID;
}

// Specify the data values for the first row

  id_data = id;


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
    //exit(0);
    return INVALID;
}

//close con
mysql_close(con);

return VALID;

}
