//
// Created by loheac on 11/26/19.
//

#include <sstream>
#include <algorithm>
#include "EngineAuxiliary.h"

/**********************************************************************************************************************
 * ValuePair Struct Implementation
 *********************************************************************************************************************/
ValuePair::ValuePair( ValueType this_type, std::string this_identifier, std::string this_value, std::string this_format )
        : type( this_type ), identifier( this_identifier ), value( this_value ), format( this_format ) { }


/**********************************************************************************************************************
* DirectoryOrderPair Struct Implementation
*********************************************************************************************************************/
DirectoryOrderPair::DirectoryOrderPair( std::string this_identifier, unsigned int this_directory_order )
    : identifier( this_identifier ), directory_order( this_directory_order ) { }

bool DirectoryOrderPair::comp( const DirectoryOrderPair left, const DirectoryOrderPair right ) {
    return left.directory_order < right.directory_order;
}

/**********************************************************************************************************************
 * Run Class Implementation
 *********************************************************************************************************************/

Run::Run() : marked_remove( false ) { }

void Run::add_value( ValuePair value ) {
    values.push_back( value );
}

std::string Run::get_value( std::string identifier ) const {
    for ( auto iter = values.begin(); iter != values.end(); ++iter ) {
        if ( iter->identifier == identifier ) return iter->value;
    }

    throw EngineException( "Value requested from run does not exist." );
}

void Run::set_value( std::string identifier, std::string value ) {
    for ( auto iter = values.begin(); iter != values.end(); ++iter ) {
        if ( iter->identifier == identifier ) {
            iter->value = value;
            return;
        }
    }

    throw EngineException( "Value to be set in run does not exist." );
}

std::string Run::get_format( std::string identifier ) const {
    for ( auto iter = values.begin(); iter != values.end(); ++iter ) {
        if ( iter->identifier == identifier ) return iter->format;
    }

    throw EngineException( "Format requested from run does not exist." );
}

ValuePair::ValueType Run::get_type( std::string identifier ) const {
    for ( auto iter = values.begin(); iter != values.end(); ++iter ) {
        if ( iter->identifier == identifier ) return iter->type;
    }

    throw EngineException( "Value type requested from run does not exist." );
}

std::string Run::emit() {
    const char QUOTE = '"';
    std::stringstream ss;
    if ( not values.empty() ) ss << "{ ";

    for ( unsigned long i = 0; i < values.size(); i++ ) {
        ss << QUOTE << values.at( i ).identifier << QUOTE << " : " << QUOTE << values.at( i ).value << QUOTE;

        if ( i < values.size() - 1 ) {  // Current element is not the last.
            ss << ", ";
        } else {
            ss << " }";
        }
    }

    return ss.str();
}

void Run::mark_remove() {
    marked_remove = true;
}

bool Run::removed() {
    return marked_remove;
}

void Run::hide_parameters(  const std::vector<std::string> &hidden_parameters ) {
    for ( auto param : hidden_parameters ) {
        remove_value( param );
    }
}

void Run::remove_value( std::string identifier ) {
    // ASSERTION: Each pair in the run has a unique identifier. Only the first match (which should the the only one
    // which exists), will be removed.
    for ( auto iter = values.begin(); iter != values.end(); ++iter ) {
        if ( iter->identifier == identifier ) {
            values.erase( iter );
            return;
        }
    }
}

void Run::sort_values( std::vector<std::string> identifiers ) {
    // Verify the length of the vectors identifiers and values are equal.
    if ( identifiers.size() != values.size() )
        throw EngineException( "Length of run to be sorted does not match the number of provided identifiers." );

    // The following performs a bubble sort style algorithm. Presuming that the number of identifiers
    // in a script should be relatively small, this seems to be the least invasive and more flexible
    // approach. In principle this could be extended to sort different runs in different orders.
    for ( int i = 0; i < identifiers.size(); i++ ) {
        if ( identifiers.at( i ) == values.at( i ).identifier ) continue;

        // The run value at index i is not in the appropriate location. Find the current location of the value which
        // should be at index i, and swap.
        int swap = -1;  // Index of -1 indicates the identifier does not exist; an exception will be thrown.
        for ( int j = i + 1; j < values.size(); j++ ) {
            if ( values.at( j ).identifier == identifiers.at( i ) ) {
                swap = j;
                break;
            }
        }

        if ( swap == -1 ) throw EngineException( "Expected identifier did not exist when sorting run values." );

        // Perform swap.
        ValuePair tmp( values.at( swap ) );
        values[ swap ] = values[ i ];
        values[ i ] = tmp;
    }
}

SymbolScope Run::to_symbol_scope() {
    SymbolScope symbols;

    for ( auto iter = values.begin(); iter != values.end(); ++iter ) {
        if ( iter->type == ValuePair::ValueType::REAL ) {
            symbols.add_symbol( Symbol::Type::REAL, iter->identifier, iter->value );
        } else if ( iter->type == ValuePair::ValueType::INT ) {
            symbols.add_symbol( Symbol::Type::INT, iter->identifier, iter->value );
        }
    }

    return symbols;
}

