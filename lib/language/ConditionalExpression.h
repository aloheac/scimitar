/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Conditional expression class definitions.
 *
 *    DESCRIPTION: This header file defines a series of classes which implement the construction and evaluation of
 *                 conditional expressions which are built in terms of a binary tree. The ConditionalExpression class
 *                 is a child class of the more generic Expression class, and provides a variety of derived types for
 *                 different kinds of operations (binary and unary) and targets of those operations (literals and
 *                 variables). Provided operations include boolean arithmetic (e.g., "and", "or", "not" operations)
 *                 upon boolean expressions, and comparision operations (e.g., "greater than", "less than", "equality"
 *                 operations) between arithmetic expressions. These expressions may be evaluated by the compiler's
 *                 engine in terms of Run objects (related to a unique set of parameters to be passed to a simulation
 *                 invocation) or SymbolScope objects (related to a subroutine executed in a user-defined function).
 *
 *    CREATION DATE: December 14, 2019
 *
 *********************************************************************************************************************/


#ifndef SCIMITAR7_CONDITIONALEXPRESSION_H
#define SCIMITAR7_CONDITIONALEXPRESSION_H

#include <memory>
#include "ArithmeticExpression.h"
#include "../engine/EngineAuxiliary.h"

/**
 * Class implementation of a conditional expression which can be evaluated to a boolean result once all identifiers are
 * provided a corresponding value via a Run or SymbolScope instance. This class is derived from the Expression class,
 * which provides a common interface between arithmetic and conditional expressions.
 *
 * The base class implements a data structure where expressions may be constructed in terms of binary trees. As such,
 * fields and methods are provided for left and right child expressions. This is natural for binary operations, but
 * subclasses for unary operations, variables, and literals are handled by using one or none of these children by
 * definition as an implementation detail.
 */
class ConditionalExpression : public Expression {

public:
    /**
     * Enumeration of binary and unary boolean opeartions.
     */
    enum BooleanOperationType {
        AND,        // Boolean "and" operation between two boolean values.
        OR,         // Boolean "or" operation between two boolean values.
        NEGATE,     // Boolean "not" operation on one boolean value.
        EQUALITY    // Boolean equality (==) operation between two boolean values.
    };

    /**
     * Enumeration of boolean expression types.
     */
    enum ExpressionType {
        BOOLEAN_OPERATION,         // Binary boolean operations including AND, OR, and EQUALITY.
        UNARY_BOOLEAN_OPERATION,   // Unary boolean operation, including negation.
        COMPARISON_OPERATION,      // Comparison operation (e.g., "greater than", "less than") between two arithmetic expressions.
        BOOLEAN_CONSTANT,          // Boolean constant literal of either TRUE or FALSE.
        VARIABLE                   // Variable of a boolean type which is bound to an identifier.
    };

    /**
     * Constructor.
     * @param type Boolean expression type of this object. One of the provided enumerated types.
     * @param left Left boolean expression child.
     * @param right Right boolean expression child. May not be used for unary operations, for instance.
     */
    ConditionalExpression( ExpressionType type, std::shared_ptr<ConditionalExpression> left,
                           std::shared_ptr<ConditionalExpression> right );

    /**
     * Sets the left-hand child expression.
     * @param expr The new conditional expression to insert as a child.
     */
    virtual void set_left_child( std::shared_ptr<ConditionalExpression> expr );

    /**
     * Sets the right-hand child expression.
     * @param expr The new conditional expression to insert as a child.
     */
    virtual void set_right_child( std::shared_ptr<ConditionalExpression> expr );

    /**
     * Evaluates the conditional expression in the context of the passed Run object and returns the boolean result. All
     * variables referenced in the expression are expected to be defined in the Run object with matching identifiers.
     * This method must be implemented by all derived classes.
     * @param state The Run context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a boolean value.
     */
    virtual bool evaluate( Run state ) = 0;

