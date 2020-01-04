#include "functions.h"


CURLcode ping(std::string username){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    curl_slist *chunk = NULL;
    std::string finalURL = URL+"ping/";
    std::string data = "?username="+username;
    finalURL+=data;
    std::string token = getToken();
    std::string header = "Authorization: Bearer "+token;
    chunk = curl_slist_append(chunk,header.c_str());
    curl_easy_setopt(curl,CURLOPT_URL,finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
    curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result = curl_easy_perform(curl);
    return result;
}

