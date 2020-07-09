//
// Created by loheac on 5/1/20.
//

#include <cassert>
#include "../engine/BasicStructures.h"
#include "../language/ConditionalExpression.h"
#include "UserFunction.h"


/**********************************************************************************************************************
 * FunctionStatement Class Implementation
 *********************************************************************************************************************/
FunctionStatement::FunctionStatement( Type this_statement_type ) : statement_type( this_statement_type ) { }

FunctionStatement::Type FunctionStatement::get_statement_type() {
    return statement_type;
}

void FunctionStatement::execute( SymbolScope &symbols ) { }

/**********************************************************************************************************************
 * FuncStmtDeclaration Class Implementation
 *********************************************************************************************************************/
FuncStmtDeclaration::FuncStmtDeclaration( Symbol::Type this_type, std::string this_identifier ) :
    FunctionStatement( FunctionStatement::Type::DECLARATION ), type( this_type ),
    identifier( this_identifier ), initialize_default( true ) { }

FuncStmtDeclaration::FuncStmtDeclaration( Symbol::Type this_type, std::string this_identifier, std::shared_ptr<Expression> this_value ) :
    FunctionStatement( FunctionStatement::Type::DECLARATION ), type( this_type ),
    identifier( this_identifier ), value( this_value ), initialize_default( false ) { }

void FuncStmtDeclaration::execute( SymbolScope &symbols ) {
    if ( type == Symbol::Type::INT ) {
        symbols.add_symbol( type, identifier, SymbolScope::INT_TYPE_DEFAULT );
    } else if ( type == Symbol::Type::REAL ) {
        symbols.add_symbol( type, identifier, SymbolScope::REAL_TYPE_DEFAULT );
    } else if ( type == Symbol::Type::BOOL ) {
        symbols.add_symbol( type, identifier, SymbolScope::BOOL_TYPE_DEFAULT );
    } else if ( type == Symbol::Type::LIST ) {
        symbols.add_symbol( type, identifier, "<list>" );
    } else throw EngineException( "Unknown symbol type." );

    if ( not initialize_default ) {
        std::shared_ptr<Symbol> rhs = value->evaluate( symbols );
        symbols.set_symbol( identifier, rhs );
    }
}


/**********************************************************************************************************************
 * FuncStmtAssignment Class Implementation
 *********************************************************************************************************************/
FuncStmtAssignment::FuncStmtAssignment( std::string this_identifier, std::shared_ptr<Expression> this_value ) :
    FunctionStatement( FunctionStatement::Type::ASSIGNMENT ), identifier( this_identifier ),
    value( this_value ) { }

void FuncStmtAssignment::execute( SymbolScope &symbols ) {
    std::shared_ptr<Symbol> rhs = value->evaluate( symbols );
    symbols.set_symbol( identifier, rhs );
}


/**********************************************************************************************************************
 * FuncStmtConditional Class Implementation
 *********************************************************************************************************************/
FuncStmtConditional::FuncStmtConditional( std::shared_ptr<ConditionalExpression> this_conditional )
    : FunctionStatement( FunctionStatement::Type::CONDITIONAL ), conditional( this_conditional ) { }

void FuncStmtConditional::add_statement( std::shared_ptr<FunctionStatement> statement ) {
    statements.push_back( statement );
}

void FuncStmtConditional::add_else_statement( std::shared_ptr<FunctionStatement> statement ) {
    else_statements.push_back( statement );
}

void FuncStmtConditional::execute( SymbolScope &symbols ) {
    std::shared_ptr<BooleanSymbol> condition = std::dynamic_pointer_cast<BooleanSymbol>( conditional->evaluate( symbols ) );

    if ( condition->get_data() ) {
        for ( auto stmt : statements ) {
            stmt->execute( symbols );
            if ( symbols.get_return_flag() ) break;
        }
    } else {
        for ( auto stmt : else_statements ) {
            stmt->execute( symbols );
            if ( symbols.get_return_flag() ) break;
        }
    }
}


/**********************************************************************************************************************
 * FuncStmtForLoop Class Implementation
 *********************************************************************************************************************/
