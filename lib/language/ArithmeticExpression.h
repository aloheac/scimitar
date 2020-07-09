/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Arithmetic expression class definitions.
 *
 *    DESCRIPTION: This header file defines a series of classes which implement the construction and evaluation of
 *                 arithmetic expressions which are built in terms of a binary tree. The ArithmeticExpression class
 *                 is a child class of the more generic Expression class, and provides a variety of derived types for
 *                 different kinds of operations (binary and unary) and targets of those operations (literals and
 *                 variables). Functions of arithmetic expressions are also provided, such as trigonometric,
 *                 exponential, logarithmic, and statistical distribution functions. These expressions may be evaluated
 *                 by the compiler's engine in terms of Run objects (related to a unique set of parameters to be passed
 *                 to a simulation invocation) or SymbolScope objects (related to a subroutine executed in a
 *                 user-defined function).
 *
 *    CREATION DATE: November 7, 2019
 *
 *********************************************************************************************************************/


#ifndef SCIMITAR7_ARITHMETICEXPRESSION_H
#define SCIMITAR7_ARITHMETICEXPRESSION_H

#include <memory>
#include <vector>
#include "Expression.h"
#include "../engine/EngineAuxiliary.h"
#include "UserFunction.h"

/**
 * Enumeration of arithmetic functions which are supported by expression objects. Each function accepts one expression
 * object as an argument.
 */
enum FunctionType {
    SQRT,
    SIN,
    COS,
    TAN,
    LOG,
    ABS,
    DISTRIBUTION_INTEGER,
    DISTRIBUTION_NORMAL,
    DISTRIBUTION_UNIFORM,
    USER_DEFINED
};


/**
 * Enumeration of arithmetic operations which are supported by expression objects. Operations may either be binary or
 * unary. This distinction is exposed in the enumeration of Expression::ExpressionType.
 */
enum OperationType {
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    POW,
    NEGATE
};


/**
 * Exception class which will be thrown upon encountering an error when evaluating or constructing an arithmetic
 * expression.
 */
class ExpressionException : public std::exception {
public:
    /**
     * Constructor.
     * @param msg Error message conveying information about the issue encountered.
     */
    ExpressionException( std::string msg );

    /**
     * Obtains the relevant error message.
     * @return The stored error message.
     */
    virtual const char* what() const throw();

private:
    /**
     * Error message conveying information about the issue encountered.
     */
    std::string msg;

};


/**
 * Class implementation of an arithmetic expression which can be evaluated to a floating-point result once all
 * identifiers are provided a corresponding value via a Run or SymbolScope instance. This class is derived from the
 * Expression class, which provides a common interface between arithmetic and conditional expressions.
 *
 * The base class implements a data structure where expressions may be constructed in terms of binary trees. As such,
 * fields and methods are provided for left and right child expressions. This is natural for binary operations, but
 * subclasses for unary operations, variables, and literals are handled by using one or none of these children by
 * definition as an implementation detail.
 */
class ArithmeticExpression : public Expression {

public:
    /**
     * Enumeration of types of derived expressions which may appear as children in the expression tree.
     */
    enum ExpressionType {
        BASE,
        OPERATION,
        UNARY_OPERATION,
        CONSTANT,
        FUNCTION,
        VARIABLE,
        LIST_ELEMENT
    };

    /**
     * Default constructor. Sets the expression type to BASE, and does not contain valid children.
     */
    ArithmeticExpression();

    /**
     * Constructor. Sets the expression type to a provided type, and does not contain valid children.
     * @param type The expression type of this child node.
     */
    ArithmeticExpression( ExpressionType type );

    /**
     * Constructor. Sets the expression type to a provided type, and also sets the left and right children expression
     * trees.
     * @param type The expression type of this child node.
     * @param left The left child tree.
     * @param right The right child tree.
     */
    ArithmeticExpression( ExpressionType type, std::shared_ptr<ArithmeticExpression> left, std::shared_ptr<ArithmeticExpression> right );

