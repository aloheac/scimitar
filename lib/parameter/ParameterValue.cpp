/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Parameter value class implementations.
 *
 *    DESCRIPTION: This file implements a series of classes which implement the concept of parameters and their
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


#include <cstdio>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <boost/algorithm/string/trim.hpp>
#include "ParameterValue.h"
#include "../frontend/ParserFrontend.h"

using namespace std;

// Macro variable defines the character buffer length used in calls to sprintf(), which is used to apply formats to
// parameter values. This value will need to be increased if the number of characters in any formatted value exceeds
// this set value. This is accessed in ParameterValue::formatted_at() and ValueFunction::evaluate_function().
#define CHAR_BUFFER_LENGTH 64


/**********************************************************************************************************************
 * ParameterBase Class Implementation
 *********************************************************************************************************************/
ParameterValueBase::ParameterValueBase( ParameterType this_type, string this_str_value, string this_format )
    : type( this_type ), str_value( this_str_value ), format( this_format ), next_index( 0 ), len( 0 ) { }

std::string ParameterValueBase::get_formatted_next() {
    next_index++;
    return "nan";
}

std::string ParameterValueBase::formatted_at( int i ) {
    return "nan";
}

bool ParameterValueBase::is_empty() {
    return next_index == len;
}

int ParameterValueBase::length() {
    return len;
}

void ParameterValueBase::reset() {
    next_index = 0;
}

string ParameterValueBase::get_str_value() {
    return str_value;
}

string ParameterValueBase::to_string() {
    return "invalid";
}

void ParameterValueBase::validate() { }

void ParameterValueBase::set_format( std::string this_format ) {
    format = this_format;
}

std::string ParameterValueBase::get_format() {
    return format;
}

ParameterType ParameterValueBase::get_type() {
    return type;
}

/**********************************************************************************************************************
 * ParameterValueException Class Implementation
 *********************************************************************************************************************/
ParameterValueException::ParameterValueException( std::string this_msg ) : exception(), msg( this_msg ) { }

const char* ParameterValueException::what() const throw() {
    return msg.c_str();
}


/**********************************************************************************************************************
 * ParameterValue Class Implementation
 *********************************************************************************************************************/
template <class T>
ParameterValue<T>::ParameterValue( ParameterType this_type, std::string this_str_value, std::string this_format )
    : ParameterValueBase( this_type, this_str_value, this_format ) {
    generator = std::vector<T>();
    validate();
}

template <class T>
string ParameterValue<T>::get_formatted_next() {
    if ( generator.empty() ) throw ParameterValueException( "Requested next formatted numerical value for an empty generator." );

    string next = formatted_at( next_index );
    next_index++;
    return next;
}

template <class T>
string ParameterValue<T>::formatted_at( int i ) {
    if ( generator.empty() ) throw ParameterValueException( "Requested formatted numerical value for an empty generator." );
    if ( i < 0 or i >= generator.size() ) throw ParameterValueException( "Generator index is out of range." );

    stringstream ss_format, ss_value;
    if ( format == "" ) {  // If no format is specified, use the default behavior of the insertion operator.
        ss_value << generator[ i ];
        return ss_value.str();
    } else {  // Otherwise, if a format is specified, apply the format.
        char buffer[ CHAR_BUFFER_LENGTH ];
        int result;

        ss_format << format;
        T value = generator[ i ];
        result = sprintf( buffer, ss_format.str().c_str(), value );

        if ( result < 0 ) throw ParameterValueException( "Failed value format conversion." );
        return string( buffer );
    }
}

template <class T>
bool ParameterValue<T>::is_empty() {
    return generator.empty() or ( next_index >= generator.size() );
}

template <class T>
int ParameterValue<T>::length() {
    return len;
}

template <class T>
void ParameterValue<T>::reset() {
    next_index = 0;  // Reset index of the next element to return.
}

template <class T>
string ParameterValue<T>::to_string() {
    return "ParameterValue[]";
}


/**********************************************************************************************************************
 * ParameterFunction Class Implementation
 *********************************************************************************************************************/
ParameterFunction::ParameterFunction( ParameterType this_type, std::string this_str_value, std::string this_format )
        : ParameterValueBase( this_type, this_str_value, this_format ) { }

