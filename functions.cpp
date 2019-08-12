#include "functions.h"
#include<curl/curl.h>
#include <iostream>
#include <fstream>
#include <cstring>
#define MAX 400
std::string URL("http://localhost:3000/api/v1/");
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    std::ofstream fout("token.bin",std::ios::binary);
    std::string data(ptr);
    std::cout<<"Token Recieved: "<<data<<std::endl;
    fout.write(reinterpret_cast<char*>(&data),MAX*sizeof(char));
    fout.close();
    return strlen(ptr);
}
CURLcode sendMessage(std::string message,std::string reciever){
        printf("\nSendMessage route initiated");
        CURL *curl;
        curl = curl_easy_init();
        CURLcode result;
        const char* path = "token.bin";
        std::string header;
        std::ifstream fin(path,std::ios::binary);
        if(fin.is_open()){
            printf("\n Token Files opened");
            std::string token;
            fin.read(reinterpret_cast<char*>(&token),MAX*sizeof(char));
            fin.close();
            printf("\nAvailable token: %s",token.c_str());
            header = "Authorization: "+token;
        } else {
            perror(path);
        }
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk,header.c_str());
        std::string finalURL = URL + "sendMessage";
        std::string data = "reciever="+reciever+"&message="+message;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
        curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
        result = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        return result;
}


CURLcode create(std::string username,std::string password){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    std::string finalURL = URL + "create";
    std::string data = "username="+username+"&password="+password;
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return result;
}

CURLcode login(std::string username,std::string password){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    char* userdata;
    std::string finalURL = URL + "login";
    std::string data = "username="+username+"&password="+password;
    curl_easy_setopt(curl,CURLOPT_POSTFIELDS,data.c_str());
    curl_easy_setopt(curl,CURLOPT_URL,finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,userdata);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return result;
}

CURLcode getMessages(std::string username){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    curl_slist *chunk = NULL;
    std::string finalURL = URL+"getMessages";
    std::string data = "username="+username;
    std::string token;
    std::ifstream fin("token.bin",std::ios::binary);
    fin.read(reinterpret_cast<char*>(&token),MAX*sizeof(char));
    fin.close();
    std::string header = "Authorization: "+token;
    chunk = curl_slist_append(chunk,header.c_str());
    curl_easy_setopt(curl,CURLOPT_URL,finalURL);curl_easy_setopt(curl,CURLOPT_POSTFIELDS,data.c_str());
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
    result = curl_easy_perform(curl);
    return result;
}


