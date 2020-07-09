
// Generated from Scimitar.g4 by ANTLR 4.8; unmodified.

#pragma once


#include "antlr4-runtime.h"




class  ScimitarParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    NEWLINE = 15, OPT = 16, OPTION = 17, END = 18, PARAM = 19, SET = 20, 
    GROUP = 21, UNGROUP = 22, RUN = 23, RETURN = 24, TYPE = 25, IF = 26, 
    FOR = 27, WHILE = 28, CONTINUE = 29, BREAK = 30, ELSE = 31, SYSTEM = 32, 
    REL_OP = 33, BOOL_OP = 34, NEG_OP = 35, REMOVE = 36, BOOL_LITERAL = 37, 
    ADD = 38, SUB = 39, MUL = 40, DIV = 41, POW = 42, NUMERIC = 43, FORMAT = 44, 
    IDENTIFIER = 45, STRING = 46, COMMENT = 47, BLOCK_COMMENT = 48, WHITESPACE = 49
  };

  enum {
    RuleRoot = 0, RuleAction = 1, RuleParam = 2, RuleFunction = 3, RuleSetParam = 4, 
    RuleSetOption = 5, RuleSetFunction = 6, RuleGroup = 7, RuleUngroup = 8, 
    RuleSystem = 9, RuleParameterValue = 10, RuleRange = 11, RuleList = 12, 
    RuleListElement = 13, RuleOption = 14, RuleOptionValue = 15, RuleScriptOption = 16, 
    RuleSystemOption = 17, RuleExpr = 18, RuleRun = 19, RuleBlock = 20, 
    RuleLoopStmt = 21, RuleCondition = 22, RuleEnd = 23, RuleUserFunction = 24, 
    RuleUserFunctionArgList = 25, RuleUserFunctionPassedArgList = 26, RuleUserFunctionArgument = 27, 
    RuleUserFunctionBlock = 28, RuleGenericExpression = 29, RuleUserFunctionStmt = 30
  };

  ScimitarParser(antlr4::TokenStream *input);
  ~ScimitarParser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class RootContext;
  class ActionContext;
  class ParamContext;
  class FunctionContext;
  class SetParamContext;
  class SetOptionContext;
  class SetFunctionContext;
  class GroupContext;
  class UngroupContext;
  class SystemContext;
  class ParameterValueContext;
  class RangeContext;
  class ListContext;
  class ListElementContext;
  class OptionContext;
  class OptionValueContext;
  class ScriptOptionContext;
  class SystemOptionContext;
  class ExprContext;
  class RunContext;
  class BlockContext;
  class LoopStmtContext;
  class ConditionContext;
  class EndContext;
  class UserFunctionContext;
  class UserFunctionArgListContext;
  class UserFunctionPassedArgListContext;
  class UserFunctionArgumentContext;
  class UserFunctionBlockContext;
  class GenericExpressionContext;
  class UserFunctionStmtContext; 

  class  RootContext : public antlr4::ParserRuleContext {
  public:
    RootContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ActionContext *> action();
    ActionContext* action(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RootContext* root();

  class  ActionContext : public antlr4::ParserRuleContext {
  public:
    ActionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ActionContext() = default;
    void copyFrom(ActionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  RunBlockContext : public ActionContext {
  public:
    RunBlockContext(ActionContext *ctx);

    RunContext *run();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionDefinitionContext : public ActionContext {
  public:
    UserFunctionDefinitionContext(ActionContext *ctx);

    UserFunctionContext *userFunction();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  EngineActionContext : public ActionContext {
  public:
    EngineActionContext(ActionContext *ctx);

    antlr4::tree::TerminalNode *NEWLINE();
    ParamContext *param();
    FunctionContext *function();
    SetParamContext *setParam();
    SetOptionContext *setOption();
    SetFunctionContext *setFunction();
    GroupContext *group();
    UngroupContext *ungroup();
    EndContext *end();
    SystemContext *system();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprCommentContext : public ActionContext {
  public:
    ExprCommentContext(ActionContext *ctx);

    antlr4::tree::TerminalNode *COMMENT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ActionContext* action();

  class  ParamContext : public antlr4::ParserRuleContext {
  public:
    ParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PARAM();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ParameterValueContext *parameterValue();
    std::vector<OptionContext *> option();
    OptionContext* option(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParamContext* param();

  class  FunctionContext : public antlr4::ParserRuleContext {
  public:
    FunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PARAM();
    antlr4::tree::TerminalNode *IDENTIFIER();
    ExprContext *expr();
    std::vector<OptionContext *> option();
    OptionContext* option(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionContext* function();

  class  SetParamContext : public antlr4::ParserRuleContext {
  public:
    SetParamContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *PARAM();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<OptionContext *> option();
    OptionContext* option(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetParamContext* setParam();

  class  SetOptionContext : public antlr4::ParserRuleContext {
  public:
    SetOptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *OPTION();
    std::vector<ScriptOptionContext *> scriptOption();
    ScriptOptionContext* scriptOption(size_t i);
    std::vector<antlr4::tree::TerminalNode *> STRING();
    antlr4::tree::TerminalNode* STRING(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetOptionContext* setOption();

  class  SetFunctionContext : public antlr4::ParserRuleContext {
  public:
    SetFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET();
    antlr4::tree::TerminalNode *PARAM();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    std::vector<OptionContext *> option();
    OptionContext* option(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetFunctionContext* setFunction();

  class  GroupContext : public antlr4::ParserRuleContext {
  public:
    GroupContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GROUP();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GroupContext* group();

  class  UngroupContext : public antlr4::ParserRuleContext {
  public:
    UngroupContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *UNGROUP();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UngroupContext* ungroup();

  class  SystemContext : public antlr4::ParserRuleContext {
  public:
    SystemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SYSTEM();
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);
    std::vector<SystemOptionContext *> systemOption();
    SystemOptionContext* systemOption(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SystemContext* system();

  class  ParameterValueContext : public antlr4::ParserRuleContext {
  public:
    ParameterValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ParameterValueContext() = default;
    void copyFrom(ParameterValueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ParameterValueRangeContext : public ParameterValueContext {
  public:
    ParameterValueRangeContext(ParameterValueContext *ctx);

    RangeContext *range();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParameterValueListContext : public ParameterValueContext {
  public:
    ParameterValueListContext(ParameterValueContext *ctx);

    ListContext *list();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParameterValueStringContext : public ParameterValueContext {
  public:
    ParameterValueStringContext(ParameterValueContext *ctx);

    antlr4::tree::TerminalNode *STRING();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParameterValueExprContext : public ParameterValueContext {
  public:
    ParameterValueExprContext(ParameterValueContext *ctx);

    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ParameterValueContext* parameterValue();

  class  RangeContext : public antlr4::ParserRuleContext {
  public:
    RangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RangeContext* range();

  class  ListContext : public antlr4::ParserRuleContext {
  public:
    ListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ListElementContext *> listElement();
    ListElementContext* listElement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListContext* list();

  class  ListElementContext : public antlr4::ParserRuleContext {
  public:
    ListElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ListElementContext() = default;
    void copyFrom(ListElementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ListElementRangeContext : public ListElementContext {
  public:
    ListElementRangeContext(ListElementContext *ctx);

    RangeContext *range();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ListElementExprContext : public ListElementContext {
  public:
    ListElementExprContext(ListElementContext *ctx);

    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ListElementContext* listElement();

  class  OptionContext : public antlr4::ParserRuleContext {
  public:
    OptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    OptionContext() = default;
    void copyFrom(OptionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  HideOptionContext : public OptionContext {
  public:
    HideOptionContext(OptionContext *ctx);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StandardOptionContext : public OptionContext {
  public:
    StandardOptionContext(OptionContext *ctx);

    antlr4::tree::TerminalNode *OPT();
    OptionValueContext *optionValue();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  OptionContext* option();

  class  OptionValueContext : public antlr4::ParserRuleContext {
  public:
    OptionValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    OptionValueContext() = default;
    void copyFrom(OptionValueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  OptionValueRangeContext : public OptionValueContext {
  public:
    OptionValueRangeContext(OptionValueContext *ctx);

    RangeContext *range();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OptionValueListContext : public OptionValueContext {
  public:
    OptionValueListContext(OptionValueContext *ctx);

    ListContext *list();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OptionValueExprContext : public OptionValueContext {
  public:
    OptionValueExprContext(OptionValueContext *ctx);

    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OptionValueStringContext : public OptionValueContext {
  public:
    OptionValueStringContext(OptionValueContext *ctx);

    antlr4::tree::TerminalNode *STRING();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OptionValueFormatContext : public OptionValueContext {
  public:
    OptionValueFormatContext(OptionValueContext *ctx);

    antlr4::tree::TerminalNode *FORMAT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  OptionValueContext* optionValue();

  class  ScriptOptionContext : public antlr4::ParserRuleContext {
  public:
    ScriptOptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> IDENTIFIER();
    antlr4::tree::TerminalNode* IDENTIFIER(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScriptOptionContext* scriptOption();

  class  SystemOptionContext : public antlr4::ParserRuleContext {
  public:
    SystemOptionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *NUMERIC();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SystemOptionContext* systemOption();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ParenthesisContext : public ExprContext {
  public:
    ParenthesisContext(ExprContext *ctx);

    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OpSubContext : public ExprContext {
  public:
    OpSubContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *SUB();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdentifierContext : public ExprContext {
  public:
    IdentifierContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprFunctionContext : public ExprContext {
  public:
    ExprFunctionContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    UserFunctionPassedArgListContext *userFunctionPassedArgList();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LiteralContext : public ExprContext {
  public:
    LiteralContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *NUMERIC();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ElementContext : public ExprContext {
  public:
    ElementContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OpPowContext : public ExprContext {
  public:
    OpPowContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *POW();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NegateContext : public ExprContext {
  public:
    NegateContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *SUB();
    ExprContext *expr();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OpDivContext : public ExprContext {
  public:
    OpDivContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *DIV();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OpAddContext : public ExprContext {
  public:
    OpAddContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *ADD();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OpMulContext : public ExprContext {
  public:
    OpMulContext(ExprContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *MUL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  RunContext : public antlr4::ParserRuleContext {
  public:
    RunContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RUN();
    std::vector<LoopStmtContext *> loopStmt();
    LoopStmtContext* loopStmt(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RunContext* run();

  class  BlockContext : public antlr4::ParserRuleContext {
  public:
    BlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LoopStmtContext *> loopStmt();
    LoopStmtContext* loopStmt(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockContext* block();

  class  LoopStmtContext : public antlr4::ParserRuleContext {
  public:
    LoopStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    LoopStmtContext() = default;
    void copyFrom(LoopStmtContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  RemoveStmtContext : public LoopStmtContext {
  public:
    RemoveStmtContext(LoopStmtContext *ctx);

    antlr4::tree::TerminalNode *REMOVE();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LoopCommentContext : public LoopStmtContext {
  public:
    LoopCommentContext(LoopStmtContext *ctx);

    antlr4::tree::TerminalNode *COMMENT();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfStmtContext : public LoopStmtContext {
  public:
    IfStmtContext(LoopStmtContext *ctx);

    antlr4::tree::TerminalNode *IF();
    ConditionContext *condition();
    std::vector<LoopStmtContext *> loopStmt();
    LoopStmtContext* loopStmt(size_t i);

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IfElseStmtContext : public LoopStmtContext {
  public:
    IfElseStmtContext(LoopStmtContext *ctx);

    antlr4::tree::TerminalNode *IF();
    ConditionContext *condition();
    std::vector<BlockContext *> block();
    BlockContext* block(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AssignmentStmtContext : public LoopStmtContext {
  public:
    AssignmentStmtContext(LoopStmtContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    ExprContext *expr();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  LoopStmtContext* loopStmt();

  class  ConditionContext : public antlr4::ParserRuleContext {
  public:
    ConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ConditionContext() = default;
    void copyFrom(ConditionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  NegateOpContext : public ConditionContext {
  public:
    NegateOpContext(ConditionContext *ctx);

    antlr4::tree::TerminalNode *NEG_OP();
    ConditionContext *condition();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  RelationContext : public ConditionContext {
  public:
    RelationContext(ConditionContext *ctx);

    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    antlr4::tree::TerminalNode *REL_OP();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BooleanLiteralContext : public ConditionContext {
  public:
    BooleanLiteralContext(ConditionContext *ctx);

    antlr4::tree::TerminalNode *BOOL_LITERAL();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BooleanOpContext : public ConditionContext {
  public:
    BooleanOpContext(ConditionContext *ctx);

    std::vector<ConditionContext *> condition();
    ConditionContext* condition(size_t i);
    antlr4::tree::TerminalNode *BOOL_OP();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ConditionParenContext : public ConditionContext {
  public:
    ConditionParenContext(ConditionContext *ctx);

    ConditionContext *condition();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BooleanIdentifierContext : public ConditionContext {
  public:
    BooleanIdentifierContext(ConditionContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConditionContext* condition();
  ConditionContext* condition(int precedence);
  class  EndContext : public antlr4::ParserRuleContext {
  public:
    EndContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *END();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EndContext* end();

  class  UserFunctionContext : public antlr4::ParserRuleContext {
  public:
    UserFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    UserFunctionArgListContext *userFunctionArgList();
    std::vector<UserFunctionStmtContext *> userFunctionStmt();
    UserFunctionStmtContext* userFunctionStmt(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UserFunctionContext* userFunction();

  class  UserFunctionArgListContext : public antlr4::ParserRuleContext {
  public:
    UserFunctionArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UserFunctionArgumentContext *> userFunctionArgument();
    UserFunctionArgumentContext* userFunctionArgument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UserFunctionArgListContext* userFunctionArgList();

  class  UserFunctionPassedArgListContext : public antlr4::ParserRuleContext {
  public:
    UserFunctionPassedArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<GenericExpressionContext *> genericExpression();
    GenericExpressionContext* genericExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WHITESPACE();
    antlr4::tree::TerminalNode* WHITESPACE(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UserFunctionPassedArgListContext* userFunctionPassedArgList();

  class  UserFunctionArgumentContext : public antlr4::ParserRuleContext {
  public:
    UserFunctionArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *IDENTIFIER();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UserFunctionArgumentContext* userFunctionArgument();

  class  UserFunctionBlockContext : public antlr4::ParserRuleContext {
  public:
    UserFunctionBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UserFunctionStmtContext *> userFunctionStmt();
    UserFunctionStmtContext* userFunctionStmt(size_t i);


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UserFunctionBlockContext* userFunctionBlock();

  class  GenericExpressionContext : public antlr4::ParserRuleContext {
  public:
    GenericExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    ConditionContext *condition();


    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericExpressionContext* genericExpression();

  class  UserFunctionStmtContext : public antlr4::ParserRuleContext {
  public:
    UserFunctionStmtContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    UserFunctionStmtContext() = default;
    void copyFrom(UserFunctionStmtContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  UserFunctionListRemoveContext : public UserFunctionStmtContext {
  public:
    UserFunctionListRemoveContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *REMOVE();
    ExprContext *expr();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionConditionalContext : public UserFunctionStmtContext {
  public:
    UserFunctionConditionalContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *IF();
    ConditionContext *condition();
    std::vector<UserFunctionBlockContext *> userFunctionBlock();
    UserFunctionBlockContext* userFunctionBlock(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionWhileLoopContext : public UserFunctionStmtContext {
  public:
    UserFunctionWhileLoopContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *WHILE();
    ConditionContext *condition();
    UserFunctionBlockContext *userFunctionBlock();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionBreakContext : public UserFunctionStmtContext {
  public:
    UserFunctionBreakContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *BREAK();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionListAppendContext : public UserFunctionStmtContext {
  public:
    UserFunctionListAppendContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *TYPE();
    GenericExpressionContext *genericExpression();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionContinueContext : public UserFunctionStmtContext {
  public:
    UserFunctionContinueContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *CONTINUE();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionAssignmentContext : public UserFunctionStmtContext {
  public:
    UserFunctionAssignmentContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
    GenericExpressionContext *genericExpression();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionReturnContext : public UserFunctionStmtContext {
  public:
    UserFunctionReturnContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *RETURN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *NEWLINE();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionForLoopContext : public UserFunctionStmtContext {
  public:
    UserFunctionForLoopContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *FOR();
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    ConditionContext *condition();
    UserFunctionBlockContext *userFunctionBlock();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  UserFunctionDeclarationContext : public UserFunctionStmtContext {
  public:
    UserFunctionDeclarationContext(UserFunctionStmtContext *ctx);

    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *NEWLINE();
    GenericExpressionContext *genericExpression();

    virtual antlrcpp::Any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  UserFunctionStmtContext* userFunctionStmt();


  virtual bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;
  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);
  bool conditionSempred(ConditionContext *_localctx, size_t predicateIndex);

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