    /**
     * Evaluates the conditional expression in the context of the passed SymbolScope object as a reference to a new
     * Symbol. The type of the returned symbol is determined by type casts as defined by the language. All symbols
     * referenced in the expression are expected to be defined in the SymbolScope object with matching identifiers.
     * This method must be implemented by all derived classes.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a Symbol literal.
     */
    virtual std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) = 0;

    /**
     * Gets the expression type of this instance. Each derived expression type is expected to provide a corresponding
     * enumerated ExpressionType.
     * @return The expression type of this instance.
     */
    ExpressionType get_type();

protected:

    /**
     * The expression type of this instance.
     */
    ExpressionType type;

    /**
     * The left expression child of this instance.
     */
    std::shared_ptr<ConditionalExpression> left;

    /**
     * The right expression child of this instance.
     */
    std::shared_ptr<ConditionalExpression> right;

};


/**
 * Implements binary boolean operations on child expressions.
 */
class BooleanOperation : public ConditionalExpression {

public:
    /**
     * Constructor.
     * @param op Binary boolean operation to be performed on children expressions. One of BooleanOperationType enumerations.
     * @param left Left conditional expression child of the binary operation.
     * @param right Right conditional expression child of the binary operation.
     */
    BooleanOperation( BooleanOperationType op, std::shared_ptr<ConditionalExpression> left,
                      std::shared_ptr<ConditionalExpression> right );

    /**
     * Evaluates the conditional expression in the context of the passed Run object as a boolean result. All variables
     * referenced in the expression are expected to be defined in the Run object with matching identifiers.
     * @param state The Run context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a boolean value.
     */
    bool evaluate( Run state ) override;

    /**
     * Evaluates the conditional expression in the context of the passed SymbolScope object as a reference to a new
     * Symbol. The type of the returned symbol is determined by type casts as defined by the language. All symbols
     * referenced in the expression are expected to be defined in the SymbolScope object with matching identifiers.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a Symbol literal.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * The boolean operation type of this instance.
     */
    BooleanOperationType op;

};


/**
 * Implements unary boolean operations on a child expression. Note that by definition, the left expression child
 * is used as the unary argument. The right expression child is set to a null pointer. Currently, the only implemented
 * unary operation is boolean negation.
 */
class UnaryBooleanOperation : public ConditionalExpression {

public:
    /**
     * Constructor.
     * @param op Unary boolean operation to be executed on the argument expression.
     * @param argument The conditional expression to be passed as an argument to the operation.
     */
    UnaryBooleanOperation( BooleanOperationType op, std::shared_ptr<ConditionalExpression> argument );

    /**
     * Evaluates the conditional expression in the context of the passed Run object as a boolean result. All variables
     * referenced in the expression are expected to be defined in the Run object with matching identifiers.
     * @param state The Run context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a boolean value.
     */
    bool evaluate( Run state ) override;

    /**
     * Evaluates the conditional expression in the context of the passed SymbolScope object as a reference to a new
     * Symbol. The type of the returned symbol is determined by type casts as defined by the language. All symbols
     * referenced in the expression are expected to be defined in the SymbolScope object with matching identifiers.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a Symbol literal.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * The boolean operation type of this instance.
     */
    BooleanOperationType op;

};


/**
 * Implements comparision operations (such as "greater than", "less than", "greater than or equal", and "equality")
 * between two arithmetic expressions. Note that this class is implemented a bit differently from other classes
 * derived from ConditionalExpression in the sense the ConditionalExpression children are ignored for
 * ArithmeticExpression children, since the argument to these operations are one or two evaluated arithmetic
 * expressions. The result of these operations is always a boolean value.
 */
class ComparisonOperation : public ConditionalExpression {

public:
    /**
     * Enumeration of possible comparison operation types.
     */
    enum ComparisonOperationType {
        GREATER_THAN,
        LESS_THAN,
        GREATER_THAN_OR_EQUAL,
        LESS_THAN_OR_EQUAL,
        EQUALITY,
        NOT_EQUAL
    };

