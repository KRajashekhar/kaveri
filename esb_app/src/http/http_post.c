/*#include<stdio.h>
#include<curl/curl.h>

int main(void)
{
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl,CURLOPT_URL, "enter a valid url");
        curl_easy_setopt(curl,CURLOPT_POSTFEILDS,"field1=value1&field2=value2"); //field =payload and value be 001-1234
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            fprintf(stderr,"curl_easy_perform() failed %s\n",curl_easy_strerror(res));
            
        }
        curl_easy_cleanup(curl);
        
    }
        curl_global_cleanup(curl);
        return 0;
}
*/