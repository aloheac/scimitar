//
// Created by loheac on 5/16/20.
//

#include <cmath>
#include "../engine/BasicStructures.h"
#include "../language/UserFunction.h"
#include "Symbol.h"

/**********************************************************************************************************************
 * Symbol Class Implementation
 *********************************************************************************************************************/
const std::string Symbol::LITERAL_IDENTIFIER = "<literal_symbol>";

Symbol::Symbol( Type this_type, std::string this_identifier ) : type( this_type ), identifier( this_identifier ), is_literal( false ) {
    if ( this_identifier == LITERAL_IDENTIFIER ) is_literal = true;
}

Symbol::Symbol( Type this_type ) : type( this_type ), identifier( LITERAL_IDENTIFIER ), is_literal( true ) { }

Symbol::Type Symbol::get_type() const {
    return type;
}

void Symbol::set_identifier( std::string this_identifier ) {
    identifier = this_identifier;
}

std::string Symbol::get_identifier() {
    return identifier;
}


/**********************************************************************************************************************
 * TypedSymbol Class Implementation
 *********************************************************************************************************************/
template <typename T>
TypedSymbol<T>::TypedSymbol( Symbol::Type this_type, std::string this_identifier, T this_data ) : Symbol( this_type, this_identifier ), data( this_data ) { }

template <typename T>
TypedSymbol<T>::TypedSymbol( Symbol::Type this_type, T this_data ) : Symbol( this_type ), data( this_data ) { }

template <typename T>
std::shared_ptr<Symbol> TypedSymbol<T>::cast( Symbol::Type cast_type ) const {
    if ( type == cast_type ) return std::make_shared< TypedSymbol<T> >( *this );

    if ( type == Symbol::Type::INT ) {
        if ( cast_type == Symbol::Type::REAL ) {
            return std::make_shared< TypedSymbol<double> >( Symbol::Type::REAL, identifier, double( data ) );
        } else throw EngineException( "Invalid cast from int." );
    } else if ( type == Symbol::Type::REAL ) {
        if ( cast_type == Symbol::Type::INT ) {
            return std::make_shared< TypedSymbol<int> >( Symbol::Type::INT, identifier, int( data ) );
        } else throw EngineException( "Invalid cast from real." );
    } else throw EngineException( "Symbol type does not support casts." );
}

template <typename T>
void TypedSymbol<T>::set( std::shared_ptr<Symbol> rhs ) {
    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs->cast( type ) );
    data = cast_rhs->get_data();
}

template <typename T>
T TypedSymbol<T>::get_data() {
    return data;
}

template <typename T>
void TypedSymbol<T>::set_data( T this_data ) {
    if ( is_literal ) throw EngineException( "Attempted to update data of a literal symbol." );
    data = this_data;
}

template <typename T>
TypedSymbol<T> TypedSymbol<T>::op_add( const Symbol &rhs ) const {
    if ( not ( ( type == Symbol::Type::INT or type == Symbol::Type::REAL )
               and ( rhs.get_type() == Symbol::Type::INT or rhs.get_type() == Symbol::Type::REAL ) ) ) {
        throw EngineException( "Addition of symbols is only supported for int and real types." );
    }

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return TypedSymbol<T>( type, data + cast_rhs->data );
}

template <typename T>
TypedSymbol<T> TypedSymbol<T>::op_sub( const Symbol &rhs ) const {
    if ( not ( ( type == Symbol::Type::INT or type == Symbol::Type::REAL )
               and ( rhs.get_type() == Symbol::Type::INT or rhs.get_type() == Symbol::Type::REAL ) ) ) {
        throw EngineException( "Subtraction of symbols is only supported for int and real types." );
    }

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return TypedSymbol<T>( type, data - cast_rhs->data );
}

template <typename T>
TypedSymbol<T> TypedSymbol<T>::op_mul( const Symbol &rhs ) const {
    if ( not ( ( type == Symbol::Type::INT or type == Symbol::Type::REAL )
               and ( rhs.get_type() == Symbol::Type::INT or rhs.get_type() == Symbol::Type::REAL ) ) ) {
        throw EngineException( "Multiplication of symbols is only supported for int and real types." );
    }

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return TypedSymbol<T>( type, data * cast_rhs->data );
}

