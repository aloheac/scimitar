/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Conditional expression class implementations.
 *
 *    DESCRIPTION: This file provides a series of classes which implement the construction and evaluation of conditional
 *                 expressions which are built in terms of a binary tree. The ConditionalExpression class is a child
 *                 class of the more generic Expression class, and provides a variety of derived types for different
 *                 kinds of operations (binary and unary) and targets of those operations (literals and variables).
 *                 Provided operations include boolean arithmetic (e.g., "and", "or", "not" operations) upon boolean
 *                 expressions, and comparision operations (e.g., "greater than", "less than", "equality" operations)
 *                 between arithmetic expressions. These expressions may be evaluated by the compiler's engine in terms
 *                 of Run objects (related to a unique set of parameters to be passed to a simulation invocation) or
 *                 SymbolScope objects (related to a subroutine executed in a user-defined function).
 *
 *    CREATION DATE: December 14, 2019
 *
 *********************************************************************************************************************/


#include "ArithmeticExpression.h"
#include "ConditionalExpression.h"

/**********************************************************************************************************************
 * ConditionalExpression Class Implementation
 *********************************************************************************************************************/
 ConditionalExpression::ConditionalExpression( ConditionalExpression::ExpressionType this_type,
         std::shared_ptr<ConditionalExpression> this_left, std::shared_ptr<ConditionalExpression> this_right )
         : Expression( Expression::Type::CONDITIONAL ), type( this_type ), left( this_left ), right( this_right ) { }

void ConditionalExpression::set_left_child( std::shared_ptr<ConditionalExpression> expr ) {
    left = expr;
}

void ConditionalExpression::set_right_child( std::shared_ptr<ConditionalExpression> expr ) {
    right = expr;
}

ConditionalExpression::ExpressionType ConditionalExpression::get_type() {
    return type;
}


/**********************************************************************************************************************
 * BooleanExpression Class Implementation
 *********************************************************************************************************************/
 BooleanOperation::BooleanOperation( ConditionalExpression::BooleanOperationType this_op,
                                     std::shared_ptr<ConditionalExpression> left, std::shared_ptr<ConditionalExpression> right )
         : ConditionalExpression( ConditionalExpression::ExpressionType::BOOLEAN_OPERATION, left, right ),
         op( this_op ) { }

 bool BooleanOperation::evaluate( Run run ) {
     bool eval_left = left->evaluate( run );
     bool eval_right = right->evaluate( run );

     if ( op == BooleanOperationType::AND ) {
         return eval_left and eval_right;
     } else if ( op == BooleanOperationType::OR ) {
         return eval_left or eval_right;
     } else if ( op == BooleanOperationType::EQUALITY ) {
         return eval_left == eval_right;
     } else {
         throw ExpressionException( "Unknown boolean operation received." );
     }
 }

std::shared_ptr<Symbol> BooleanOperation::evaluate( SymbolScope symbols ) {
    std::shared_ptr<BooleanSymbol> eval_left = std::dynamic_pointer_cast<BooleanSymbol>( left->evaluate( symbols ) );
    std::shared_ptr<BooleanSymbol> eval_right = std::dynamic_pointer_cast<BooleanSymbol>( right->evaluate( symbols ) );

    if ( op == BooleanOperationType::AND ) {
        return std::make_shared<BooleanSymbol>( eval_left->op_and( *eval_right ) );
    } else if ( op == BooleanOperationType::OR ) {
        return std::make_shared<BooleanSymbol>( eval_left->op_or( *eval_right ) );
    } else if ( op == BooleanOperationType::EQUALITY ) {
        return std::make_shared<BooleanSymbol>( eval_left->op_eq( *eval_right ) );
    } else throw ExpressionException( "Unknown boolean operation received." );
}


/**********************************************************************************************************************
* UnaryBooleanExpression Class Implementation
*********************************************************************************************************************/
UnaryBooleanOperation::UnaryBooleanOperation( ConditionalExpression::BooleanOperationType op,
        std::shared_ptr<ConditionalExpression> argument ) : ConditionalExpression( ConditionalExpression::ExpressionType::UNARY_BOOLEAN_OPERATION,  argument, std::shared_ptr<ConditionalExpression>( nullptr ) ) { }

bool UnaryBooleanOperation::evaluate( Run state ) {
    bool argument = left->evaluate( state );

    if ( op == BooleanOperationType::NEGATE ) {
        return not argument;
    } else {
        throw ExpressionException( "Unknown unary boolean operation received." );
    }
}

std::shared_ptr<Symbol> UnaryBooleanOperation::evaluate( SymbolScope symbols ) {
    std::shared_ptr<BooleanSymbol> argument = std::dynamic_pointer_cast<BooleanSymbol>( left->evaluate( symbols ) );

    if ( op == BooleanOperationType::NEGATE ) {
        return std::make_shared<BooleanSymbol>( argument->op_not() );
    } else throw ExpressionException( "Unknown unary boolean operation received." );
}

/**********************************************************************************************************************
* ComparisonExpression Class Implementation
*********************************************************************************************************************/
ComparisonOperation::ComparisonOperation( ComparisonOperationType this_op, std::shared_ptr<ArithmeticExpression> this_left, std::shared_ptr<ArithmeticExpression> this_right )
        : ConditionalExpression( ConditionalExpression::ExpressionType::COMPARISON_OPERATION, std::shared_ptr<ConditionalExpression>( nullptr ), std::shared_ptr<ConditionalExpression>( nullptr ) ),
         op( this_op ), left( this_left ), right( this_right ) { }

