/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Parameter class definition.
 *
 *    DESCRIPTION: This header file defines an implementation the concept of a parameter in the Scimitar language, and
 *                 its interface between the compiler's Engine which executes the end-to-end logic. This class is
 *                 dependent on the ParameterValueBase class and its subtypes to implement the details of each parameter
 *                 type; a reference to the polymorphic object is created for each Parameter instance. This class stores
 *                 additional data about each parameter which is not visible to the corresponding ParameterValue object,
 *                 including the parameter's identifier and its directory order. A variety of "getters" and "setters"
 *                 are provided to configure all parameters from a common interface.
 *
 *    CREATION DATE: October 30, 2019
 *
 *********************************************************************************************************************/


#ifndef SCIMITAR7_PARAMETER_H
#define SCIMITAR7_PARAMETER_H

#include <string>
#include "ParameterValue.h"

/**
 * Implements a parameter of a given type, identifier, value, and format. The interface provided by this class is
 * visible to other parts of the compiler. Note this class abstracts away the internal storage type of a parameter,
 * which is apparent in the ParameterValue class.
 */
class Parameter {

public:

    /**
     * Constructor for parameters whose value can be expressed using a string. Valid types are REAL, INT, and STRING.
     * @param type The parameter type. One of REAL, INT, or STRING.
     * @param identifier The unique identifier of this parameter.
     * @param value The value this parameter takes. May be a singleton, list, or a range, as defined by the grammar.
     * @param format The format this parameter takes, as defined by the grammar.
     */
    Parameter( ParameterType type, std::string identifier, std::string value, std::string format );

    /**
     * Constructor for function parameter. The type is set to ParameterType::FUNCTION.
     * @param identifier The unique identifier of this parameter.
     * @param expr The expression object of this parameter which will be evaluated for each run upon compilation.
     * @param format The format this parameter takes, as defined by the grammar.
     */
    Parameter( std::string identifier, std::shared_ptr<ArithmeticExpression> expr, std::string format );

    /**
     * Destructor.
     */
    ~Parameter();

    /**
     * Sets the directory order of this parameter. Setting order to 0 indicates a subdirectory will not be created for
     * this parameter.
     * @param order The new directory order to be assigned.
     */
    void set_directory_order( int order );

    /**
     * Gets the current directory order of this parameter.
     * @return The current directory order.
     */
    unsigned int get_directory_order();

    /**
     * Sets the format of this parameter.
     * @param format The new format to be assigned.
     */
    void set_format( std::string format );

    /**
     * Gets the current format of this parameter.
     * @return The current format.
     */
    std::string get_format();

    /**
     * Obtains the next value of this parameter provided by the internal generator. The value is formatted according
     * to the current format specifier, and is returned as a string. See the reset() method to reset the state of the
     * internal generator back to the first element.
     * @return The next formatted value of this parameter.
     */
    std::string get_formatted_next();

    /**
     * Obtains the value of this parameter by the value's index. The index corresponds to the order in which values
     * are provided by the internal generator. Note that the get_formatted_next() method is the preferred way to
     * iterate over the set of all values provided by this parameter.
     * @param i The index of the parameter value to access.
     * @return The value of this parameter at index i.
     */
    std::string formatted_at( int i );

    /**
     * Gets the unique identifier of this parameter.
     * @return The identifier of this parameter.
     */
    std::string get_identifier();

    /**
     * Sets the value of this parameter to a new value. The previous value is deleted, but the parameter's format is
     * retained. The parameter type of the new type must be the same as the previous type, which must be one of REAL,
     * INT, STRING, or RAND.
     * @param value The new value to be assigned to this parameter.
     */
    void set_value( std::string value );

    /**
     * Sets the value of this parameter to a new function expression. This method may only be called when this
     * parameter's type is set to FUNCTION. The previous expression is deleted, but the parameter's format is
     * retained.
     * @param expr The new expression to be assigned to this parameter.
     */
    void set_value( std::shared_ptr<ArithmeticExpression> expr );

    /**
     * Gets the string representation of this parameter's value.
     * @return The string representation of this parameter's value.
     */
    std::string get_value();

    /**
     * Gets a pretty-printed representation of this parameter. Indicates the identifier and value.
     * @return A pretty-printed representation of this parameter.
     */
    std::string to_string();

    /**
     * Gets the length of this parameter. The length indicates the number of values this parameter takes on which will
     * contribute to the overall number of runs which will be executed. This may not correspond to the number of unique
     * values this parameter may produce: for instance RAND and FUNCTION types will always have a length of 1.
     * @return The length of this parameter.
     */
    int length();

    /**
     * Resets the state of the internal generator back to the first element.
     */
    void reset();

    /**
     * Returns true of the internal generator will produce no additional values, and false otherwise.
     * @return True if the generator is empty, false otherwise.
     */
    bool is_empty();

    /**
     * Gets the type of this parameter.
     * @return The type of this parameter.
     */
    ParameterType get_type();

    /**
     * Evaluates the parameter's function expression on a Run instance, where the function may accept zero or more of
     * the Run's parameters as arguments. The result of the function evaluation is formatted according to the
     * parameter's format specifier and is returned as a string. Note that this method must only be called if the
     * parameter's type is FUNCTION.
     * @param symbols The Run instance whose parameters will be passed as arguments to the function.
     * @return The formatted result of the function evaluation.
     */
    std::string evaluate_function( SymbolScope symbols );

private:

    /**
     * The unique identifier of this parameter.
     */
    std::string identifier;

    /**
     * The directory order of this parameter.
     */
    unsigned int directory_order;

    /**
     * The assigned type of this parameter.
     */
    ParameterType type;

    /**
     * The parameter value object which contains all related logic and data. The derived type which is constructed is
     * determined by the parameter's type.
     */
    ParameterValueBase* value;

};


#endif //SCIMITAR7_PARAMETER_H