/**********************************************************************************************************************
 * RunComparator Class Implementation
 *********************************************************************************************************************/
RunComparator::RunComparator( std::vector<std::string> this_directory_order )
        : directory_order( this_directory_order ) { }

bool RunComparator::operator()( const Run left, const Run right ) {
    // ASSUMPTION: The directory_order vector is sorted by the value of the directory order.
    for ( auto dir : directory_order ) {
        if ( left.get_value( dir ) == right.get_value( dir ) ) {
            continue;  // The parameter values at the current directory order are equal. Consider the next level down.
        } else {
            // In order to appropriately compare values, we must check if a value is a numeric or string type.
            if ( left.get_type( dir ) == ValuePair::ValueType::STRING ) {
                return left.get_value( dir ) < right.get_value( dir );
            } else if ( left.get_type( dir ) == ValuePair::ValueType::INT ) {  // Type is INT. Compare as a integer.
                return stoi( left.get_value( dir ) ) < stoi( right.get_value( dir ) );
            } else if ( left.get_type( dir ) == ValuePair::ValueType::REAL ) {  // Type is REAL. Compare as double.
                return stod( left.get_value( dir ) ) < stod( right.get_value( dir ) );
            } else { // Else, the ValueType is invalid, and we throw the exception below.
                throw EngineException( "Unknown parameter type provided when comparing runs." );
            }
        }
    }

    // If the two runs have equal values for all directory orders, then the two runs are considered equal.
    return false;
}


/**********************************************************************************************************************
 * ExecutionResult Class Implementation
 *********************************************************************************************************************/
ExecutionResult::ExecutionResult() : index( 0 ), emptyResultReturned( false ) { }

void ExecutionResult::reset() {
    index = 0;
}

Run ExecutionResult::next() {
    if ( runs.size() == 0 and not emptyResultReturned ) {
        emptyResultReturned = true;
        return Run();
    }

    if ( empty() ) throw EngineException( "Attempted to obtain run from an empty execution result." );

    Run next = runs.at( index );
    index++;
    return next;
}

long ExecutionResult::length() {
    return runs.size();
}

bool ExecutionResult::empty() {
    if ( runs.size() == 0 and not emptyResultReturned ) {
        return false;
    } else {
        return index >= runs.size();
    }
}

void ExecutionResult::add_run( Run run ) {
    runs.push_back( run );
}

void ExecutionResult::set_option_set( OptionSet this_options ) {
    options = this_options;
}

void ExecutionResult::set_directory_order( std::vector<std::string> this_directory_order ) {
    directory_order = this_directory_order;
}

void ExecutionResult::set_hidden_parameters( std::vector<std::string> hidden ) {
    hidden_parameters = hidden;

    // Remove hidden parameters.
    for ( auto run = runs.begin(); run != runs.end(); ++run ) {
        run->hide_parameters( hidden_parameters );
    }
}

std::string ExecutionResult::emit() {
    std::stringstream ss;

    const std::string RUN_LISTING_VAR_NAME( "RUN_LISTING" );
    const std::string DIR_ORDER_VAR_NAME( "DIR_ORDER" );
    const std::string OPTION_VAR_NAME( "OPTION" );

    // Write out run listing.
    ss << RUN_LISTING_VAR_NAME << " = [ ";
    for ( unsigned long i = 0; i < runs.size(); i++ ) {
        ss << runs.at( i ).emit();

        if ( i < runs.size() - 1 ) {  // Current element is not the last.
            ss << ", ";
        }
    }

    ss << " ]";

    // Write out directory order.
    ss << std::endl << DIR_ORDER_VAR_NAME << " = [ ";
    for ( unsigned long i = 0; i < directory_order.size(); i++ ) {
        ss << '"' << directory_order.at( i ) << '"';

        if ( i < directory_order.size() - 1 ) {  // Current element is not the last.
            ss << ", ";
        }
    }

    ss << " ]";

    // Write out updated options.
    ss << std::endl << OPTION_VAR_NAME << " = { ";
    for ( unsigned long i = 0; i < options.size(); i++ ) {
        ss << '"' << options.at( i ).option << "\" : \"" << options.at( i ).value << '"';

        if ( i < options.size() - 1 ) {  // Current element is not the last.
            ss << ", ";
        }
    }

    ss << " }";

    return ss.str();
}

void ExecutionResult::sort_runs( std::vector<std::string> identifiers ) {
    // Sort values within each run by the order in which they were defined.
    for ( auto iter = runs.begin(); iter != runs.end(); ++iter ) {
        iter->sort_values( identifiers );
    }

    // Sort runs according to their directory order.
    RunComparator comparator( directory_order );
    std::sort( runs.begin(), runs.end(), comparator );
}