    /**
     * Sets the left-hand child expression.
     * @param expr The new arithmetic expression to insert as a child.
     */
    virtual void set_left_child( std::shared_ptr<ArithmeticExpression> expr );

    /**
     * Sets the right-hand child expression.
     * @param expr The new arithmetic expression to insert as a child.
     */
    virtual void set_right_child( std::shared_ptr<ArithmeticExpression> expr );

    /**
     * Evaluates the arithmetic expression in the context of the passed Run object as a floating-point result. All
     * variables referenced in the expression are expected to be defined in the Run object with matching identifiers.
     * @param state The Run context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a double-precision floating point value.
     */
    virtual double evaluate( Run state );

    /**
     * Evaluates the arithmetic expression in the context of the passed SymbolScope object as a reference to a new
     * Symbol. The type of the returned symbol is determined by type casts as defined by the language. All symbols
     * referenced in the expression are expected to be defined in the SymbolScope object with matching identifiers.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a Symbol literal.
     */
    virtual std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) = 0;

    /**
     * Evaluates a literal arithmetic expression to its floating-point result. Variables may not be referenced in the
     * expression when calling this method. This is equivalent to calling evaluate( Run ) with an empty Run object.
     * @return The evaluated result as a double-precision floating point value.
     */
    virtual double evaluate_literal();

    /**
     * Gets the expression type of this instance. Each derived expression type is expected to provide a corresponding
     * enumerated ExpressionType.
     * @return The expression type of this instance.
     */
    ExpressionType get_type();

protected:
    /**
     * Defines an effective floating-point epsilon within this class. Currently used to detect an attempted division by
     * zero.
     */
    static double EPSILON;

    /**
     * The expression type of this instance.
     */
    ExpressionType expr_type;

    /**
     * The left expression child of this instance.
     */
    std::shared_ptr<ArithmeticExpression> left_child;

    /**
     * The right expression child of this instance.
     */
    std::shared_ptr<ArithmeticExpression> right_child;

};


/**
 * Implements arithmetic binary operations on child expressions.
 */
class ExprOperation : public ArithmeticExpression {

public:
    /**
     * Constructor.
     * @param op Binary arithmetic operation to perform on the children expressions. One of OperationType enumerations.
     * @param left Left arithmetic expression child.
     * @param right Right arithmetic expression child.
     */
    ExprOperation( OperationType op, std::shared_ptr<ArithmeticExpression> left, std::shared_ptr<ArithmeticExpression> right );

    /**
     * Evaluates the arithmetic expression in the context of the passed Run object as a floating-point result. All
     * variables referenced in the expression are expected to be defined in the Run object with matching identifiers.
     * @param state The Run context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a double-precision floating point value.
     */
    double evaluate( Run state ) override;

    /**
     * Evaluates the arithmetic expression in the context of the passed SymbolScope object as a reference to a new
     * Symbol. The type of the returned symbol is determined by type casts as defined by the language. All symbols
     * referenced in the expression are expected to be defined in the SymbolScope object with matching identifiers.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a Symbol literal.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:

    /**
     * Private subroutine for evaluating arithmetic operations which accepts templated symbols as arguments and returns
     * a symbol of a matching storage type.
     * @tparam T The storage type of the passed numerical arguments.
     * @param left The left arithmetic expression child.
     * @param right The right arithmetic expression child.
     * @return The result of the evaluation of the function as a literal symbol, where the result as the same storage
     *         type as the arguments.
     */
    template <typename T>
    TypedSymbol<T> evaluate_op( std::shared_ptr< TypedSymbol<T> > left, std::shared_ptr< TypedSymbol<T> > right );

    /**
     * The arithmetic operation type of this instance.
     */
    OperationType operation;

};


/**
 * Implements arithmetic unary operations on the child expressions. Note that by definition, the left expression child
 * is used as the unary argument. The right expression child is set to a null pointer. Currently, the only implemented
 * unary operation is negation.
 */
