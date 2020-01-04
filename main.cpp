#include <iostream>
#include <stdio.h>
#include "curl/curl.h"
#include "functions.h"
#include <utility>

enum statusCode {
    OK,
    NO_CMD_FND,
    INV_INP
};

enum commandList {
        cmd_create,
        cmd_login,
        cmd_sendMessage,
        cmd_getMessages,
        cmd_ping,
        cmd_chkspd,
        cmd_fileupload,
        cmd_invalid
};
commandList hashIt(std::string const& cmd){
    if(cmd == "create") return cmd_create;
    if(cmd == "login")  return cmd_login;
    if(cmd == "m")      return cmd_sendMessage;
    if(cmd == "g")      return cmd_getMessages;
    if(cmd == "ping")   return cmd_ping;
    if(cmd == "checkspeed") return cmd_chkspd;
    if(cmd == "fileupload") return cmd_fileupload;
    else                return cmd_invalid;
}
int main(int argc,char* argv[])
{   
    CURLcode res;
    std::string input;
    std::pair<std::vector<std::string>,int> tokens;
    if(argc == 1){
            std::getline(std::cin,input);
            tokens = inputParse(input);
            if(tokens.second == NO_CMD_FND) {
                std::cout<<"No Command Found. Type -help for help."<<std::endl;
                return 0;
            }
            else if(tokens.second == INV_INP) {
                std::cout<<"Invalid Input. Type -help for help."<<std::endl;
                return 0;
            }
    }
    else    
        for(int i =1;i < argc; ++i) 
            tokens.first.push_back(argv[i]);
    // for(std::vector<std::string>::iterator it = tokens.first.begin(); it != tokens.first.end(); ++it){
    //     if(it[0])
    // }
    for(std::string &i : tokens.first)
        std::cout<<i<<std::endl;
    switch(hashIt(tokens.first[0])) {
    case cmd_create     :
                        res = create(tokens.first[1],tokens.first[2]);
                        if(res != CURLE_OK)
                          fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nSuccessfully created account");
                        break;
    case cmd_login      :
                        {
                        std::string u(""),p("");
                        if(tokens.first.size() == 1)
                            res = login(u,p);
                        else
                            res = login(tokens.first[1],tokens.first[2]);
                        if(res != CURLE_OK)
                            fprintf(stderr, "curl_easy_perform() failed: %s\n",curl_easy_strerror(res));
                        else
                            printf("\nLogin Successful");
                        break;
                        }
    case cmd_sendMessage:
                        {
                            std::string message;
                            for(unsigned int i = 2 ; i < tokens.first.size(); i++)
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
                            printf("\nSuccessfully pinged %s",tokens.first[1].c_str());
                        break;
    case cmd_fileupload:{
                        char* name = "makefile";
                        fileupload(argv[2]);
                        break;
                        }

    case cmd_chkspd     :
                        check_speed(1,argv);
                        break;
    case cmd_invalid    :
                        printf("\nInvalid Command Entered");
                        break;
    }
    std::cin.get();
}