template <typename T>
TypedSymbol<T> TypedSymbol<T>::op_div( const Symbol &rhs ) const {
    if ( not ( ( type == Symbol::Type::INT or type == Symbol::Type::REAL )
               and ( rhs.get_type() == Symbol::Type::INT or rhs.get_type() == Symbol::Type::REAL ) ) ) {
        throw EngineException( "Division of symbols is only supported for int and real types." );
    }

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return TypedSymbol<T>( type, data / cast_rhs->data );
}

template <typename T>
TypedSymbol<T> TypedSymbol<T>::op_pow( const Symbol &arg ) const {
    if ( not ( ( type == Symbol::Type::INT or type == Symbol::Type::REAL )
               and ( arg.get_type() == Symbol::Type::INT or arg.get_type() == Symbol::Type::REAL ) ) ) {
        throw EngineException( "Exponentiation of symbols is only supported for int and real types." );
    }

    std::shared_ptr< TypedSymbol<T> > cast_arg = std::dynamic_pointer_cast< TypedSymbol<T> >( arg.cast( type ) );
    return TypedSymbol<T>( type, std::pow( data, cast_arg->data ) );
}

template <typename T>
TypedSymbol<T> TypedSymbol<T>::op_negate() const {
    if ( not ( type == Symbol::Type::INT or type == Symbol::Type::REAL ) )
        throw EngineException( "Negation of symbols is only supported for int and real types." );

    return TypedSymbol<T>( type, -data );
}

template <typename T>
BooleanSymbol TypedSymbol<T>::op_equality( const Symbol &rhs ) const {
    if ( not ( type == Symbol::Type::INT or type == Symbol::Type::REAL ) )
        throw EngineException( "Real and int types may not be compared with non-numerical types." );

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return BooleanSymbol( data == cast_rhs->data );
}

template <typename T>
BooleanSymbol TypedSymbol<T>::op_not_equal( const Symbol &rhs ) const {
    if ( not ( type == Symbol::Type::INT or type == Symbol::Type::REAL ) )
        throw EngineException( "Real and int types may not be compared with non-numerical types." );

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return BooleanSymbol( data != cast_rhs->data );
}

template <typename T>
BooleanSymbol TypedSymbol<T>::op_less_than( const Symbol &rhs ) const {
    if ( not ( type == Symbol::Type::INT or type == Symbol::Type::REAL ) )
        throw EngineException( "Real and int types may not be compared with non-numerical types." );

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return BooleanSymbol( data < cast_rhs->data );
}

template <typename T>
BooleanSymbol TypedSymbol<T>::op_greater_than( const Symbol &rhs ) const {
    if ( not ( type == Symbol::Type::INT or type == Symbol::Type::REAL ) )
        throw EngineException( "Real and int types may not be compared with non-numerical types." );

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return BooleanSymbol( data > cast_rhs->data );
}

template <typename T>
BooleanSymbol TypedSymbol<T>::op_lt_or_eq( const Symbol &rhs ) const {
    if ( not ( type == Symbol::Type::INT or type == Symbol::Type::REAL ) )
        throw EngineException( "Real and int types may not be compared with non-numerical types." );

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return BooleanSymbol( data <= cast_rhs->data );
}

template <typename T>
BooleanSymbol TypedSymbol<T>::op_gt_or_eq( const Symbol &rhs ) const {
    if ( not ( type == Symbol::Type::INT or type == Symbol::Type::REAL ) )
        throw EngineException( "Real and int types may not be compared with non-numerical types." );

    std::shared_ptr< TypedSymbol<T> > cast_rhs = std::dynamic_pointer_cast< TypedSymbol<T> >( rhs.cast( type ) );
    return BooleanSymbol( data >= cast_rhs->data );
}

/**********************************************************************************************************************
 * BooleanSymbol Class Implementation
 *********************************************************************************************************************/
BooleanSymbol::BooleanSymbol(std::string this_identifier, bool this_data) :
        Symbol( Symbol::Type::BOOL, this_identifier ), data( this_data ) { }

BooleanSymbol::BooleanSymbol( bool this_data ) : Symbol( Symbol::Type::BOOL ), data( this_data ) { }