class ExprUnaryOperation : public ArithmeticExpression {

public:
    /**
     * Constructor.
     * @param op Unary arithmetic operation to be performed on the child.
     * @param expr Arithmetic child expression (e.g., the operation argument).
     */
    ExprUnaryOperation( OperationType op, std::shared_ptr<ArithmeticExpression> expr );

    /**
     * Evaluates the arithmetic expression in the context of the passed Run object as a floating-point result. All
     * variables referenced in the expression are expected to be defined in the Run object with matching identifiers.
     * @param state The Run context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a double-precision floating point value.
     */
    double evaluate( Run state ) override;

    /**
     * Evaluates the arithmetic expression in the context of the passed SymbolScope object as a reference to a new
     * Symbol. The type of the returned symbol is determined by type casts as defined by the language. All symbols
     * referenced in the expression are expected to be defined in the SymbolScope object with matching identifiers.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a Symbol literal.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * The arithmetic operation type of this instance.
     */
    OperationType operation;

};


/**
 * Implements a floating-point constant value.
 */
class ExprConstant : public ArithmeticExpression {

public:
    /**
     * Constructor.
     * @param value Constant value of this expression.
     */
    ExprConstant( double value );

    /**
     * Constructor.
     * @param str_value Constant value of this expression as a string. A conversion to a double-precision floating point
     * type will be performed.
     */
    ExprConstant( std::string str_value );

    /**
     * Evaluates the arithmetic expression in the context of the passed Run object as a floating-point result. All
     * variables referenced in the expression are expected to be defined in the Run object with matching identifiers.
     * @param state The Run context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a double-precision floating point value.
     */
    double evaluate( Run state ) override;

    /**
     * Evaluates the arithmetic expression in the context of the passed SymbolScope object as a reference to a new
     * Symbol. The type of the returned symbol is determined by type casts as defined by the language. All symbols
     * referenced in the expression are expected to be defined in the SymbolScope object with matching identifiers.
     * @param symbols The SymbolScope context to be used in the evaluation of the expression.
     * @return The result of the evaluation as a Symbol literal.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * Constant value of this expression.
     */
    double value;

};

/**
 * Implements a function of one or more arithmetic expressions which returns a single floating-point result. A function
 * may either be an intrinsic function or a user-defined function.
 *
 *   - Intrinsic functions include basic arithmetic functions of a single argument, including square root, cosine, sine,
 *     tangent, natural logarithm, and absolute value. Basic random-number generators, including the uniform real
 *     distribution, uniform integer distribution, and normal distribution are also provided.
 *
 *   - User-defined functions are also provided through this object, as defined by a unique identifier and a vector of
 *     one or more arithmetic expressions as arguments which will be passed to the function. Note that user-defined
 *     functions are evaluated within the context of a SymbolScope object, and not a Run object.
 */
class ExprFunction : public ArithmeticExpression {

public:
    /**
     * Constructor for an intrinsic function of a single argument.
     * @param function The function to be evaluated, as indicated by one of the provided enumerations.
     * @param argument Argument of this function as an arithmetic expression.
     */
    ExprFunction( FunctionType function, std::shared_ptr<ArithmeticExpression> argument );

    /**
     * Constructor for an intrinsic function, where the arguments are already provided as an element of a vector.
     * @param function The function to be evaluated, as indicated by one of the provided enumerations.
     * @param arguments Arguments of this function as an arithmetic expression contained as members of a vector.
     */
    ExprFunction( FunctionType function, std::vector< std::shared_ptr<Expression> > arguments );

    /**
     * Constructor for a user-defined function of one or more arguments.
     * @param user_function_identifier The unique identifier of this user-defined function.
     * @param arguments A vector of arguments of this function as arithmetic expressions. These expressions will be
     *                  evaluated in the context of a SymbolScope.
     */
    ExprFunction( std::string user_function_identifier, std::vector< std::shared_ptr<Expression> > arguments );

    /**
     * Evaluates an intrinsic function in the context of the passed Run object as a floating-point result. All
     * variables referenced in the function's arguments are expected to be defined in the Run object with matching
     * identifiers.
     * @param state The Run context to be used in the evaluation of the function.
     * @return The result of the evaluation as a double-precision floating point value.
     */
    double evaluate( Run state ) override;