FuncStmtForLoop::FuncStmtForLoop( Symbol::Type this_loop_symbol_type, std::string this_loop_symbol_identifier,
     std::shared_ptr<ArithmeticExpression> this_initial_value, std::shared_ptr<ConditionalExpression> this_conditional,
     std::shared_ptr<ArithmeticExpression> this_step)
     : FunctionStatement( FunctionStatement::Type::FOR_LOOP ), loop_symbol_type( this_loop_symbol_type ),
     loop_symbol_identifier( this_loop_symbol_identifier ), initial_value( this_initial_value ),
     conditional( this_conditional ), step( this_step ) { }

void FuncStmtForLoop::add_statement( std::shared_ptr<FunctionStatement> statement ) {
    statements.push_back( statement );
}

void FuncStmtForLoop::execute( SymbolScope &symbols ) {
     std::shared_ptr<Symbol> ev_initial = initial_value->evaluate( symbols )->cast( loop_symbol_type );
     std::shared_ptr<Symbol> ev_step = step->evaluate( symbols )->cast( loop_symbol_type );

     // Construct the loop variable symbol.
     std::shared_ptr<Symbol> loop;
     if ( loop_symbol_type == Symbol::Type::INT ) {
         int cast_initial = std::dynamic_pointer_cast< TypedSymbol<int> >( ev_initial->cast( Symbol::Type::INT ) )->get_data();
         loop = std::make_shared< TypedSymbol<int> >( Symbol::Type::INT, loop_symbol_identifier, cast_initial );
     } else if ( loop_symbol_type == Symbol::Type::REAL ) {
         double cast_initial = std::dynamic_pointer_cast< TypedSymbol<double> >( ev_initial->cast( Symbol::Type::REAL ) )->get_data();
         loop = std::make_shared< TypedSymbol<double> >( Symbol::Type::REAL, loop_symbol_identifier, cast_initial );
     } else throw EngineException( "Invalid loop variable data type." );

     // Add the loop variable to a new symbol table.
     SymbolScope loop_symbols( symbols );
     loop_symbols.add_symbol( loop );

     // Initialize the loop condition.
    std::shared_ptr<BooleanSymbol> ev_condition = std::dynamic_pointer_cast<BooleanSymbol>( conditional->evaluate( loop_symbols ) );

     // Execute the loop.
     while ( ev_condition->get_data() ) {
         for ( auto stmt : statements ) {
             // Check for break or continue statements.
             if ( loop_symbols.get_break_flag() ) break;
             else if ( loop_symbols.get_continue_flag() ) {
                 loop_symbols.reset_continue_flag();
                 increment( loop, ev_step );
                 continue;
             }

             stmt->execute( loop_symbols );

             increment( loop, ev_step );
             ev_condition = std::dynamic_pointer_cast<BooleanSymbol>( conditional->evaluate( loop_symbols ) );
         }
     }
}

void FuncStmtForLoop::increment( std::shared_ptr<Symbol> &loop_symbol, std::shared_ptr<Symbol> &step_symbol ) {
    assert( loop_symbol->get_type() == step_symbol->get_type() );

    if ( loop_symbol->get_type() == Symbol::Type::INT ) {
        std::shared_ptr< TypedSymbol<int> > t_loop_symbol = std::dynamic_pointer_cast< TypedSymbol<int> >( loop_symbol );
        std::shared_ptr< TypedSymbol<int> > t_step_symbol = std::dynamic_pointer_cast< TypedSymbol<int> >( step_symbol );
        t_loop_symbol->set_data( t_loop_symbol->get_data() + t_step_symbol->get_data() );
    } else if ( loop_symbol->get_type() == Symbol::Type::REAL ) {
        std::shared_ptr< TypedSymbol<double> > t_loop_symbol = std::dynamic_pointer_cast< TypedSymbol<double> >( loop_symbol );
        std::shared_ptr< TypedSymbol<double> > t_step_symbol = std::dynamic_pointer_cast< TypedSymbol<double> >( step_symbol );
        t_loop_symbol->set_data( t_loop_symbol->get_data() + t_step_symbol->get_data() );
    }
}


