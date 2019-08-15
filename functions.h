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
    std::pair<std::vector<std::string>,int> inputParse(std::string const&);
#endif // FUNCTIONS_H
