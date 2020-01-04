#include "functions.h"

using namespace std;



size_t getMessages_callback(char* ptr,size_t size,size_t nmemb, void *userdata){
    std::cout<<ptr<<std::endl;
    return strlen(ptr);
}



CURLcode getMessages(std::string convId,string username =  ""){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    curl_slist *chunk = NULL;
    char* userdata=NULL;
    std::string finalURL = URL+"getMessages/";
    std::string data = "?username="+username;
    finalURL+=data;
    std::string token = getToken();
    std::string header = "Authorization: Bearer "+token;
    chunk = curl_slist_append(chunk,header.c_str());
    chunk = curl_slist_append(chunk,convId.c_str());
    curl_easy_setopt(curl,CURLOPT_URL,finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,userdata);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getMessages_callback);
    curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result = curl_easy_perform(curl);
    return result;
}
