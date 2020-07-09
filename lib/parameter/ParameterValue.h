/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Parameter value class definitions.
 *
 *    DESCRIPTION: This header file defines a series of classes which implement the concept of parameters and their
 *                 associated properties (including data type, data value, and formats) as defined in the Scimitar
 *                 language. The bulk of the logic behind processing the tokens which indicate the set of explicit
 *                 values a parameter can take (such as for lists and ranges) is provided through definitions given
 *                 here. A higher level of abstraction is provided through the Parameter class, which is exposed to
 *                 the compiler's Engine. The Parameter class, however, relies on this ParameterValue class (and its
 *                 derived classes) to implement the lower-level logic required for each data and data storage type.
 *
 *    CREATION DATE: October 23, 2019
 *
 *********************************************************************************************************************/


#ifndef SCIMITAR7_PARAMETERVALUE_H
#define SCIMITAR7_PARAMETERVALUE_H

#include <string>
#include <vector>
#include <random>
#include "../language/ArithmeticExpression.h"

/**
 * Enumeration of parameter types supported by the interpreter.
 */
enum ParameterType {
    INT,
    REAL,
    STRING,
    FUNCTION
};

/**
 * Base class implementation of a parameter value. A parameter is an object which represents a single parameter which
 * appears as an input to the target simulation. It enumerates a finite set of real values over which the parameter
 * will execute.
 *
 * There are two distinct types of parameters which are implemented:
 *
 *     - Constant parameters, which take on a set of values which are completely known and evaluated at the beginning
 *       of compiler execution. All elements appear as an ordered set within the internal generator object (a field of
 *       the parameter), and the size of this generator may be 1 or greater. Examples include the INT, REAL, and STRING
 *       types.
 *
 *     - Function parameters, whose values are not known at the beginning of compiler execution, and do not make use
 *       of the internal generator object. These are specialized objects which contain significant custom
 *       implementation within the evaluate_function() method, which may choose to accept arguments. These parameters
 *       are implemented by the FUNCTION type.
 *
 * Note that explicit base classes for these two types of parameters are not provided for simplicity and flexibility.
 *
 * The ParameterValue is a derived templated class whose template argument defines the internal data type that stores
 * elements of this parameter. The ParameterValueBase class abstracts away from this template with the restriction that
 * all parameter elements are provided as a formatted string, not as the internal type. Derived class implementations
 * are expected to provide a suitable conversion to a string. Since this formatted result is the required end product,
 * this base class is used throughout the Engine class.
 */
class ParameterValueBase {

public:

    /**
     * Constructor.
     * @param type Type of this parameter (as defined by the language).
     * @param str_value String representation of the value this parameter takes; generally the corresponding token.
     * @param format Format specifier of this parameter.
     */
    ParameterValueBase( ParameterType type, std::string str_value, std::string format );

    /**
     * Destructor; implemented as the compiler default.
     */
    virtual ~ParameterValueBase() = default;

    /**
     * Returns the next formatted value provided by the generator. If the generator has been exhausted, an empty
     * string is returned.
     * @return The next formatted value of the generator.
     */
    virtual std::string get_formatted_next();

    /**
     * Returns the formatted value provided by the generator at a given index.
     * @param i The index of the value to return.
     * @return The formatted value at index i.
     */
    virtual std::string formatted_at( int i );

    /**
     * Indicates whether the generator has been exhausted.
     * @return True if the generator has been exhausted, false otherwise.
     */
    virtual bool is_empty();

    /**
     * Gets the number of elements the parameter provides. In the case of function parameters, the length is always
     * defined to be 1.
     * @return Number of elements.
     */
    virtual int length();

    /**
     * Resets the state of the value generator to the first element.
     */
    virtual void reset();

    /**
     * Gets the contents of the value token which generated this parameter, as passed to the constructor.
     * @return The token string.
     */
    std::string get_str_value();

    /**
     * Returns a pretty-printed representation of this parameter. Generally used for debugging purposes.
     * @return A pretty-printed representation of this parameter.
     */
    virtual std::string to_string();

    /**
     * Sets the format string of this parameter.
     * @param format The format string of this parameter.
     */
    void set_format( std::string format );

    /**
     * Gets the format specifier.
     * @return The format specifier.
     */
    std::string get_format();

