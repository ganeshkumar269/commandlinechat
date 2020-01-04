#include "functions.h"




std::string getToken(){
    char token[200];
    std::string token_string("");
    std::ifstream fin("token.bin",std::ios::binary);
    if(!fin) std::cout<<"Error occured in opening token"<<std::endl;
    else{
        fin.seekg(0,std::ios::end);
        int n = fin.tellg();
        fin.seekg(0,std::ios::beg);
        fin.getline(token,n);
        fin.close();
        token_string = token;
    }
    return token_string;
}
