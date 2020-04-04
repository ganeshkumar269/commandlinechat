#include <vector>
#include <string>
#include <curl/curl.h>
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
    CURLcode sendMessage(std::string,std::string);
    CURLcode create(std::string,std::string);
    CURLcode login(std::string,std::string);
    CURLcode getMessages(std::string);
    CURLcode ping(std::string);
    std::string getToken();
    std::vector<std::string> inputParse(std::string);

    enum statusCode {
        OK,
        NO_CMD_FND,
        INV_INP
    };
    const std::string URL("http://node-server-t.herokuapp.com/api/v1/");

    //status code: 0 - everything okay
    //             1 - no cmd found
    //             2 - invalid input string

#endif // FUNCTIONS_H