std::shared_ptr<Symbol> BooleanSymbol::cast( Symbol::Type cast_type ) const {
    if ( type == cast_type ) {
        return std::make_shared< BooleanSymbol >( *this );
    } else throw EngineException( "Boolean symbols may not be cast to other types." );
}

void BooleanSymbol::set( std::shared_ptr<Symbol> rhs ) {
    std::shared_ptr<BooleanSymbol> cast_rhs = std::dynamic_pointer_cast<BooleanSymbol>( rhs->cast( type ) );
    data = cast_rhs->get_data();
}

bool BooleanSymbol::get_data() {
    return data;
}

void BooleanSymbol::set_data( bool this_data ) {
    data = this_data;
}

BooleanSymbol BooleanSymbol::op_not() const {
    if ( not ( type == Symbol::Type::BOOL ) )
        throw EngineException( "Boolean negation of symbols is only supported for bool types." );

    return BooleanSymbol( not data );
}

BooleanSymbol BooleanSymbol::op_and(const BooleanSymbol &rhs) const {
    if ( not ( type == Symbol::Type::BOOL ) )
        throw EngineException( "Boolean 'and' of symbols is only supported for bool types." );

    return BooleanSymbol( data and rhs.data );
}

BooleanSymbol BooleanSymbol::op_or(const BooleanSymbol &rhs) const {
    if ( not ( type == Symbol::Type::BOOL ) )
        throw EngineException( "Boolean 'or' of symbols is only supported for bool types." );

    return BooleanSymbol( data or rhs.data );
}

BooleanSymbol BooleanSymbol::op_eq( const BooleanSymbol &rhs) const {
    if ( not ( type == Symbol::Type::BOOL ) )
        throw EngineException( "Boolean '==' of symbols is only supported for bool types." );

    return BooleanSymbol( data == rhs.data );
}


/**********************************************************************************************************************
 * List Class Implementation
 *********************************************************************************************************************/
List::List( std::string identifier ) : Symbol( Symbol::Type::LIST, identifier ) { }

std::shared_ptr<Symbol> List::cast( Symbol::Type cast_type ) const {
    if ( type == cast_type ) {
        return std::make_shared<List>( *this );
    } else throw EngineException( "Casting lists to other types is not supported." );
}

void List::set( std::shared_ptr<Symbol> rhs ) {
    if ( rhs->get_type() != Symbol::Type::LIST ) throw EngineException( "Tried to assign a list to an invalid type." );
    std::shared_ptr<List> rhs_list = std::dynamic_pointer_cast<List>( rhs );

    list.clear();  // Empty out the current list.
    for ( auto element : rhs_list->list )  {
        list.push_back( element );
    }
}

void List::append( std::shared_ptr<Symbol> element ) {
    list.push_back( element );
}

std::shared_ptr<Symbol> List::at( unsigned long i ) {
    if ( i >= list.size() ) throw EngineException( "List index is out of range." );
    return list.at( i );
}

void List::remove( unsigned long i ) {
    if ( i >= list.size() ) throw EngineException( "List index is out of range." );
    list.erase( list.begin() + i );
}


/**********************************************************************************************************************
 * SymbolScope Class Implementation
 *********************************************************************************************************************/
const std::string SymbolScope::INT_TYPE_DEFAULT = "0";

const std::string SymbolScope::REAL_TYPE_DEFAULT = "0.0";

const std::string SymbolScope::BOOL_TYPE_DEFAULT = SymbolScope::BOOL_FALSE;

const std::string SymbolScope::BOOL_TRUE = "true";

const std::string SymbolScope::BOOL_FALSE = "false";

SymbolScope::SymbolScope() : return_flag( false ), break_flag( false ), continue_flag( false ) { }

