#include "functions.hpp"
#include <string>
#include <vector>
using namespace std;

std::vector<std::string> inputParse(std::string  input){
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
    return tokens;
}


