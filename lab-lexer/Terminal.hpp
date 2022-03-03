
#pragma once
#include <iostream>
namespace lab {
class Terminal {
public:
    Terminal(const std::string &tag = "< ", const std::string &start_msg = "welcome to use lexer!")
        : tag_(tag), start_msg_(start_msg) {
            OutPutStartMsg();
        }

    std::string Input() {
        std::string str;
        std::getline(std::cin, str);
        OutPutTag();
        return str;
    }

    void OutPut(const std::string &str){
         std::cout << str << std::endl;
         OutPutTag();
    }
private:
    void OutPutTag(){
        std::cout << tag_;
    }
    void OutPutStartMsg(){
        OutPutTag();
        std::cout << start_msg_ << std::endl;
        OutPutTag();
    }
private:
    std::string tag_;
    std::string start_msg_;
};

}   // namespace lab