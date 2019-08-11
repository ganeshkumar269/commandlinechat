#include <stdio.h>
#include <curl/curl.h>
#include "functions.h"
#include <curl/curlbuild.h>
#include <utility>

enum commandList {
        cmd_create,
        cmd_login,
        cmd_sendMessage,
        cmd_invalid
};
commandList hashIt(std::string const& cmd){
    if(cmd == "create") return cmd_create;
    if(cmd == "login") return cmd_login;
    if(cmd == "sendMessage") return cmd_sendMessage;
    else return cmd_invalid;
}
int main(void)
{
    std::string input;
    std::getline(std::cin,input);
    std::pair<std::vector<std::string>,int> tokens = inputParse(input);
    CURLcode res;
    switch(hashIt(tokens.first[0])) {
    case cmd_create     :
                        res = create(tokens.first[1],tokens.first[2]);
                        if(res != CURLE_OK)
                          fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nSuccessfully created account");
                        break;
    case cmd_login      :
                        res = login(tokens.first[1],tokens.first[2]);
                        if(res != CURLE_OK)
                            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nLogin Successful");
                        break;
    case cmd_sendMessage:
                        res = sendMessage(tokens.first[1],tokens.first[2],tokens.first[3]);
                        if(res != CURLE_OK)
                          fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nSuccessfully sent the message");
                        break;
    case cmd_invalid    :
                        std::cout<<"Invalid command Entered"<<std::endl;
    }
    /*CURLcode res = sendMessage("ganesh","what is up fam","kumar");
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
    else
        printf("\nUnsuccessful");
    return 0;*/
}
