/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Arithmetic expression class implementations.
 *
 *    DESCRIPTION: This file provides a series of classes which implement the construction and evaluation of arithmetic
 *                 expressions which are built in terms of a binary tree. The ArithmeticExpression class is a child
 *                 class of the more generic Expression class, and provides a variety of derived types for different
 *                 kinds of operations (binary and unary) and targets of those operations (literals and variables).
 *                 Functions of arithmetic expressions are also provided, such as trigonometric, exponential,
 *                 logarithmic, and statistical distribution functions. These expressions may be evaluated by the
 *                 compiler's engine in terms of Run objects (related to a unique set of parameters to be passed to a
 *                 simulation invocation) or SymbolScope objects (related to a subroutine executed in a user-defined
 *                 function).
 *
 *    CREATION DATE: November 7, 2019
 *
 *********************************************************************************************************************/


#include <cmath>
#include <random>
#include "ArithmeticExpression.h"
#include "../engine/Engine.h"

using namespace std;

/**********************************************************************************************************************
 * ExpressionException Class Implementation
 *********************************************************************************************************************/
ExpressionException::ExpressionException( std::string this_msg ) : exception(), msg( this_msg ) { }

const char* ExpressionException::what() const throw() {
    return msg.c_str();
}


/**********************************************************************************************************************
 * Expression Class Implementation
 *********************************************************************************************************************/
double ArithmeticExpression::EPSILON = 1e-10;

ArithmeticExpression::ArithmeticExpression() : Expression( Expression::Type::ARITHMETIC), expr_type( ExpressionType::BASE ) { }

ArithmeticExpression::ArithmeticExpression( ExpressionType type ) : Expression( Expression::Type::ARITHMETIC ), expr_type( type ) { }

ArithmeticExpression::ArithmeticExpression( ExpressionType type, std::shared_ptr< ArithmeticExpression > left,
        std::shared_ptr< ArithmeticExpression > right ) : Expression( Expression::Type::ARITHMETIC),
        expr_type( type ), left_child( left ), right_child( right ) { }

void ArithmeticExpression::set_left_child( std::shared_ptr< ArithmeticExpression > expr ) {
    left_child = expr;
}

void ArithmeticExpression::set_right_child( std::shared_ptr< ArithmeticExpression > expr ) {
    right_child = expr;
}

double ArithmeticExpression::evaluate( Run state ) {
    return FP_NAN;
}

double ArithmeticExpression::evaluate_literal() {
    Run empty;

    double result;
    try {
        result = evaluate( empty );
    } catch ( ExpressionException e ) {
        throw ExpressionException( "Failed to evaluate expression literal. Parameters may not be referenced in expression literals." );
    }

    return result;
}

ArithmeticExpression::ExpressionType ArithmeticExpression::get_type() {
    return expr_type;
}

/**********************************************************************************************************************
 * ExprOperation Class Implementation
 *********************************************************************************************************************/
ExprOperation::ExprOperation( OperationType op, shared_ptr<ArithmeticExpression> left, shared_ptr<ArithmeticExpression> right )
    : ArithmeticExpression( ExpressionType::OPERATION, left, right ), operation( op ) { }

double ExprOperation::evaluate( Run state ) {
    if ( operation == OperationType::ADD ) {
        return left_child->evaluate( state ) + right_child->evaluate( state );
    } else if ( operation == OperationType::SUBTRACT ) {
        return left_child->evaluate( state ) - right_child->evaluate( state );
    } else if ( operation == OperationType::MULTIPLY ) {
        return left_child->evaluate( state ) * right_child->evaluate( state );
    } else if ( operation == OperationType::DIVIDE ) {
        if ( abs( right_child->evaluate( state ) ) < EPSILON ) throw ExpressionException( "Expression division by zero." );
        return left_child->evaluate( state ) / right_child->evaluate( state );
    } else if ( operation == OperationType::POW ) {
        return pow( left_child->evaluate( state ), right_child->evaluate( state ) );
    } else {
        throw ExpressionException( "Invalid evaluation of operation requested." );
    }
}

