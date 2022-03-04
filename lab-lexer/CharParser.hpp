#pragma once

namespace lab{

class CharParser{
public:
     enum Type{
         Alpha,
         Digit,
         Blanck,
         Operator,
         Unknow
     };
     
     Type operator()(char ch){

        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
             return Alpha;
         
        if(ch >= '0' && ch <= '9')
           return Digit;

        if(ch == '+' || ch == '<' || ch == '=' || ch == '*'||
           ch == '/' || ch == '-' || ch == '(' || ch == ')'||
           ch == '>')
           return Operator;

        if(ch == ' ' || ch == '\n' || ch == '\t')
          return Blanck;

        return Unknow;
     }
};

}