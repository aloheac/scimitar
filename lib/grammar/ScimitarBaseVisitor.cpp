
// Generated from Scimitar.g4 by ANTLR 4.7.2


#include "ScimitarBaseVisitor.h"
#include "../frontend/ParserFrontend.h"

antlrcpp::Any ScimitarBaseVisitor::visitStandardOption( ScimitarParser::StandardOptionContext* ctx ) {
    OptionPair opt;
    std::string value = visit( ctx->optionValue() );

    opt.option = ctx->OPT()->getText();
    opt.value = value;

    return opt;
}

antlrcpp::Any ScimitarBaseVisitor::visitHideOption(ScimitarParser::HideOptionContext *ctx) {
    OptionPair opt;
    opt.option = "hide";
    opt.value = "true";

    return opt;
}

antlrcpp::Any ScimitarBaseVisitor::visitRunBlock(ScimitarParser::RunBlockContext *ctx) {
    std::shared_ptr<RunLoop> run_loop = visit( ctx->run() );
    actions.emplace_back( new ActionSetRunBlock( run_loop ) );

    return 0;
}

std::string ScimitarBaseVisitor::visitParameterValueExpr(ScimitarParser::ParameterValueExprContext *ctx) {
    std::string expr = ctx->getText();
    double result = evaluate_expression_literal( expr );

    std::stringstream ss;
    ss << result;
    return ss.str();
}

std::string ScimitarBaseVisitor::visitParameterValueRange(ScimitarParser::ParameterValueRangeContext *ctx) {
    assert( ctx->children.size() == 1 );
    return visit( ctx->children.at( 0 ) );
}

std::string ScimitarBaseVisitor::visitParameterValueList(ScimitarParser::ParameterValueListContext *ctx) {
    assert( ctx->children.size() == 1 );
    return visit( ctx->children.at( 0 ) );
}

std::string ScimitarBaseVisitor::visitParameterValueString(ScimitarParser::ParameterValueStringContext *ctx) {
    return ctx->getText();
}

std::string ScimitarBaseVisitor::visitOptionValueExpr(ScimitarParser::OptionValueExprContext *ctx) {
    assert( ctx->children.size() == 1 );
    std::string expr = ctx->children.at( 0 )->getText();
    double result = evaluate_expression_literal( expr );

    std::stringstream ss;
    ss << result;
    return ss.str();
}

std::string ScimitarBaseVisitor::visitOptionValueRange(ScimitarParser::OptionValueRangeContext *ctx) {
    assert( ctx->children.size() == 1 );
    return visit( ctx->children.at( 0 ) );
}

std::string ScimitarBaseVisitor::visitOptionValueList(ScimitarParser::OptionValueListContext *ctx) {
    return ctx->getText();
}

std::string ScimitarBaseVisitor::visitOptionValueFormat(ScimitarParser::OptionValueFormatContext *ctx) {
    return ctx->getText();
}

std::string ScimitarBaseVisitor::visitOptionValueString(ScimitarParser::OptionValueStringContext *ctx) {
    return ctx->getText();
}

std::string ScimitarBaseVisitor::visitList(ScimitarParser::ListContext *ctx) {
    assert( ctx->listElement().size() > 0 );
    std::stringstream ss;
    ss << "[";

    // Iterate over child listElement instances, and append results.
    std::string result;
    std::string l;
    for ( int i = 0; i < ctx->listElement().size(); i++ ) {
        // Note the templated method antlrcpp::Any::as() casts the return of visit() to a std::string; all children of
        // listElement contexts explicitly return std::string objects.
        result = visit( ctx->listElement().at( i ) ).as<std::string>();
        ss << result;
        if ( i < ctx->listElement().size() - 1 ) {
            ss << ',';
        }
         l = ss.str();
    }

    ss << "]";
    return ss.str();
}

std::string ScimitarBaseVisitor::visitListElementExpr(ScimitarParser::ListElementExprContext *ctx) {
        std::string expr = ctx->expr()->getText();
        double result = evaluate_expression_literal( expr );

        std::stringstream ss;
        ss << result;
        return ss.str();
}