    /**
     * Evaluates the function in the context of the passed SymbolScope object as a reference to a new Symbol. The type
     * of the returned symbol is determined by type casts as defined by the language. All symbols referenced in the
     * function's arguments are expected to be defined in the SymbolScope object with matching identifiers. Note the
     * function may either be an intrinsic or user-defined function.
     * @param symbols The SymbolScope context to be used in the evaluation of the function.
     * @return The result of the evaluation as a Symbol literal.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * Private subroutine for evaluating intrinsic functions, including trigonometric, exponential, logarithmic, and
     * statistical distribution functions. Note intrinsic functions accept either one or two arguments. Note this
     * subroutine is only used when evaluating in the context of a SymbolScope.
     * @param arguments Vector of symbols which will be passed as arguments to the target function.
     * @return The result of the function evaluated as a literal symbol.
     */
    std::shared_ptr<Symbol> evaluate_function( std::vector< std::shared_ptr<Symbol> > arguments );

    /**
     * The function to be executed, as defined by the provided enumerated functions.
     */
    FunctionType function;

    /**
     * Vector of arguments to be provided to the target function.
     */
    std::vector< std::shared_ptr<Expression> > arguments;

    /**
     * Identifier of this user function; used only if applicable.
     */
    std::string user_function_identifier;

};


/**
 * Implements a variable numerical value bound to a unique identifier in an arithmetic expression. The evaluation of
 * a variable will lookup the current matching value in the Run or SymbolScope object and return the result. This class
 * also implements physical constants; if the symbol matches the identifier of an intrinsic constant, that value will
 * be returned immediately instead of performing a lookup.
 */
class ExprVariable : public ArithmeticExpression {
public:

    /**
     * Constructor.
     * @param identifier Identifier of this variable. Valid identifiers are defined by the grammar.
     */
    ExprVariable( std::string identifier );

    /**
     * Evaluates the variable in the context of the passed Run object. A lookup is performed in the context for the
     * matching unique identifier, and the corresponding floating-point value is returned.
     * @param state The Run object context where the variable lookup should be performed.
     * @return The value of the referenced variable as defined in the context's current state.
     */
    double evaluate( Run state ) override;

    /**
     * Evaluates the variable in the context of the passed SymbolScope object. A lookup is performed in the context for
     * the matching unique identifier, and a corresponding symbol literal is returned.
     * @param symbols The SymbolScope object context where the variable lookup should be performed.
     * @return The value of the referenced variable as defined in the context's current state.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

private:
    /**
     * Identifier of this variable.
     */
    std::string identifier;

    /**
     * Values of intrinsic physical constants.
     */
    static const double PI, E;

};


/**
 * Implementation of a list expression (e.g., an array of arithmetic expressions) element access at a provided index.
 * Note that list expressions are only valid within user-defined functions, and may therefore only be evaluated in the
 * context of a symbol scope. These objects correspond to the Symbol::Type::LIST grammar object.
 */
class ExprListElement : public ArithmeticExpression {
public:
    /**
     * Constructor.
     * @param list List object which contains the element to retrieve.
     * @param index An expression which evaluates to the index of the element to retrieve.
     */
    ExprListElement( std::shared_ptr<ArithmeticExpression> list, std::shared_ptr<ArithmeticExpression> index );

    /**
     * Evaluation of a list element in the context of a Run is not supported. This method should not be called directly,
     * and is implemented to complete the abstract interface. Calling this method will throw an exception.
     * @param state The Run object context to evaluate the expression in.
     * @return None. An exception will be immediately thrown by this method.
     */
    double evaluate( Run state ) override;

    /**
     * Evaluates the list element access in the context of the passed SymbolScope object. The expression for the index
     * is evaluated within this scope.
     * @param symbols The SymbolScope object which contains the referenced list object.
     * @return The symbol stored in the referenced list at the provided index.
     */
    std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) override;

};

#endif //SCIMITAR7_ARITHMETICEXPRESSION_H
