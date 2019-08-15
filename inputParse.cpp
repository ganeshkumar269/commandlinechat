#include "functions.h"

enum statusCode {
    OKAY,
    NO_CMD_FND,
    INV_INP
};

//status code: 0 - everything okay
//             1 - no cmd found
//             2 - invalid input string


std::pair<std::vector<std::string>,int> inputParse(std::string const& input){
    std::vector<std::string> tokens;
    int pos = input.find('-');
    if(pos == std::string::npos)
        return std::make_pair(tokens,NO_CMD_FND);
    for(int i = 0; i< pos; i++)
        if(input[i] != 32)
            return std::make_pair(tokens,INV_INP);
    int t = 0;
    for(int curr_pos = pos+1; curr_pos < input.length(); ){
        std::string nexttoken = (t = input.find(32,curr_pos)) != std::string::npos
        ? input.substr(curr_pos, t - curr_pos) : input.substr(curr_pos);
        std::cout<<"token: "<<nexttoken<<'\t'<<nexttoken.length()<<" Current Position: "<<curr_pos<<std::endl;
        curr_pos += nexttoken.length()+1;
        if(nexttoken.length() != 0)
            tokens.push_back(nexttoken);
    }
    return std::make_pair(tokens,OKAY);
}

