//
// Created by loheac on 11/9/19.
//

#include <sstream>
#include <algorithm>
#include "Engine.h"

using namespace std;

/**********************************************************************************************************************
 * Engine Class Implementation
 *********************************************************************************************************************/
std::default_random_engine Engine::rng;

Engine::Engine() : parameter_count( 0 ) {
    parameters = vector<Parameter*>();
    groups = vector<Group*>();
    run_loop = RunLoop();
}

Engine::~Engine() {
    // Delete all parameters.
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) delete *iter;

    // Delete all groups.
    for ( auto iter = groups.begin(); iter != groups.end(); ++iter ) delete *iter;

    // Delete all user functions.
    for ( auto iter = user_functions.begin(); iter != user_functions.end(); ++iter ) delete *iter;
}

void Engine::add_parameter( ParameterType type, string identifier, string value, string format ) {
    // Verify that the identifier doesn't already exist. If it does, throw an exception.
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        if ( (*iter)->get_identifier() == identifier ) throw EngineException( "Parameter with matching identifier already exists." );
    }

    // Construct parameter and insert into vector of parameters.
    Parameter* new_param = new Parameter( type, identifier, value, format );
    parameters.push_back( new_param );

    // Construct a new group for the parameter.
    Group* new_group = new Group( new_param );
    groups.push_back( new_group );
    parameter_count++;
}

void Engine::add_function( std::string identifier, std::shared_ptr<ArithmeticExpression> expr, std::string format ) {
    // Verify the identifier doesn't already exist. If it does, throw an exception.
    for ( auto iter : parameters ) {
        if ( iter->get_identifier() == identifier ) throw EngineException( "Parameter with matching identifier already exists." );
    }

    // Construct the function parameter and insert into vector of parameters.
    Parameter* new_param = new Parameter( identifier, expr, format );
    parameters.push_back( new_param );

    // Construct a new group for the function.
    Group* new_group = new Group( new_param );
    groups.push_back( new_group );
    parameter_count++;
}

void Engine::delete_parameter( std::string identifier ) {
    // Iterate through groups to find any matching parameters. Note that if no match is found, an exception is not thrown.
    // In principle, a parameter should only belong to a single group. If this isn't true, thrown an exception.
    bool parameter_removed = false;  // Boolean value to indicate whether or not a matching parameter was found and removed.
    auto iter = groups.begin();
    while ( iter != groups.end() ) {  // Pattern to loop over elements of groups, act on each group, and remove empty groups.
        if ( (*iter)->has_parameter( identifier ) ) {  // Check if the group has a matching parameter.
            // Assertion: if a matching parameter has already been removed, but another match has been found, throw an exception.
            if ( parameter_removed ) throw EngineException( "Matching identifier found in multiple groups when deleting associated parameter." );

            // Remove the parameter from the group.
            (*iter)->delete_parameter( identifier );
            parameter_removed = true;

            // If the group is empty, remove the group from the engine.
            if ( (*iter)->length() == 0 ) {
                iter = groups.erase( iter );  // A call to erase() effectively increments iter.
            } else {
                ++iter;
            }
        } else {
            ++iter;  // Increment to next group to check.
        }
    }

    // Assertion: Each parameter should exist in exist in exactly one group (even if it is a group with a single element).
    if ( not parameter_removed ) throw EngineException( "Group containing parameter requested to be removed not found." );

    // Loop over the set of parameters to find the object with a matching identifier. This will destroy the object.
    // Assertion: If a match is not found, throw an exception.
    parameter_removed = false;
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        if ( (*iter)->get_identifier() == identifier ) {
            delete *iter;
            parameters.erase( iter );
            parameter_removed = true;
            break;
        }
    }

    if ( not parameter_removed ) throw EngineException( "Parameter requested to be removed not found." );
}

long Engine::get_run_count() {
    long count = 1;
    for ( auto iter = groups.begin(); iter != groups.end(); ++iter ) {
        count *= (*iter)->length();
    }

    return count;
}

