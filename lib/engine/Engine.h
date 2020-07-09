//
// Created by loheac on 11/9/19.
//

#ifndef SCIMITAR7_ENGINE_H
#define SCIMITAR7_ENGINE_H

#include "Group.h"
#include "EngineAuxiliary.h"
#include "../language/LoopStatement.h"
#include "BasicStructures.h"

class Engine {

public:

    Engine();

    ~Engine();

    void add_parameter( ParameterType type, std::string identifier, std::string value, std::string format );

    void add_function( std::string identifier, std::shared_ptr<ArithmeticExpression> expr, std::string format );

    void delete_parameter( std::string identifier );

    long get_run_count();

    ExecutionResult execute();

    void group_parameters( std::string identifierA, std::string identifierB );

    void ungroup_parameter( std::string identifier );

    void set_directory_order( std::string identifier, int order );

    unsigned int get_directory_order( std::string identifier );

    void set_format( std::string identifier, std::string format );

    std::string get_format( std::string identifier );

    void set_value( std::string identifier, std::string value );

    void set_value( std::string identifier, std::shared_ptr<ArithmeticExpression> expr );

    void set_option( OptionPair option );

    void set_run_loop( RunLoop loop );

    void hide_parameter( std::string identifier );

    bool is_hidden( std::string identifier );

    void add_user_function( UserFunction function );

    std::vector<UserFunction*> get_user_functions();

    std::string to_string();

    static void set_rng_seed( long seed );

    /**
     * The random number generator object to be used by all instances.
     */
    static std::default_random_engine rng;

private:

    static ExecutionResult get_run_product( ExecutionResult initial_result, Group group );

    Run evaluate_function_parameters( Run run );

    void validate();

    ExecutionResult last_result;

    Parameter* get_parameter( std::string identifier );

    Group* get_group( std::string identifier );

    std::vector<Parameter*> parameters;

    std::vector<Group*> groups;

    OptionSet options;

    int parameter_count;

    RunLoop run_loop;

    std::vector<UserFunction*> user_functions;

};

#endif //SCIMITAR7_ENGINE_H
