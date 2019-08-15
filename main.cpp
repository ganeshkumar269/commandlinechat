#include <stdio.h>
#include <curl/curl.h>
#include "functions.h"
#include <utility>

enum commandList {
        cmd_create,
        cmd_login,
        cmd_sendMessage,
        cmd_getMessages,
        cmd_ping,
        cmd_invalid
};
commandList hashIt(std::string const& cmd){
    if(cmd == "create") return cmd_create;
    if(cmd == "login")  return cmd_login;
    if(cmd == "m")      return cmd_sendMessage;
    if(cmd == "g")      return cmd_getMessages;
    if(cmd == "ping")   return cmd_ping;
    else                return cmd_invalid;
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
                        {
                            std::string message;
                            for(int i = 2 ; i < tokens.first.size(); i++)
                                    message += tokens.first[i]+" ";
                            res = sendMessage(tokens.first[1],message);
                            if(res != CURLE_OK)
                                fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                            else
                                printf("\nSuccessfully sent the message");
                            break;
                        }
    case cmd_getMessages:
                        res = getMessages(tokens.first[1]);
                        if(res != CURLE_OK)
                          fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nSuccessfully sent the message");
                        break;
    case cmd_ping       :
                        res = ping(tokens.first[1]);
                        if(res != CURLE_OK)
                            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nSuccessfully pinged %s",tokens.first[1]);
                        break;
    case cmd_invalid    :
                        printf("\nInvalid Command Entered");
                        break;
    }
}
