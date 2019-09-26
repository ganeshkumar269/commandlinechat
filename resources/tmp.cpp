#include "dependencies/rapidjson/document.h"
#include "dependencies/rapidjson/writer.h"
#include "dependencies/rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
using namespace rapidjson;
int main() {
    // 1. Parse a JSON string into DOM.
    std::ifstream fin("json.txt");
    std::string t;
    char json[1000];
    fin.getline(json,1000);
    Document d;
    d.Parse(json);
    // 2. Modify it by DOM.
    Value& s = d["messages"];
    s[0]["_id"].SetString("WOrking broda2");
    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);
    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
    return 0;
}


