/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Parser frontend implementations.
 *
 *    DESCRIPTION: This file implements functions which serve as the "frontend" or user-facing access to the parser. The
 *                 available functions accept source code as input and provide a compiled output as a result.
 *
 *    CREATION DATE: November 22, 2019
 *
 *********************************************************************************************************************/

#include <memory>
#include "ParserFrontend.h"
#include "SourceFileStream.h"
#include "../engine/Engine.h"
#include <antlr4-runtime.h>
#include "../grammar/GrammarErrorHandler.h"
#include "../grammar/ScimitarLexer.h"
#include "../grammar/ScimitarParser.h"
#include "../grammar/ScimitarBaseVisitor.h"

std::shared_ptr<ArithmeticExpression> parse_expression( std::string str_expr ) {
    antlr4::ANTLRInputStream input( str_expr );
    ScimitarLexer lexer( &input );
    antlr4::CommonTokenStream tokens( &lexer );
    tokens.fill();

    ScimitarParser parser( &tokens );
    parser.removeErrorListeners();
    GrammarErrorHandler parseErrorHandler;
    parser.addErrorListener( &parseErrorHandler );

    antlr4::tree::ParseTree* tree = parser.expr();

    ScimitarBaseVisitor visitor;
    std::shared_ptr<ArithmeticExpression> result = visitor.visit( tree );

    return result;
}

double evaluate_expression_literal( std::string expr ) {
    std::shared_ptr<ArithmeticExpression> expr_ast = parse_expression( expr );
    return expr_ast->evaluate_literal();
}

std::string evaluate_job( std::string source ) {
    Engine engine;
    std::stringstream result_string;

    bool encounteredError = false;  // Flag to indicate whether a compilation error has happened.
    antlr4::ANTLRInputStream input( source );
    GrammarErrorHandler errorHandler;

    try {

        // Set up and execute the lexer.
        ScimitarLexer lexer( &input );
        lexer.removeErrorListeners();  // Remove all default error listeners, and add our own.
        lexer.addErrorListener( &errorHandler );
        antlr4::CommonTokenStream tokens( &lexer );
        tokens.fill();

        // Set up and execute the parser.
        ScimitarParser parser( &tokens );
        parser.removeErrorListeners();  // Remove all default error listeners, and add our own.
        parser.addErrorListener( &errorHandler );

        antlr4::tree::ParseTree* tree = parser.root();  // Build the syntax tree.

        // Visit nodes of the tree and build EngineAction components.
        ScimitarBaseVisitor eval;
        eval.visit( tree );

        std::vector< std::shared_ptr<EngineAction> > actions = eval.get_result();

        for ( auto action : actions ) {
            action->execute( &engine );
        }

    } catch ( GrammarException &e ) {

        encounteredError = true;
        result_string << "STATUS = 1" << std::endl << "ERROR_MSG = \"" << e.what() << "\"";

    } catch ( EngineException &e ) {

        encounteredError = true;
        result_string << "STATUS = 2" << std::endl << "ERROR_MSG = \"" << e.what() << "\"";

    } catch ( ParameterValueException &e ) {

        encounteredError = true;
        result_string << "STATUS = 2" << std::endl << "ERROR_MSG = \"" << e.what() << "\"";

    }

    if ( not encounteredError ) {  // If we haven't encountered a parsing error, continue to execute the engine.
        ExecutionResult result;

        try {

            result = engine.execute();

        } catch ( EngineException &e ) {

            encounteredError = true;
            result_string << "STATUS = 3" << std::endl << "ERROR_MSG = \"" << e.what() << "\"";

        }

        // If we reached this point, everything completed successfully.
        if ( not encounteredError ) result_string << "STATUS = 0" << std::endl << result.emit();
    }

    return result_string.str();
}