
// @authors Kucharla Rajashekhar and Vinay Prabhakar


#include<stdio.h>
#include<string.h>
#include<curl/curl.h>

#include"email.h"
/*
static size_t payload_source (void *ptr, size_t size, size_t nmemb,void *userp) {
 		struct upload_status *upload_ctx=(struct upload_status *)userp;
 		const char *data;
 		
 		if((size==0)|| (nmemb==0)||((size *nmemb)<1))
 		{
 			return 0;
 		}
 		
 		data =payload_file_path[upload_ctx->lines_read];
 		
 		if(data)
 		{
 			size_t len=strlen(data);
 			memcpy(ptr,data,len);
 			upload_ctx->lines_read++;
 			
 			return len;
 		}
 		
 		return 0;
}
 */
 
int send_mail(char *to,char *file_path)
{
	printf("Sending to %s\n",to);
	
	CURL *curl;
	CURLcode res=CURLE_OK;
	struct curl_slist *recipients =NULL;
	//struct upload_status upload_ctx;
	
	//upload_ctx.lines_read=0;
	
	curl=curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl,CURLOPT_USERNAME,"testmailv1");
		curl_easy_setopt(curl,CURLOPT_PASSWORD,"password");
		
		//smtp url
		curl_easy_setopt(curl,CURLOPT_URL,"smtp://smtp.gmail.com:587/");
		curl_easy_setopt(curl,CURLOPT_USE_SSL,CURLUSESSL_ALL);
		//security certificztion as per ssl
		
		//from address
		curl_easy_setopt(curl,CURLOPT_MAIL_FROM,FROM);
		
		//recipients
		
		recipients=curl_slist_append(recipients,to);
		recipients=curl_slist_append(recipients,CC);
		curl_easy_setopt(curl,CURLOPT_MAIL_RCPT,recipients);
		//now writing a call back function
		
		FILE *fp=fopen(file_path,"r");
		curl_easy_setopt(curl,CURLOPT_READDATA,fp);
		//running information
		curl_easy_setopt(curl,CURLOPT_UPLOAD,1L);
		res=curl_easy_perform(curl);
		
		if(res!=CURLE_OK)
		{	
			fprintf(stderr,"curl_easy_perform() failed %s\n",curl_easy_strerror(res));
			}
		//free
		
		curl_slist_free_all(recipients);
		
		//cleanup
		curl_easy_cleanup(curl);
		}
		
		return (int) res;
}

/*
int main()
{
	char *path=payload_to_xml();
	int t=send_mail("testmailv1@gmail.com","file1.txt");
	printf("%d",t);
	return 0;
	
}
*/
