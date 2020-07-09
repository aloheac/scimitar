//
// Created by loheac on 11/16/19.
//

#ifndef SCIMITAR7_ENGINEACTION_H
#define SCIMITAR7_ENGINEACTION_H

#include "Engine.h"
#include "../language/LoopStatement.h"
#include "BasicStructures.h"

enum ActionType {
    PARAM,
    SET_PARAM,
    FUNCTION_PARAM,
    SET_FUNCTION,
    GROUP,
    UNGROUP,
    RUN_BLOCK,
    SET_OPTION,
    SYSTEM_CONFIG,
    USER_FUNCTION
};

class EngineAction {

public:

    EngineAction( ActionType type );

    virtual ~EngineAction() = default;

    void set_engine( Engine* engine );

    ActionType get_type();

    void execute( Engine* engine );

    virtual void execute() = 0;

protected:

    ActionType type;

    Engine* engine;

};


class ActionParam : public EngineAction {

public:

    ActionParam( std::string type, std::string identifier, std::string value, OptionSet options );

    void execute() override;

private:

    void set_option( OptionPair option );

    std::string type;

    std::string identifier;

    std::string value;

    OptionSet options;
};


class ActionFunction : public EngineAction {

public:

    ActionFunction( std::string identifier, std::shared_ptr<ArithmeticExpression> expr, OptionSet options );

    void execute() override;

private:

    void set_option( OptionPair option );

    std::string identifier;

    std::shared_ptr<ArithmeticExpression> expr;

    OptionSet options;
};


class ActionSetParam : public EngineAction {

public:

    ActionSetParam( std::string identifier, OptionSet options );

    void execute() override;

private:

    void set_option( OptionPair option );

    std::string identifier;

    OptionSet options;

};

class ActionSetFunction : public EngineAction {

public:

    ActionSetFunction( std::string identifier, std::shared_ptr<ArithmeticExpression> expr, OptionSet options );

    void execute() override;

private:

    void set_option( OptionPair option );

    std::string identifier;

    std::shared_ptr<ArithmeticExpression> expr;

    OptionSet options;

};


class ActionSetOption : public EngineAction {

public:

    ActionSetOption( OptionSet options );

    void execute() override;

private:

    OptionSet options;

};


class ActionGroup : public EngineAction {

public:

    ActionGroup( std::vector<std::string> identifiers );

    void execute() override;

private:

    std::vector<std::string> identifiers;

};


class ActionUngroup : public EngineAction {

public:

    ActionUngroup( std::vector<std::string> identifiers );

    void execute() override;

private:

    std::vector<std::string> identifiers;

};


class ActionSetRunBlock : public EngineAction {

public:

    ActionSetRunBlock( std::shared_ptr<RunLoop> loop );

    void execute() override;

private:

    std::shared_ptr<RunLoop> loop;

};


class ActionSystemConfig : public EngineAction {

public:

    ActionSystemConfig( OptionSet config );

    void execute() override;

private:

    OptionSet config;

};


class ActionUserFunction : public EngineAction {

public:

    ActionUserFunction( std::shared_ptr<UserFunction> function );

    void execute() override;

private:

    std::shared_ptr<UserFunction> function;

};

#endif //SCIMITAR7_ENGINEACTION_H
