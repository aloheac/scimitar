//
// Created by loheac on 12/12/19.
//

#include <sstream>
#include "GrammarErrorHandler.h"

GrammarException::GrammarException( std::string this_msg ) : std::exception(), msg( this_msg ) { }

const char* GrammarException::what() const throw() {
    return msg.c_str();
}

GrammarErrorHandler::GrammarErrorHandler() : antlr4::BaseErrorListener() { }

void GrammarErrorHandler::syntaxError( antlr4::Recognizer* recognizer, antlr4::Token* token, size_t line,
                                       size_t charPositionInLine, const std::string &msg, std::exception_ptr e ) {
    std::stringstream error_msg;
    error_msg << "line " << line << ":" << charPositionInLine << " - " << msg;

    throw GrammarException( error_msg.str() );
}