std::string ParameterFunction::to_string() {
    return "invalid";
}

/**
 * Simple check to see if a parameter value may match a range (but does not verify it is a range). Checks if there are
 * two (and only two) ':' characters in the value, and if there are at least five characters in total. Returns false if
 * a comma is found in the string; the input should be checked if it matches a list. Final verification of the
 * sub-tokens is left to the implementation of the derived ParameterValue class.
 * @param value String to check for interpretation as a range.
 * @return True if the value may further be interpreted as a range, false otherwise.
 */
bool check_if_possible_range( string value ) {
    if ( value.length() < 5 ) return false;

    // Iterate over string and count number of ':' characters which appear.
    int n_chars = 0;
    for ( int i = 0; i < value.length(); i++ ) {
        if ( value.at( i ) == ':' ) {
            n_chars++;
        } else if ( value.at( i ) == ',' ) return false;  // Value cannot be a range if a comma exists.
    }

    return n_chars == 2;
}


/**
 * Simple check to see if a parameter value may match a list (but does not verify if the list elements are well-formed).
 * If this function returns true on a passed value, the parser should continue to interpret the value as a list.
 * Note in this case, a list is not defined as a single element (e.g., 5 or [5]).
 * @param value String to check for interpretation as a list.
 * @return True if the value may further be interpreted as a list, false otherwise.
 */
bool check_if_possible_list( string value ) {
    if ( value.length() < 5 ) return false;  // Smallest possible list is 5 characters (e.g., [5,2]).
    boost::algorithm::trim( value );  // Trim off leading and trailing whitespace.

    // Verify the value string begins with an opening bracket.
    if ( value.at( 0 ) == '[' ) {
        value.erase( 0, 1 );
    }  else {
        return false;
    }

    // Verify the value string ends with a closing bracket.
    if ( value.at( value.length() - 1 ) == ']' ) {
        value.erase( value.length() - 1, 1 );
    } else {
        return false;
    }

    // Iterate over string and determine if a comma exists.
    for ( int i = 0; i < value.length(); i++ ) {
        if ( value.at( i ) == ',' ) {
            return true;
        }
    }

    return false;
}

/**
 * Simplifies a trivial list (e.g., [5]) to its single element by trimming leading and trailing whitespace and removing
 * the opening and closing brackets, if they exist.
 * @param value The value to be trimmed.
 * @return The trimmed string.
 */
std::string trim_trivial_list( std::string value ) {
    boost::algorithm::trim( value );  // Trim off leading and trailing whitespace.
    if ( value.at( 0 ) == '[' ) value.erase( 0, 1 );  // Remove opening bracket.
    if ( value.at( value.length() - 1 ) == ']' ) value.erase( value.length() - 1, 1 );  // Remove closing bracket.

    return value;
}

/**
 * Removes leading and trailing whitespace and opening and closing quotes from a string literal, and returns the
 * characters of the string.
 * @param value The string literal to trim.
 * @return The characters contained within the string.
 */
std::string trim_string( std::string value ) {
    boost::algorithm::trim( value );  // Trim off leading and trailing whitespace.

    // Remove opening quote, and enforce syntax of strings.
    if ( value.at( 0 ) == '"' ) {
        value.erase( 0, 1 );
    } else {
        throw ParameterValueException( "Expected '\"' when opening string." );
    }

    // Remove closing quote, and enforce syntax of strings.
    if ( value.at( value.length() - 1 ) == '"' ) {
        value.erase( value.length() - 1, 1 );
    } else {
        throw ParameterValueException( "Expected '\"' when closing string." );
    }

    return value;
}


/**
 * Splits a range into its component tokens: the lower limit, step, and upper limit. The string must contain no
 * whitespace, and expects the range to be well-formatted. An exception is thrown if formatting expectations are not
 * met.
 * @param value String representation of the range to split.
 * @return A Range instance with the lower, step, and upper fields set as std::string instances.
 */