std::shared_ptr<Symbol> ExprOperation::evaluate( SymbolScope symbols ) {
    std::shared_ptr<Symbol> left = left_child->evaluate( symbols );
    std::shared_ptr<Symbol> right = right_child->evaluate( symbols );

    if ( left->get_type() == Symbol::Type::INT and right->get_type() == Symbol::Type::INT ) {
        shared_ptr< TypedSymbol<int> > t_left = dynamic_pointer_cast< TypedSymbol<int> >( left );
        shared_ptr< TypedSymbol<int> > t_right = dynamic_pointer_cast< TypedSymbol<int> >( right );

        return std::make_shared <TypedSymbol<int> >( evaluate_op<int>( t_left, t_right ) );
    } else if ( ( left->get_type() == Symbol::Type::INT or left->get_type() == Symbol::Type::REAL )
        and ( right->get_type() == Symbol::Type::INT or right->get_type() == Symbol::Type::REAL ) ) {
        shared_ptr< TypedSymbol<double> > t_left = dynamic_pointer_cast< TypedSymbol<double> >( left->cast( Symbol::Type::REAL ) );
        shared_ptr< TypedSymbol<double> > t_right = dynamic_pointer_cast< TypedSymbol<double> >( right->cast( Symbol::Type::REAL ) );

        return std::make_shared< TypedSymbol<double> >( evaluate_op<double>( t_left, t_right ) );
    } else throw EngineException( "Unknown symbol type." );
}

template <typename T>
TypedSymbol<T> ExprOperation::evaluate_op( std::shared_ptr< TypedSymbol<T> > left, std::shared_ptr< TypedSymbol<T> > right ) {
    if ( operation == OperationType::ADD ) {
        return left->op_add( *right );
    } else if ( operation == OperationType::SUBTRACT ) {
        return left->op_sub( *right );
    } else if ( operation == OperationType::MULTIPLY ) {
        return left->op_mul( *right );
    } else if ( operation == OperationType::DIVIDE ) {
        if ( abs( right->get_data() ) < EPSILON ) throw ExpressionException( "Expression division by zero." );
        return left->op_div( *right );
    } else if ( operation == OperationType::POW ) {
        return left->op_pow( *right );
    } else {
        throw ExpressionException( "Invalid evaluation of operation requested." );
    }
}

/**********************************************************************************************************************
 * ExprUnaryOperation Class Implementation
 *********************************************************************************************************************/
 ExprUnaryOperation::ExprUnaryOperation( OperationType op, std::shared_ptr<ArithmeticExpression> expr )
    : ArithmeticExpression( ExpressionType::UNARY_OPERATION, expr, std::shared_ptr<ArithmeticExpression>( nullptr ) ), operation( op )  { }

 double ExprUnaryOperation::evaluate( Run state ) {
     if ( operation == OperationType::NEGATE ) {
         return -( left_child->evaluate( state ) );  // By definition the right_child is ignored for unary operations.
     } else {
         throw ExpressionException( "Invalid evaluation of operation requested." );
     }
 }

std::shared_ptr<Symbol> ExprUnaryOperation::evaluate( SymbolScope symbols ) {
    std::shared_ptr<Symbol> left = left_child->evaluate( symbols );

    if ( operation == OperationType::NEGATE ) {
        if ( left->get_type() == Symbol::Type::INT ) {
            std::shared_ptr< TypedSymbol<int> > t_left = dynamic_pointer_cast< TypedSymbol<int> >( left );
            return std::make_shared< TypedSymbol<int> >( t_left->op_negate() );
        } else if ( left->get_type() == Symbol::Type::REAL ) {
            std::shared_ptr< TypedSymbol<double> > t_left = dynamic_pointer_cast< TypedSymbol<double> >( left );
            return std::make_shared< TypedSymbol<double> >( t_left->op_negate() );
        } else throw ExpressionException( "Unknown symbol type." );
    } else throw ExpressionException( "Invalid evaluation of operation requested." );
}

