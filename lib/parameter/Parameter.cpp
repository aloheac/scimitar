/**********************************************************************************************************************
 * Scimitar 7 - A tool for parameter-space exploration.
 * Compiler Library Implementation
 *
 * Copyright (c) 2013-2020 Andrew C. Loheac, Joaquin E. Drut, et al.
 * See LICENSE.TXT distributed with the source for for license information.
 *
 *    Parameter class implementation.
 *
 *    DESCRIPTION: This file provides an implementation the concept of a parameter in the Scimitar language, and its
 *                 interface between the compiler's Engine which executes the end-to-end logic. This class is dependent
 *                 on the ParameterValueBase class and its subtypes to implement the details of each parameter type; a
 *                 reference to the polymorphic object is created for each Parameter instance. This class stores
 *                 additional data about each parameter which is not visible to the corresponding ParameterValue object,
 *                 including the parameter's identifier and its directory order. A variety of "getters" and "setters"
 *                 are provided to configure all parameters from a common interface.
 *
 *    CREATION DATE: October 30, 2019
 *
 *********************************************************************************************************************/


#include <sstream>
#include "Parameter.h"

Parameter::Parameter( ParameterType this_type, std::string this_identifier, std::string this_value, std::string format )
    : type( this_type ), identifier( this_identifier ), directory_order( 0 ) {

    if ( type == ParameterType::REAL ) {
        value = new ValueReal( this_value, format );
    } else if ( type == ParameterType::INT ) {
        value = new ValueInt( this_value, format );
    } else if ( type == ParameterType::STRING ) {
        value = new ValueString( this_value );
    } else {
        throw ParameterValueException( "Invalid parameter type." );
    }
}

Parameter::Parameter( std::string this_identifier, std::shared_ptr<ArithmeticExpression> expr, std::string format )
    : type( ParameterType::FUNCTION ), identifier( this_identifier ), directory_order( 0 ) {
    // If this constructor is called, the parameter type is automatically assumed to be a function.
    value = new ValueFunction( expr, format );
}

Parameter::~Parameter() {
    delete value;
}

void Parameter::set_directory_order( int order ) {
    if ( order < 0 ) throw ParameterValueException( "Directory order must be positive." );
    directory_order = order;
}

unsigned int Parameter::get_directory_order() {
    return directory_order;
}

void Parameter::set_format( std::string format ) {
    value->set_format( format );
}

std::string Parameter::get_format() {
    return value->get_format();
}

std::string Parameter::get_formatted_next() {
    return value->get_formatted_next();
}

std::string Parameter::formatted_at( int i ) {
    return value->formatted_at( i );
}

std::string Parameter::get_identifier() {
    return identifier;
}

void Parameter::set_value( std::string this_value ) {
    // Remove the old parameter.
    std::string format = value->get_format();  // Retain the previous format.
    delete value;

    if ( type == ParameterType::REAL ) {
        value = new ValueReal( this_value, format );
    } else if ( type == ParameterType::INT ) {
        value = new ValueInt( this_value, format );
    } else if ( type == ParameterType::STRING ) {
        value = new ValueString( this_value );
    } else {
        throw ParameterValueException( "Invalid parameter type." );
    }
}

void Parameter::set_value( std::shared_ptr<ArithmeticExpression> expr ) {
    if ( type != ParameterType::FUNCTION )
        throw ParameterValueException( "Expected type to be function when assigning a new function." );

    ValueFunction* func = dynamic_cast<ValueFunction*>( value );
    func->set_function( expr );
}

std::string Parameter::get_value() {
    return value->get_str_value();
}

int Parameter::length() {
    return value->length();
}

std::string Parameter::to_string() {
    std::stringstream ss;
    ss << identifier << " -> " << value->to_string();
    return ss.str();
}

void Parameter::reset() {
    value->reset();
}

bool Parameter::is_empty() {
    return value->is_empty();
}

ParameterType Parameter::get_type() {
    return value->get_type();
}

std::string Parameter::evaluate_function( SymbolScope symbols ) {
    if ( value->get_type() == ParameterType::FUNCTION ) {
        return dynamic_cast<ValueFunction*>( value )->evaluate_function( symbols );
    } else {
        throw ParameterValueException( "Attempted to evaluate a function on a non-function parameter type." );
    }
}