Range<string> split_range( string value ) {
    // A string has a minimum length of 5 characters to be a valid string (e.g., a:b:c). Check that the passed value
    // meets this requirement, if not, throw an exception.
    if ( value.length() < 5 ) throw ParameterValueException( "Invalid range passed to be split." );

    int first_sep, second_sep;  // Holds locations in string for the first and second separator characters.

    first_sep = value.find( ":" );  // Find location of the first separator.

    // If a separator does not exist, or it is at the end of the string, throw an exception.
    if ( first_sep == string::npos or first_sep == value.length() - 1 ) throw ParameterValueException( "Expected range separator ':' in value." );
    second_sep = value.substr( first_sep + 1 ).find( ":" ) + first_sep + 1;  // Find the location of the second separator.

    // If the second separator does not exist, or it is at the end of the string, throw an exception.
    if ( second_sep == string::npos or second_sep == value.length() - 1 ) throw ParameterValueException( "Expected second range separator ':' in value." );

    // Construct the range by substring according to the pattern lower:step:upper.
    Range<string> r;
    r.lower = value.substr( 0, first_sep );
    r.step = value.substr( first_sep + 1, second_sep - first_sep - 1 );
    r.upper = value.substr( second_sep + 1 );

    return r;
}

/**
 * Splits a list into its component tokens. An exception is thrown if formatting expectations are not met.
 * @param value String representation of the list to split.
 * @return A vector instance with the list elements as std::string instances.
 */
vector<string> split_list( string value ) {
    vector<string> list;
    boost::algorithm::trim( value );  // Trim leading and trailing whitespace.

    // Remove opening bracket (first character).
    if ( value.at( 0 ) == '[' ) {
        value.erase( 0, 1 );
    }  else {
        throw ParameterValueException( "Expected '[' at the beginning of a list." );
    }

    // Remove closing bracket (last character).
    if ( value.at( value.length() - 1 ) == ']' ) {
        value.erase( value.length() - 1, 1 );
    } else {
        throw ParameterValueException( "Expected ']' at the end of a list." );
    }

    size_t current_pos, previous_pos = 0;
    current_pos = value.find( ',' );
    if ( current_pos == string::npos ) throw ParameterValueException( "Expected list separator ',' in value." );

    while ( current_pos != string::npos ) {
        if ( current_pos == value.size() - 1 ) throw ParameterValueException( "Badly formed list." );
        list.push_back( value.substr( previous_pos, current_pos - previous_pos ) );
        previous_pos = current_pos + 1;  // Skip delimiter.
        current_pos = value.find( ',', current_pos + 1 );
    }

    list.push_back( value.substr( previous_pos, current_pos - previous_pos ) );

    return list;
}


/**
 * Expands a range into a vector of all elements the range represents. Handles negative step sizes.
 * @tparam T Internal numerical data type of the parameter.
 * @param range Range with the upper and lower limits and step size specified.
 * @return A populated vector containing all elements of the range.
 */
template <typename T> vector<T> expand_range( const Range<T> range ) {
    vector<T> expanded_range;

    // Throw an exception if the step size is zero. This will lead to an infinite loop otherwise.
    if ( range.step == 0 ) throw ParameterValueException( "Step size in range cannot be zero." );

    // If the step is negative, handle the case separately.
    if ( range.step > 0 ) {
        for ( T i = range.lower; i < range.upper; i += range.step ) {
            expanded_range.push_back( i );
        }
    } else {
        for ( T i = range.lower; i > range.upper; i += range.step ) {
            expanded_range.push_back( i );
        }
    }

    return expanded_range;
}

/**********************************************************************************************************************
 * ValueReal Class Implementation
 *********************************************************************************************************************/
ValueReal::ValueReal( std::string this_str_value, std::string this_format ) : ParameterValue<double>( ParameterType::REAL, this_str_value, this_format ) {
    validate();
}

