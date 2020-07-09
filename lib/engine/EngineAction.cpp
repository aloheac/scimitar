//
// Created by loheac on 11/16/19.
//

#include <stdexcept>
#include "EngineAction.h"

/**********************************************************************************************************************
 * EngineAction Class Implementation
 *********************************************************************************************************************/
EngineAction::EngineAction( ActionType this_type ) : type( this_type ), engine( nullptr ) { }

void EngineAction::set_engine( Engine* this_engine ) {
    engine = this_engine;
}

void EngineAction::execute( Engine* this_engine ) {
    set_engine( this_engine );
    execute();
}

ActionType EngineAction::get_type() {
    return type;
}


/**********************************************************************************************************************
 * ActionParam Class Implementation
 *********************************************************************************************************************/
ActionParam::ActionParam( std::string this_type, std::string this_identifier, std::string this_value, OptionSet this_options )
    : EngineAction( ActionType::PARAM ), type( this_type ), identifier( this_identifier ), value( this_value ), options( this_options ) { }


void ActionParam::execute() {
    // Get the parameter format.
    std::string format;
    if ( options.has_option( "format" ) ) {
        format = options.get_option( "format" );
    } else {
        format = "";
    }

    // Get the parameter type.
    ParameterType paramType;
    if ( type == "real" ) {
        paramType = ParameterType::REAL;
    } else if ( type == "int" ) {
        paramType = ParameterType::INT;
    } else if ( type == "string" ) {
        paramType = ParameterType::STRING;
    } else {
        throw EngineException( "Unknown parameter type." );
    }

    engine->add_parameter( paramType, identifier, value,  format );

    // Set parameter options.
    for ( unsigned long i = 0; i < options.size(); i++ ) {
        set_option( options.at( i ) );
    }
}

void ActionParam::set_option( OptionPair option ) {
    if ( option.option == "dir" ) {
        int dir;
        try {
            dir = stoi( option.value );
        } catch ( const std::invalid_argument &e ) {
            throw EngineException( "Invalid conversion of token to a directory order." );
        } catch ( const std::out_of_range &e ) {
            throw EngineException( "Overflow in conversion of token to a directory order." );
        }

        engine->set_directory_order( identifier, dir );
    } else if ( option.option == "format" ) {
        engine->set_format( identifier, option.value );
    } else if ( option.option == "hide" ) {
        engine->hide_parameter( identifier );
    } else if ( option.option == "value" ) {
        throw EngineException( "Using value= in a parameter definition statement is not permitted." );
    } else {
        throw EngineException( "Invalid option." );
    }
}


/**********************************************************************************************************************
 * ActionFunction Class Implementation
 *********************************************************************************************************************/
 ActionFunction::ActionFunction( std::string this_identifier, std::shared_ptr<ArithmeticExpression> this_expr, OptionSet this_options )
    : EngineAction( ActionType::FUNCTION_PARAM ), identifier( this_identifier ), expr( this_expr ), options( this_options ) { }

void ActionFunction::execute() {
    // Get the parameter format.
    std::string format;
    if ( options.has_option( "format" ) ) {
        format = options.get_option( "format" );
    } else {
        format = "";
    }

    engine->add_function( identifier, expr, format );

    // Set parameter options.
    for ( unsigned long i = 0; i < options.size(); i++ ) {
        set_option( options.at( i ) );
    }
 }

void ActionFunction::set_option( OptionPair option ) {
    if ( option.option == "dir" ) {
        int dir;
        try {
            dir = stoi( option.value );
        } catch ( const std::invalid_argument &e ) {
            throw EngineException( "Invalid conversion of token to a directory order." );
        } catch ( const std::out_of_range &e ) {
            throw EngineException( "Overflow in conversion of token to a directory order." );
        }

        engine->set_directory_order( identifier, dir );
    } else if ( option.option == "format" ) {
        engine->set_format( identifier, option.value );
    } else if ( option.option == "hide" ) {
        engine->hide_parameter( identifier );
    } else if ( option.option == "value" ) {
        throw EngineException( "Using value= in a function definition is not permitted." );
    } else {
        throw EngineException( "Invalid option." );
    }
}

/**********************************************************************************************************************
 * ActionSetParam Class Implementation
 *********************************************************************************************************************/
 ActionSetParam::ActionSetParam( std::string this_identifier, OptionSet this_options )
    : EngineAction( ActionType::SET_PARAM ), identifier( this_identifier ), options( this_options ) { }

void ActionSetParam::execute() {
    // Set parameter options.
    for ( unsigned long i = 0; i < options.size(); i++ ) {
        set_option( options.at( i ) );
    }
}