ExecutionResult Engine::execute() {
    // Perform final validation on parameter set.
    validate();

    ExecutionResult result;

    // ***** GENERATE RUN LISTING *****
    for ( auto group : groups ) {
        result = get_run_product( result, *group );
    }

    // We should not allow an empty run to continue.
    if ( result.length() == 0 ) throw EngineException( "Job contains zero runs." );

    // Evaluate all function parameter in result.
    ExecutionResult evaluated_result;
    Run evaluated_next;
    while ( not result.empty() ) {
        evaluated_next = evaluate_function_parameters( result.next() );
        evaluated_result.add_run( evaluated_next );
    }

    // ***** EXECUTE RUN LOOP *****
    ExecutionResult final;
    Run next;
    while ( not evaluated_result.empty() ) {
        next = run_loop.execute( evaluated_result.next() );
        if ( not next.removed() ) final.add_run( next );
    }

    // ***** GENERATE DIRECTORY ORDER *****
    std::vector<std::string> directory_order_identifiers;
    std::vector<DirectoryOrderPair> directory_order_pairs;

    for ( auto param : parameters ) {
        if ( param->get_directory_order() != 0 )
            directory_order_pairs.emplace_back( param->get_identifier(), param->get_directory_order() );
    }

    std::sort( directory_order_pairs.begin(), directory_order_pairs.end(), DirectoryOrderPair::comp );

    for ( auto pair : directory_order_pairs ) {
        directory_order_identifiers.push_back( pair.identifier );
    }

    final.set_directory_order( directory_order_identifiers );

    // ***** SORT VALUES AND RUNS ACCORDING TO DEFINITION AND DIRECTORY ORDERS *****
    std::vector<std::string> identifiers;
    for ( auto param : parameters ) {
        identifiers.push_back( param->get_identifier() );
    }

    final.sort_runs( identifiers );

    // ***** SET OPTIONS *****
    final.set_option_set( options );

    // ***** REMOVE HIDDEN PARAMETERS *****
    // Get concatenated list of hidden identifiers across all groups.
    std::vector<std::string> hidden_identifiers;
    for ( auto param : parameters ) {
        if ( is_hidden( param->get_identifier() ) ) hidden_identifiers.push_back( param->get_identifier() );
    }

    final.set_hidden_parameters( hidden_identifiers );

    last_result = final;
    return final;
}

ExecutionResult Engine::get_run_product( ExecutionResult initial_result, Group group ) {
    initial_result.reset();
    ExecutionResult next_result;
    while ( not initial_result.empty() ) {
        Run initial_run = initial_result.next();
        group.reset();
        while ( not group.is_empty() ) {
            Run next_run( initial_run );
            std::vector<ValuePair> group_parameters = group.get_next();

            for ( auto param : group_parameters ) {
                next_run.add_value( param );
            }

            next_result.add_run( next_run );
        }
    }

    return next_result;
}

Run Engine::evaluate_function_parameters( Run run ) {
    std::string result;
    for ( auto param : parameters ) {
        if ( param->get_type() == ParameterType::FUNCTION ) {
            SymbolScope symbols = run.to_symbol_scope();

            // Add references to user-defined functions to the symbol scope.
            symbols.set_functions( user_functions );

            result = param->evaluate_function( symbols );
            run.set_value( param->get_identifier(), result );

            // Reset execution limit counters for all user functions.
            for ( auto function : user_functions ) function->reset();
        }
    }

    return run;
}

void Engine::group_parameters( std::string identifierA, std::string identifierB ) {
    Group* groupB = get_group( identifierB );
    get_group( identifierA )->merge( *get_group( identifierB ) );

    // Delete group B.
    for ( auto iter = groups.begin(); iter != groups.end(); ++iter ) {
        if ( *iter == groupB ) {
            groups.erase( iter );
            break;
        }
    }

    delete groupB;
}

void Engine::ungroup_parameter( std::string identifier ) {
    Group* completeGroup = get_group( identifier );
    Parameter* ungroupedParam = completeGroup->get_parameter( identifier );

    completeGroup->delete_parameter( identifier );
    groups.push_back( new Group( ungroupedParam ) );
}