/**********************************************************************************************************************
 * ExprConstant Class Implementation
 *********************************************************************************************************************/
ExprConstant::ExprConstant( double this_value ) : ArithmeticExpression( ExpressionType::CONSTANT ), value( this_value ) { }

double ExprConstant::evaluate( Run state ) {
    return value;
}

std::shared_ptr<Symbol> ExprConstant::evaluate( SymbolScope symbols ) {
    return std::make_shared< TypedSymbol<double> >( Symbol::Type::REAL, value );
}

ExprConstant::ExprConstant( std::string str_value ) : ArithmeticExpression() {
    // Convert the string representation into a floating-point value.
    try {
        value = stod( str_value );
    } catch ( const invalid_argument &e ) {
        throw ExpressionException( "Invalid conversion of token to a real value." );
    } catch ( const out_of_range &e ) {
        throw ExpressionException ( "Overflow in conversion of token to a double-precision real value." );
    }
}

/**********************************************************************************************************************
 * ExprFunction Class Implementation
 *********************************************************************************************************************/
 ExprFunction::ExprFunction( FunctionType this_function, std::shared_ptr< ArithmeticExpression > this_argument )
    : ArithmeticExpression( ExpressionType::FUNCTION ), function( this_function ), user_function_identifier( "<intrinsic>" ) {
     arguments.push_back( this_argument );
 }

ExprFunction::ExprFunction( FunctionType this_function, std::vector< std::shared_ptr<Expression> > this_arguments )
    : function( this_function ), arguments( this_arguments ), user_function_identifier( "<intrinsic>" ) { }

ExprFunction::ExprFunction( std::string this_user_function_identifier,
    std::vector< std::shared_ptr<Expression> > this_arguments ) : ArithmeticExpression( ExpressionType::FUNCTION ),
    function( FunctionType::USER_DEFINED ), user_function_identifier( this_user_function_identifier ), arguments( this_arguments) { }

 double ExprFunction::evaluate( Run state ) {
     if ( arguments.empty() ) throw ExpressionException( "Unexpected number of function arguments function." );
     if ( arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
         throw ExpressionException( "Expected an arithmetic expression as a function argument." );

     if ( arguments.size() == 2 and arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
         throw ExpressionException( "Expected an arithmetic expression as a function argument." );

     // Evaluate first argument, which is required (as an arithmetic expression) for all available functions.
     double argumentA = std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 0 ) )->evaluate( state );

     if ( function == FunctionType::SQRT ) {
         if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'sqrt'." );
         return sqrt( argumentA );
     } else if ( function == FunctionType::SIN ) {
         if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'sin'." );
         return sin( argumentA );
     } else if ( function == FunctionType::COS ) {
         if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'cos'." );
         return cos( argumentA );
     } else if ( function == FunctionType::TAN ) {
         if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'tan'." );
         return tan( argumentA );
     } else if ( function == FunctionType::LOG ) {
         if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'log'." );
         return log( argumentA );
     } else if ( function == FunctionType::ABS ) {
         if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'abs'." );
         return abs( argumentA );
     } else if ( function == FunctionType::DISTRIBUTION_INTEGER ) {
         if ( arguments.size() != 2 ) throw ExpressionException( "Unexpected number of function arguments to 'rand'." );
         double argumentB = std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 1 ) )->evaluate( state );
         // In the case of the uniform integer distribution, argumentA corresponds to the lower limit and argumentB
         // corresponds to the upper limit.
         std::uniform_int_distribution<int> dist( argumentA, argumentB );  // Distribution requires an integral type.
         return double( dist( Engine::rng ) );
     } else if ( function == FunctionType::DISTRIBUTION_NORMAL ) {
         if ( arguments.size() != 2 ) throw ExpressionException( "Unexpected number of function arguments to 'normal'." );
         double argumentB = std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 1 ) )->evaluate( state );
         // In the case of the normal integer distribution, argumentA corresponds to the mean and argumentB corresponds
         // to the standard deviation.
         std::normal_distribution<double> dist( argumentA, argumentB );
         return dist( Engine::rng );
     } else if ( function == FunctionType::DISTRIBUTION_UNIFORM ) {
         if ( arguments.size() != 2 ) throw ExpressionException( "Unexpected number of function arguments to 'uniform'." );
         // In the case of the uniform real distribution, argumentA corresponds to the lower limit and argumentB
         // corresponds to the upper limit.
         double argumentB = std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 1 ) )->evaluate( state );
         std::uniform_real_distribution<double> dist( argumentA, argumentB );
         return dist( Engine::rng );
     } else {
         throw ExpressionException( "Invalid evaluation of function requested." );
     }
 }

