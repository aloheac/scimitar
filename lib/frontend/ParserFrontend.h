/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Parser frontend.
 *
 *    DESCRIPTION: This header file defines functions which serve as the "frontend" or user-facing access to the parser.
 *                 The available functions accept source code as input and provide a compiled output as a result.
 *
 *    CREATION DATE: November 22, 2019
 *
 *********************************************************************************************************************/


#ifndef SCIMITAR7_PARSERFRONTEND_H
#define SCIMITAR7_PARSERFRONTEND_H

#include "../language/ArithmeticExpression.h"
#include "../language/LoopStatement.h"


/**
 * Parses an arithmetic expression provided as source code and returns the corresponding binary tree which will evaluate
 * the passed expression. The returned pointer corresponds to the root node of the expression tree.
 * @param expr The expression to be parsed as a string of source code.
 * @return Pointer to the corresponding expression tree.
 */
std::shared_ptr<ArithmeticExpression> parse_expression( std::string expr );


/**
 * Parses and evaluates an arithmetic expression which is only a function of literal values (e.g., the expression does
 * not reference variables which would be defined in the context of a variable scope). The expression is evaluated to
 * a double-precision floating point value, which is returned. This function calls parse_expression() and evaluates the
 * returned tree.
 * @param expr The expression of numerical literals to evaluate.
 * @return The evaluated result of the expression as a floating-point value.
 */
double evaluate_expression_literal( std::string expr );


/**
 * High-level function which performs the end-to-end compilation of a source file in the target language. The
 * compilation returns valid Python code which defines variables indicating the list of jobs to be executed, the
 * directory order of parameters, defined options, and a status code indicating success or failure of the compilation.
 *
 * If the compilation is successful, the following variables are defined in the returned string:
 *     - RUN_LISTING : A Python list of dictionaries where each element of the list defines the parameter values for a
 *                     unique execution of the target simulation program. Each element is a Python dictionary, in which
 *                     one element exists for each defined parameter. The dictionary key is the identifier of the
 *                     parameter, and the corresponding value is the value of that parameter for the run.
 *
 *     - DIR_ORDER : A Python list of parameter identifiers, where the order of the identifiers indicates the order of
 *                   nested directories which form the directory structure of all executed simulations. For instance, if
 *                   DIR_ORDER = ["a", "b"], then the resulting generated directories would be "a_0/b_0", "a_0/b_1",
 *                   "a_1/b_0", etc.
 *
 *     - OPTION : A Python dictionary of script options specified by the user, where the key is the identifier of the
 *                option, and the value is the specified option value.
 *
 *     - STATUS : An integer specifying the type of error that has occurred during compilation. If no error occurs, this
 *                value will be 0.
 *
 * If the compilation is not successful, the following variables will be defined in the returned string:
 *     - STATUS : An integer specifying the type of error that has occurred during compilation. A return result of 1
 *                indicates a parsing error, 2 indicates an engine logic error, and 3 indicates a compilation error.
 *
 *     - ERROR_MSG : A string providing a more detailed description of the error that was encountered.
 * @param expr Source code in the target language to be parsed and compiled.
 * @return The result of the compilation as a string containing valid Python code defining a sequence of variables.
 */
std::string evaluate_job( std::string expr );

#endif //SCIMITAR7_PARSERFRONTEND_H
