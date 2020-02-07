#include <iostream>
#include <stdio.h>
#include "curl/curl.h"
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
int main(int argc,char* argv[])
{   
    CURLcode res;
    std::string input;
    std::vector<std::string> tokens;
    if(argc == 1){
            std::getline(std::cin,input);
            tokens = inputParse(input);
    }
    else    
        for(int i =1;i < argc; ++i) 
            tokens.push_back(argv[i]);
    for(std::string &i : tokens)
        std::cout<<i<<std::endl;
    switch(hashIt(tokens[0])) {
    case cmd_create     :
                        res = create(tokens[1],tokens[2]);
                        if(res != CURLE_OK)
                          fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nSuccessfully created account");
                        break;
    case cmd_login      :
                        {
                        std::string u(""),p("");
                        if(tokens.size() == 1)
                            res = login(u,p);
                        else
                            res = login(tokens[1],tokens[2]);
                        if(res != CURLE_OK)
                            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nLogin Successful");
                        break;
                        }
    case cmd_sendMessage:
                        {
                            std::string message;
                            for(unsigned int i = 2 ; i < tokens.size(); i++)
                                    message += tokens[i]+" ";
                            res = sendMessage(tokens[1],message);
                            if(res != CURLE_OK)
                                fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                            else
                                printf("\nSuccessfully sent the message");
                            break;
                        }
    case cmd_getMessages:{
                            res = getMessages(tokens.size() > 1 ? tokens[1] : std::string(""));
                            if(res != CURLE_OK)
                            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                            else
                                printf("\nSuccessfully sent the message");
                            break;
                        }
    case cmd_ping       :{
                            res = ping(tokens[1]);
                            if(res != CURLE_OK)
                                fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                            else
                                printf("\nSuccessfully pinged %s",tokens[1].c_str());
                            break;
                        }
    case cmd_invalid    :
                        printf("\nInvalid Command Entered");
                        break;
    }
    std::cin.get();
}
