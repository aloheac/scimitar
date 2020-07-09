
// Generated from Scimitar.g4 by ANTLR 4.7.2

#pragma once


#include "antlr4-runtime.h"
#include "ScimitarVisitor.h"
#include "../engine/EngineAction.h"


/**
 * This class provides an empty implementation of ScimitarVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  ScimitarBaseVisitor : public ScimitarVisitor {
public:

  /* Root-level parser rules. */

  virtual antlrcpp::Any visitRoot(ScimitarParser::RootContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitEngineAction(ScimitarParser::EngineActionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRunBlock(ScimitarParser::RunBlockContext *ctx) override;

  virtual antlrcpp::Any visitUserFunctionDefinition(ScimitarParser::UserFunctionDefinitionContext *ctx) override;

  virtual antlrcpp::Any visitExprComment(ScimitarParser::ExprCommentContext *ctx) override {
    return visitChildren(ctx);
  }


  /* Action statement parser rules. */

  virtual antlrcpp::Any visitParam(ScimitarParser::ParamContext *ctx) override;

  virtual antlrcpp::Any visitFunction(ScimitarParser::FunctionContext *ctx) override;

  virtual antlrcpp::Any visitSetParam(ScimitarParser::SetParamContext *ctx) override;

  virtual antlrcpp::Any visitSetOption(ScimitarParser::SetOptionContext *ctx) override;

  virtual antlrcpp::Any visitSetFunction(ScimitarParser::SetFunctionContext *ctx) override;

  virtual antlrcpp::Any visitGroup(ScimitarParser::GroupContext *ctx) override;

  virtual antlrcpp::Any visitUngroup(ScimitarParser::UngroupContext *ctx) override;

  virtual antlrcpp::Any visitSystem(ScimitarParser::SystemContext *ctx) override;


  /* Parameter value parser rules. */

  virtual std::string visitParameterValueExpr(ScimitarParser::ParameterValueExprContext *ctx) override;

  virtual std::string visitParameterValueRange(ScimitarParser::ParameterValueRangeContext *ctx) override;

  virtual std::string visitParameterValueList(ScimitarParser::ParameterValueListContext *ctx) override;

  virtual std::string visitParameterValueString(ScimitarParser::ParameterValueStringContext *ctx) override;

  virtual std::string visitRange(ScimitarParser::RangeContext *ctx) override;

  virtual std::string visitList(ScimitarParser::ListContext *ctx) override;

  virtual std::string visitListElementExpr(ScimitarParser::ListElementExprContext *ctx) override;

  virtual std::string visitListElementRange(ScimitarParser::ListElementRangeContext *ctx) override;

  virtual std::string visitOptionValueExpr(ScimitarParser::OptionValueExprContext *ctx) override;

  virtual std::string visitOptionValueRange(ScimitarParser::OptionValueRangeContext *ctx) override;

  virtual std::string visitOptionValueList(ScimitarParser::OptionValueListContext *ctx) override;

  virtual std::string visitOptionValueFormat(ScimitarParser::OptionValueFormatContext *ctx) override;

  virtual std::string visitOptionValueString(ScimitarParser::OptionValueStringContext *ctx) override;

  virtual antlrcpp::Any visitStandardOption(ScimitarParser::StandardOptionContext *ctx) override;

  virtual antlrcpp::Any visitHideOption(ScimitarParser::HideOptionContext *ctx) override;

  virtual antlrcpp::Any visitScriptOption(ScimitarParser::ScriptOptionContext *ctx) override;

  virtual antlrcpp::Any visitSystemOption(ScimitarParser::SystemOptionContext *ctx) override;


  /* Mathematical expression parser rules. */

  virtual std::shared_ptr<ArithmeticExpression> visitParenthesis(ScimitarParser::ParenthesisContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitOpPow(ScimitarParser::OpPowContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitOpMul(ScimitarParser::OpMulContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitOpDiv(ScimitarParser::OpDivContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitOpAdd(ScimitarParser::OpAddContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitOpSub(ScimitarParser::OpSubContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitNegate(ScimitarParser::NegateContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitExprFunction(ScimitarParser::ExprFunctionContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitLiteral(ScimitarParser::LiteralContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitElement(ScimitarParser::ElementContext *ctx) override;

  virtual std::shared_ptr<ArithmeticExpression> visitIdentifier(ScimitarParser::IdentifierContext *ctx) override;


  /* Run loop and block parser rules. */

  virtual std::shared_ptr<RunLoop> visitRun(ScimitarParser::RunContext *ctx) override;

  virtual std::vector< std::shared_ptr<LoopStatement > > visitBlock(ScimitarParser::BlockContext *ctx) override;

  virtual std::shared_ptr<LoopStatement> visitIfStmt(ScimitarParser::IfStmtContext *ctx) override;

  virtual std::shared_ptr<LoopStatement> visitIfElseStmt(ScimitarParser::IfElseStmtContext *ctx) override;

  virtual std::shared_ptr<LoopStatement> visitRemoveStmt(ScimitarParser::RemoveStmtContext *ctx) override;

  virtual std::shared_ptr<LoopStatement> visitAssignmentStmt(ScimitarParser::AssignmentStmtContext *ctx) override;

  virtual antlrcpp::Any visitLoopComment(ScimitarParser::LoopCommentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::shared_ptr<ConditionalExpression> visitNegateOp(ScimitarParser::NegateOpContext *ctx) override;

  virtual std::shared_ptr<ConditionalExpression> visitRelation(ScimitarParser::RelationContext *ctx) override;

  virtual std::shared_ptr<ConditionalExpression> visitBooleanLiteral(ScimitarParser::BooleanLiteralContext *ctx) override;

  virtual std::shared_ptr<ConditionalExpression> visitBooleanOp(ScimitarParser::BooleanOpContext *ctx) override;

  virtual std::shared_ptr<ConditionalExpression> visitConditionParen(ScimitarParser::ConditionParenContext *ctx) override;

  virtual std::shared_ptr<ConditionalExpression> visitBooleanIdentifier(ScimitarParser::BooleanIdentifierContext *ctx) override;

  virtual antlrcpp::Any visitEnd(ScimitarParser::EndContext *ctx) override {
    return visitChildren(ctx);
  }


  /* User function definition and block parser rules. */

  virtual std::shared_ptr<UserFunction> visitUserFunction(ScimitarParser::UserFunctionContext *ctx) override;

  virtual FunctionArgumentSet visitUserFunctionArgList(ScimitarParser::UserFunctionArgListContext *ctx) override;

  virtual std::vector< std::shared_ptr<Expression> > visitUserFunctionPassedArgList(ScimitarParser::UserFunctionPassedArgListContext *ctx) override;

    virtual antlrcpp::Any visitUserFunctionArgument(ScimitarParser::UserFunctionArgumentContext *ctx) override {
        return visitChildren(ctx);
    }

    virtual std::vector< std::shared_ptr<FunctionStatement> > visitUserFunctionBlock(ScimitarParser::UserFunctionBlockContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionDeclaration(ScimitarParser::UserFunctionDeclarationContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionAssignment(ScimitarParser::UserFunctionAssignmentContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionListAppend(ScimitarParser::UserFunctionListAppendContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionListRemove(ScimitarParser::UserFunctionListRemoveContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionConditional(ScimitarParser::UserFunctionConditionalContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionReturn(ScimitarParser::UserFunctionReturnContext *ctx) override;

    virtual std::shared_ptr<Expression> visitGenericExpression(ScimitarParser::GenericExpressionContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionForLoop(ScimitarParser::UserFunctionForLoopContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionWhileLoop(ScimitarParser::UserFunctionWhileLoopContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionContinue(ScimitarParser::UserFunctionContinueContext *ctx) override;

    virtual std::shared_ptr<FunctionStatement> visitUserFunctionBreak(ScimitarParser::UserFunctionBreakContext *ctx) override;

  std::vector< std::shared_ptr<EngineAction> > get_result();

private:

    std::vector< std::shared_ptr<EngineAction> > actions;

};
