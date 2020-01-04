#include "functions.h"
using namespace std;

std::pair<std::vector<std::string>,int> inputParse(std::string  input){
    vector<string> tokens;
    uint32_t i =0,start = -1;
    while(i<input.size()){
        if(input[i] != ' '){
            start = i;
            for(;i<input.size() and input[i] != ' ';i++);
            tokens.push_back(input.substr(start,i-start));
        }
        i++;
    }
    return {tokens,OK};
}


