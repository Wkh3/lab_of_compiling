#include <Lexer.hpp>
#include <Terminal.hpp>
#include <Token.hpp>

int main() {
    lab::Terminal terminal;
    lab::Lexer lexer([&terminal](const std::string& str) { terminal.OutPut(str); });

    while (1) {
        std::string str = terminal.Input();

        for (char c : str) lexer.Post(c);
    }
    return 0;
}