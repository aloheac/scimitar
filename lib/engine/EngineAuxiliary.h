//
// Created by loheac on 11/26/19.
//

#ifndef SCIMITAR7_ENGINEAUXILIARY_H
#define SCIMITAR7_ENGINEAUXILIARY_H

#include <string>
#include <vector>
#include "BasicStructures.h"
#include "../language/UserFunction.h"

class Engine;

struct ValuePair {

    enum ValueType {
        INT,
        REAL,
        STRING
    };

    ValuePair( ValueType type, std::string identifier, std::string value, std::string format );

    ValueType type;

    std::string identifier;

    std::string value;

    std::string format;

};

struct DirectoryOrderPair {

    DirectoryOrderPair( std::string identifier, unsigned int directory_order );

    std::string identifier;

    unsigned int directory_order;

    static bool comp( const DirectoryOrderPair left, const DirectoryOrderPair right );

};

class Run {

public:

    Run();

    void add_value( ValuePair value );

    std::string get_value( std::string identifier ) const;

    void set_value( std::string identifier, std::string value );

    std::string get_format( std::string identifier ) const;

    ValuePair::ValueType get_type( std::string identifier ) const;

    std::string emit();

    void mark_remove();

    bool removed();

    void hide_parameters( const std::vector<std::string> &hidden_parameters );

    void sort_values( std::vector<std::string> identifiers );

    SymbolScope to_symbol_scope();

private:

    void remove_value( std::string identifier );

    std::vector<ValuePair> values;

    bool marked_remove;

};

class RunComparator {

public:

    RunComparator( std::vector<std::string> directory_order );

    bool operator()( const Run left, const Run right );

private:

    std::vector<std::string> directory_order;

};

class ExecutionResult {

public:

    ExecutionResult();

    void add_run( Run run );

    void set_option_set( OptionSet options );

    void set_directory_order( std::vector<std::string> directory_order );

    void set_hidden_parameters( std::vector<std::string> hidden );

    void reset();

    Run next();

    long length();

    bool empty();

    std::string emit();

    void sort_runs( std::vector<std::string> identifiers );

private:

    unsigned long index;

    std::vector<Run> runs;

    std::vector<std::string> directory_order;

    std::vector<std::string> hidden_parameters;

    OptionSet options;

    bool emptyResultReturned;

};

#endif //SCIMITAR7_ENGINEAUXILIARY_H
