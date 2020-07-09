//
// Created by loheac on 5/16/20.
//

#ifndef SCIMITAR7_SYMBOL_H
#define SCIMITAR7_SYMBOL_H

#include <memory>
#include <vector>

class UserFunction;

/**
 * Base class implementing a symbol which is defined within the scope of a user-defined function. A symbol may currently
 * take the data types of integers (INT), double-precision floating points (REAL), and booleans (BOOL).
 *
 * Note that symbols have a different purpose in comparison to parameters. Parameters hold a value in terms of a string
 * representation and an optionally defined format. A symbol, on the other hand, defines a piece of data in terms of its
 * raw representation. As such, symbols must respect proper casting between data types.
 */
class Symbol {

public:

    /**
     * Enumeration of the data types this symbol can take in terms of the language.
     */
    enum Type {
        INT,    // Integer type. Stored as an int.
        REAL,   // Double-precision floating point. Stored as a double.
        BOOL,   // Boolean value. Stored as a bool.
        LIST    // List of Symbol elements. Stored as a std::vector<Symbol>.
    };

    /**
     * Constructor for a defined symbol with an identifier which is bound to a value.
     * @param type Data type of this symbol.
     * @param identifier Unique identifier of this symbol.
     */
    Symbol( Type type, std::string identifier );

    /**
     * Constructor for a literal symbol of a given type.
     * @param type Data type of this symbol.
     */
    Symbol( Type type );

    /**
     * Constructs a new Symbol instance which is of the same identifier but of a new type. The data is cast to the new
     * underlying storage type.
     * @param type The new data type to cast the symbol to.
     * @return A shared pointer to tne newly-constructed symbol.
     */
    virtual std::shared_ptr<Symbol> cast( Type type ) const = 0;

    /**
     * Sets the data of this symbol to the data of the passed symbol. A cast is performed if necessary. Derived classes
     * are expected to implement this method.
     * @param rhs The source symbol.
     */
    virtual void set( std::shared_ptr<Symbol> rhs ) = 0;

    /**
     * Gets the type of this symbol.
     * @return The type of this symbol.
     */
    Type get_type() const;

    /**
     * Sets the identifier of this symbol to a new string.
     * @param identifier The new identifier of this symbol.
     */
    void set_identifier( std::string identifier );

    /**
     * Gets the identifier of this symbol.
     * @return The identifier of this symbol.
     */
    std::string get_identifier();

protected:

    /**
     * The identifier to be used for all literal symbols.
     */
    static const std::string LITERAL_IDENTIFIER;

    /**
     * The data type of this symbol.
     */
    Type type;

    /**
     * The identifier of this symbol.
     */
    std::string identifier;

    /**
     * Flag indicating whether this symbol is a literal value.
     */
    bool is_literal;

};


/**
 * Derived Symbol class implementing a boolean variable.
 */
class BooleanSymbol : public Symbol {

public:
    /**
     * Constructor for a defined symbol with an identifier which is bound to a value.
     * @param identifier Identifier of this symbol.
     * @param data Boolean data bound to this symbol.
     */
    BooleanSymbol( std::string identifier, bool data );

    /**
     * Constructor for a literal boolean value.
     * @param data Boolean data bound to this symbol.
     */
    BooleanSymbol( bool data );

    /**
     * Constructs a new Symbol instance which is of the same identifier but of a new type. The data is cast to the new
     * underlying storage type.
     * @param type The new data type to cast the symbol to.
     * @return A shared pointer to tne newly-constructed symbol.
     */
    std::shared_ptr<Symbol> cast( Symbol::Type type ) const override;

    /**
     * Sets the data of this symbol to the data of the passed symbol. A cast is performed if necessary.
     * @param rhs The source symbol.
     */
    void set( std::shared_ptr<Symbol> rhs ) override;

    /**
     * Gets the boolean data for this symbol.
     * @return The boolean data for this symbol.
     */
    bool get_data();