    /**
     * Gets the type of this parameter.
     * @return Type of this parameter.
     */
    ParameterType get_type();

protected:
    /**
     * Validates the state of internal fields, parses that data, and produces the generator of values for this
     * parameter. After this method completes, the parameter is ready for consumption by other classes which
     * expect to use it. In practice, this method should be called only by the constructor of ParameterValueBase
     * or one of its derived classes.
     *
     * The base class implementation performs no action, and must be implemented in derived classes.
     */
    virtual void validate();

    /**
     * Index of the next value for the generator to produce.
     */
    int next_index;

    /**
     * The number of parameter values which can be produced.
     */
    int len;

    /**
     * The data type of this parameter.
     */
    ParameterType type;

    /**
     * The value of this parameter as a string which was provided as input.
     */
    std::string str_value;

    /**
     * The format specifier for this parameter.
     */
    std::string format;

};

/**
 * Structure to hold elements of a range: the lower limit, upper limit, and step size.
 * @tparam T Class type of structure elements. The information should be numerical.
 */
template <class T> struct Range {
    T lower;  // Lower limit of the range.
    T step;   // Step size of the range.
    T upper;  // Upper limit of the range.
};

/**
 * Exception class which is thrown when a compile-time logic error is encountered within the ParameterValue class
 * of a derived class.
 */
class ParameterValueException : public std::exception {
public:

    /**
     * Constructor.
     * @param msg Error message associated with this exception
     */
    ParameterValueException( std::string msg );

    /**
     * Provides the exception's error message.
     * @return The error message.
     */
    virtual const char* what() const throw();

private:

    /**
     * The associated error message.
     */
    std::string msg;

};


/**
 * Templated base class implementation of a parameter. Derived from ParameterValueBase, and implements a variety of
 * overridden methods based on the parameter type (and corresponding internal representation T).
 * @tparam T The internal representation of the parameter values. Generally one of int, double, or std::string.
 */
template <class T>
class ParameterValue : public ParameterValueBase {

public:
    /**
     * Constructor.
     * @param type Type of this parameter (as defined by the language).
     * @param str_value String representation of the value this parameter takes; generally the corresponding token.
     * @param format Format specifier of this parameter.
     */
    ParameterValue( ParameterType type, std::string str_value, std::string format );

    /**
     * Obtains the next value provided by the generator as a string formatted according to the format specifier. Throws
     * an exception if the generator is empty, or if the format conversion fails.
     * @return The next available formatted value.
     */
    std::string get_formatted_next();

    /**
     * Obtains the parameter value at a specified index as a string formatted according to the format specifier. Throws
     * an exception if the index is out of range, or if the conversion fails.
     * @param i The index of the parameter value to obtain.
     * @return The formatted value at index i.
     */
    std::string formatted_at( int i );

    /**
     * Returns whether the generator is exhausted. Note that this does not indicate if the parameter contains zero
     * elements. This status will be reset upon a call to reset().
     * @return
     */
    bool is_empty();

    /**
     * Gets the number of elements the parameter provides. In the case of function parameters, the length is always
     * defined to be 1.
     * @return Number of elements.
     */
    virtual int length();

    /**
     * Resets the state of the generator to the first element.
     */
    virtual void reset();

    /**
     * Returns a pretty-printed representation of this parameter. Generally used for debugging purposes.
     * @return A pretty-printed representation of this parameter.
     */
    virtual std::string to_string();

protected:
    /**
     * Storage for the elements of this parameter. Used only for constant parameters.
     */
    std::vector<T> generator;

};

/**
 * Implementation of a parameter which behaves as a function which accepts zero or more arguments. This function is
 * evaluated independently for each run after the complete set of runs are generated. Therefore, function parameters
 * may not themselves increase the total number of runs executed by the resulting script; a function parameter is simply
 * a function of already existing parameters.
 *
 * Derived classes of ParameterFunction are expected to implement the function "evaluate_function" which returns a
 * std::string containing a string representation of the result. This function may generally accept any required
 * argument; by design, passing these arguments are handled in the Parameter::evaluate_function( Run ) method by case
 * for each derived class. The Parameter class abstractly exposes this evaluation to the Engine class using the current
 * Run instance as an argument. As such, the evaluate_function is not overridden in this base class for the purposes of
 * flexibility.
 */
class ParameterFunction : public ParameterValueBase {

public:
    /**
     * Constructor.
     * @param type Type of this parameter (as defined by the language).
     * @param str_value String representation of the value this parameter takes; generally the corresponding token.
     * @param format Format specifier of this parameter.
     */
    ParameterFunction( ParameterType type, std::string str_value, std::string format );

