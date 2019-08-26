#include "functions.h"
std::string URL("http://node-server-clc.herokuapp.com/api/v1/");
//std::string URL("http://localhost:3000/api/v1/");
size_t login_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    std::ofstream fout("d:\\codeblocks\\testingCURL\\token.bin",std::ios::binary);
    if(!fout) std::cout<<"Error occured in opening file"<<std::endl;
    else{
        std::cout<<"Token Recieved: "<<ptr<<std::endl;
        fout<<ptr<<std::endl;
        fout.close();
    }
    return strlen(ptr);
}

size_t getMessages_callback(char* ptr,size_t size,size_t nmemb, void *userdata){
    std::cout<<ptr<<std::endl;
    return strlen(ptr);
}

std::string getToken(){
    char token[200];
    std::string token_string("");
    std::ifstream fin("d:\\codeblocks\\testingCURL\\token.bin",std::ios::binary);
    if(!fin) std::cout<<"Error occured in opening token"<<std::endl;
    else{
        fin.seekg(0,std::ios::end);
        int n = fin.tellg();
        fin.seekg(0,std::ios::beg);
        fin.getline(token,n);
        fin.close();
        token_string = token;
    }
    return token_string;
}
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

CURLcode getMessages(std::string username){
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
    curl_easy_setopt(curl,CURLOPT_URL,finalURL.c_str());
    curl_easy_setopt(curl,CURLOPT_HTTPHEADER,chunk);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,userdata);
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,getMessages_callback);
    curl_easy_setopt(curl,CURLOPT_VERBOSE,1L);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result = curl_easy_perform(curl);
    return result;
}

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