void ValueReal::validate() {
    if ( check_if_possible_range( str_value ) ) {
        // Split range into upper and lower limits, and step size.
        Range<double> range = range_stod( split_range( trim_trivial_list( str_value ) ) );

        // Populate generator with elements of range.
        vector<double> expanded_range = expand_range<double>( range );
        generator.insert( generator.begin() + generator.size(), expanded_range.begin(), expanded_range.end() );

    } else if ( check_if_possible_list( str_value ) ) {
        vector<string> str_list = split_list( str_value );

        for ( vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); ++iter ) {
            try {
                // Check if the current list element is a possible range. If so, expand the range and push all elements in generator.
                if ( check_if_possible_range( *iter ) ) {
                    Range<double> range = range_stod( split_range( trim_trivial_list( *iter ) ) );
                    vector<double> expanded_range = expand_range<double>( range );
                    generator.insert( generator.begin() + generator.size(), expanded_range.begin(), expanded_range.end() );
                } else {
                    generator.push_back( stod( *iter ) );
                }
            } catch ( const invalid_argument &e ) {
                throw ParameterValueException( "Invalid conversion of list token to a real value." );
            } catch ( const out_of_range &e ) {
                throw ParameterValueException( "Overflow in conversion of list token to a double-precision real value." );
            }
        }
    } else {
        double value;

        try {
            value = stod( trim_trivial_list( str_value ) );
        } catch ( const invalid_argument &e ) {
            throw ParameterValueException( "Invalid conversion of token to a real value." );
        } catch ( const out_of_range &e ) {
            throw ParameterValueException ( "Overflow in conversion of token to a double-precision real value." );
        }

        generator.push_back( value );
    }

    len = generator.size();
}

string ValueReal::to_string() {
    stringstream ss;

    ss << "Real[ ";

    for ( int i = 0; i < generator.size(); i++ ) {
        ss << formatted_at( i );
        if ( i != generator.size() - 1 ) ss << ", ";
    }

    ss << " ]";

    return ss.str();
}


Range<double> ValueReal::range_stod( Range< std::string > str_range ) {
    Range<double> dbl_range;

    try {
        dbl_range.lower = stod( str_range.lower );
        dbl_range.step = stod( str_range.step );
        dbl_range.upper = stod( str_range.upper );
    } catch ( const invalid_argument &e ) {
        throw ParameterValueException( "Invalid conversion of range token to a real value." );
    } catch ( const out_of_range &e ) {
        throw ParameterValueException( "Overflow in conversion of range token to a double-precision real value." );
    }

    return dbl_range;
}

/**********************************************************************************************************************
 * ValueInt Class Implementation
 *********************************************************************************************************************/
ValueInt::ValueInt( std::string this_str_value, std::string this_format ) : ParameterValue<long>( ParameterType::INT, this_str_value, this_format ) {
    if ( format.empty() ) format = "%i";  // Set a default format if the provided format string is empty.
    validate();
}


void ValueInt::validate() {
    if ( check_if_possible_range( str_value ) ) {
        // Split range into upper and lower limits, and step size.
        Range<string> str_range = split_range( str_value );
        Range<long> range = range_stol( str_range );

        // Populate generator with elements of range.
        vector<long> expanded_range = expand_range<long>( range );
        generator.insert( generator.begin() + generator.size(), expanded_range.begin(), expanded_range.end() );
    } else if ( check_if_possible_list( str_value ) ) {
        vector<string> str_list = split_list( str_value );

        for ( vector<string>::iterator iter = str_list.begin(); iter != str_list.end(); ++iter ) {
            try {
                // Check if the current list element is a possible range. If so, expand the range and push all elements in generator.
                if ( check_if_possible_range( *iter ) ) {
                    Range<long> range = range_stol( split_range( trim_trivial_list( *iter ) ) );
                    vector<long> expanded_range = expand_range<long>( range );
                    generator.insert( generator.begin() + generator.size(), expanded_range.begin(), expanded_range.end() );
                } else {
                    generator.push_back( str_to_long( *iter ) );
                }
            } catch ( const invalid_argument &e ) {
                throw ParameterValueException( "Invalid conversion of list token to an integer value." );
            } catch ( const out_of_range &e ) {
                throw ParameterValueException( "Overflow in conversion of list token to a double-precision integer value." );
            }
        }
    } else {
        long value;

        try {
            value = str_to_long( trim_trivial_list( str_value ) );
        } catch ( const invalid_argument &e ) {
            throw ParameterValueException( "Invalid conversion of token to an integer value." );
        } catch ( const out_of_range &e ) {
            throw ParameterValueException ( "Overflow in conversion of token to an integer value." );
        }

        generator.push_back( value );
    }

    len = generator.size();
}