    /**
     * Constructor.
     * @param op Comparison operation type to be executed on the child expressions.
     * @param left Arithmetic expression on the left-hand side of the operation.
     * @param right Arithmetic expression on the right-hand side of the operation.
     */
    ComparisonOperation( ComparisonOperationType op, std::shared_ptr<ArithmeticExpression> left,
                         std::shared_ptr<ArithmeticExpression> right );

    /**
     * Evaluates the left and right arithmetic expressions and then evaluates the comparison operations in the context
     * of the passed Run object. The result of the comparison is returned as a boolean value. All variables referenced
     * in both arithmetic expressions are expected to be defined in the provided scope with matching identifiers.
     * @param run The Run context to be used in the evaluation of the expression.
     * @return The result of the comparison operation as a boolean value.
     */
    bool evaluate( Run run ) override;

    /**
     * Evaluates the left and right arithmetic expressions and then evaluates the comparison operations in the context
     * of the passed SymbolScope. The result of the comparison is returned as a Symbol literal of a boolean type. All
     * variables referenced in both arithmetic expressions are expected to be defined in the provided scope with
     * matching identifiers.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the comparison operation as a Symbol literal of a boolean type.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * Private subroutine for evaluating comparison operations which accepts templated symbols as arguments and returns
     * a boolean symbol containing the result. Casts between types are attempted as defined by the language, but the
     * templated definition of symbols requires the storage type of both arguments to be the same type T.
     * @tparam T The storage type of both symbols passed as arguments.
     * @param eval_left The symbol appearing on the left-hand side of the comparison.
     * @param eval_right The symbol appearing on the right-hand side of the comparison.
     * @return The result of the comparison as a boolean symbol.
     */
    template <typename T>
    BooleanSymbol evaluate_comparison( std::shared_ptr< TypedSymbol<T> > eval_left, std::shared_ptr< TypedSymbol<T> > eval_right );

    /**
     * The comparison operation to be performed by this instance.
     */
    ComparisonOperationType op;

    /**
     * The arithmetic expression appearing on the left-hand side of the operation.
     */
    std::shared_ptr<ArithmeticExpression> left;

    /**
     * The arithmetic expression appearing on the right-hand side of the operation.
     */
    std::shared_ptr<ArithmeticExpression> right;

};


/**
 * Implements a boolean literal value.
 */
class BooleanLiteral : public ConditionalExpression {

public:
    /**
     * Constructor.
     * @param literal Value of TRUE or FALSE that this symbol will take.
     */
    BooleanLiteral( bool literal );

    /**
     * Evaluates this symbol by returning the stored value of this literal symbol.
     * @param run The Run context the expression is evaluated in. This object is invariant to the current context state.
     * @return The boolean value of this literal.
     */
    bool evaluate( Run run ) override;

    /**
     * Evaluates this symbol by returning the stored value of this literal as a boolean symbol.
     * @param symbols The Symbol context the expression is evaluated in. This object is invariant to the current context
     *                state.
     * @return The boolean value of this literal as a boolean symbol.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * The stored boolean value of this literal.
     */
    bool value;

};


/**
 * Implements a boolean variable which is bound to a value defined in a provided scope.
 */
class BooleanVariable : public ConditionalExpression {

public:
    /**
     * Constructor.
     * @param identifier The unique identifier of this variable.
     */
    BooleanVariable( std::string identifier );

    /**
     * Evaluates this variable by performing a lookup of the current value of this variable in the provided context. The
     * context is expected to contain a matching identifier.
     * @param run The Run object to with which perform the variable lookup.
     * @return The current value of the variable in the provided scope as a boolean value.
     */
    bool evaluate( Run run ) override;

    /**
     * Evaluates the variable by performing a lookup of the current value of this variable in the provided context. The
     * context is expected to contain a matching identifier.
     * @param symbols The SymbolScope object with which to perform the variable lookup.
     * @return The current value of the variable in the provided scope as a boolean symbol.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * The unique identifier of this boolean variable.
     */
    std::string identifier;

};

#endif //SCIMITAR7_CONDITIONALEXPRESSION_H
