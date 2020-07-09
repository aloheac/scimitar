//
// Created by loheac on 5/1/20.
//

#ifndef SCIMITAR7_USERFUNCTION_H
#define SCIMITAR7_USERFUNCTION_H

#include <string>
#include <memory>
#include <vector>
#include "../parameter/Symbol.h"

// Forward class declarations.
class ArithmeticExpression;
class ConditionalExpression;
class Expression;


class FunctionStatement {

public:

    enum Type {
        DECLARATION,
        ASSIGNMENT,
        CONDITIONAL,
        FOR_LOOP,
        WHILE_LOOP,
        RETURN,
        BREAK,
        CONTINUE,
        LIST_APPEND,
        LIST_REMOVE
    };

    FunctionStatement( Type statement_type );

    Type get_statement_type();

    virtual void execute( SymbolScope &symbols );

private:

    Type statement_type;

};


class FuncStmtDeclaration : public FunctionStatement {

public:

    FuncStmtDeclaration( Symbol::Type type, std::string identifier );

    FuncStmtDeclaration( Symbol::Type type, std::string identifier, std::shared_ptr<Expression> value );

    void execute( SymbolScope &symbols ) override;

private:

    Symbol::Type type;

    std::string identifier;

    std::shared_ptr<Expression> value;

    bool initialize_default;

};


class FuncStmtAssignment : public FunctionStatement {

public:

    FuncStmtAssignment( std::string identifier, std::shared_ptr<Expression> value );

    void execute( SymbolScope &symbols ) override;

private:

    std::string identifier;

    std::shared_ptr<Expression> value;

};


class FuncStmtConditional : public FunctionStatement {

public:

    FuncStmtConditional( std::shared_ptr<ConditionalExpression> conditional );

    void add_statement( std::shared_ptr<FunctionStatement> statement );

    void add_else_statement( std::shared_ptr<FunctionStatement> statement );

    void execute( SymbolScope &symbols ) override;

private:

    std::shared_ptr<ConditionalExpression> conditional;

    std::vector< std::shared_ptr<FunctionStatement> > statements;

    std::vector< std::shared_ptr<FunctionStatement> > else_statements;

};

class FuncStmtForLoop : public FunctionStatement {

public:

    FuncStmtForLoop( Symbol::Type loop_symbol_type, std::string loop_symbol_identifier, std::shared_ptr<ArithmeticExpression> initial_value,
            std::shared_ptr<ConditionalExpression> conditional, std::shared_ptr<ArithmeticExpression> step );

    void add_statement( std::shared_ptr<FunctionStatement> statement );

    void execute( SymbolScope &symbols ) override;

private:

    static void increment( std::shared_ptr<Symbol> &loop_symbol, std::shared_ptr<Symbol> &step_symbol );

    Symbol::Type loop_symbol_type;

    std::string loop_symbol_identifier;

    std::shared_ptr<ArithmeticExpression> initial_value;

    std::shared_ptr<ConditionalExpression> conditional;

    std::shared_ptr<ArithmeticExpression> step;

    std::vector< std::shared_ptr<FunctionStatement> > statements;

};

class FuncStmtWhileLoop : public FunctionStatement {

public:

    FuncStmtWhileLoop( std::shared_ptr<ConditionalExpression> conditional );

    void add_statement( std::shared_ptr<FunctionStatement> statement );

    void execute( SymbolScope &symbols ) override;

private:

    std::shared_ptr<ConditionalExpression> conditional;

    std::vector< std::shared_ptr<FunctionStatement> > statements;

};

class FuncStmtBreak : public FunctionStatement {

public:

    FuncStmtBreak();

    void execute( SymbolScope &symbols ) override;

};

class FuncStmtContinue : public FunctionStatement {

public:

    FuncStmtContinue();

    void execute( SymbolScope &symbols ) override;

};

class FuncStmtReturn : public FunctionStatement {

public:

    FuncStmtReturn( std::shared_ptr<ArithmeticExpression> return_stmt );

    void execute( SymbolScope &symbols ) override;

private:

    std::shared_ptr<ArithmeticExpression> return_stmt;

};

class FuncStmtListAppend : public FunctionStatement {

public:

    FuncStmtListAppend( std::string list_identifier, Symbol::Type append_type, std::shared_ptr<Expression> append_expr );

    void execute( SymbolScope &symbols ) override;

private:

    std::string list_identifier;

    Symbol::Type append_type;

    std::shared_ptr<Expression> append_expr;

};

class FuncStmtListRemove : public FunctionStatement {

public:

    FuncStmtListRemove( std::string list_identifier, std::shared_ptr<ArithmeticExpression> remove_expr );

    void execute( SymbolScope &symbols ) override;

private:

    std::string list_identifier;

    std::shared_ptr<ArithmeticExpression> remove_expr;

};

class FunctionArgumentSet {

public:

    struct Argument {

        Argument( Symbol::Type type, std::string identifier );

        Symbol::Type type;

        std::string identifier;

    };

    void add_argument( Symbol::Type type, std::string identifier);

    long length();

    Argument at ( long i );

    Argument get_argument( std::string identifier );

private:

    std::vector<Argument> arguments;

};

class UserFunction {

public:
    UserFunction( std::string identifier );

    void add_argument( Symbol::Type, std::string identifier );

    void add_statement( std::shared_ptr<FunctionStatement> statement );

    std::string get_identifier();

    FunctionArgumentSet get_arguments();

    void reset();

    std::shared_ptr<Symbol> execute( SymbolScope arguments );

    static const std::string RETURN_IDENTIFIER;

    static long EXECUTION_LIMIT;

private:

    std::string identifier;

    SymbolScope symbols;

    FunctionArgumentSet arguments;

    std::vector< std::shared_ptr<FunctionStatement> > statements;

    long execution_count;

};

template class TypedSymbol<int>;
template class TypedSymbol<double>;
template class TypedSymbol<bool>;

#endif //SCIMITAR7_USERFUNCTION_H