string ValueInt::to_string() {
    stringstream ss;

    ss << "Int[";

    for ( int i = 0; i < generator.size(); i++ ) {
        ss << formatted_at( i );
        if ( i != generator.size() - 1 ) ss << ", ";
    }

    ss << "]";

    return ss.str();
}

long ValueInt::str_to_long( string val ) {
    double fp_val;

    // Convert the string to a double-precision value.
    try {
        fp_val = stof( val );
    } catch ( const invalid_argument &e ) {
        throw ParameterValueException( "Invalid conversion of token to a floating-point value." );
    } catch ( const out_of_range &e ) {
        throw ParameterValueException( "Overflow in conversion of token to a floating-point value." );
    }

    // Round to the nearest integer value.
    long int_val = lround( fp_val );
    return int_val;
}

Range<long> ValueInt::range_stol( Range<std::string> str_range ) {
    Range<long> lng_range;

    try {
        lng_range.lower = str_to_long( str_range.lower );
        lng_range.step = str_to_long( str_range.step );
        lng_range.upper = str_to_long( str_range.upper );
    } catch ( const invalid_argument &e ) {
        throw ParameterValueException( "Invalid conversion of range token to an integer value." );
    } catch ( const out_of_range &e ) {
        throw ParameterValueException( "Overflow in conversion of range token to a double-precision integer value." );
    }

    return lng_range;
}

/**********************************************************************************************************************
 * ValueString Class Implementation
 *********************************************************************************************************************/
ValueString::ValueString( std::string this_str_value ) : ParameterValue<string>( ParameterType::STRING, this_str_value, "" ) {
    validate();
}

void ValueString::validate() {
    if ( check_if_possible_list( str_value ) ) {  // Input is expected to be a list of strings.
        vector<string> list = split_list( str_value );

        for ( auto iter = list.begin(); iter != list.end(); ++iter ) {
            generator.push_back( trim_string( *iter ) );
        }
    } else {  // Input is treated as a single element.
        generator.push_back( trim_string( str_value ) );
    }

    len = generator.size();
}

string ValueString::to_string() {
    stringstream ss;

    ss << "String[";

    for ( auto iter = generator.begin(); iter != generator.end(); ++iter ) {
        ss << *iter << ",";
    }

    ss << "]";

    return ss.str();
}


/**********************************************************************************************************************
 * ValueFunction Class Implementation
 *********************************************************************************************************************/
ValueFunction::ValueFunction( std::shared_ptr<ArithmeticExpression> this_expr, std::string this_format )
    : ParameterFunction( ParameterType::FUNCTION, "<function>", this_format ), expr( this_expr ) {
    len = 1;
}

std::string ValueFunction::to_string() {
    return "ValueFunction";
}

std::string ValueFunction::evaluate_function( SymbolScope symbols ) {
    std::shared_ptr<Symbol> result = expr->evaluate( symbols );
    if ( result->get_type() != Symbol::Type::REAL ) throw ParameterValueException( "Incorrect return type." );
    double dbl_result = std::dynamic_pointer_cast< TypedSymbol<double> >( result )->get_data();

    // Perform formatted conversion. Same method as in ParameterValue::formatted_at().
    stringstream ss_format, ss_value;
    if ( format == "" ) {  // If no format is specified, use the default behavior of the insertion operator.
        ss_value << dbl_result;
        return ss_value.str();
    } else {  // Otherwise, apply the format.
        char buffer[ CHAR_BUFFER_LENGTH ];
        int result;

        ss_format << format;
        result = sprintf( buffer, ss_format.str().c_str(), dbl_result );

        if ( result < 0 ) throw ParameterValueException( "Failed value format conversion." );

        return string( buffer );
    }
}

void ValueFunction::set_function( std::shared_ptr<ArithmeticExpression> this_expr ) {
    expr = this_expr;
}


/*
 * Explicit template class instantiations.
 */
template class ParameterValue<double>;
template class ParameterValue<int>;
template class ParameterValue<string>;