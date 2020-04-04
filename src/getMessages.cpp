#include "functions.hpp"
#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;


size_t getMessages_callback(char* ptr,size_t size,size_t nmemb, void *userdata){
    Document document;
    document.Parse(ptr);
    if(document.IsObject() and document.HasMember("data")){
        Value& messages = document["data"]["messages"];
        for ( uint32_t i = 0; i <  messages.Size(); i++){
            cout << i <<". userId:" << messages[i]["userId"].GetString()<< " ";
            cout << messages[i]["body"].GetString() << endl;
        }
    }else
        std::cout<<ptr<<std::endl;
    return strlen(ptr);
}



CURLcode getMessages(std::string convId){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    curl_slist *chunk = NULL;
    char* userdata=NULL;
    std::string finalURL = URL+"getMessages";
    std::string token = getToken();
    std::string token_header = "Authorization: Bearer "+token;
    std::string convId_header = "convId: " + convId;
    chunk = curl_slist_append(chunk,token_header.c_str());
    if(convId.length() > 0)
        chunk = curl_slist_append(chunk,convId_header.c_str());
    curl_easy_setopt(curl,CURLOPT_URL,finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,userdata);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getMessages_callback);
    // curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result = curl_easy_perform(curl);
    return result;
}