    /**
     * Sets the boolean data for this symbol.
     * @param data The new boolean data for this symbol.
     */
    void set_data( bool data );

    /**
     * Performs the boolean "not" operation on this symbol and returns a new instance with the evaluated result.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_not() const;

    /**
     * Performs the boolean "and" operation between this symbol and the passed symbol, and returns a new instance with
     * the evaluated result.
     * @param rhs The right-hand side of the binary "and" operation.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_and( const BooleanSymbol &rhs ) const;

    /**
     * Performs the boolean "or" operation between this symbol and the passed symbol, and returns a new instance with
     * the evaluated result.
     * @param rhs The right-hand side of the binary "or" operation.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_or( const BooleanSymbol &rhs ) const;

    /**
     * Performs the boolean equivalence operation between this symbol and the passed symbol, and returns a new instance
     * with the evaluated result.
     * @param rhs The right-hand side of the binary equivalence operation.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_eq( const BooleanSymbol &rhs ) const;

private:

    /**
     * The boolean data for this symbol.
     */
    bool data;

};


/**
 * Derived symbol template class which implements symbols of a numerical data type. The underlying storage is given by
 * template parameter. This class currently implements the INT and REAL data types in the language.
 * @tparam T The underlying storage class of the numerical data type.
 */
template <typename T>
class TypedSymbol : public Symbol {

public:

    /**
     * Constructor for a defined symbol with an identifier which is bound to a value.
     * @param type The type of this parameter (in terms of the data type provided by the language).
     * @param identifier The identifier of this symbol.
     * @param data The numerical data bound to this symbol.
     */
    TypedSymbol( Symbol::Type type, std::string identifier, T data );

    /**
     * Constructor for a literal numerical value.
     * @param type The type of this parameter (in terms of the data type provided by the language).
     * @param data The numerical data bound to this symbol.
     */
    TypedSymbol( Symbol::Type type, T data );

    /**
     * Constructs a new Symbol instance which is of the same identifier but of a new type. The data is cast to the new
     * underlying storage type.
     * @param type The new data type to cast the symbol to.
     * @return A shared pointer to tne newly-constructed symbol.
     */
    std::shared_ptr<Symbol> cast( Symbol::Type type ) const override;

    /**
     * Sets the data of this symbol to the data of the passed symbol. A cast is performed if necessary. Derived classes
     * are expected to implement this method.
     * @param rhs The source symbol.
     */
    void set( std::shared_ptr<Symbol> rhs ) override;

    /**
     * Gets the type of this symbol.
     * @return The type of this symbol.
     */
    T get_data();

    /**
     * Sets the data of this symbol to a new value.
     * @param data The new value of this symbol.
     */
    void set_data( T data );

    /**
     * Performs the addition operation between this symbol and the passed symbol and returns a new instance with the
     * evaluated result.
     * @return A new instance of the evaluated result.
     */
    TypedSymbol<T> op_add( const Symbol &rhs ) const;

    /**
     * Performs the subtraction operation between this symbol and the passed symbol and returns a new instance with the
     * evaluated result.
     * @return A new instance of the evaluated result.
     */
    TypedSymbol<T> op_sub( const Symbol &rhs ) const;

    /**
     * Performs the multiplication operation between this symbol and the passed symbol and returns a new instance with
     * the evaluated result.
     * @return A new instance of the evaluated result.
     */
    TypedSymbol<T> op_mul( const Symbol &rhs ) const;

    /**
     * Performs the division operation between this symbol and the passed symbol and returns a new instance with the
     * evaluated result.
     * @return A new instance of the evaluated result.
     */
    TypedSymbol<T> op_div( const Symbol &rhs ) const;

    /**
     * Performs the exponentiation operation between this symbol and the passed symbol and returns a new instance with
     * the evaluated result.
     * @return A new instance of the evaluated result.
     */
    TypedSymbol<T> op_pow( const Symbol &arg ) const;

