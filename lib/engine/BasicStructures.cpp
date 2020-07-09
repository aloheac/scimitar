//
// Created by loheac on 12/21/19.
//

#include "BasicStructures.h"

/**********************************************************************************************************************
 * EngineException Class Implementation
 *********************************************************************************************************************/
EngineException::EngineException( std::string this_msg ) : exception(), msg( this_msg ) { }

const char* EngineException::what() const throw() {
    return msg.c_str();
}


/**********************************************************************************************************************
 * OptionPair Struct Implementation
 *********************************************************************************************************************/
OptionPair::OptionPair() : option( "" ), value( "" ) { }

OptionPair::OptionPair( std::string this_option, std::string this_value ) : option( this_option ), value( this_value ) { }


/**********************************************************************************************************************
 * OptionSet Class Implementation
 *********************************************************************************************************************/
OptionSet::OptionSet() {
    options = std::vector<OptionPair>();
}

void OptionSet::add_option( OptionPair option ) {
    // If the option already exists, update the value.
    for ( auto current_option : options ) {
        if ( current_option.option == option.option ) {
            current_option.value = option.value;
            return;
        }
    }

    // If the option doesn't already exist, add it.
    options.push_back( option );
}

bool OptionSet::has_option( std::string option ) {
    for ( auto iter = options.begin(); iter != options.end(); ++iter ) {
        if ( iter->option == option ) return true;
    }

    return false;
}

std::string OptionSet::get_option( std::string option ) {
    for ( auto iter = options.begin(); iter != options.end(); ++iter ) {
        if ( iter->option == option ) return iter->value;
    }

    throw EngineException( "Requested parameter option does not exist." );
}

OptionPair OptionSet::at( unsigned long i ) {
    return options.at( i );
}

unsigned long OptionSet::size() {
    return options.size();
}