#include<stdio.h>
#include<curl/curl.h>
#include<stdlib.h>
#include<string.h>

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}


int main(void)
{
	CURL *curl;
	CURLcode res;
   // struct curl_slist *headers=NULL; 
   //headers = curl_slist_append(headers, "Accept: application/json");  
    //headers = curl_slist_append(headers, "Content-Type: application/json");
   // headers = curl_slist_append(headers, "charset: utf-8"); 

	curl_global_init(CURL_GLOBAL_ALL);
	curl=curl_easy_init();
	if(curl)
	{
		struct string s;
    	init_string(&s);

//curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl,CURLOPT_URL,"https://ifsc.razorpay.com/IDIB000V086");
		//curl_easy_setopt(curl,CURLOPT_HTTPGET,"001-01-1234");
		curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl,CURLOPT_WRITEDATA,&s);
		res=curl_easy_perform(curl);
		printf("%s\n",s.ptr);
		free(s.ptr);
		if(res!=CURLE_OK)
		{
			fprintf(stderr,"curl failed %s\n",curl_easy_strerror(res));
			}
		curl_easy_cleanup(curl);
		}
		curl_global_cleanup();
		return 0;
}
