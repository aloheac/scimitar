//
// Created by loheac on 11/1/19.
//

#include <cassert>
#include <sstream>
#include "Group.h"

using namespace std;

/**********************************************************************************************************************
* Group Class Implementation
*********************************************************************************************************************/
Group::Group() : next_index( 0 ), len( 0 ), parameter_len( 0 ) {
    parameters = vector<Parameter*>();
}

Group::Group( Parameter* parameter ) : next_index( 0 ), len( 1 ), parameter_len( parameter->length() ) {
    parameters = vector<Parameter*>();
    parameters.push_back( parameter );
}

Group::~Group() { }

void Group::add_parameter( Parameter* parameter ) {
    if ( parameter == nullptr ) throw ParameterValueException( "[CRITICAL] Received null pointer to parameter." );

    if ( len == 0 ) {
        parameter_len = parameter->length();
    } else {
        if ( parameter->length() != parameter_len )
            throw ParameterValueException( "Attempted to add parameter to group of incompatible length." );
    }

    parameters.push_back( parameter );
    len++;
    assert( parameters.size() == len );
}

void Group::delete_parameter( std::string identifier ) {
    bool parameter_removed = false;
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        if ( (*iter)->get_identifier() == identifier ) {
            parameters.erase( iter );
            parameter_removed = true;
            break;
        }
    }

    len--;
    if ( not parameter_removed ) throw ParameterValueException( "Parameter requested to be removed from group not found." );
}

bool Group::has_parameter( std::string identifier ) {
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        if ( (*iter)->get_identifier() == identifier ) return true;
    }

    return false;
}

Parameter* Group::get_parameter( std::string identifier ) {
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        if ( (*iter)->get_identifier() == identifier ) return *iter;
    }

    throw ParameterValueException( "Requested parameter not found in group." );
}

vector<ValuePair> Group::get_next() {
    vector<ValuePair> values;

    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        // Establish the corresponding ValuePair type for this parameter's type.
        ValuePair::ValueType type;

        if ( (*iter)->get_type() == ParameterType::INT ) {
            type = ValuePair::ValueType::INT;
        } else if ( ( (*iter)->get_type() == ParameterType::REAL ) or ( (*iter)->get_type() == ParameterType::FUNCTION ) ) {
            type = ValuePair::ValueType::REAL;
        } else if ( (*iter)->get_type() == ParameterType::STRING ) {
            type = ValuePair::ValueType::STRING;
        } else throw ParameterValueException( "Unknown parameter type." );

        values.emplace_back( ValuePair( type, (*iter)->get_identifier(), (*iter)->get_formatted_next(), (*iter)->get_format() ) );
    }

    return values;
}

void Group::validate() {
    // Determine whether all parameters in the group are hidden. This information is required in the following steps.
    bool all_hidden = false;
    if ( parameters.size() == hidden_identifiers.size() ) all_hidden = true;

    if ( parameter_len > 1 ) {
        // Verify that at least a non-zero directory order is set on at least one parameter, unless all parameters are
        // hidden.
        bool validated = false;
        for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
            if ( ( *iter )->get_directory_order() > 0 ) {
                validated = true;
                break;
            }
        }

        if ( not validated and not all_hidden ) throw ParameterValueException( "Expected parameter group with length > 1 to have a non-zero directory order." );

        // Verify that the lengths of all group members match.
        int requiredLength = parameters[ 0 ]->length();
        for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
            if ( ( *iter )->length() != requiredLength )
                throw ParameterValueException( "Parameter value lengths of all group members must match." );
        }
    }
}

int Group::length() {
    return len;
}

int Group::parameter_length() {
    return parameter_len;
}

void Group::merge( Group group ) {
    // Verify that the lengths of this group and the group to merge match.
    if ( parameter_len != group.parameter_len ) throw ParameterValueException( "Lengths of groups to join do not match." );

    // Iterate over parameters within the passed group and add those members to this group.
    for ( auto iter = group.parameters.begin(); iter != group.parameters.end(); ++iter ) {
        parameters.push_back( *iter );
    }

    len += group.len;  // Update size of this group.
}

vector<Group> Group::split() {
    vector<Group> split_groups;

    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        split_groups.emplace_back( *iter );
    }

    return split_groups;
}

string Group::to_string() {
    stringstream ss;
    ss << "Group[ ";

    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        ss << (*iter)->to_string() << " ";
    }

    ss << "]";
    return ss.str();
}

void Group::reset() {
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        (*iter)->reset();
    }
}

bool Group::is_empty() {
    if ( len == 0 ) return true;
    bool empty = parameters.at( 0 )->is_empty();

    // Verify that all parameters agree with the first is_empty() result. If not, throw an exception.
    for ( auto iter = parameters.begin()++; iter != parameters.end(); ++iter ) {
        if ( not (*iter)->is_empty() == empty ) throw ParameterValueException( "Logic error encountered when determining if a group is empty." );
    }

    return empty;
}

void Group::hide_parameter( std::string identifier ) {
    // Verify the parameter exists in the group.
    if ( not has_parameter( identifier ) ) throw ParameterValueException( "Parameter identifier does not exist." );

    // Check if the identifier is already hidden.
    for ( auto id : hidden_identifiers ) {
        if ( id == identifier ) return;
    }

    // If it doesn't already exist, add it to the vector.
    hidden_identifiers.push_back( identifier );
}

bool Group::is_hidden( std::string identifier ) {
    for ( auto id : hidden_identifiers ) {
        if ( id == identifier ) return true;
    }

    return false;
}