void ActionSetParam::set_option( OptionPair option ) {
    if ( option.option == "dir" ) {
        int dir;
        try {
            dir = stoi( option.value );
        } catch ( const std::invalid_argument &e ) {
            throw EngineException( "Invalid conversion of token to a directory order." );
        } catch ( const std::out_of_range &e ) {
            throw EngineException( "Overflow in conversion of token to a directory order." );
        }

        engine->set_directory_order( identifier, dir );
    } else if ( option.option == "format" ) {
        engine->set_format( identifier, option.value );
    } else if ( option.option == "value" ) {
        engine->set_value( identifier, option.value );
    } else if ( option.option == "hide" ) {
        engine->hide_parameter( identifier );
    } else {
        throw EngineException( "Invalid option." );
    }
}


/**********************************************************************************************************************
 * ActionSetFunction Class Implementation
 *********************************************************************************************************************/
ActionSetFunction::ActionSetFunction( std::string this_identifier, std::shared_ptr<ArithmeticExpression> this_expr, OptionSet this_options )
        : EngineAction( ActionType::SET_FUNCTION ), identifier( this_identifier ), expr( this_expr ), options( this_options ) { }

void ActionSetFunction::execute() {
    engine->set_value( identifier, expr );

    // Set parameter options.
    for ( unsigned long i = 0; i < options.size(); i++ ) {
        set_option( options.at( i ) );
    }
}

void ActionSetFunction::set_option( OptionPair option ) {
    if ( option.option == "dir" ) {
        int dir;
        try {
            dir = stoi( option.value );
        } catch ( const std::invalid_argument &e ) {
            throw EngineException( "Invalid conversion of token to a directory order." );
        } catch ( const std::out_of_range &e ) {
            throw EngineException( "Overflow in conversion of token to a directory order." );
        }

        engine->set_directory_order( identifier, dir );
    } else if ( option.option == "format" ) {
        engine->set_format( identifier, option.value );
    } else if ( option.option == "hide" ) {
        engine->hide_parameter( identifier );
    } else if ( option.option == "value" ) {
        throw EngineException( "Setting a function using value= is invalid." );
    } else {
        throw EngineException( "Invalid option." );
    }
}


/**********************************************************************************************************************
 * ActionSetOption Class Implementation
 *********************************************************************************************************************/
ActionSetOption::ActionSetOption( OptionSet this_options ) : EngineAction( ActionType::SET_OPTION ),
    options( this_options ) { }

void ActionSetOption::execute() {
    for ( int i = 0; i < options.size(); i++ ) {
        engine->set_option( options.at( i ) );
    }
}

/**********************************************************************************************************************
 * ActionGroup Class Implementation
 *********************************************************************************************************************/
ActionGroup::ActionGroup( std::vector< std::string > this_identifiers )
    : EngineAction( ActionType::GROUP ), identifiers( this_identifiers ) { }

void ActionGroup::execute() {
    // Verify that the list of identifiers is not empty.
    if ( identifiers.empty() ) throw EngineException( "Group action was provided no identifiers." );

    std::string firstID = identifiers.at( 0 );
    for ( auto id : identifiers ) {
        if ( firstID != id ) engine->group_parameters( firstID, id );
    }
}


/**********************************************************************************************************************
 * ActionUngroup Class Implementation
 *********************************************************************************************************************/
ActionUngroup::ActionUngroup( std::vector< std::string > this_identifiers )
        : EngineAction( ActionType::UNGROUP ), identifiers( this_identifiers ) { }

void ActionUngroup::execute() {
    // Verify that the list of identifiers is not empty.
    if ( identifiers.empty() ) throw EngineException( "Ungroup action was provided no identifiers." );

    for ( auto id : identifiers ) {
         engine->ungroup_parameter( id );
    }
}


/**********************************************************************************************************************
 * ActionSetRunBlock Class Implementation
 *********************************************************************************************************************/
 ActionSetRunBlock::ActionSetRunBlock( std::shared_ptr<RunLoop> this_loop )
    : EngineAction( ActionType::RUN_BLOCK ), loop( this_loop ) { }

 void ActionSetRunBlock::execute() {
     engine->set_run_loop( *loop );
 }


/**********************************************************************************************************************
* ActionSystemConfig Class Implementation
*********************************************************************************************************************/
ActionSystemConfig::ActionSystemConfig(OptionSet this_config)
    : EngineAction( ActionType::SYSTEM_CONFIG ), config( this_config ) { }

void ActionSystemConfig::execute() {
    std::string option;
    for ( int i = 0; i < config.size(); i++ ) {
        option = config.at( i ).option;

        if ( option == "seed" ) {
            // Try to parse the option value as a long integer.
            long seed;
            try {
                seed = std::stol( config.at( i ).value );
            } catch ( std::invalid_argument ) {
                throw EngineException( "Failed to parse the provided random number generator seed as an integer." );
            }

            engine->set_rng_seed( seed );
        } else {
            throw EngineException( "Unknown system configuration option.");
        }
    }
}


/**********************************************************************************************************************
* ActionUserFunction Class Implementation
*********************************************************************************************************************/
ActionUserFunction::ActionUserFunction( std::shared_ptr<UserFunction> this_function )
    : EngineAction( ActionType::USER_FUNCTION ), function( this_function ) { }

void ActionUserFunction::execute() {
    engine->add_user_function( *function );
}