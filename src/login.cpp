#include "functions.h"

size_t login_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    std::ofstream fout("token.bin",std::ios::binary);
    if(!fout) std::cout<<"Error occured in token"<<std::endl;
    else{
        std::cout<<"Token Recieved: "<<ptr<<std::endl;
        fout<<ptr<<std::endl;
        fout.close();
    }
    return strlen(ptr);
}

CURLcode login(std::string username,std::string password){
    CURL *curl;
    curl = curl_easy_init();
    CURLcode result;
    char* userdata=NULL;
    if(username.length() == 0){
        std::cout<<"\nEnter UserName:";
        std::getline(std::cin,username);
        std::cout<<"\nEnter Password:";
        std::getline(std::cin,password);
    }
    std::string finalURL = URL + "login";
    std::string data = "username="+username+"&password="+password;
    curl_easy_setopt(curl,CURLOPT_POSTFIELDS,data.c_str());
    curl_easy_setopt(curl,CURLOPT_URL,finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,userdata);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,login_callback);
    curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return result;
}