#include<stdio.h>
#include<curl/curl.h>
int main()
{
	CURL *curl;
	CURLcode res;
    struct curl_slist *headers=NULL; 
   headers = curl_slist_append(headers, "Accept: application/json");  
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, "charset: utf-8"); 
	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl)
	{

curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl,CURLOPT_URL,"https://ifsc.razorpay.com/");
		curl_easy_setopt(curl,CURLOPT_HTTPGET,"IDIB000V086");
		res=curl_easy_perform(curl);
		if(res!=CURLE_OK)
		{
			fprintf(stderr,"curl failed %s\n",curl_easy_strerror(res));
			}
		curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
		return 0;
}