    /**
     * Performs the negation operation on this symbol and returns a new instance with the evaluated result.
     * @return A new instance of the evaluated result.
     */
    TypedSymbol<T> op_negate() const;

    /**
     * Performs the boolean equality operation between this symbol and the passed symbol and returns a new instance with
     * the evaluated result.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_equality( const Symbol &arg ) const;

    /**
     * Performs the boolean "not equal" operation between this symbol and the passed symbol and returns a new instance
     * with the evaluated result.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_not_equal( const Symbol &arg ) const;

    /**
     * Performs the boolean "less than" operation between this symbol and the passed symbol and returns a new instance
     * with the evaluated result.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_less_than( const Symbol &arg ) const;

    /**
     * Performs the boolean "greater than" operation between this symbol and the passed symbol and returns a new
     * instance with the evaluated result.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_greater_than( const Symbol &arg ) const;

    /**
     * Performs the boolean "less than or equal" operation between this symbol and the passed symbol and returns a new
     * instance with the evaluated result.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_lt_or_eq( const Symbol &arg ) const;

    /**
     * Performs the boolean "greater than or equal" operation between this symbol and the passed symbol and returns a new
     * instance with the evaluated result.
     * @return A new instance of the evaluated result.
     */
    BooleanSymbol op_gt_or_eq( const Symbol &arg ) const;

private:

    /**
     * The numerical data held by this symbol.
     */
    T data;

};


/**
 * Derived symbol class which implements an ordered list data structure of zero or more Symbol instances. Elements of a
 * List may be of different types derived from Symbol.
 */
class List : public Symbol {

public:

    /**
     * Constructor.
     * @param identifier Identifier of this List instance.
     */
    List( std::string identifier );

    /**
     * Constructs a new Symbol instance which is of the same identifier but of a new type. The data is cast to the new
     * underlying storage type.
     * @param type The new data type to cast the symbol to.
     * @return A shared pointer to tne newly-constructed symbol.
     */
    std::shared_ptr<Symbol> cast( Symbol::Type type ) const override;

    /**
     * Sets the data of this symbol to the data of the passed symbol. A cast is performed if necessary. Derived classes
     * are expected to implement this method.
     * @param rhs The source symbol.
     */
    void set( std::shared_ptr<Symbol> rhs ) override;

    /**
     * Appends a new element to the end of this list.
     * @param element Pointer to the new list element to add.
     */
    void append( std::shared_ptr<Symbol> element );

    /**
     * Returns a pointer to the list element located at the passed index. List indices begin from zero.
     * @param i Index of the element to obtain.
     * @return Base-class pointer to the element at the passed index.
     */
    std::shared_ptr<Symbol> at( unsigned long i );

    /**
     * Removes the list element at the provided index.
     * @param i The index of the element to remove.
     */
    void remove( unsigned long i );

private:

    /**
     * Container for the ordered list elements.
     */
    std::vector< std::shared_ptr<Symbol> > list;
};

/**
 * A container object which holds a set of symbols which are defined within a given scope.
 */
class SymbolScope {

public:

    /**
     * Constructor.
     */
    SymbolScope();

    /**
     * Adds a new symbol to this scope. The value is provided as a string, which is converted to the underlying storage
     * type matching the provided symbol type.
     * @param type The type of this symbol (in terms of the data type provided by the language).
     * @param identifier The identifier of this symbol.
     * @param value The value of this symbol in a string representation.
     */
    void add_symbol( Symbol::Type type, std::string identifier, std::string value );

    /**
     * Adds a symbol to this scope.
     * @param symbol The symbol to add to this scope.
     */
    void add_symbol( std::shared_ptr<Symbol> symbol );

    /**
     * Gets a reference to a symbol within this scope matching the passed identifier.
     * @param identifier The identifier of the symbol to obtain.
     * @return A reference to the matching symbol.
     */
    std::shared_ptr<Symbol> get_symbol( std::string identifier );