void SymbolScope::add_symbol( Symbol::Type this_type, std::string this_identifier, std::string this_value ) {
    // Check if the symbol identifier already exists. If so, throw an exception.

    // Convert the value string to the appropriate type.
    if ( this_type == Symbol::Type::INT ) {
        int data = std::stoi( this_value );
        std::shared_ptr<Symbol> sym = std::make_shared< TypedSymbol<int> >( Symbol::Type::INT, this_identifier, data );
        symbols.push_back( sym );
    } else if ( this_type == Symbol::Type::REAL ) {
        double data = std::stod(this_value);
        std::shared_ptr<Symbol> sym = std::make_shared< TypedSymbol<double> >(Symbol::Type::REAL, this_identifier, data );
        symbols.push_back( sym );
    } else if ( this_type == Symbol::Type::BOOL ) {
        bool data;
        if ( this_value == BOOL_TRUE ) {
            data = true;
        } else if ( this_value == BOOL_FALSE ) {
            data = false;
        } else throw EngineException( "Invalid boolean literal." );
        std::shared_ptr<Symbol> sym = std::make_shared< TypedSymbol<bool> >( Symbol::Type::BOOL, this_identifier, data );
        symbols.push_back( sym );
    } else if ( this_type == Symbol::Type::LIST ) {
        std::shared_ptr<Symbol> sym = std::make_shared<List>( this_identifier );
        symbols.push_back( sym );
    } else {
        throw EngineException( "Unknown symbol type." );
    }
}

void SymbolScope::add_symbol( std::shared_ptr<Symbol> symbol ) {
    symbols.push_back( symbol );
}

std::shared_ptr<Symbol> SymbolScope::get_symbol( std::string identifier ) {
    for ( auto symbol : symbols ) {
        if ( symbol->get_identifier() == identifier ) {
            return symbol;
        }
    }

    throw EngineException( "Symbol does not exist." );
}

void SymbolScope::set_symbol( std::string identifier, std::string value ) {
    std::shared_ptr<Symbol> sym = get_symbol( identifier );

    if ( sym->get_type() == Symbol::Type::INT ) {
        int data = std::stoi( value );
        std::shared_ptr< TypedSymbol<int> > t_sym = std::dynamic_pointer_cast< TypedSymbol<int> >( sym );
        t_sym->set_data( data );
    } else if ( sym->get_type() == Symbol::Type::REAL ) {
        double data = std::stod( value );
        std::shared_ptr< TypedSymbol<double> > t_sym = std::dynamic_pointer_cast< TypedSymbol<double> >( sym );
        t_sym->set_data( data );
    } else if ( sym->get_type() == Symbol::Type::BOOL ) {
        bool data;
        if ( value == BOOL_TRUE ) {
            data = true;
        } else if ( value == BOOL_FALSE ) {
            data = false;
        } else throw EngineException( "Unknown boolean type." );

        std::shared_ptr<BooleanSymbol> t_sym = std::dynamic_pointer_cast<BooleanSymbol>( sym );
        t_sym->set_data( data );
    } else throw EngineException( "Unknown symbol type." );

}

void SymbolScope::set_symbol( std::string identifier, std::shared_ptr<Symbol> rhs ) {
    std::shared_ptr<Symbol> lhs = get_symbol( identifier );  // Find the symbol with the matching identifier.
    lhs->set( rhs );  // Update that symbol's value with the right-hand side of the assignment.
}

void SymbolScope::set_functions( std::vector<UserFunction*> this_functions ) {
    functions = this_functions;
}

UserFunction* SymbolScope::get_function( std::string identifier ) {
    for ( auto fun : functions ) {
        if ( fun->get_identifier() == identifier ) return fun;
    }

    throw EngineException( "User function is not defined." );
}

std::vector<UserFunction*> SymbolScope::get_functions() {
    return functions;
}

int SymbolScope::length() {
    return symbols.size();
}

std::shared_ptr<Symbol> SymbolScope::at( int i ) {
    return symbols.at( i );
}

void SymbolScope::clear() {
    symbols.clear();
    functions.clear();
    reset_return_flag();
    reset_break_flag();
}

void SymbolScope::set_return_flag() {
    return_flag = true;
}

void SymbolScope::reset_return_flag() {
    return_flag = false;
}

bool SymbolScope::get_return_flag() {
    return return_flag;
}

void SymbolScope::set_break_flag() {
    break_flag = true;
}

void SymbolScope::reset_break_flag() {
    break_flag = false;
}

bool SymbolScope::get_break_flag() {
    return break_flag;
}

void SymbolScope::set_continue_flag() {
    continue_flag = true;
}

void SymbolScope::reset_continue_flag() {
    continue_flag = false;
}

bool SymbolScope::get_continue_flag() {
    return continue_flag;
}
