#include "functions.h"


CURLcode sendMessage(std::string username,std::string message){
        printf("\nSendMessage route initiated");
        CURL *curl;
        curl = curl_easy_init();
        CURLcode result;
        std::string token = getToken();
        std::string header = "Authorization: Bearer "+token;
        std::cout<<header<<std::endl;
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk,header.c_str());
        std::string finalURL = URL + "sendMessage";
        std::string data = "username="+username+"&message="+message;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
        curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
        curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
        result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return result;
}
