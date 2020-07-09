/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Expression base class definition.
 *
 *    DESCRIPTION: This header file defines the Expression class, which serves as a base type for different kinds of
 *                 expressions which appear within the Scimitar grammar. Expressions, in this context, refer to
 *                 operations among objects which may be evaluated in the context of a variable scope to produce a
 *                 reduced result. Expressions encountered in the language may be categorized into two types:
 *                 arithmetic and conditional expressions. Each of these types has their own derived classes,
 *                 ArithmeticExpression and ConditionalExpression, respectively. Classes further derived from these
 *                 types implement specific expression elements and their behavior when the expression is evaluated.
 *
 *    CREATION DATE: May 5, 2020
 *
 *********************************************************************************************************************/


#ifndef SCIMITAR7_EXPRESSION_H
#define SCIMITAR7_EXPRESSION_H

#include <memory>
#include "UserFunction.h"

/**
 * Base class implementation for arithmetic and conditional expressions which appear in the grammar. This class is an
 * abstract interface, and must be fully implemented in derived classes.
 */
class Expression {

public:
    /**
     * Enumeration of the implemented expression types.
     */
    enum Type {
        ARITHMETIC,
        CONDITIONAL
    };

    /**
     * Constructor.
     * @param type The high-level type of this expression.
     */
    Expression( Type type );

    /**
     * Destructor.
     */
    virtual ~Expression() = default;

    /**
     * Evaluates the expression in the context of the provided symbol scope and returns the result as a new symbol. The
     * members of the context may be modified by the execution of an evaluation. This method must be implemented by all
     * derived classes.
     * @param symbols The symbol scope in which to perform the evaluation of the expression.
     * @return The result of the evaluation as a new symbol instance.
     */
    virtual std::shared_ptr<Symbol> evaluate( SymbolScope symbols ) = 0;

    /**
     * Gets the type of this expression.
     * @return The type of this expression.
     */
    Type get_type();

private:
    /**
     * The type of this expression.
     */
    Type type;

};

#endif //SCIMITAR7_EXPRESSION_H
