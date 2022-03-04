#pragma once

#include <StatusMachine.hpp>
#include <Token.hpp>
#include <functional>
#include <list>
namespace lab {

#define TypeMap(XX)                                                                                \
        XX(Identifier, Identifier)                                                                 \
        XX(Operator, Operator)                                                                     \
        XX(IntLiteral, IntLiteral)                                                                 \
        XX(Int,Int)


enum Type {
    #define XX(name,str) name,
    TypeMap(XX)
    #undef XX 
};

enum class State {
    Initial,
    Id,
    Int,
    Int1,
    Int2,
    Int3,
    IntLiteral,
    Plus,           //  +
    Sub,            //  -
    Mul,            //  *
    Divide,         //  /
    LeftParen,      //  (
    RightParen,     //  )
    Assignment,     //  =
    SemiColon,      //  ;
    GreaterThan,    //  >
    GreaterEqual,   //  >=
    LessThan,       //  <   
    LessEqual,      //  <=
    Equal           //  ==
};


class Lexer : public StatusMachine<State, char, std::function<State(char)>> {
public:
    using Token = lab::Token<Type>;
    using TokenObserver = std::function<void(const std::string&)>;
    using TokenList = std::list<Token>;
    Lexer();
    Lexer(const TokenObserver& observer);

    Lexer(const Lexer&) = delete;
    Lexer& operator=(const Lexer&) = delete;
    Lexer(Lexer&&) = delete;
    Lexer& operator=(Lexer&&) = delete;

    virtual bool Post(char c) override;

    const TokenList& getTokens() const {
        return tokens_;
    }

private:
    void RegisterHandlers();
    void FinishParserToken();
    StateType OperatorToState(char c);
    //handlers
    StateType InitialHandle(char c);
private:
    Token token_;
    TokenList tokens_;
    TokenObserver token_observer_;
};

}   // namespace lab