bool ComparisonOperation::evaluate( Run run ) {
    double eval_left = left->evaluate( run );
    double eval_right = right->evaluate( run );

    if ( op == ComparisonOperationType::EQUALITY ) {
        return eval_left == eval_right;
    } else if ( op == ComparisonOperationType::NOT_EQUAL ) {
        return eval_left != eval_right;
    } else if ( op == ComparisonOperationType::GREATER_THAN ) {
        return eval_left > eval_right;
    } else if ( op == ComparisonOperationType::LESS_THAN ) {
        return eval_left < eval_right;
    } else if ( op == ComparisonOperationType::GREATER_THAN_OR_EQUAL ) {
        return eval_left >= eval_right;
    } else if ( op == ComparisonOperationType::LESS_THAN_OR_EQUAL ) {
        return eval_left <= eval_right;
    } else {
        throw ExpressionException( "Unknown comparison operation requested." );
    }
}

std::shared_ptr<Symbol> ComparisonOperation::evaluate( SymbolScope symbols ) {
    std::shared_ptr<Symbol> eval_left = left->evaluate( symbols );
    std::shared_ptr<Symbol> eval_right = right->evaluate( symbols );

    if ( eval_left->get_type() == Symbol::Type::INT ) {
        std::shared_ptr< TypedSymbol<int> > t_eval_left = std::dynamic_pointer_cast< TypedSymbol<int> >( eval_left );
        std::shared_ptr< TypedSymbol<int> > t_eval_right = std::dynamic_pointer_cast< TypedSymbol<int> >( eval_right->cast( Symbol::Type::INT ) );

        return std::make_shared<BooleanSymbol>( evaluate_comparison<int>( t_eval_left, t_eval_right ) );
    } else if ( eval_left->get_type() == Symbol::Type::REAL ) {
        std::shared_ptr< TypedSymbol<double> > t_eval_left = std::dynamic_pointer_cast< TypedSymbol<double> >( eval_left );
        std::shared_ptr< TypedSymbol<double> > t_eval_right = std::dynamic_pointer_cast< TypedSymbol<double> >( eval_right->cast( Symbol::Type::REAL ) );

        return std::make_shared<BooleanSymbol>( evaluate_comparison<double>( t_eval_left, t_eval_right ) );
    } else if ( eval_right->get_type() == Symbol::Type::BOOL ) {
        std::shared_ptr< BooleanSymbol > t_eval_left = std::dynamic_pointer_cast< BooleanSymbol >( eval_left );
        std::shared_ptr< BooleanSymbol > t_eval_right = std::dynamic_pointer_cast< BooleanSymbol >( eval_right->cast( Symbol::Type::BOOL ) );

        if ( op == ComparisonOperationType::EQUALITY ) {
            return std::make_shared<BooleanSymbol>( t_eval_left->get_data() == t_eval_right->get_data() );
        } else if ( op == ComparisonOperationType::NOT_EQUAL ) {
            return std::make_shared<BooleanSymbol>(t_eval_left->get_data() != t_eval_right->get_data());
        } else throw ExpressionException( "Unknown comparison operation requested." );
    } else throw ExpressionException( "Unknown symbol type." );
}

template <typename T>
BooleanSymbol ComparisonOperation::evaluate_comparison( std::shared_ptr< TypedSymbol<T> > eval_left, std::shared_ptr< TypedSymbol<T> > eval_right ) {
    if ( op == ComparisonOperationType::EQUALITY ) {
        return eval_left->op_equality( *eval_right );
    } else if ( op == ComparisonOperationType::NOT_EQUAL ) {
        return eval_left->op_not_equal( *eval_right );
    } else if ( op == ComparisonOperationType::GREATER_THAN ) {
        return eval_left->op_greater_than( *eval_right );
    } else if ( op == ComparisonOperationType::LESS_THAN ) {
        return eval_left->op_less_than( *eval_right );
    } else if ( op == ComparisonOperationType::GREATER_THAN_OR_EQUAL ) {
        return eval_left->op_gt_or_eq( *eval_right );
    } else if ( op == ComparisonOperationType::LESS_THAN_OR_EQUAL ) {
        return eval_left->op_lt_or_eq( *eval_right );
    } else {
        throw ExpressionException( "Unknown comparison operation requested." );
    }
}

/**********************************************************************************************************************
* BooleanLiteral Class Implementation
*********************************************************************************************************************/
BooleanLiteral::BooleanLiteral( bool literal ) : ConditionalExpression( ConditionalExpression::ExpressionType::BOOLEAN_CONSTANT,
        std::shared_ptr<ConditionalExpression>( nullptr ), std::shared_ptr<ConditionalExpression>( nullptr ) ), value( literal ) { }

bool BooleanLiteral::evaluate( Run run ) {
    return value;
}

std::shared_ptr<Symbol> BooleanLiteral::evaluate( SymbolScope symbols ) {
    return std::make_shared<BooleanSymbol>( value );
}


/**********************************************************************************************************************
* BooleanVariable Class Implementation
*********************************************************************************************************************/
BooleanVariable::BooleanVariable( std::string this_identifier ) : ConditionalExpression( ConditionalExpression::ExpressionType::VARIABLE,
        std::shared_ptr<ConditionalExpression>( nullptr ), std::shared_ptr<ConditionalExpression>( nullptr ) ), identifier( this_identifier ) { }

bool BooleanVariable::evaluate( Run run ) {
    std::string value = run.get_value( identifier );

    if ( value == SymbolScope::BOOL_TRUE ) {
        return true;
    } else if ( value == SymbolScope::BOOL_FALSE ) {
        return false;
    } else throw ExpressionException( "Unknown boolean literal." );
}

std::shared_ptr<Symbol> BooleanVariable::evaluate( SymbolScope symbols ) {
    return symbols.get_symbol( identifier );
}