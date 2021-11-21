#include "Utils.h"
std::vector<std::string> split(const std::string& str, const std::string& pattern)
{
    //const char* convert to char*
    char* strc = new char[strlen(str.c_str()) + 1];
    strcpy_s(strc,str.size()+1, str.c_str());
    std::vector<std::string> resultVec;
    char* ptr1 = NULL;
    char* tmpStr = strtok_s(strc, pattern.c_str(),&ptr1);
    while (tmpStr != NULL)
    {
        resultVec.push_back(std::string(tmpStr));
        tmpStr = strtok_s(NULL, pattern.c_str(),&ptr1);
    }

    delete[] strc;

    return resultVec;
};


std::string replaceWith(std::string& str,std::string find,std::string replace) {
    int pos;
    pos = str.find(find);
    while (pos != -1) {
        // str.length()求字符的长度，注意str必须是string类型
        str.replace(pos, std::string(find).length(), replace);
        pos = str.find(find);
    }
    return str;
}

