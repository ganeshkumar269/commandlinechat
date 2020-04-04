#include "functions.hpp"
#include <cstring>


CURLcode sendMessage(std::string convId,std::string message){
        printf("\nSendMessage route initiated");
        CURL *curl;
        curl = curl_easy_init();
        CURLcode result;
        std::string token = getToken();
        std::string token_header = "Authorization: Bearer "+token;
        std::string convId_header = "convId: "+convId;
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk,token_header.c_str());
        chunk = curl_slist_append(chunk,convId_header.c_str());
        std::string finalURL = URL + "sendMessage";
        std::string data = "message="+message;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
        // curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
        curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
        result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return result;
}
