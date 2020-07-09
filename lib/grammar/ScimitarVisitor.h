
// Generated from Scimitar.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "ScimitarParser.h"
#include "../language/ArithmeticExpression.h"
#include "../language/LoopStatement.h"


/**
 * This class defines an abstract visitor for a parse tree
 * produced by ScimitarParser.
 */
class  ScimitarVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by ScimitarParser.
   */

    /* Root-level parser rules. */

    virtual antlrcpp::Any visitRoot(ScimitarParser::RootContext *context) = 0;

    virtual antlrcpp::Any visitEngineAction(ScimitarParser::EngineActionContext *context) = 0;

    virtual antlrcpp::Any visitRunBlock(ScimitarParser::RunBlockContext *context) = 0;

    virtual antlrcpp::Any visitExprComment(ScimitarParser::ExprCommentContext *context) = 0;

    virtual antlrcpp::Any visitUserFunctionDefinition(ScimitarParser::UserFunctionDefinitionContext *context) = 0;


    /* Action statement parser rules. */

    virtual antlrcpp::Any visitParam(ScimitarParser::ParamContext *context) = 0;

    virtual antlrcpp::Any visitFunction(ScimitarParser::FunctionContext *context) = 0;

    virtual antlrcpp::Any visitSetParam(ScimitarParser::SetParamContext *context) = 0;

    virtual antlrcpp::Any visitSetOption(ScimitarParser::SetOptionContext *context) = 0;

    virtual antlrcpp::Any visitSetFunction(ScimitarParser::SetFunctionContext *context) = 0;

    virtual antlrcpp::Any visitGroup(ScimitarParser::GroupContext *context) = 0;

    virtual antlrcpp::Any visitUngroup(ScimitarParser::UngroupContext *context) = 0;

    virtual antlrcpp::Any visitSystem(ScimitarParser::SystemContext *context) = 0;


    /* Parameter value parser rules. */

    virtual std::string visitParameterValueExpr(ScimitarParser::ParameterValueExprContext *context) = 0;

    virtual std::string visitParameterValueRange(ScimitarParser::ParameterValueRangeContext *context) = 0;

    virtual std::string visitParameterValueList(ScimitarParser::ParameterValueListContext *context) = 0;

    virtual std::string visitParameterValueString(ScimitarParser::ParameterValueStringContext *context) = 0;

    virtual std::string visitRange(ScimitarParser::RangeContext *context) = 0;

    virtual std::string visitList(ScimitarParser::ListContext *context) = 0;

    virtual std::string visitListElementExpr(ScimitarParser::ListElementExprContext *context) = 0;

    virtual std::string visitListElementRange(ScimitarParser::ListElementRangeContext *context) = 0;

    virtual std::string visitOptionValueExpr(ScimitarParser::OptionValueExprContext *context) = 0;

    virtual std::string visitOptionValueRange(ScimitarParser::OptionValueRangeContext *context) = 0;

    virtual std::string visitOptionValueList(ScimitarParser::OptionValueListContext *context) = 0;

    virtual std::string visitOptionValueFormat(ScimitarParser::OptionValueFormatContext *context) = 0;

    virtual std::string visitOptionValueString(ScimitarParser::OptionValueStringContext *context) = 0;

    virtual antlrcpp::Any visitStandardOption(ScimitarParser::StandardOptionContext *context) = 0;

    virtual antlrcpp::Any visitHideOption(ScimitarParser::HideOptionContext *context) = 0;

    virtual antlrcpp::Any visitScriptOption(ScimitarParser::ScriptOptionContext *context) = 0;

    virtual antlrcpp::Any visitSystemOption(ScimitarParser::SystemOptionContext *context) = 0;


    /* Mathematical expression parser rules. */

    virtual std::shared_ptr<ArithmeticExpression> visitParenthesis(ScimitarParser::ParenthesisContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitOpPow(ScimitarParser::OpPowContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitOpMul(ScimitarParser::OpMulContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitOpDiv(ScimitarParser::OpDivContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitOpAdd(ScimitarParser::OpAddContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitOpSub(ScimitarParser::OpSubContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitNegate(ScimitarParser::NegateContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitExprFunction(ScimitarParser::ExprFunctionContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitLiteral(ScimitarParser::LiteralContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitElement(ScimitarParser::ElementContext *context) = 0;

    virtual std::shared_ptr<ArithmeticExpression> visitIdentifier(ScimitarParser::IdentifierContext *context) = 0;


    /* Run loop and block parser rules. */

    virtual std::shared_ptr<RunLoop> visitRun(ScimitarParser::RunContext *context) = 0;

    virtual std::vector< std::shared_ptr<LoopStatement > > visitBlock(ScimitarParser::BlockContext *context) = 0;

    virtual std::shared_ptr<LoopStatement> visitIfStmt(ScimitarParser::IfStmtContext *context) = 0;

    virtual std::shared_ptr<LoopStatement> visitIfElseStmt(ScimitarParser::IfElseStmtContext *context) = 0;

    virtual std::shared_ptr<LoopStatement> visitRemoveStmt(ScimitarParser::RemoveStmtContext *context) = 0;

    virtual std::shared_ptr<LoopStatement> visitAssignmentStmt(ScimitarParser::AssignmentStmtContext *context) = 0;

    virtual antlrcpp::Any visitLoopComment(ScimitarParser::LoopCommentContext *context) = 0;

    virtual std::shared_ptr<ConditionalExpression> visitNegateOp(ScimitarParser::NegateOpContext *context) = 0;

    virtual std::shared_ptr<ConditionalExpression> visitRelation(ScimitarParser::RelationContext *context) = 0;

    virtual std::shared_ptr<ConditionalExpression> visitBooleanLiteral(ScimitarParser::BooleanLiteralContext *context) = 0;

    virtual std::shared_ptr<ConditionalExpression> visitBooleanOp(ScimitarParser::BooleanOpContext *context) = 0;

    virtual std::shared_ptr<ConditionalExpression> visitConditionParen(ScimitarParser::ConditionParenContext *context) = 0;

    virtual std::shared_ptr<ConditionalExpression> visitBooleanIdentifier(ScimitarParser::BooleanIdentifierContext *context) = 0;

    virtual antlrcpp::Any visitEnd(ScimitarParser::EndContext *context) = 0;


    /* User function definition and block parser rules. */

    virtual std::shared_ptr<UserFunction> visitUserFunction(ScimitarParser::UserFunctionContext *context) = 0;

    virtual FunctionArgumentSet visitUserFunctionArgList(ScimitarParser::UserFunctionArgListContext *context) = 0;

    virtual std::vector< std::shared_ptr<Expression> > visitUserFunctionPassedArgList(ScimitarParser::UserFunctionPassedArgListContext *context) = 0;

    virtual antlrcpp::Any visitUserFunctionArgument(ScimitarParser::UserFunctionArgumentContext *context) = 0;

    virtual std::vector< std::shared_ptr<FunctionStatement> > visitUserFunctionBlock(ScimitarParser::UserFunctionBlockContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionDeclaration(ScimitarParser::UserFunctionDeclarationContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionAssignment(ScimitarParser::UserFunctionAssignmentContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionListAppend(ScimitarParser::UserFunctionListAppendContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionListRemove(ScimitarParser::UserFunctionListRemoveContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionConditional(ScimitarParser::UserFunctionConditionalContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionReturn(ScimitarParser::UserFunctionReturnContext *context) = 0;

    virtual std::shared_ptr<Expression> visitGenericExpression(ScimitarParser::GenericExpressionContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionForLoop(ScimitarParser::UserFunctionForLoopContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionWhileLoop(ScimitarParser::UserFunctionWhileLoopContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionContinue(ScimitarParser::UserFunctionContinueContext *context) = 0;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionBreak(ScimitarParser::UserFunctionBreakContext *context) = 0;

};