std::shared_ptr<Symbol> ExprFunction::evaluate( SymbolScope symbols ) {
     // Evaluate all function arguments in the context of the current symbol scope.
     std::vector< std::shared_ptr<Symbol> > evaluated_arguments;
     for ( auto arg : arguments ) {
         evaluated_arguments.push_back( arg->evaluate( symbols ) );
     }

     if ( function == FunctionType::USER_DEFINED ) {
        UserFunction* user_function = symbols.get_function( user_function_identifier );

         // Ensure that the number of evaluated arguments and the number of expected arguments match.
         if ( user_function->get_arguments().length() != evaluated_arguments.size() )
             throw ExpressionException( "Incorrect number of function arguments." );

         // Add evaluated arguments to a new symbol table.
         // Cast evaluated arguments to the expected types, as defined in the function signature.
         SymbolScope passed_arguments;
         for ( int i = 0; i < evaluated_arguments.size(); i++ ) {
             std::shared_ptr<Symbol> cast_arg = evaluated_arguments.at( i )->cast( user_function->get_arguments().at( i ).type );
             cast_arg->set_identifier( user_function->get_arguments().at( i ).identifier );
             passed_arguments.add_symbol( cast_arg );
         }

         // Add user function references to the new symbol table.
         passed_arguments.set_functions( symbols.get_functions() );

         return user_function->execute( passed_arguments );
     } else {
         return evaluate_function( evaluated_arguments );
     }
}

