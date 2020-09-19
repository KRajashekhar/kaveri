// @authors Kucharla Rajashekhar and Vinay Prabhakar


#include<stdio.h>
#include<curl/curl.h>
#include<stdlib.h>
#include<string.h>

#include "http.h"

int http_send_request_2(char *URL)
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_ALL);
    curl=curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl,CURLOPT_URL, "enter a valid url");
        curl_easy_setopt(curl,CURLOPT_POSTFIELDS,"field1=value1&field2=value2"); //field =payload and value be 001-1234
        res=curl_easy_perform(curl);
        if(res!=CURLE_OK)
        {
            fprintf(stderr,"curl_easy_perform() failed %s\n",curl_easy_strerror(res));
            
        }
        curl_easy_cleanup(curl);
        
    }
        curl_global_cleanup();
        return 0;
}
