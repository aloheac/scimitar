//
// Created by loheac on 12/14/19.
//

#include <sstream>
#include "../engine/Engine.h"
#include "LoopStatement.h"

/**********************************************************************************************************************
 * LoopStatement Class Implementation
 *********************************************************************************************************************/
LoopStatement::LoopStatement( LoopStatement::StatementType this_type ) : type( this_type ) { }

LoopStatement::StatementType LoopStatement::get_type() {
    return type;
}

/**********************************************************************************************************************
 * StmtIf Class Implementation
 *********************************************************************************************************************/
StmtIf::StmtIf( std::shared_ptr< ConditionalExpression > this_conditional )
    : LoopStatement( LoopStatement::StatementType::IF ), conditional( this_conditional ) { }

void StmtIf::add_statement( std::shared_ptr<LoopStatement> stmt ) {
    statements.push_back( stmt );
}

Run StmtIf::execute( Run state ) {
    bool condition = conditional->evaluate( state );

    if ( condition ) {
        for ( auto stmt : statements ) {
            state = stmt->execute( state );
        }
    }

    return state;
}

/**********************************************************************************************************************
 * StmtIfElse Class Implementation
 *********************************************************************************************************************/
StmtIfElse::StmtIfElse( std::shared_ptr<ConditionalExpression> this_conditional ) : LoopStatement( LoopStatement::StatementType::IF_ELSE ),
        conditional( this_conditional ) { }

void StmtIfElse::add_statement( std::shared_ptr<LoopStatement> stmt ) {
    statements.push_back( stmt );
}

void StmtIfElse::add_else_statement( std::shared_ptr< LoopStatement > stmt ) {
    else_statements.push_back( stmt );
}

Run StmtIfElse::execute( Run state ) {
    bool condition = conditional->evaluate( state );

    if ( condition ) {
        for ( auto stmt : statements ) {
            state = stmt->execute( state );
        }
    } else {
        for ( auto stmt : else_statements ) {
            state = stmt->execute( state );
        }
    }

    return state;
}

/**********************************************************************************************************************
 * StmtRemove Class Implementation
 *********************************************************************************************************************/
 StmtRemove::StmtRemove() : LoopStatement( LoopStatement::StatementType::REMOVE ) { }

 Run StmtRemove::execute( Run state ) {
     state.mark_remove();
     return state;
 }

/**********************************************************************************************************************
* StmtAssignment Class Implementation
**********************************************************************************************************************/
StmtAssignment::StmtAssignment( std::string this_identifier, std::shared_ptr<ArithmeticExpression> this_value )
    : LoopStatement( LoopStatement::StatementType::ASSIGNMENT ), identifier( this_identifier ), value( this_value ) { }

Run StmtAssignment::execute( Run state ) {
    double rhs = value->evaluate( state );
    std::string format = state.get_format( identifier );

    // If no format is specified, use the default behavior of the insertion operator to convert rhs to a string.
    if ( format.empty() ) {
        std::stringstream ss_value;
        ss_value << rhs;
        state.set_value( identifier, ss_value.str() );
    } else {
        // Apply the parameter format to the evaluated result.
        std::stringstream ss_format, ss_value;
        ss_format << '%' << state.get_format( identifier );
        char buffer[ 64 ];

        // If the ValueType is an integer, then we must cast rhs to an int before passing it to sprintf, which will
        // expect an int type.
        int result;
        if ( state.get_type( identifier ) == ValuePair::ValueType::INT ) {
            result = sprintf( buffer, ss_format.str().c_str(), int( rhs ) );
        } else if ( state.get_type( identifier ) == ValuePair::ValueType::REAL ) {
            result = sprintf( buffer, ss_format.str().c_str(), rhs );
        } else throw EngineException( "Unknown value type." );

        if ( result < 0 ) throw EngineException( "Failed format conversion in loop assignment statement." );

        state.set_value( identifier, std::string( buffer ) );
    }

    return state;
}

/**********************************************************************************************************************
* RunLoop Class Implementation
**********************************************************************************************************************/
void RunLoop::add_statement( std::shared_ptr<LoopStatement> stmt ) {
    statements.push_back( stmt );
}

Run RunLoop::execute( Run state ) {
    for ( auto stmt : statements ) {
        state = stmt->execute( state );
    }

    return state;
}