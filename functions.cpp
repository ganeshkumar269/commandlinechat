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
CURLcode sendMessage(std::string sender,std::string message,std::string reciever){
        CURL *curl;
        curl = curl_easy_init();
        CURLcode result;
        std::string finalURL = URL + "sendMessage";
        std::string data = "sender="+sender+"&message="+message+"&reciever="+reciever;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());
        curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
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
    std::string data = "username="+username+"&password"+password;
    curl_easy_setopt(curl,CURLOPT_POSTFIELDS,data.c_str());
    curl_easy_setopt(curl,CURLOPT_URL,finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,userdata);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return result;
}


