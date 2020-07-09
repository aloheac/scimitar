//
// Created by loheac on 12/12/19.
//

#ifndef SCIMITAR7_GRAMMARERRORHANDLER_H
#define SCIMITAR7_GRAMMARERRORHANDLER_H

#include <antlr4-runtime.h>

class GrammarException : public std::exception {
public:

    GrammarException( std::string msg );

    virtual const char* what() const throw();

private:

    std::string msg;
};


class GrammarErrorHandler : public antlr4::BaseErrorListener {
public:

    GrammarErrorHandler();

    void syntaxError( antlr4::Recognizer* recognizer, antlr4::Token* token, size_t line, size_t charPositionInLine,
            const std::string &msg, std::exception_ptr e ) override;

};

#endif //SCIMITAR7_GRAMMARERRORHANDLER_H
