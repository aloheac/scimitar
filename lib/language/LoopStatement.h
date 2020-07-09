//
// Created by loheac on 12/14/19.
//

#ifndef SCIMITAR7_LOOPSTATEMENT_H
#define SCIMITAR7_LOOPSTATEMENT_H

#include <vector>
#include "ArithmeticExpression.h"
#include "ConditionalExpression.h"

/**
 * Base class implementation for a "loop statement" grammar element. A loop statement is a statement which appears
 * a run loop. These include "run" statements, conditionals ("if" statements and "if-else" statements),
 * "remove" statements, and assignment statements. Each of these statements implements its own derived class.
 */
class LoopStatement {
public:

    /**
     * Enumerations of the kinds of loop statements which are implemented.
     */
    enum StatementType {
        IF,
        IF_ELSE,
        REMOVE,
        ASSIGNMENT
    };

    /**
     * Constructor.
     * @param type Indicates the type of statement type.
     */
    LoopStatement( StatementType type );

    /**
     * Implements the logic which is to be executed by the Engine on a run state when this statement is encountered.
     * This should be implemented by the derived class.
     * @param state The Run instance which this statement is executed on.
     * @return The mutated Run instance which is the result of the statement execution.
     */
    virtual Run execute( Run state ) = 0;

    /**
     * Gets the run statement type of this instance.
     * @return The statement type of this instance.
     */
    StatementType get_type();

private:

    /**
     * The run statement type of this instance.
     */
    StatementType type;

};


/**
 * Derived run statement class which implements an "if" statement.
 */
class StmtIf : public LoopStatement {

public:
    /**
     * Constructor.
     * @param conditional Conditional expression tree this object will execute.
     */
    StmtIf( std::shared_ptr<ConditionalExpression> conditional );

    /**
     * Adds a loop statement to the execution block, which will run when the conditional evaluates to true.
     * @param stmt The statement to be added.
     */
    void add_statement( std::shared_ptr<LoopStatement> stmt );

    /**
     * Execute the conditional statement on a given Run object state, and return the resulting modified Run object.
     * @param state The initial state to execute the conditional statement upon.
     * @return The resulting state of the conditional block execution.
     */
    Run execute( Run state ) override;

private:
    /**
     * The conditional expression tree to be evaluated upon execution of the statement.
     */
    std::shared_ptr<ConditionalExpression> conditional;

    /**
     * Run-block statements which will be executed upon the Run object if the conditional evaluates to true.
     */
    std::vector< std::shared_ptr<LoopStatement> > statements;

};

/**
 * Derived run statement class which implements an "if-else" statement.
 */
class StmtIfElse : public LoopStatement {

public:
    /**
     * Constructor.
     * @param conditional Conditional expression tree this object will execute.
     */
    StmtIfElse( std::shared_ptr<ConditionalExpression> conditional );

    /**
     * Adds a loop statement to the execution block, which will run when the conditional evaluates to true.
     * @param stmt The statement to be added.
     */
    void add_statement( std::shared_ptr<LoopStatement> stmt );

    /**
     * Adds a loop statement to the "else" execution block, which will execute when the conditional evaluates to false.
     * @param stmt The statement to be added.
     */
    void add_else_statement( std::shared_ptr<LoopStatement> stmt );

    /**
     * Execute the conditional statement on a given Run object state, and returns the resulting modified Run object.
     * @param state The initial state to execute the conditional statement upon.
     * @return The resulting state of the conditional block execution.
     */
    Run execute( Run state ) override;

private:
    /**
     * The conditional expression tree to be evaluated upon execution of the statement.
     */
    std::shared_ptr<ConditionalExpression> conditional;

    /**
     * Run-block statements which will be executed upon the Run object if the conditional evaluates to true.
     */
    std::vector< std::shared_ptr<LoopStatement> > statements;

    /**
     * Run-block statements which will be executed upon the Run object if the conditional evaluates to false.
     */
    std::vector< std::shared_ptr<LoopStatement> > else_statements;

};

/**
 * Derived run statement which implements an action which removes the run from the set of runs to be executed. Note that
 * this statement accepts no arguments (e.g., other statements, options, or parameters).
 */
class StmtRemove : public LoopStatement {

public:
    /**
     * Constructor.
     */
    StmtRemove();

    /**
     * Executes the "remove" statement on the given Run object state. Simply marks the Run to be removed by the Engine
     * from the set of runs.
     * @param state The initial state to execute the "remove" statement upon.
     * @return The state marked as to be removed by the Engine.
     */
    Run execute( Run state );

};

/**
 * Derived run statement which implements the assignment of a run parameter to a new value.
 */
class StmtAssignment : public LoopStatement {

public:
    /**
     * Constructor. Accepts the identifier of the parameter whose value is to be updated, and the arithmetic expression
     * tree corresponding to the new value, which will be immediately evaluated in the context of the provided state.
     * @param identifier Identifier of the parameter whose value is to be updated.
     * @param value Expression tree corresponding to the new parameter value.
     */
    StmtAssignment( std::string identifier, std::shared_ptr<ArithmeticExpression> value );

    /**
     * Executes the assignment statement on the given Run object state, and returns the resulting modified Run object.
     * @param state The initial state to execute the assignment statement upon.
     * @return The resulting state of the assignment statement execution.
     */
    Run execute( Run state );

private:

    /**
     * Identifier of the parameter whose value is to be updated.
     */
    std::string identifier;

    /**
     * Arithmetic expression tree corresponding to the new value of the parameter matching the identifier.
     */
    std::shared_ptr<ArithmeticExpression> value;

};

/**
 * Derived run statement which implements a "run" loop. The statement block will be executed by the Engine upon each run
 * generated. Per the grammar, only one Run loop may exist in a given script.
 */
class RunLoop {

public:
    /**
     * Adds a statement to the run loop.
     * @param stmt The run loop statement tree to be added to the loop.
     */
    void add_statement( std::shared_ptr<LoopStatement> stmt );

    /**
     * Executes the loop block on the given Run object state, and returns the resulting modified Run object.
     * @param state The initial state to execute the loop block statements upon.
     * @return The resulting state of the loop block execution.
     */
    Run execute( Run state );

private:

    /**
     * Set of loop statements which will be executed upon each set of generated runs.
     */
    std::vector< std::shared_ptr<LoopStatement> > statements;

};

#endif //SCIMITAR7_LOOPSTATEMENT_H
