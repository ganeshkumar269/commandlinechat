#ifndef FUNCTIONS_H
#define FUNCTIONS_H
    #include <curl/curl.h>
    #include <string.h>
    #include <iostream>
    #include <vector>
    #include <utility>
    #include <fstream>
    #include <cstring>
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
