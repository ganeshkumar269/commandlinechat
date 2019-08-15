#include <iostream>
#include <curl/curl.h>
#include <cstring>
#include <fstream>
#include <iomanip>
#define MAX 100
using namespace std;
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata){
    ofstream fout("token2.txt");
    string data(ptr);
    cout<<"String: "<<data<<endl;
    fout.write(reinterpret_cast<char*>(&data),MAX*sizeof(char));
    fout.close();
    ifstream fin("token2.txt");
    fin.read(reinterpret_cast<char*>(&data),MAX*sizeof(char));
    cout<<"Read String: "<<data<<endl;
    fin.close();
    return strlen(ptr);
}

string readthestring(){
    ifstream fin("token2.txt");
    string data;
    fin.read(reinterpret_cast<char*>(&data),MAX*sizeof(char));
    cout<<data<<endl;
    fin.close();
    data = data+"\0";
    return data;
}

int main(){
    CURL *curl;
    curl = curl_easy_init();
    char* data;
    curl_easy_setopt(curl,CURLOPT_URL,"http://localhost:8008/");
    curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,write_callback);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,data);
    CURLcode res = curl_easy_perform(curl);
    fprintf(stderr,"%s",curl_easy_strerror(res));
    cout<<res<<endl;
    cout<<readthestring()<<endl;
    curl_easy_cleanup(curl);
    return 0;
}