    /**
     * Returns a pretty-printed representation of this parameter. Generally used for debugging purposes.
     * @return A pretty-printed representation of this parameter.
     */
    virtual std::string to_string();
};

/**
 * Implementation of a real-valued, floating-point, constant parameter.
 */
class ValueReal : public ParameterValue<double> {

public:
    /**
     * Constructor.
     * @param str_value String representation of the value this parameter takes; generally the corresponding token.
     * @param format Format specifier of this parameter.
     */
    ValueReal( std::string str_value, std::string format );

    /**
     * Validates the value of the token and constructs the generator.
     */
    void validate() override;

    /**
     * Returns a pretty-printed representation of this parameter. Generally used for debugging purposes.
     * @return A pretty-printed representation of this parameter.
     */
    std::string to_string() override;

private:
    /**
     * Converts a Range object of type std::string to one of type double.
     * @param range Source Range instance to convert.
     * @return Converted Range of type double.
     */
    static Range<double> range_stod( Range<std::string> range );

};

/**
 * Implementation of an integer, constant parameter.
 * The internal representation of the integer is a long, and may take multiple values which are stored and provided by
 * the generator.
 */
class ValueInt : public ParameterValue<long> {

public:
    /**
     * Constructor.
     * @param str_value String representation of the value this parameter takes; generally the corresponding token.
     * @param format Format specifier of this parameter.
     */
    ValueInt( std::string str_value, std::string format );

    /**
     * Validates the provided token, converts its representation, and populates the generator. Throws an exception if
     * the token cannot be parsed as expected.
     */
    void validate() override;

    /**
     * Returns a pretty-printed representation of this parameter. Generally used for debugging purposes.
     * @return A pretty-printed representation of this parameter.
     */
    std::string to_string() override;

private:
    /**
     * Utility function to convert a numerical string value to an integer which is rounded to the nearest value
     * using desired behavior. Intended to handle situations where the input string is possibly floating point.
     * Ranges and lists are expected to be resolved prior to a call; input strings should be a single value.
     * @param val Numerical value to parse.
     * @return Rounded integer representation of the input value.
     */
    static long str_to_long( std::string val );

    /**
     * Utility function to convert a Range of strings to a Range of integers.
     * @param range The Range of std::string types to convert.
     * @return The Range converted to a Range of integers.
     */
    static Range<long> range_stol( Range<std::string> range );

};

/**
 * Implementation of a constant string-type parameter.
 */
class ValueString: public ParameterValue<std::string> {

public:

    /**
     * Constructor.
     * @param str_value String representation of the value this parameter takes; generally the corresponding token. Note
     * that the token is expected to be enclosed in double quotes, where the first character is a double quote.
     */
    ValueString( std::string str_value );

    /**
     * Validates the provided token and populates the generator. Throws an exception if the token cannot be parsed as
     * expected.
     */
    void validate() override;

    /**
     * Returns a pretty-printed representation of this parameter. Generally used for debugging purposes.
     * @return A pretty-printed representation of this parameter.
     */
    std::string to_string() override;

};

/**
 * Implementation of a function parameter which accepts other parameters as arguments.
 */
class ValueFunction: public ParameterFunction {
public:

    /**
     * Constructor.
     * @param expr Expression object for this function.
     * @param format Format specifier for this parameter.
     */
    ValueFunction( std::shared_ptr<ArithmeticExpression> expr, std::string format );

    /**
     * Returns a pretty-printed representation of this parameter. Generally used for debugging purposes.
     * @return A pretty-printed representation of this parameter.
     */
    std::string to_string() override;

    /**
     * Evaluates the function at the parameters specified by the run, and returns the formatted result. Intermediate
     * evaluations are performed using double precision.
     * @param run The run containing the parameter values at which the function is evaluated,
     * @return The formatted result according to the stored format specifier.
     */
    std::string evaluate_function( SymbolScope symbols );

    /**
     * Updates the stored expression.
     * @param expr The new function.
     */
    void set_function( std::shared_ptr<ArithmeticExpression> expr );

private:
    /**
     * The expression which will be evaluated.
     */
    std::shared_ptr<ArithmeticExpression> expr;

};

#endif //SCIMITAR7_PARAMETERVALUE_H
