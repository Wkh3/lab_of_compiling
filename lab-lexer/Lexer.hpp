#pragma once

#include <StatusMachine.hpp>
#include <Token.hpp>
#include <functional>
#include <list>
namespace lab {

enum Type {

};

enum State {

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

private:
    Token token_;
    TokenList tokens_;
    TokenObserver token_observer_;
};

}   // namespace lab