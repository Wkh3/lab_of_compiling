#include <CharParser.hpp>
#include <Lexer.hpp>
#include <iostream>
namespace lab {


template <>
class TypeCast<Type> {
public:
    std::string operator()(const Type& type) {
#define XX(name, str)                                                                              \
    case name:                                                                                     \
        return #str;
        switch (type) { TypeMap(XX) default : return "unknow"; }
#undef XX
    }
};

Lexer::Lexer() {
    RegisterHandlers();
}

Lexer::Lexer(const TokenObserver& observer) : token_observer_(observer) {
    RegisterHandlers();
}

bool Lexer::Post(char c) {
    auto it = handlers_.find(state_);

    if (it == handlers_.end()) return false;

    state_ = it->second(c);

    return true;
}

void Lexer::FinishParserToken() {
    if (!token_.getValue().empty()) {
        if (token_observer_) {
            token_observer_(token_.toString());
        }
        tokens_.push_back(std::move(token_));
    }
}

Lexer::StateType Lexer::OperatorToState(char c){
    switch (c) {
            case '+':
                return StateType::Plus;
            case '-':
                return StateType::Sub;
            case '*':
                return StateType::Mul;
            case '/':
                return StateType::Divide;
            case '=':
                return StateType::Assignment;
            case ';':
                return StateType::SemiColon;
            case '(':
                return StateType::LeftParen;
            case ')':
                return StateType::RightParen;
            case '>':
                return StateType::GreaterThan;
            case '<':
                return StateType::LessThan;
            default:
                return StateType::Initial;
    }
}
Lexer::StateType Lexer::InitialHandle(char c) {
    auto type = CharParser()(c);

    if (type == CharParser::Blanck) {
        FinishParserToken();
        return StateType::Initial;
    }

    if (type == CharParser::Alpha) {
        token_.setType(Type::Identifier);
        token_ >> c;
        return c == 'i' ? StateType::Int1 : StateType::Id;
    } else if (type == CharParser::Digit) {
        token_.setType(Type::IntLiteral);
        token_ >> c;
        return StateType::IntLiteral;
    } else if (type == CharParser::Operator) {
        token_ >> c;
        token_.setType(Type::Operator);
        return OperatorToState(c);
    }

    return StateType::Initial;
}

void Lexer::RegisterHandlers() {
    state_ = State::Initial;

    Register(StateType::Initial, [this](char c) { return InitialHandle(c); });

    Register(StateType::Id, [this](char c) {
        auto type = CharParser()(c);
        if (type == CharParser::Blanck || c == ';') {
            FinishParserToken();
            return StateType::Initial;
        }

        token_ >> c;
        return state_;
    });

    Register(StateType::Assignment, [this](char c) {
        if (c != '=') {
            FinishParserToken();
            return StateType::Initial;
        } else {
            token_ >> c;
            return StateType::Equal;
        }
    });

    Register(StateType::GreaterThan, [this](char c) {
        if (c != '=') {
            FinishParserToken();
            return InitialHandle(c);
        } else {
            token_ >> c;
            return StateType::GreaterEqual;
        }
    });

    Register(StateType::LessThan, [this](char c) {
        if (c != '=') {
            FinishParserToken();
            return InitialHandle(c);
        } else {
            token_ >> c;
            return StateType::LessEqual;
        }
    });

    Register(StateType::IntLiteral,[this](char c){
        auto type = CharParser()(c);
        if(type != CharParser::Digit){
            FinishParserToken();
            return InitialHandle(c);
        }

        token_ >> c;

        return state_;
    });

    Register(StateType::Int1,[this](char c){
        auto type = CharParser()(c);

        if(type == CharParser::Blanck || c == ';')
        {
            FinishParserToken();
            return InitialHandle(c);
        }

        token_ >> c;

        return c == 'n' ? StateType::Int2 : StateType::Id;
    });

    Register(StateType::Int2,[this](char c){
        auto type = CharParser()(c);

        if(type == CharParser::Blanck || c == ';')
        {
            FinishParserToken();
            return InitialHandle(c);
        }

        token_ >> c;

        return c == 't' ? StateType::Int3 : StateType::Id;
    });

    Register(StateType::Int3,[this](char c){
        token_.setType(Type::Int);

        return InitialHandle(c);
    });

    auto operator_func = [this](char c){
        FinishParserToken();
        return InitialHandle(c);
    };

    Register(StateType::Mul,operator_func);
    Register(StateType::Plus,operator_func);
    Register(StateType::Sub,operator_func);
    Register(StateType::Divide,operator_func);
    Register(StateType::RightParen,operator_func);
    Register(StateType::LeftParen,operator_func);
    Register(StateType::LessEqual,operator_func);
    Register(StateType::GreaterEqual,operator_func);
    Register(StateType::Equal,operator_func);
    
}


}   // namespace lab