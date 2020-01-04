#include "functions.h"

CURLcode create(std::string username,std::string password){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    std::string finalURL = URL + "create";
    std::string data = "username="+username+"&password="+password;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return result;
}