/**********************************************************************************************************************
 * FuncStmtWhileLoop Class Implementation
 *********************************************************************************************************************/
FuncStmtWhileLoop::FuncStmtWhileLoop( std::shared_ptr<ConditionalExpression> this_conditional )
    : FunctionStatement( FunctionStatement::Type::WHILE_LOOP ), conditional( this_conditional ) { }

void FuncStmtWhileLoop::add_statement( std::shared_ptr<FunctionStatement> statement ) {
    statements.push_back( statement );
}

void FuncStmtWhileLoop::execute( SymbolScope &symbols ) {
    SymbolScope loop_symbols( symbols );
    std::shared_ptr<BooleanSymbol> eval_conditional
        = std::dynamic_pointer_cast<BooleanSymbol>( conditional->evaluate( loop_symbols ) );

    while ( eval_conditional->get_data() ) {
        for ( auto stmt : statements ) {
            // Check for break or continue statements.
            if ( loop_symbols.get_break_flag() ) break;
            else if ( loop_symbols.get_continue_flag() ) {
                loop_symbols.reset_continue_flag();
                continue;
            }

            stmt->execute( loop_symbols );
            eval_conditional = std::dynamic_pointer_cast<BooleanSymbol>( conditional->evaluate( loop_symbols ) );
        }
    }
}


/**********************************************************************************************************************
 * FuncStmtReturn Class Implementation
 *********************************************************************************************************************/
FuncStmtReturn::FuncStmtReturn( std::shared_ptr<ArithmeticExpression> this_return_stmt )
    : FunctionStatement( FunctionStatement::Type::RETURN ), return_stmt( this_return_stmt ) { }

void FuncStmtReturn::execute( SymbolScope &symbols ) {
    std::shared_ptr< TypedSymbol<double> > ret = std::dynamic_pointer_cast< TypedSymbol<double> >
            ( return_stmt->evaluate( symbols )->cast( Symbol::Type::REAL ) );

    symbols.set_symbol( UserFunction::RETURN_IDENTIFIER, ret );
    symbols.set_return_flag();
}


/**********************************************************************************************************************
 * FuncStmtListAppend Class Implementation
 *********************************************************************************************************************/
FuncStmtListAppend::FuncStmtListAppend( std::string this_list_identifier, Symbol::Type this_append_type,
        std::shared_ptr<Expression> this_append_expr ) : FunctionStatement( FunctionStatement::Type::LIST_APPEND ),
        list_identifier( this_list_identifier ), append_type( this_append_type ), append_expr( this_append_expr ) { }

void FuncStmtListAppend::execute( SymbolScope &symbols ) {
    // Get the matching symbol, and verify it is a list instance.
    std::shared_ptr<Symbol> list_sym = symbols.get_symbol( list_identifier );
    if ( list_sym->get_type() != Symbol::Type::LIST ) throw EngineException( "Expected identifier to resolve to a list." );

    std::shared_ptr<List> list = std::dynamic_pointer_cast<List>( list_sym );
    std::shared_ptr<Symbol> new_element = append_expr->evaluate( symbols )->cast( append_type );
    list->append( new_element );
}

/**********************************************************************************************************************
 * FuncStmtListRemove Class Implementation
 *********************************************************************************************************************/
FuncStmtListRemove::FuncStmtListRemove( std::string this_list_identifier, std::shared_ptr<ArithmeticExpression> this_remove_expr )
    : FunctionStatement( FunctionStatement::Type::LIST_REMOVE ), list_identifier( this_list_identifier ),
    remove_expr( this_remove_expr ) { }

void FuncStmtListRemove::execute( SymbolScope &symbols ) {
    // Get the matching symbol, and verify it is a list instance.
    std::shared_ptr<Symbol> list_sym = symbols.get_symbol( list_identifier );
    if ( list_sym->get_type() != Symbol::Type::LIST ) throw EngineException( "Expected identifier to resolve to a list." );

    std::shared_ptr<List> list = std::dynamic_pointer_cast<List>( list_sym );

    // Evaluate the index of the element to remove.
    std::shared_ptr<Symbol> i_sym = remove_expr->evaluate( symbols )->cast( Symbol::Type::INT );
    long i = std::dynamic_pointer_cast< TypedSymbol<int> >( i_sym )->get_data();

    list->remove( i );
}

