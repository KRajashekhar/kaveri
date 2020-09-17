
#ifndef _EMAIL_H
#define _EMAIL_H

#include<stdio.h>
#include<stdlib.h>

#define FROM "testmailv1@gmail.com"
#define CC "testmailv2@gmail.com"
#define TO "testmailv3@gmail.com"
struct upload_status
{
	int lines_read;
};
/*
static const char *payload_file_path[]={
 	"Date:Wed,4 Sept 2016 21:45:11 +1100\r\n",
 	"To:" TO "\r\n",
 	"From:"FROM "(example)\r\n",
 	"Cc: " CC "(example)\r\n",
 	"Message-ID:<dc7cb-11db-487a-9f3a-e52a9458ef@"
 	"rfcpedant.example.org>\r\n",
 	"Subject: FTP TLS example message \r\n",
 	"\r\n",
   // empty line to divide headers from body ,see RFC5322 
 	"The message starts from here .\r\n",
 	"\r\n",
 	"It can be bigger that this , continue .\r\n",
 	"Check RFC5322.\r\n",
 	NULL
};
*/

//static size_t payload_source (void *ptr, size_t size, size_t nmemb,void *userp);
int send_mail(char *to,char *file_path);
#endif