Parameter* Engine::get_parameter( std::string identifier ) {
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        if ( (*iter)->get_identifier() == identifier ) return *iter;
    }

    throw EngineException( "Requested parameter with an invalid identifier." );
}

void Engine::set_directory_order( std::string identifier, int order ) {
    // Check if directory order already exists. If so, throw an exception.
    for ( auto iter = parameters.begin(); iter != parameters.end(); ++iter ) {
        if ( (*iter)->get_directory_order() == order and (*iter)->get_directory_order() != 0 )
            throw EngineException( "Directory order already exists." );
    }

    get_parameter( identifier )->set_directory_order( order );
}

unsigned int Engine::get_directory_order( std::string identifier ) {
    return get_parameter( identifier )->get_directory_order();
}


void Engine::set_value( std::string identifier, std::string value ) {
    Parameter* param = get_parameter( identifier );
    param->set_value( value );
}

void Engine::set_value( std::string identifier, std::shared_ptr<ArithmeticExpression> expr ) {
    Parameter* param = get_parameter( identifier );
    param->set_value( expr );
}

void Engine::set_option( OptionPair option ) {
    options.add_option( option );
}

void Engine::set_run_loop( RunLoop loop ) {
    run_loop = loop;
}

void Engine::set_format( std::string identifier, std::string format ) {
    get_parameter( identifier )->set_format( format );
}

std::string Engine::get_format( std::string identifier ) {
    return get_parameter( identifier )->get_format();
}

Group* Engine::get_group( std::string identifier ) {
    for ( auto iter = groups.begin(); iter != groups.end(); ++iter ) {
        if ( (*iter)->has_parameter( identifier ) ) return *iter;
    }

    throw EngineException( "Requested group with an invalid identifier." );
}

void Engine::hide_parameter(std::string identifier) {
    get_group( identifier )->hide_parameter( identifier );
}

bool Engine::is_hidden( std::string identifier ) {
    return get_group( identifier )->is_hidden( identifier );
}

void Engine::add_user_function( UserFunction function ) {
    // Make a copy of the new UserFunction to be added to the engine. This class will assume memory management for this
    // copy.
    UserFunction* ptr = new UserFunction( function );
    user_functions.push_back( ptr );
}

std::vector<UserFunction*> Engine::get_user_functions() {
    return user_functions;
}

string Engine::to_string() {
    stringstream ss;
    ss << "{ ";

    for ( auto iter = groups.begin(); iter != groups.end(); ++iter ) {
        ss << (*iter)->to_string() << " ";
    }

    ss << "; (" << groups.size() << " groups, " << parameters.size() << " parameters) }";
    return ss.str();
}

void Engine::validate() {
    // Run validation on all groups.
    for ( auto group : groups ) group->validate();

    // Verify that the provided directory orders are valid.
    // Recall that dir=0 corresponds to parameter which will not be listed in the directory structure.
    std::vector<unsigned int> directoryOrders;
    for ( auto param : parameters ) {  // Copy directory orders into vector which can be sorted.
        directoryOrders.push_back( param->get_directory_order() );
    }

    std::sort( directoryOrders.begin(), directoryOrders.end() );

    // Confirm the directory orders appear in the expected sequence.
    unsigned int nextDirectoryOrder = 1;
    for ( auto order : directoryOrders ) {
        if ( order != 0 ) {
            if ( order == nextDirectoryOrder ) {
                nextDirectoryOrder++;
            } else {
                throw EngineException( "Parameter directory order is not sequential." );
            }
        }
    }

    // Confirm that parameters with non-zero directory orders are not hidden.
    std::vector<std::string> hidden_identifiers;
    for ( auto param : parameters ) {
        if ( is_hidden( param->get_identifier() ) ) {
            if ( get_directory_order( param->get_identifier() ) != 0 )
                throw EngineException( "Hidden parameters cannot have a non-zero directory order." );
        }
    }
}

void Engine::set_rng_seed( long seed ) {
    rng.seed( seed );
}