/**********************************************************************************************************************
 * FuncStmtBreak Class Implementation
 *********************************************************************************************************************/
FuncStmtBreak::FuncStmtBreak() : FunctionStatement( FunctionStatement::Type::BREAK ) { }

void FuncStmtBreak::execute( SymbolScope &symbols ) {
    symbols.set_break_flag();
}


/**********************************************************************************************************************
 * FuncStmtContinue Class Implementation
 *********************************************************************************************************************/
FuncStmtContinue::FuncStmtContinue() : FunctionStatement( FunctionStatement::Type::CONTINUE ) { }

void FuncStmtContinue::execute( SymbolScope &symbols ) {
    symbols.set_continue_flag();
}


/**********************************************************************************************************************
 * FunctionArgumentSet Class Implementation
 *********************************************************************************************************************/
FunctionArgumentSet::Argument::Argument( Symbol::Type this_type, std::string this_identifier ) : type( this_type ),
    identifier( this_identifier ) { }

void FunctionArgumentSet::add_argument( Symbol::Type this_type, std::string this_identifier ) {
     // Verify that an argument with a matching identifier doesn't already exist.
     for ( auto arg : arguments ) {
         if ( arg.identifier == this_identifier )
             throw EngineException( "User-defined function contains duplicate argument identifiers." );
     }

     arguments.emplace_back( this_type, this_identifier );
 }

FunctionArgumentSet::Argument FunctionArgumentSet::get_argument( std::string identifier ) {
     for ( auto arg : arguments ) {
         if ( arg.identifier == identifier ) return arg;
     }

     throw EngineException( "Requested function argument with an identifier that does not exist." );
}

long FunctionArgumentSet::length() {
    return arguments.size();
}

FunctionArgumentSet::Argument FunctionArgumentSet::at( long i ) {
    if ( i > arguments.size() - 1 or i < 0 ) throw EngineException( "Function argument index is out of range." );
    return arguments.at( i );
}

/**********************************************************************************************************************
* UserFunction Class Implementation
*********************************************************************************************************************/
const std::string UserFunction::RETURN_IDENTIFIER = "<return_value>";

long UserFunction::EXECUTION_LIMIT = 2000;

UserFunction::UserFunction( std::string this_identifier ) : identifier( this_identifier ), execution_count( 0 ) { }

void UserFunction::add_argument( Symbol::Type type, std::string identifier ) {
    arguments.add_argument( type, identifier );
}

void UserFunction::add_statement( std::shared_ptr<FunctionStatement> statement ) {
    statements.push_back( statement );
}

std::string UserFunction::get_identifier() {
    return identifier;
}

FunctionArgumentSet UserFunction::get_arguments() {
    return arguments;
}

void UserFunction::reset() {
    execution_count = 0;
}

std::shared_ptr<Symbol> UserFunction::execute( SymbolScope passed_arguments ) {
    // Check if we have surpassed the execution count limit.
    if ( execution_count > EXECUTION_LIMIT ) throw EngineException( "Reached user function invocation limit. Verify a recursive loop does not exist, and raise the execution limit." );
    execution_count++;

    // Add arguments to the symbol table.
    for ( long i = 0; i < arguments.length(); i++ ) {
        std::shared_ptr<Symbol> cast_arg = passed_arguments.at( i )->cast( arguments.at( i ).type );
        symbols.add_symbol( cast_arg );
    }

    // Add function references to the symbol table.
    symbols.set_functions( passed_arguments.get_functions() );

    // Add the return value symbol.
    symbols.add_symbol( Symbol::Type::REAL, RETURN_IDENTIFIER, "0.0" );

    for ( auto stmt : statements ) {
        stmt->execute( symbols );
        if ( symbols.get_return_flag() ) break;
    }

    // Save the return value, and clear the symbol table.
    std::shared_ptr<Symbol> ret = symbols.get_symbol( RETURN_IDENTIFIER );
    symbols.clear();

    // Get the return value.
    return ret;
}