std::shared_ptr<Symbol> ExprFunction::evaluate_function( std::vector< std::shared_ptr<Symbol> > arguments ) {
     std::vector<double> data;
     double result;

     for ( auto arg : arguments ) {
         if ( arg->get_type() == Symbol::Type::INT ) {
             std::shared_ptr< TypedSymbol<int> > cast_argument = std::dynamic_pointer_cast< TypedSymbol<int> >( arg );
             data.push_back( (double)( cast_argument->get_data() ) );
         } else if ( arg->get_type() == Symbol::Type::REAL ) {
             std::shared_ptr< TypedSymbol<double> > cast_argument = std::dynamic_pointer_cast< TypedSymbol<double> >( arg );
             data.push_back( cast_argument->get_data() );
         } else throw ExpressionException( "Expected numerical argument." );
     }

    if ( function == FunctionType::SQRT ) {
        if ( data.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'sqrt'." );
        result = sqrt( data.at( 0 ) );
    } else if ( function == FunctionType::SIN ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'sin'." );
        result = sin( data.at( 0 ) );
    } else if ( function == FunctionType::COS ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'cos'." );
        result = cos( data.at( 0 ) );
    } else if ( function == FunctionType::TAN ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'tan'." );
        result = tan( data.at( 0 ) );
    } else if ( function == FunctionType::LOG ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'log'." );
        result = log( data.at( 0) );
    } else if ( function == FunctionType::ABS ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Unexpected number of function arguments to 'abs'." );
        result = abs( data.at( 0 ) );
    } else if ( function == FunctionType::DISTRIBUTION_INTEGER ) {
        if ( arguments.size() != 2 ) throw ExpressionException( "Unexpected number of function arguments to 'rand'." );
        // In the case of the uniform integer distribution, the first argument corresponds to the lower limit and the
        // second argument corresponds to the upper limit.
        std::uniform_int_distribution<int> dist( data.at( 0 ), data.at( 1 ) );  // Distribution requires an integral type.
        result = double( dist( Engine::rng ) );
    } else if ( function == FunctionType::DISTRIBUTION_NORMAL ) {
        if ( arguments.size() != 2 ) throw ExpressionException( "Unexpected number of function arguments to 'normal'." );
        // In the case of the normal integer distribution, the first argument corresponds to the mean and the second
        // argument corresponds to the standard deviation.
        std::normal_distribution<double> dist( data.at( 0 ), data.at( 1 ) );
        result = dist( Engine::rng );
    } else if ( function == FunctionType::DISTRIBUTION_UNIFORM ) {
        if ( arguments.size() != 2 ) throw ExpressionException( "Unexpected number of function arguments to 'uniform'." );
        // In the case of the uniform real distribution, the first argument corresponds to the lower limit and the
        // second argument corresponds to the upper limit.
        std::uniform_real_distribution<double> dist( data.at( 0 ), data.at( 1 ) );
        result = dist( Engine::rng );
    } else {
        throw ExpressionException( "Invalid evaluation of function requested." );
    }

    return std::make_shared< TypedSymbol<double> >( Symbol::Type::REAL, result );
}


/**********************************************************************************************************************
* ExprVariable Class Implementation
*********************************************************************************************************************/
const double ExprVariable::PI = 3.14159265358979323846;

const double ExprVariable::E = 2.71828182845904523536;

ExprVariable::ExprVariable( std::string this_identifier )
    : ArithmeticExpression( ExpressionType::VARIABLE ), identifier( this_identifier ) { }

double ExprVariable::evaluate( Run state ) {
    // Check if the identifier matches a defined constant, and if so, return the value of the matching constant.
    if ( identifier == "pi" ) return PI;
    if ( identifier == "e" ) return E;

    double dbl_value;
    try {
        dbl_value = stod( state.get_value( identifier ) );
    } catch ( const invalid_argument &e ) {
        throw ExpressionException( "Invalid conversion of expression variable to a real value." );
    } catch ( const out_of_range &e ) {
        throw ExpressionException ( "Overflow in conversion of expression variable to a double-precision real value." );
    }

    return dbl_value;
}

std::shared_ptr<Symbol> ExprVariable::evaluate( SymbolScope symbols ) {
    // Check if the identifier matches a defined constant, and if so, return the value of the matching constant.
    if ( identifier == "pi" ) return std::make_shared< TypedSymbol<double> >( Symbol::Type::REAL, PI );
    if ( identifier == "e" ) return std::make_shared< TypedSymbol<double> >( Symbol::Type::REAL, E );

    return symbols.get_symbol( identifier );
}


/**********************************************************************************************************************
* ExprListElement Class Implementation
*********************************************************************************************************************/
ExprListElement::ExprListElement( std::shared_ptr<ArithmeticExpression> list, std::shared_ptr<ArithmeticExpression> this_index )
    : ArithmeticExpression( ArithmeticExpression::ExpressionType::LIST_ELEMENT, list, this_index ) { }

double ExprListElement::evaluate( Run state ) {
    throw ExpressionException( "Accessing list elements is not valid in this context." );
}

std::shared_ptr<Symbol> ExprListElement::evaluate( SymbolScope symbols ) {
    std::shared_ptr<Symbol> ev_list = left_child->evaluate( symbols );

    // Verify the evaluated list expression is a list symbol.
    if ( ev_list->get_type() != Symbol::Type::LIST ) throw ExpressionException( "Expected a symbol of type list." );
    std::shared_ptr<List> list = std::dynamic_pointer_cast<List>( ev_list );

    // Evaluate the list index.
    std::shared_ptr< TypedSymbol<int> > sym_i = std::dynamic_pointer_cast< TypedSymbol<int> >( right_child->evaluate( symbols )->cast( Symbol::Type::INT ) );
    long i = sym_i->get_data();

    return list->at( i );
}