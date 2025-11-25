#include <iostream>
#include <memory>
#include <string>

#include "Lexer.hpp"
#include "Parser.hpp"
#include "Program.hpp"
#include "Token.hpp"
#include "utils/Error.hpp"

int main() {
  Lexer lexer;
  Parser parser;
  Program program;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line.empty()) {
      continue;
    }
    try {
      // TODO: The main function.
      TokenStream stream = lexer.tokenize(line);
      // BASIC指令
      if (stream.peek()->type == TokenType::RUN) {
        program.run();
      } else if (stream.peek()->type == TokenType::LIST) {
        program.list();
      } else if (stream.peek()->type == TokenType::CLEAR) {
        program.clear();
      } else if (stream.peek()->type == TokenType::QUIT) {
        program.clear();
        exit(0);
      } else if (stream.peek()->type == TokenType::HELP) {
        std::cout << "Contact infinityhty@sjtu.edu.cn for more information!"
                  << std::endl;
      } else {
        ParsedLine parse_line = parser.parseLine(stream, line);
        // 删除一行
        if (parse_line.getStatement() == nullptr &&
            parse_line.getLine().has_value()) {
          program.removeStmt(parse_line.getLine().value());
        }
        // 没有行号的语句(LET,PRINT,INPUT,INDENT,DEDENT)
        else if (!parse_line.getLine().has_value() &&
                 parse_line.getStatement() != nullptr) {
          program.execute(parse_line.getStatement());
        }
        // 有行号的语句
        else {
          //std::cerr << parse_line.getStatement()->text() << std::endl;
          program.addStmt(parse_line.getLine().value(),
                          parse_line.fetchStatement());
        }
      }
    } catch (const BasicError& e) {
      std::cout << e.message() << "\n";
    }
  }
  return 0;
}