std::string ScimitarBaseVisitor::visitListElementRange(ScimitarParser::ListElementRangeContext *ctx) {
    return visit( ctx->range() );
}

std::string ScimitarBaseVisitor::visitRange(ScimitarParser::RangeContext *ctx) {
    assert( ctx->children.size() == 5 );
    std::string expr_lower, expr_step, expr_upper;
    double result_lower, result_step, result_upper;

    expr_lower = ctx->expr().at( 0 )->getText();
    expr_step = ctx->expr().at( 1 )->getText();
    expr_upper = ctx->expr().at( 2 )->getText();

    result_lower = evaluate_expression_literal( expr_lower );
    result_step = evaluate_expression_literal( expr_step );
    result_upper = evaluate_expression_literal( expr_upper );

    std::stringstream ss;
    ss << result_lower << ":" << result_step << ":" << result_upper;
    return ss.str();
}

antlrcpp::Any ScimitarBaseVisitor::visitParam(ScimitarParser::ParamContext *ctx) {
    // Gather tokens from parser.
    std::string type = ctx->TYPE()->getText();
    std::string identifier = ctx->IDENTIFIER()->getText();
    std::string value = visit( ctx->parameterValue() );

    // Iterate over option expressions.
    OptionSet options;
    OptionPair pair;
    std::string option, option_value;

    std::vector<ScimitarParser::OptionContext*> option_ctx = ctx->option();
    for ( auto iter = option_ctx.begin(); iter != option_ctx.end(); ++iter ) {
        pair = visit( *iter );
        options.add_option( OptionPair( pair ) );
    }

    actions.emplace_back( new ActionParam( type, identifier, value, options ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitFunction(ScimitarParser::FunctionContext *ctx) {
    // Gather identifiers from parser.
    std::string identifier = ctx->IDENTIFIER()->getText();
    std::shared_ptr<ArithmeticExpression> function = visit( ctx->expr() );

    // Iterate over option expressions.
    OptionSet options;
    OptionPair pair;
    std::string option, option_value;

    std::vector<ScimitarParser::OptionContext*> option_ctx = ctx->option();
    for ( auto iter = option_ctx.begin(); iter != option_ctx.end(); ++iter ) {
        pair = visit( *iter );
        options.add_option( OptionPair( pair ) );
    }

    actions.emplace_back( new ActionFunction( identifier, function, options ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitSetParam(ScimitarParser::SetParamContext *ctx) {
    // Gather tokens from parser.
    std::string identifier = ctx->IDENTIFIER()->getText();

    // Iterate over option expressions.
    OptionSet options;
    OptionPair pair;
    std::string option, option_value;

    std::vector<ScimitarParser::OptionContext*> option_ctx = ctx->option();
    for ( auto iter = option_ctx.begin(); iter != option_ctx.end(); ++iter ) {
        pair = visit( *iter );
        options.add_option( OptionPair( pair ) );
    }

    actions.emplace_back( new ActionSetParam( identifier, options ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitSetOption(ScimitarParser::SetOptionContext *ctx) {
    unsigned int count = ctx->scriptOption().size();
    assert( ctx->scriptOption().size() == ctx->STRING().size() );

    OptionSet options;
    for ( unsigned int i = 0; i < count; i++ ) {
        std::string option = ctx->scriptOption().at( i )->getText();
        // Strip quotes from string.
        std::string value = ctx->STRING().at( i )->getText();
        if ( value.at( 0 ) != '"' or value.at( value.length() - 1 ) != '"'  )
            throw EngineException( "Expected string to open and close with double quotes." );

        value = value.substr( 1, value.length() - 2 );
        options.add_option( OptionPair( option, value ) );
    }

    actions.emplace_back( new ActionSetOption( options ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitScriptOption(ScimitarParser::ScriptOptionContext *ctx) {
    return ctx->getText();
}

antlrcpp::Any ScimitarBaseVisitor::visitSetFunction(ScimitarParser::SetFunctionContext *ctx) {
    // Gather tokens from parser.
    std::string identifier = ctx->IDENTIFIER()->getText();

    // Get the new expression.
    assert( ctx->expr().size() > 0 );
    std::shared_ptr<ArithmeticExpression> expr = visit( ctx->expr().at( ctx->expr().size() - 1 ) );

    // Iterate over option expressions.
    OptionSet options;
    OptionPair pair;
    std::string option, option_value;

    std::vector<ScimitarParser::OptionContext*> option_ctx = ctx->option();
    for ( auto iter = option_ctx.begin(); iter != option_ctx.end(); ++iter ) {
        pair = visit( *iter );
        options.add_option( OptionPair( pair ) );
    }

    actions.emplace_back( new ActionSetFunction( identifier, expr, options ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitGroup(ScimitarParser::GroupContext *ctx) {
    // Gather identifiers from parser.
    std::vector<std::string> identifiers;
    std::vector<antlr4::tree::TerminalNode*> id_ctx = ctx->IDENTIFIER();

    for ( auto id : id_ctx ) {
        identifiers.push_back( id->getText() );
    }

    actions.emplace_back( new ActionGroup( identifiers ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitUngroup(ScimitarParser::UngroupContext *ctx) {
    // Gather identifiers from parser.
    std::vector<std::string> identifiers;
    std::vector<antlr4::tree::TerminalNode*> id_ctx = ctx->IDENTIFIER();

    for ( auto id : id_ctx ) {
        identifiers.push_back( id->getText() );
    }

    actions.emplace_back( new ActionUngroup( identifiers ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitSystem(ScimitarParser::SystemContext *ctx) {
    unsigned int count = ctx->systemOption().size();
    assert( ctx->systemOption().size() == ctx->IDENTIFIER().size() );

    OptionSet config;
    for ( unsigned int i = 0; i < count; i++ ) {
        std::string option = ctx->IDENTIFIER().at( i )->getText();
        std::string value  = ctx->systemOption().at( i )->getText();
        config.add_option( OptionPair( option, value ) );
    }

    actions.emplace_back( new ActionSystemConfig( config ) );

    return 0;
}

antlrcpp::Any ScimitarBaseVisitor::visitSystemOption(ScimitarParser::SystemOptionContext *ctx) {
    return ctx->getText();
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitParenthesis(ScimitarParser::ParenthesisContext *ctx) {
    return visit( ctx->expr() );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitOpSub(ScimitarParser::OpSubContext *ctx) {
    assert( ctx->expr().size() == 2 );
    return std::make_shared<ExprOperation>( OperationType::SUBTRACT, visit( ctx->expr().at( 0 ) ), visit( ctx->expr().at( 1 ) ) );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitIdentifier(ScimitarParser::IdentifierContext *ctx) {
    return std::make_shared<ExprVariable>( ctx->IDENTIFIER()->getText() );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitExprFunction(ScimitarParser::ExprFunctionContext *ctx) {
    std::string func = ctx->IDENTIFIER()->getText();

    std::vector< std::shared_ptr<Expression> > arguments;
    if ( ctx->userFunctionPassedArgList() != nullptr ) {
        std::vector< std::shared_ptr<Expression> > arg = visit( ctx->userFunctionPassedArgList() );
        arguments = arg;
    }


    if ( func == "sqrt" ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Incorrect number of arguments passed to 'sqrt'." );
        if ( arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
            throw ExpressionException( "Expected numerical argument to be passed to 'sqrt'." );

        return std::make_shared<ExprFunction>( FunctionType::SQRT, std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 0 ) ) );
    } else if ( func == "sin" ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Incorrect number of arguments passed to 'sin'." );
        if ( arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
            throw ExpressionException( "Expected numerical argument to be passed to 'sin'." );

        return std::make_shared<ExprFunction>( FunctionType::SIN, std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 0 ) ) );
    } else if ( func == "cos" ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Incorrect number of arguments passed to 'cos'." );
        if ( arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
            throw ExpressionException( "Expected numerical argument to be passed to 'cos'." );

        return std::make_shared<ExprFunction>( FunctionType::COS, std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 0 ) ) );
    } else if ( func == "tan" ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Incorrect number of arguments passed to 'tan'." );
        if ( arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
            throw ExpressionException( "Expected numerical argument to be passed to 'tan'." );

        return std::make_shared<ExprFunction>( FunctionType::TAN, std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 0 ) ) );
    } else if ( func == "log" ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Incorrect number of arguments passed to 'log'." );
        if ( arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
            throw ExpressionException( "Expected numerical argument to be passed to 'log'." );

        return std::make_shared<ExprFunction>( FunctionType::LOG, std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 0 ) ) );
    } else if ( func == "abs" ) {
        if ( arguments.size() != 1 ) throw ExpressionException( "Incorrect number of arguments passed to 'abs'." );
        if ( arguments.at( 0 )->get_type() != Expression::Type::ARITHMETIC )
            throw ExpressionException( "Expected numerical argument to be passed to 'abs'." );

        return std::make_shared<ExprFunction>( FunctionType::ABS, std::dynamic_pointer_cast<ArithmeticExpression>( arguments.at( 0 ) ) );
    } else if ( func == "rand" ) {
        if ( arguments.size() != 2 ) throw ExpressionException( "Incorrect number of arguments passed to 'rand'." );
        return std::make_shared<ExprFunction>( FunctionType::DISTRIBUTION_INTEGER, arguments );
    } else if ( func == "uniform" ) {
        if ( arguments.size() != 2 ) throw ExpressionException( "Incorrect number of arguments passed to 'uniform'." );
        return std::make_shared<ExprFunction>( FunctionType::DISTRIBUTION_UNIFORM, arguments );
    } else if ( func == "normal" ) {
        if ( arguments.size() != 2 ) throw ExpressionException( "Incorrect number of arguments passed to 'normal'." );
        return std::make_shared<ExprFunction>( FunctionType::DISTRIBUTION_NORMAL, arguments );
    } else if ( not func.empty() ) {  // A user function. Note an empty function name is not valid. A valid identifier should be checked by the parser.
        return std::make_shared<ExprFunction>( ctx->IDENTIFIER()->getText(), arguments );
    } else throw ExpressionException( "Unknown expression function." );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitLiteral(ScimitarParser::LiteralContext *ctx) {
    return std::make_shared<ExprConstant>( ctx->NUMERIC()->getText() );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitElement(ScimitarParser::ElementContext *ctx) {
    assert( ctx->expr().size() == 2 );
    std::shared_ptr<ArithmeticExpression> list = visit( ctx->expr().at( 0 ) );
    std::shared_ptr<ArithmeticExpression> index = visit( ctx->expr().at( 1 ) );

    return std::make_shared<ExprListElement>( list, index );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitOpPow( ScimitarParser::OpPowContext *ctx ) {
    assert( ctx->expr().size() == 2 );
    return std::make_shared<ExprOperation>( OperationType::POW, visit( ctx->expr().at( 0 ) ), visit( ctx->expr().at( 1 ) ) );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitNegate( ScimitarParser::NegateContext *ctx ) {
    return std::make_shared<ExprUnaryOperation>( OperationType::NEGATE, visit( ctx->expr() ) );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitOpAdd( ScimitarParser::OpAddContext *ctx ) {
    assert( ctx->expr().size() == 2 );
    return std::make_shared<ExprOperation>( OperationType::ADD, visit( ctx->expr().at( 0 ) ), visit( ctx->expr().at( 1 ) ) );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitOpDiv( ScimitarParser::OpDivContext *ctx ) {
    assert( ctx->expr().size() == 2 );
    return std::make_shared<ExprOperation>( OperationType::DIVIDE, visit( ctx->expr().at( 0 ) ), visit( ctx->expr().at( 1 ) ) );
}

std::shared_ptr<ArithmeticExpression> ScimitarBaseVisitor::visitOpMul( ScimitarParser::OpMulContext *ctx ) {
    assert( ctx->expr().size() == 2 );
    return std::make_shared<ExprOperation>( OperationType::MULTIPLY, visit( ctx->expr().at( 0 ) ), visit( ctx->expr().at( 1 ) ) );
}

std::shared_ptr<RunLoop> ScimitarBaseVisitor::visitRun(ScimitarParser::RunContext *ctx) {
    std::shared_ptr<RunLoop> loop( new RunLoop );

    for ( auto stmt : ctx->loopStmt() ) {
        loop->add_statement( visit( stmt ) );
    }

    return loop;
}

std::vector< std::shared_ptr<LoopStatement > > ScimitarBaseVisitor::visitBlock(ScimitarParser::BlockContext *ctx) {
    std::vector< std::shared_ptr<LoopStatement > > stmts;

    for ( auto stmt : ctx->loopStmt() ) {
        stmts.push_back( visit( stmt ) );
    }

    return stmts;
}

std::shared_ptr<LoopStatement> ScimitarBaseVisitor::visitIfStmt(ScimitarParser::IfStmtContext *ctx) {
    std::shared_ptr<ConditionalExpression> condition = visit( ctx->condition() );
    std::shared_ptr<StmtIf> if_stmt( new StmtIf( condition ) );

    for ( auto stmt : ctx->loopStmt() ) {
        if_stmt->add_statement( visit( stmt ) );
    }

    return if_stmt;
}

std::shared_ptr<LoopStatement> ScimitarBaseVisitor::visitIfElseStmt( ScimitarParser::IfElseStmtContext *ctx ) {
    assert( ctx->block().size() == 2 );
    std::shared_ptr<ConditionalExpression> condition = visit( ctx->condition() );
    std::shared_ptr<StmtIfElse> if_stmt( new StmtIfElse( condition ) );

    std::vector< std::shared_ptr<LoopStatement > > if_block = visit( ctx->block().at( 0 ) );
    std::vector< std::shared_ptr<LoopStatement > > if_else_block = visit( ctx->block().at( 1 ) );

    for ( auto stmt : if_block ) {
        if_stmt->add_statement( stmt );
    }

    for ( auto stmt : if_else_block ) {
        if_stmt->add_else_statement( stmt );
    }

    return if_stmt;
}

std::shared_ptr<LoopStatement> ScimitarBaseVisitor::visitRemoveStmt(ScimitarParser::RemoveStmtContext *ctx) {
    return std::make_shared<StmtRemove>();
}

std::shared_ptr<LoopStatement> ScimitarBaseVisitor::visitAssignmentStmt(ScimitarParser::AssignmentStmtContext *ctx) {
    std::string identifier = ctx->IDENTIFIER()->getText();
    std::shared_ptr<ArithmeticExpression> expr = visit( ctx->expr() );

    return std::make_shared<StmtAssignment>( identifier, expr );
}

std::shared_ptr<ConditionalExpression> ScimitarBaseVisitor::visitNegateOp(ScimitarParser::NegateOpContext *ctx) {
    return std::make_shared<UnaryBooleanOperation>( ConditionalExpression::BooleanOperationType::NEGATE, visit( ctx->condition() ) );
}

std::shared_ptr<ConditionalExpression> ScimitarBaseVisitor::visitRelation(ScimitarParser::RelationContext *ctx) {
    assert( ctx->expr().size() == 2 );
    std::string op = ctx->REL_OP()->getText();
    std::shared_ptr<ArithmeticExpression> lhs = visit( ctx->expr().at( 0 ) );
    std::shared_ptr<ArithmeticExpression> rhs = visit( ctx->expr().at( 1 ) );

    if ( op == "<" ) {
        return std::make_shared<ComparisonOperation>( ComparisonOperation::ComparisonOperationType::LESS_THAN, lhs, rhs );
    } else if ( op == ">") {
        return std::make_shared<ComparisonOperation>( ComparisonOperation::ComparisonOperationType::GREATER_THAN, lhs, rhs );
    } else if ( op == "==" ) {
        return std::make_shared<ComparisonOperation>( ComparisonOperation::ComparisonOperationType::EQUALITY, lhs, rhs );
    } else if ( op == "!=" ) {
        return std::make_shared<ComparisonOperation>( ComparisonOperation::ComparisonOperationType::NOT_EQUAL, lhs, rhs );
    } else if ( op == "<=" ) {
        return std::make_shared<ComparisonOperation>( ComparisonOperation::ComparisonOperationType::LESS_THAN_OR_EQUAL, lhs, rhs );
    } else if ( op == ">=" ) {
        return std::make_shared<ComparisonOperation>( ComparisonOperation::ComparisonOperationType::GREATER_THAN_OR_EQUAL, lhs, rhs );
    } else throw ExpressionException( "Unknown relation function." );
}

std::shared_ptr<ConditionalExpression> ScimitarBaseVisitor::visitBooleanLiteral(ScimitarParser::BooleanLiteralContext *ctx) {
    std::string literal = ctx->BOOL_LITERAL()->getText();

    if ( literal == "true" ) {
        return std::make_shared<BooleanLiteral>( true );
    } else if ( literal == "false" ) {
        return std::make_shared<BooleanLiteral>( false );
    } else throw ExpressionException( "Unknown boolean literal." );
}

std::shared_ptr<ConditionalExpression> ScimitarBaseVisitor::visitBooleanOp(ScimitarParser::BooleanOpContext *ctx) {
    assert( ctx->condition().size() == 2 );
    std::string op = ctx->BOOL_OP()->getText();
    std::shared_ptr<ConditionalExpression> lhs = visit( ctx->condition().at( 0 ) );
    std::shared_ptr<ConditionalExpression> rhs = visit( ctx->condition().at( 1 ) );

    if ( op == "and" ) {
        return std::make_shared<BooleanOperation>( BooleanOperation::BooleanOperationType::AND, lhs, rhs );
    } else if ( op == "or" ) {
        return std::make_shared<BooleanOperation>(BooleanOperation::BooleanOperationType::OR, lhs, rhs);
    } else if ( op == "eq" ) {
        return std::make_shared<BooleanOperation>( BooleanOperation::BooleanOperationType::EQUALITY, lhs, rhs );
    } else throw ExpressionException( "Unknown boolean operation." );
}

std::shared_ptr<ConditionalExpression> ScimitarBaseVisitor::visitConditionParen(ScimitarParser::ConditionParenContext *ctx) {
    return visit( ctx->condition() );
}

std::shared_ptr<ConditionalExpression> ScimitarBaseVisitor::visitBooleanIdentifier(ScimitarParser::BooleanIdentifierContext *ctx) {
    return std::make_shared<BooleanVariable>( ctx->IDENTIFIER()->getText() );
}

antlrcpp::Any ScimitarBaseVisitor::visitUserFunctionDefinition(ScimitarParser::UserFunctionDefinitionContext *ctx) {
    std::shared_ptr<UserFunction> function = visit( ctx->userFunction() );
    actions.emplace_back( new ActionUserFunction( function ) );

    return 0;
}

std::shared_ptr<UserFunction> ScimitarBaseVisitor::visitUserFunction(ScimitarParser::UserFunctionContext *ctx) {
    std::string identifier = ctx->IDENTIFIER()->toString();
    std::shared_ptr<UserFunction> function = std::make_shared<UserFunction>( identifier );

    // Obtain all function signature arguments and add them to the function object.
    if ( ctx->userFunctionArgList() != nullptr ) {
        FunctionArgumentSet arguments = visit( ctx->userFunctionArgList() );
        for ( long  i = 0; i < arguments.length(); i++ ) {
            function->add_argument( arguments.at( i ).type, arguments.at( i ).identifier );
        }
    }

    for ( auto stmt : ctx->userFunctionStmt() ) {
        std::shared_ptr<FunctionStatement> function_stmt = visit( stmt );
        function->add_statement( function_stmt );
    }

    return function;
}

FunctionArgumentSet ScimitarBaseVisitor::visitUserFunctionArgList(ScimitarParser::UserFunctionArgListContext *ctx) {
    FunctionArgumentSet arguments;
    std::string type, identifier;
    Symbol::Type symbol_type;
    for ( auto arg : ctx->userFunctionArgument() ) {
        type = arg->TYPE()->toString();
        identifier = arg->IDENTIFIER()->toString();

        if ( type == "real" ) {
            symbol_type = Symbol::Type::REAL;
        } else if ( type == "int" ) {
            symbol_type = Symbol::Type::INT;
        } else if ( type == "bool" ) {
            symbol_type = Symbol::Type::BOOL;
        } else throw EngineException( "Unknown function symbol type." );

        arguments.add_argument( symbol_type, identifier );
    }

    return arguments;
}

std::vector< std::shared_ptr<Expression> > ScimitarBaseVisitor::visitUserFunctionPassedArgList(ScimitarParser::UserFunctionPassedArgListContext *ctx) {
    std::vector< std::shared_ptr<Expression> > arguments;

    for ( auto arg_expr : ctx->genericExpression() ) {
        arguments.push_back( visit( arg_expr ) );
    }

    return arguments;
}

std::vector< std::shared_ptr<FunctionStatement> > ScimitarBaseVisitor::visitUserFunctionBlock(ScimitarParser::UserFunctionBlockContext *ctx) {
    std::vector< std::shared_ptr<FunctionStatement> > stmts;

    for ( auto stmt : ctx->userFunctionStmt() ) {
        stmts.push_back( visit( stmt ) );
    }

    return stmts;
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionDeclaration(ScimitarParser::UserFunctionDeclarationContext *ctx) {
    Symbol::Type type;
    std::string str_type = ctx->TYPE()->getText();
    if ( str_type == "real" ) {
        type = Symbol::Type::REAL;
    } else if ( str_type == "int" ) {
        type = Symbol::Type::INT;
    } else if ( str_type == "bool" ) {
        type = Symbol::Type::BOOL;
    } else if ( str_type == "list" ) {
        type = Symbol::Type::LIST;
    } else throw EngineException( "Invalid type in user function variable declaration." );

    if ( ctx->genericExpression() != nullptr ) {
        std::shared_ptr<Expression> value = visit( ctx->genericExpression() );
        return std::make_shared<FuncStmtDeclaration>( type, ctx->IDENTIFIER()->getText(), value );
    }

    return std::make_shared<FuncStmtDeclaration>( type, ctx->IDENTIFIER()->getText() );
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionAssignment(ScimitarParser::UserFunctionAssignmentContext *ctx) {
    std::shared_ptr<Expression> expr = visit( ctx->genericExpression() );
    return std::make_shared<FuncStmtAssignment>( ctx->IDENTIFIER()->getText(), expr );
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionListAppend(ScimitarParser::UserFunctionListAppendContext *ctx) {
    std::string list_identifier = ctx->IDENTIFIER()->getText();
    std::string str_list_type = ctx->TYPE()->getText();

    Symbol::Type list_type;
    if ( str_list_type == "int" ) {
        list_type = Symbol::Type::INT;
    } else if ( str_list_type == "real" ) {
        list_type = Symbol::Type::REAL;
    } else if ( str_list_type == "list" ) {
        list_type = Symbol::Type::LIST;
    } else throw EngineException( "Invalid list element type." );

    std::shared_ptr<Expression> element = visit( ctx->genericExpression() );

    return std::make_shared<FuncStmtListAppend>( list_identifier, list_type, element );
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionListRemove(ScimitarParser::UserFunctionListRemoveContext *ctx) {
    std::string list_identifier = ctx->IDENTIFIER()->getText();
    std::shared_ptr<ArithmeticExpression> index = visit( ctx->expr() );

    return std::make_shared<FuncStmtListRemove>( list_identifier, index );
}

std::shared_ptr<Expression> ScimitarBaseVisitor::visitGenericExpression(ScimitarParser::GenericExpressionContext *ctx) {
    std::shared_ptr<Expression> child_expr;

    if ( ctx->expr() != nullptr ) {
        std::shared_ptr<ArithmeticExpression> arithmetic_expr = visit( ctx->expr() );
        child_expr = arithmetic_expr;
    } else {
        std::shared_ptr<ConditionalExpression> conditional_expr = visit( ctx->condition() );
        child_expr = conditional_expr;
    }

    return child_expr;
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionConditional(ScimitarParser::UserFunctionConditionalContext *ctx) {
    assert( ctx->userFunctionBlock().size() == 1 or ctx->userFunctionBlock().size() == 2 );
    std::shared_ptr<ConditionalExpression> condition = visit( ctx->condition() );
    std::shared_ptr<FuncStmtConditional> conditional_block = std::make_shared<FuncStmtConditional>( condition );

    std::vector< std::shared_ptr<FunctionStatement> > statements = visit( ctx->userFunctionBlock().at( 0 ) );
    for ( auto stmt : statements ) {
        conditional_block->add_statement( stmt );
    }

    if ( ctx->userFunctionBlock().size() == 2 ) {  // If true, an if-else block exists.
        std::vector< std::shared_ptr<FunctionStatement> > else_statements = visit( ctx->userFunctionBlock().at( 1 ) );
        for ( auto stmt : else_statements ) {
            conditional_block->add_else_statement( stmt );
        }
    }

    return conditional_block;
}

std::vector< std::shared_ptr<EngineAction> > ScimitarBaseVisitor::get_result() {
    return actions;
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionReturn(ScimitarParser::UserFunctionReturnContext *ctx) {
    std::shared_ptr<ArithmeticExpression> ret_expr = visit( ctx->expr() );
    return std::make_shared<FuncStmtReturn>( ret_expr );
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionForLoop(ScimitarParser::UserFunctionForLoopContext *ctx) {
    assert( ctx->expr().size() == 2 );
    std::string str_type = ctx->TYPE()->getText();
    std::string loop_identifier = ctx->IDENTIFIER()->getText();
    std::shared_ptr<ArithmeticExpression> initial_value = visit( ctx->expr().at( 0 ) );
    std::shared_ptr<ConditionalExpression> conditional = visit( ctx->condition() );
    std::shared_ptr<ArithmeticExpression> step = visit( ctx->expr().at( 1 ) );

    Symbol::Type type;
    if ( str_type == "int" ) {
        type = Symbol::Type::INT;
    } else if ( str_type == "real" ) {
        type = Symbol::Type::REAL;
    } else throw EngineException( "Invalid loop counter variable type." );

    std::shared_ptr<FuncStmtForLoop> loop_stmt = std::make_shared<FuncStmtForLoop>( type, loop_identifier, initial_value, conditional, step );

    std::vector< std::shared_ptr<FunctionStatement> > statements = visit( ctx->userFunctionBlock() );
    for ( auto statement : statements ) {
        loop_stmt->add_statement( statement );
    }

    return loop_stmt;
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionWhileLoop(ScimitarParser::UserFunctionWhileLoopContext *ctx) {
    std::shared_ptr<ConditionalExpression> conditional = visit( ctx->condition() );

    std::shared_ptr<FuncStmtWhileLoop> loop_stmt = std::make_shared<FuncStmtWhileLoop>( conditional );

    std::vector< std::shared_ptr<FunctionStatement> > statements = visit( ctx->userFunctionBlock() );
    for ( auto statement : statements ) {
        loop_stmt->add_statement( statement );
    }

    return loop_stmt;
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionContinue(ScimitarParser::UserFunctionContinueContext *ctx) {
    return std::make_shared<FuncStmtContinue>();
}

std::shared_ptr<FunctionStatement> ScimitarBaseVisitor::visitUserFunctionBreak(ScimitarParser::UserFunctionBreakContext *ctx) {
    return std::make_shared<FuncStmtBreak>();
}