    /**
     * Sets the value of this symbol to the interpreted value of the passed string. Conversions are supported to INT,
     * REAL, and BOOL types.
     * @param identifier The identifier of the symbol whose data is to be updated.
     * @param value The new value of the symbol, formatted as a string. If the conversion from a string type is not
     * successful, an exception will be thrown.
     */
    void set_symbol( std::string identifier, std::string value );

    /**
     * Sets the value of this symbol equal to the value of another symbol. A conversion between the data of the two
     * symbols is attempted if necessary.
     * @param identifier The identifier of the symbol whose data is to be updated.
     * @param symbol The source symbol of the data to copy.
     */
    void set_symbol( std::string identifier, std::shared_ptr<Symbol> symbol );

    /**
     * Sets the vector of function pointers for this scope.
     * @param functions The vector of function pointers for this scope.
     */
    void set_functions( std::vector<UserFunction*> functions );

    /**
     * Gets the vector of function pointer for this scope.
     * @return The vector of function pointers for this scope.
     */
    std::vector<UserFunction*> get_functions();

    /**
     * Gets a reference to a function matching the passed identifier.
     * @param identifier Identifier of the function reference to obtain.
     * @return A pointer to the matching function.
     */
    UserFunction* get_function( std::string identifier );

    /**
     * Gets the count of symbols in this scope.
     * @return The count of symbols in this scope.
     */
    int length();

    /**
     * Obtains the symbol at the passed index, where the indices are given by the order in which symbols are defined.
     * Intended for cases where all symbols are iterated over.
     * @param i The index of the symbol to obtain.
     * @return The symbol at index i.
     */
    std::shared_ptr<Symbol> at( int i );

    /**
     * Resets the state of this scope. The symbol and function references are cleared, and all flags are reset.
     */
    void clear();

    /**
     * Sets the return flag to true.
     */
    void set_return_flag();

    /**
     * Resets the return flag to false.
     */
    void reset_return_flag();

    /**
     * Gets the current state of the return flag. The return flag indicates whether a return statement has been executed
     * within this scope.
     * @return The current state of the return flag.
     */
    bool get_return_flag();

    /**
     * Sets the break flag to true.
     */
    void set_break_flag();

    /**
     * Resets the break flag to false.
     */
    void reset_break_flag();

    /**
     * Gets the current state of the break flag. The break flag indicates whether a break statement has been executed
     * within this scope.
     * @return The current state of the break flag.
     */
    bool get_break_flag();

    /**
     * Sets the continue flag to true.
     */
    void set_continue_flag();

    /**
     * Resets the continue flag to false.
     */
    void reset_continue_flag();

    /**
     * Gets the current state of the continue flag.
     * @return The current state of the continue flag.
     */
    bool get_continue_flag();

    /**
     * The default initialized value of an integer type.
     */
    static const std::string INT_TYPE_DEFAULT;

    /**
     * The default initialized value of a real type.
     */
    static const std::string REAL_TYPE_DEFAULT;

    /**
     * The default initialized value of a boolean type.
     */
    static const std::string BOOL_TYPE_DEFAULT;

    /**
     * String token for a boolean true value, as defined by the language.
     */
    static const std::string BOOL_TRUE;

    /**
     * String token for a boolean false value, as defined by the language.
     */
    static const std::string BOOL_FALSE;

private:

    /**
     * Vector of symbols which are defined within this symbol scope.
     */
    std::vector< std::shared_ptr<Symbol> > symbols;

    /**
     * Vector of user functions which are defined within this symbol scope.
     */
    std::vector<UserFunction*> functions;

    /**
     * Flag to indicate to calling functions whether a return statement has been executed.
     */
    bool return_flag;

    /**
     * Flag to indicate to calling functions whether a continue statement has been executed.
     */
    bool continue_flag;

    /**
     * Flag to indicate to calling functions whether a break statement has been executed.
     */
    bool break_flag;

};

#endif //SCIMITAR7_SYMBOL_H
