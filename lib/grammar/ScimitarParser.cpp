
// Generated from Scimitar.g4 by ANTLR 4.8; unmodified.


#include "ScimitarVisitor.h"

#include "ScimitarParser.h"


using namespace antlrcpp;
using namespace antlr4;

ScimitarParser::ScimitarParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

ScimitarParser::~ScimitarParser() {
  delete _interpreter;
}

std::string ScimitarParser::getGrammarFileName() const {
  return "Scimitar.g4";
}

const std::vector<std::string>& ScimitarParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& ScimitarParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- RootContext ------------------------------------------------------------------

ScimitarParser::RootContext::RootContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ScimitarParser::ActionContext *> ScimitarParser::RootContext::action() {
  return getRuleContexts<ScimitarParser::ActionContext>();
}

ScimitarParser::ActionContext* ScimitarParser::RootContext::action(size_t i) {
  return getRuleContext<ScimitarParser::ActionContext>(i);
}


size_t ScimitarParser::RootContext::getRuleIndex() const {
  return ScimitarParser::RuleRoot;
}


antlrcpp::Any ScimitarParser::RootContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitRoot(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::RootContext* ScimitarParser::root() {
  RootContext *_localctx = _tracker.createInstance<RootContext>(_ctx, getState());
  enterRule(_localctx, 0, ScimitarParser::RuleRoot);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ScimitarParser::T__12)
      | (1ULL << ScimitarParser::END)
      | (1ULL << ScimitarParser::PARAM)
      | (1ULL << ScimitarParser::SET)
      | (1ULL << ScimitarParser::GROUP)
      | (1ULL << ScimitarParser::UNGROUP)
      | (1ULL << ScimitarParser::RUN)
      | (1ULL << ScimitarParser::SYSTEM)
      | (1ULL << ScimitarParser::COMMENT))) != 0)) {
      setState(62);
      action();
      setState(67);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ActionContext ------------------------------------------------------------------

ScimitarParser::ActionContext::ActionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::ActionContext::getRuleIndex() const {
  return ScimitarParser::RuleAction;
}

void ScimitarParser::ActionContext::copyFrom(ActionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RunBlockContext ------------------------------------------------------------------

ScimitarParser::RunContext* ScimitarParser::RunBlockContext::run() {
  return getRuleContext<ScimitarParser::RunContext>(0);
}

ScimitarParser::RunBlockContext::RunBlockContext(ActionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::RunBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitRunBlock(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionDefinitionContext ------------------------------------------------------------------

ScimitarParser::UserFunctionContext* ScimitarParser::UserFunctionDefinitionContext::userFunction() {
  return getRuleContext<ScimitarParser::UserFunctionContext>(0);
}

ScimitarParser::UserFunctionDefinitionContext::UserFunctionDefinitionContext(ActionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionDefinitionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionDefinition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- EngineActionContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::EngineActionContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::ParamContext* ScimitarParser::EngineActionContext::param() {
  return getRuleContext<ScimitarParser::ParamContext>(0);
}

ScimitarParser::FunctionContext* ScimitarParser::EngineActionContext::function() {
  return getRuleContext<ScimitarParser::FunctionContext>(0);
}

ScimitarParser::SetParamContext* ScimitarParser::EngineActionContext::setParam() {
  return getRuleContext<ScimitarParser::SetParamContext>(0);
}

ScimitarParser::SetOptionContext* ScimitarParser::EngineActionContext::setOption() {
  return getRuleContext<ScimitarParser::SetOptionContext>(0);
}

ScimitarParser::SetFunctionContext* ScimitarParser::EngineActionContext::setFunction() {
  return getRuleContext<ScimitarParser::SetFunctionContext>(0);
}

ScimitarParser::GroupContext* ScimitarParser::EngineActionContext::group() {
  return getRuleContext<ScimitarParser::GroupContext>(0);
}

ScimitarParser::UngroupContext* ScimitarParser::EngineActionContext::ungroup() {
  return getRuleContext<ScimitarParser::UngroupContext>(0);
}

ScimitarParser::EndContext* ScimitarParser::EngineActionContext::end() {
  return getRuleContext<ScimitarParser::EndContext>(0);
}

ScimitarParser::SystemContext* ScimitarParser::EngineActionContext::system() {
  return getRuleContext<ScimitarParser::SystemContext>(0);
}

ScimitarParser::EngineActionContext::EngineActionContext(ActionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::EngineActionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitEngineAction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprCommentContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::ExprCommentContext::COMMENT() {
  return getToken(ScimitarParser::COMMENT, 0);
}

ScimitarParser::ExprCommentContext::ExprCommentContext(ActionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ExprCommentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitExprComment(this);
  else
    return visitor->visitChildren(this);
}
ScimitarParser::ActionContext* ScimitarParser::action() {
  ActionContext *_localctx = _tracker.createInstance<ActionContext>(_ctx, getState());
  enterRule(_localctx, 2, ScimitarParser::RuleAction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(84);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ScimitarParser::END:
      case ScimitarParser::PARAM:
      case ScimitarParser::SET:
      case ScimitarParser::GROUP:
      case ScimitarParser::UNGROUP:
      case ScimitarParser::SYSTEM: {
        _localctx = dynamic_cast<ActionContext *>(_tracker.createInstance<ScimitarParser::EngineActionContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(77);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          setState(68);
          param();
          break;
        }

        case 2: {
          setState(69);
          function();
          break;
        }

        case 3: {
          setState(70);
          setParam();
          break;
        }

        case 4: {
          setState(71);
          setOption();
          break;
        }

        case 5: {
          setState(72);
          setFunction();
          break;
        }

        case 6: {
          setState(73);
          group();
          break;
        }

        case 7: {
          setState(74);
          ungroup();
          break;
        }

        case 8: {
          setState(75);
          end();
          break;
        }

        case 9: {
          setState(76);
          system();
          break;
        }

        }
        setState(79);
        match(ScimitarParser::NEWLINE);
        break;
      }

      case ScimitarParser::RUN: {
        _localctx = dynamic_cast<ActionContext *>(_tracker.createInstance<ScimitarParser::RunBlockContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(81);
        run();
        break;
      }

      case ScimitarParser::T__12: {
        _localctx = dynamic_cast<ActionContext *>(_tracker.createInstance<ScimitarParser::UserFunctionDefinitionContext>(_localctx));
        enterOuterAlt(_localctx, 3);
        setState(82);
        userFunction();
        break;
      }

      case ScimitarParser::COMMENT: {
        _localctx = dynamic_cast<ActionContext *>(_tracker.createInstance<ScimitarParser::ExprCommentContext>(_localctx));
        enterOuterAlt(_localctx, 4);
        setState(83);
        match(ScimitarParser::COMMENT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

ScimitarParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::ParamContext::PARAM() {
  return getToken(ScimitarParser::PARAM, 0);
}

tree::TerminalNode* ScimitarParser::ParamContext::TYPE() {
  return getToken(ScimitarParser::TYPE, 0);
}

tree::TerminalNode* ScimitarParser::ParamContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::ParameterValueContext* ScimitarParser::ParamContext::parameterValue() {
  return getRuleContext<ScimitarParser::ParameterValueContext>(0);
}

std::vector<ScimitarParser::OptionContext *> ScimitarParser::ParamContext::option() {
  return getRuleContexts<ScimitarParser::OptionContext>();
}

ScimitarParser::OptionContext* ScimitarParser::ParamContext::option(size_t i) {
  return getRuleContext<ScimitarParser::OptionContext>(i);
}


size_t ScimitarParser::ParamContext::getRuleIndex() const {
  return ScimitarParser::RuleParam;
}


antlrcpp::Any ScimitarParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::ParamContext* ScimitarParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 4, ScimitarParser::RuleParam);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    match(ScimitarParser::PARAM);
    setState(87);
    match(ScimitarParser::TYPE);
    setState(88);
    match(ScimitarParser::IDENTIFIER);
    setState(89);
    parameterValue();
    setState(98);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::T__0) {
      setState(90);
      match(ScimitarParser::T__0);
      setState(94);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ScimitarParser::T__8

      || _la == ScimitarParser::OPT) {
        setState(91);
        option();
        setState(96);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(97);
      match(ScimitarParser::T__1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionContext ------------------------------------------------------------------

ScimitarParser::FunctionContext::FunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::FunctionContext::PARAM() {
  return getToken(ScimitarParser::PARAM, 0);
}

tree::TerminalNode* ScimitarParser::FunctionContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::ExprContext* ScimitarParser::FunctionContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

std::vector<ScimitarParser::OptionContext *> ScimitarParser::FunctionContext::option() {
  return getRuleContexts<ScimitarParser::OptionContext>();
}

ScimitarParser::OptionContext* ScimitarParser::FunctionContext::option(size_t i) {
  return getRuleContext<ScimitarParser::OptionContext>(i);
}


size_t ScimitarParser::FunctionContext::getRuleIndex() const {
  return ScimitarParser::RuleFunction;
}


antlrcpp::Any ScimitarParser::FunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitFunction(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::FunctionContext* ScimitarParser::function() {
  FunctionContext *_localctx = _tracker.createInstance<FunctionContext>(_ctx, getState());
  enterRule(_localctx, 6, ScimitarParser::RuleFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(100);
    match(ScimitarParser::PARAM);
    setState(101);
    match(ScimitarParser::T__2);
    setState(102);
    match(ScimitarParser::IDENTIFIER);
    setState(103);
    expr(0);
    setState(112);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::T__0) {
      setState(104);
      match(ScimitarParser::T__0);
      setState(108);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ScimitarParser::T__8

      || _la == ScimitarParser::OPT) {
        setState(105);
        option();
        setState(110);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(111);
      match(ScimitarParser::T__1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetParamContext ------------------------------------------------------------------

ScimitarParser::SetParamContext::SetParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::SetParamContext::SET() {
  return getToken(ScimitarParser::SET, 0);
}

tree::TerminalNode* ScimitarParser::SetParamContext::PARAM() {
  return getToken(ScimitarParser::PARAM, 0);
}

tree::TerminalNode* ScimitarParser::SetParamContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

std::vector<ScimitarParser::OptionContext *> ScimitarParser::SetParamContext::option() {
  return getRuleContexts<ScimitarParser::OptionContext>();
}

ScimitarParser::OptionContext* ScimitarParser::SetParamContext::option(size_t i) {
  return getRuleContext<ScimitarParser::OptionContext>(i);
}


size_t ScimitarParser::SetParamContext::getRuleIndex() const {
  return ScimitarParser::RuleSetParam;
}


antlrcpp::Any ScimitarParser::SetParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitSetParam(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::SetParamContext* ScimitarParser::setParam() {
  SetParamContext *_localctx = _tracker.createInstance<SetParamContext>(_ctx, getState());
  enterRule(_localctx, 8, ScimitarParser::RuleSetParam);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(114);
    match(ScimitarParser::SET);
    setState(115);
    match(ScimitarParser::PARAM);
    setState(116);
    match(ScimitarParser::IDENTIFIER);
    setState(117);
    match(ScimitarParser::T__0);
    setState(119); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(118);
      option();
      setState(121); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ScimitarParser::T__8

    || _la == ScimitarParser::OPT);
    setState(123);
    match(ScimitarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetOptionContext ------------------------------------------------------------------

ScimitarParser::SetOptionContext::SetOptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::SetOptionContext::SET() {
  return getToken(ScimitarParser::SET, 0);
}

tree::TerminalNode* ScimitarParser::SetOptionContext::OPTION() {
  return getToken(ScimitarParser::OPTION, 0);
}

std::vector<ScimitarParser::ScriptOptionContext *> ScimitarParser::SetOptionContext::scriptOption() {
  return getRuleContexts<ScimitarParser::ScriptOptionContext>();
}

ScimitarParser::ScriptOptionContext* ScimitarParser::SetOptionContext::scriptOption(size_t i) {
  return getRuleContext<ScimitarParser::ScriptOptionContext>(i);
}

std::vector<tree::TerminalNode *> ScimitarParser::SetOptionContext::STRING() {
  return getTokens(ScimitarParser::STRING);
}

tree::TerminalNode* ScimitarParser::SetOptionContext::STRING(size_t i) {
  return getToken(ScimitarParser::STRING, i);
}


size_t ScimitarParser::SetOptionContext::getRuleIndex() const {
  return ScimitarParser::RuleSetOption;
}


antlrcpp::Any ScimitarParser::SetOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitSetOption(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::SetOptionContext* ScimitarParser::setOption() {
  SetOptionContext *_localctx = _tracker.createInstance<SetOptionContext>(_ctx, getState());
  enterRule(_localctx, 10, ScimitarParser::RuleSetOption);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(ScimitarParser::SET);
    setState(126);
    match(ScimitarParser::OPTION);
    setState(131); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(127);
      scriptOption();
      setState(128);
      match(ScimitarParser::T__3);
      setState(129);
      match(ScimitarParser::STRING);
      setState(133); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ScimitarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetFunctionContext ------------------------------------------------------------------

ScimitarParser::SetFunctionContext::SetFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::SetFunctionContext::SET() {
  return getToken(ScimitarParser::SET, 0);
}

tree::TerminalNode* ScimitarParser::SetFunctionContext::PARAM() {
  return getToken(ScimitarParser::PARAM, 0);
}

tree::TerminalNode* ScimitarParser::SetFunctionContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

std::vector<ScimitarParser::ExprContext *> ScimitarParser::SetFunctionContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::SetFunctionContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

std::vector<ScimitarParser::OptionContext *> ScimitarParser::SetFunctionContext::option() {
  return getRuleContexts<ScimitarParser::OptionContext>();
}

ScimitarParser::OptionContext* ScimitarParser::SetFunctionContext::option(size_t i) {
  return getRuleContext<ScimitarParser::OptionContext>(i);
}


size_t ScimitarParser::SetFunctionContext::getRuleIndex() const {
  return ScimitarParser::RuleSetFunction;
}


antlrcpp::Any ScimitarParser::SetFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitSetFunction(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::SetFunctionContext* ScimitarParser::setFunction() {
  SetFunctionContext *_localctx = _tracker.createInstance<SetFunctionContext>(_ctx, getState());
  enterRule(_localctx, 12, ScimitarParser::RuleSetFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(135);
    match(ScimitarParser::SET);
    setState(136);
    match(ScimitarParser::PARAM);
    setState(137);
    match(ScimitarParser::IDENTIFIER);
    setState(138);
    match(ScimitarParser::T__0);
    setState(147); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(147);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case ScimitarParser::T__2: {
          setState(139);
          match(ScimitarParser::T__2);
          setState(140);
          match(ScimitarParser::T__3);
          setState(141);
          expr(0);
          break;
        }

        case ScimitarParser::T__8:
        case ScimitarParser::OPT: {
          setState(143); 
          _errHandler->sync(this);
          alt = 1;
          do {
            switch (alt) {
              case 1: {
                    setState(142);
                    option();
                    break;
                  }

            default:
              throw NoViableAltException(this);
            }
            setState(145); 
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
          } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(149); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ScimitarParser::T__2)
      | (1ULL << ScimitarParser::T__8)
      | (1ULL << ScimitarParser::OPT))) != 0));
    setState(151);
    match(ScimitarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupContext ------------------------------------------------------------------

ScimitarParser::GroupContext::GroupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::GroupContext::GROUP() {
  return getToken(ScimitarParser::GROUP, 0);
}

std::vector<tree::TerminalNode *> ScimitarParser::GroupContext::IDENTIFIER() {
  return getTokens(ScimitarParser::IDENTIFIER);
}

tree::TerminalNode* ScimitarParser::GroupContext::IDENTIFIER(size_t i) {
  return getToken(ScimitarParser::IDENTIFIER, i);
}


size_t ScimitarParser::GroupContext::getRuleIndex() const {
  return ScimitarParser::RuleGroup;
}


antlrcpp::Any ScimitarParser::GroupContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitGroup(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::GroupContext* ScimitarParser::group() {
  GroupContext *_localctx = _tracker.createInstance<GroupContext>(_ctx, getState());
  enterRule(_localctx, 14, ScimitarParser::RuleGroup);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(153);
    match(ScimitarParser::GROUP);
    setState(155); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(154);
      match(ScimitarParser::IDENTIFIER);
      setState(157); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ScimitarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UngroupContext ------------------------------------------------------------------

ScimitarParser::UngroupContext::UngroupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::UngroupContext::UNGROUP() {
  return getToken(ScimitarParser::UNGROUP, 0);
}

std::vector<tree::TerminalNode *> ScimitarParser::UngroupContext::IDENTIFIER() {
  return getTokens(ScimitarParser::IDENTIFIER);
}

tree::TerminalNode* ScimitarParser::UngroupContext::IDENTIFIER(size_t i) {
  return getToken(ScimitarParser::IDENTIFIER, i);
}


size_t ScimitarParser::UngroupContext::getRuleIndex() const {
  return ScimitarParser::RuleUngroup;
}


antlrcpp::Any ScimitarParser::UngroupContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUngroup(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::UngroupContext* ScimitarParser::ungroup() {
  UngroupContext *_localctx = _tracker.createInstance<UngroupContext>(_ctx, getState());
  enterRule(_localctx, 16, ScimitarParser::RuleUngroup);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(159);
    match(ScimitarParser::UNGROUP);
    setState(161); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(160);
      match(ScimitarParser::IDENTIFIER);
      setState(163); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ScimitarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SystemContext ------------------------------------------------------------------

ScimitarParser::SystemContext::SystemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::SystemContext::SYSTEM() {
  return getToken(ScimitarParser::SYSTEM, 0);
}

std::vector<tree::TerminalNode *> ScimitarParser::SystemContext::IDENTIFIER() {
  return getTokens(ScimitarParser::IDENTIFIER);
}

tree::TerminalNode* ScimitarParser::SystemContext::IDENTIFIER(size_t i) {
  return getToken(ScimitarParser::IDENTIFIER, i);
}

std::vector<ScimitarParser::SystemOptionContext *> ScimitarParser::SystemContext::systemOption() {
  return getRuleContexts<ScimitarParser::SystemOptionContext>();
}

ScimitarParser::SystemOptionContext* ScimitarParser::SystemContext::systemOption(size_t i) {
  return getRuleContext<ScimitarParser::SystemOptionContext>(i);
}


size_t ScimitarParser::SystemContext::getRuleIndex() const {
  return ScimitarParser::RuleSystem;
}


antlrcpp::Any ScimitarParser::SystemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitSystem(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::SystemContext* ScimitarParser::system() {
  SystemContext *_localctx = _tracker.createInstance<SystemContext>(_ctx, getState());
  enterRule(_localctx, 18, ScimitarParser::RuleSystem);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(165);
    match(ScimitarParser::SYSTEM);
    setState(169); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(166);
      match(ScimitarParser::IDENTIFIER);
      setState(167);
      match(ScimitarParser::T__3);
      setState(168);
      systemOption();
      setState(171); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == ScimitarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterValueContext ------------------------------------------------------------------

ScimitarParser::ParameterValueContext::ParameterValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::ParameterValueContext::getRuleIndex() const {
  return ScimitarParser::RuleParameterValue;
}

void ScimitarParser::ParameterValueContext::copyFrom(ParameterValueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParameterValueRangeContext ------------------------------------------------------------------

ScimitarParser::RangeContext* ScimitarParser::ParameterValueRangeContext::range() {
  return getRuleContext<ScimitarParser::RangeContext>(0);
}

ScimitarParser::ParameterValueRangeContext::ParameterValueRangeContext(ParameterValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ParameterValueRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitParameterValueRange(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParameterValueListContext ------------------------------------------------------------------

ScimitarParser::ListContext* ScimitarParser::ParameterValueListContext::list() {
  return getRuleContext<ScimitarParser::ListContext>(0);
}

ScimitarParser::ParameterValueListContext::ParameterValueListContext(ParameterValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ParameterValueListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitParameterValueList(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParameterValueStringContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::ParameterValueStringContext::STRING() {
  return getToken(ScimitarParser::STRING, 0);
}

ScimitarParser::ParameterValueStringContext::ParameterValueStringContext(ParameterValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ParameterValueStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitParameterValueString(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParameterValueExprContext ------------------------------------------------------------------

ScimitarParser::ExprContext* ScimitarParser::ParameterValueExprContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

ScimitarParser::ParameterValueExprContext::ParameterValueExprContext(ParameterValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ParameterValueExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitParameterValueExpr(this);
  else
    return visitor->visitChildren(this);
}
ScimitarParser::ParameterValueContext* ScimitarParser::parameterValue() {
  ParameterValueContext *_localctx = _tracker.createInstance<ParameterValueContext>(_ctx, getState());
  enterRule(_localctx, 20, ScimitarParser::RuleParameterValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(177);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ParameterValueContext *>(_tracker.createInstance<ScimitarParser::ParameterValueExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(173);
      expr(0);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ParameterValueContext *>(_tracker.createInstance<ScimitarParser::ParameterValueRangeContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(174);
      range();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<ParameterValueContext *>(_tracker.createInstance<ScimitarParser::ParameterValueListContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(175);
      list();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<ParameterValueContext *>(_tracker.createInstance<ScimitarParser::ParameterValueStringContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(176);
      match(ScimitarParser::STRING);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RangeContext ------------------------------------------------------------------

ScimitarParser::RangeContext::RangeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ScimitarParser::ExprContext *> ScimitarParser::RangeContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::RangeContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}


size_t ScimitarParser::RangeContext::getRuleIndex() const {
  return ScimitarParser::RuleRange;
}


antlrcpp::Any ScimitarParser::RangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitRange(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::RangeContext* ScimitarParser::range() {
  RangeContext *_localctx = _tracker.createInstance<RangeContext>(_ctx, getState());
  enterRule(_localctx, 22, ScimitarParser::RuleRange);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(179);
    expr(0);
    setState(180);
    match(ScimitarParser::T__4);
    setState(181);
    expr(0);
    setState(182);
    match(ScimitarParser::T__4);
    setState(183);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListContext ------------------------------------------------------------------

ScimitarParser::ListContext::ListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ScimitarParser::ListElementContext *> ScimitarParser::ListContext::listElement() {
  return getRuleContexts<ScimitarParser::ListElementContext>();
}

ScimitarParser::ListElementContext* ScimitarParser::ListContext::listElement(size_t i) {
  return getRuleContext<ScimitarParser::ListElementContext>(i);
}

std::vector<tree::TerminalNode *> ScimitarParser::ListContext::WHITESPACE() {
  return getTokens(ScimitarParser::WHITESPACE);
}

tree::TerminalNode* ScimitarParser::ListContext::WHITESPACE(size_t i) {
  return getToken(ScimitarParser::WHITESPACE, i);
}


size_t ScimitarParser::ListContext::getRuleIndex() const {
  return ScimitarParser::RuleList;
}


antlrcpp::Any ScimitarParser::ListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitList(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::ListContext* ScimitarParser::list() {
  ListContext *_localctx = _tracker.createInstance<ListContext>(_ctx, getState());
  enterRule(_localctx, 24, ScimitarParser::RuleList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(185);
    match(ScimitarParser::T__5);
    setState(199);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(187);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ScimitarParser::WHITESPACE) {
          setState(186);
          match(ScimitarParser::WHITESPACE);
        }
        setState(189);
        listElement();
        setState(191);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ScimitarParser::WHITESPACE) {
          setState(190);
          match(ScimitarParser::WHITESPACE);
        }
        setState(193);
        match(ScimitarParser::T__6);
        setState(195);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
        case 1: {
          setState(194);
          match(ScimitarParser::WHITESPACE);
          break;
        }

        } 
      }
      setState(201);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
    setState(203);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::WHITESPACE) {
      setState(202);
      match(ScimitarParser::WHITESPACE);
    }
    setState(205);
    listElement();
    setState(207);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::WHITESPACE) {
      setState(206);
      match(ScimitarParser::WHITESPACE);
    }
    setState(209);
    match(ScimitarParser::T__7);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ListElementContext ------------------------------------------------------------------

ScimitarParser::ListElementContext::ListElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::ListElementContext::getRuleIndex() const {
  return ScimitarParser::RuleListElement;
}

void ScimitarParser::ListElementContext::copyFrom(ListElementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ListElementRangeContext ------------------------------------------------------------------

ScimitarParser::RangeContext* ScimitarParser::ListElementRangeContext::range() {
  return getRuleContext<ScimitarParser::RangeContext>(0);
}

ScimitarParser::ListElementRangeContext::ListElementRangeContext(ListElementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ListElementRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitListElementRange(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ListElementExprContext ------------------------------------------------------------------

ScimitarParser::ExprContext* ScimitarParser::ListElementExprContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

ScimitarParser::ListElementExprContext::ListElementExprContext(ListElementContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ListElementExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitListElementExpr(this);
  else
    return visitor->visitChildren(this);
}
ScimitarParser::ListElementContext* ScimitarParser::listElement() {
  ListElementContext *_localctx = _tracker.createInstance<ListElementContext>(_ctx, getState());
  enterRule(_localctx, 26, ScimitarParser::RuleListElement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(213);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 22, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<ListElementContext *>(_tracker.createInstance<ScimitarParser::ListElementExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(211);
      expr(0);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<ListElementContext *>(_tracker.createInstance<ScimitarParser::ListElementRangeContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(212);
      range();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionContext ------------------------------------------------------------------

ScimitarParser::OptionContext::OptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::OptionContext::getRuleIndex() const {
  return ScimitarParser::RuleOption;
}

void ScimitarParser::OptionContext::copyFrom(OptionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- HideOptionContext ------------------------------------------------------------------

ScimitarParser::HideOptionContext::HideOptionContext(OptionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::HideOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitHideOption(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StandardOptionContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::StandardOptionContext::OPT() {
  return getToken(ScimitarParser::OPT, 0);
}

ScimitarParser::OptionValueContext* ScimitarParser::StandardOptionContext::optionValue() {
  return getRuleContext<ScimitarParser::OptionValueContext>(0);
}

ScimitarParser::StandardOptionContext::StandardOptionContext(OptionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::StandardOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitStandardOption(this);
  else
    return visitor->visitChildren(this);
}
ScimitarParser::OptionContext* ScimitarParser::option() {
  OptionContext *_localctx = _tracker.createInstance<OptionContext>(_ctx, getState());
  enterRule(_localctx, 28, ScimitarParser::RuleOption);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(219);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case ScimitarParser::OPT: {
        _localctx = dynamic_cast<OptionContext *>(_tracker.createInstance<ScimitarParser::StandardOptionContext>(_localctx));
        enterOuterAlt(_localctx, 1);
        setState(215);
        match(ScimitarParser::OPT);
        setState(216);
        match(ScimitarParser::T__3);
        setState(217);
        optionValue();
        break;
      }

      case ScimitarParser::T__8: {
        _localctx = dynamic_cast<OptionContext *>(_tracker.createInstance<ScimitarParser::HideOptionContext>(_localctx));
        enterOuterAlt(_localctx, 2);
        setState(218);
        match(ScimitarParser::T__8);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionValueContext ------------------------------------------------------------------

ScimitarParser::OptionValueContext::OptionValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::OptionValueContext::getRuleIndex() const {
  return ScimitarParser::RuleOptionValue;
}

void ScimitarParser::OptionValueContext::copyFrom(OptionValueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- OptionValueRangeContext ------------------------------------------------------------------

ScimitarParser::RangeContext* ScimitarParser::OptionValueRangeContext::range() {
  return getRuleContext<ScimitarParser::RangeContext>(0);
}

ScimitarParser::OptionValueRangeContext::OptionValueRangeContext(OptionValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OptionValueRangeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOptionValueRange(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OptionValueListContext ------------------------------------------------------------------

ScimitarParser::ListContext* ScimitarParser::OptionValueListContext::list() {
  return getRuleContext<ScimitarParser::ListContext>(0);
}

ScimitarParser::OptionValueListContext::OptionValueListContext(OptionValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OptionValueListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOptionValueList(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OptionValueExprContext ------------------------------------------------------------------

ScimitarParser::ExprContext* ScimitarParser::OptionValueExprContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

ScimitarParser::OptionValueExprContext::OptionValueExprContext(OptionValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OptionValueExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOptionValueExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OptionValueStringContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::OptionValueStringContext::STRING() {
  return getToken(ScimitarParser::STRING, 0);
}

ScimitarParser::OptionValueStringContext::OptionValueStringContext(OptionValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OptionValueStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOptionValueString(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OptionValueFormatContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::OptionValueFormatContext::FORMAT() {
  return getToken(ScimitarParser::FORMAT, 0);
}

ScimitarParser::OptionValueFormatContext::OptionValueFormatContext(OptionValueContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OptionValueFormatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOptionValueFormat(this);
  else
    return visitor->visitChildren(this);
}
ScimitarParser::OptionValueContext* ScimitarParser::optionValue() {
  OptionValueContext *_localctx = _tracker.createInstance<OptionValueContext>(_ctx, getState());
  enterRule(_localctx, 30, ScimitarParser::RuleOptionValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(226);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 24, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<OptionValueContext *>(_tracker.createInstance<ScimitarParser::OptionValueExprContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(221);
      expr(0);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<OptionValueContext *>(_tracker.createInstance<ScimitarParser::OptionValueRangeContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(222);
      range();
      break;
    }

    case 3: {
      _localctx = dynamic_cast<OptionValueContext *>(_tracker.createInstance<ScimitarParser::OptionValueListContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(223);
      list();
      break;
    }

    case 4: {
      _localctx = dynamic_cast<OptionValueContext *>(_tracker.createInstance<ScimitarParser::OptionValueFormatContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(224);
      match(ScimitarParser::FORMAT);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<OptionValueContext *>(_tracker.createInstance<ScimitarParser::OptionValueStringContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(225);
      match(ScimitarParser::STRING);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ScriptOptionContext ------------------------------------------------------------------

ScimitarParser::ScriptOptionContext::ScriptOptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> ScimitarParser::ScriptOptionContext::IDENTIFIER() {
  return getTokens(ScimitarParser::IDENTIFIER);
}

tree::TerminalNode* ScimitarParser::ScriptOptionContext::IDENTIFIER(size_t i) {
  return getToken(ScimitarParser::IDENTIFIER, i);
}


size_t ScimitarParser::ScriptOptionContext::getRuleIndex() const {
  return ScimitarParser::RuleScriptOption;
}


antlrcpp::Any ScimitarParser::ScriptOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitScriptOption(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::ScriptOptionContext* ScimitarParser::scriptOption() {
  ScriptOptionContext *_localctx = _tracker.createInstance<ScriptOptionContext>(_ctx, getState());
  enterRule(_localctx, 32, ScimitarParser::RuleScriptOption);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(232);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(228);
      match(ScimitarParser::IDENTIFIER);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(229);
      match(ScimitarParser::IDENTIFIER);
      setState(230);
      match(ScimitarParser::T__9);
      setState(231);
      match(ScimitarParser::IDENTIFIER);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SystemOptionContext ------------------------------------------------------------------

ScimitarParser::SystemOptionContext::SystemOptionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::SystemOptionContext::STRING() {
  return getToken(ScimitarParser::STRING, 0);
}

tree::TerminalNode* ScimitarParser::SystemOptionContext::NUMERIC() {
  return getToken(ScimitarParser::NUMERIC, 0);
}


size_t ScimitarParser::SystemOptionContext::getRuleIndex() const {
  return ScimitarParser::RuleSystemOption;
}


antlrcpp::Any ScimitarParser::SystemOptionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitSystemOption(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::SystemOptionContext* ScimitarParser::systemOption() {
  SystemOptionContext *_localctx = _tracker.createInstance<SystemOptionContext>(_ctx, getState());
  enterRule(_localctx, 34, ScimitarParser::RuleSystemOption);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(234);
    _la = _input->LA(1);
    if (!(_la == ScimitarParser::NUMERIC

    || _la == ScimitarParser::STRING)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ScimitarParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::ExprContext::getRuleIndex() const {
  return ScimitarParser::RuleExpr;
}

void ScimitarParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParenthesisContext ------------------------------------------------------------------

ScimitarParser::ExprContext* ScimitarParser::ParenthesisContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

ScimitarParser::ParenthesisContext::ParenthesisContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ParenthesisContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitParenthesis(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OpSubContext ------------------------------------------------------------------

std::vector<ScimitarParser::ExprContext *> ScimitarParser::OpSubContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::OpSubContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

tree::TerminalNode* ScimitarParser::OpSubContext::SUB() {
  return getToken(ScimitarParser::SUB, 0);
}

ScimitarParser::OpSubContext::OpSubContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OpSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOpSub(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::IdentifierContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::IdentifierContext::IdentifierContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprFunctionContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::ExprFunctionContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::UserFunctionPassedArgListContext* ScimitarParser::ExprFunctionContext::userFunctionPassedArgList() {
  return getRuleContext<ScimitarParser::UserFunctionPassedArgListContext>(0);
}

ScimitarParser::ExprFunctionContext::ExprFunctionContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ExprFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitExprFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LiteralContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::LiteralContext::NUMERIC() {
  return getToken(ScimitarParser::NUMERIC, 0);
}

ScimitarParser::LiteralContext::LiteralContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElementContext ------------------------------------------------------------------

std::vector<ScimitarParser::ExprContext *> ScimitarParser::ElementContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::ElementContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

ScimitarParser::ElementContext::ElementContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OpPowContext ------------------------------------------------------------------

std::vector<ScimitarParser::ExprContext *> ScimitarParser::OpPowContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::OpPowContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

tree::TerminalNode* ScimitarParser::OpPowContext::POW() {
  return getToken(ScimitarParser::POW, 0);
}

ScimitarParser::OpPowContext::OpPowContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OpPowContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOpPow(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegateContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::NegateContext::SUB() {
  return getToken(ScimitarParser::SUB, 0);
}

ScimitarParser::ExprContext* ScimitarParser::NegateContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

ScimitarParser::NegateContext::NegateContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::NegateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitNegate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OpDivContext ------------------------------------------------------------------

std::vector<ScimitarParser::ExprContext *> ScimitarParser::OpDivContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::OpDivContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

tree::TerminalNode* ScimitarParser::OpDivContext::DIV() {
  return getToken(ScimitarParser::DIV, 0);
}

ScimitarParser::OpDivContext::OpDivContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OpDivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOpDiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OpAddContext ------------------------------------------------------------------

std::vector<ScimitarParser::ExprContext *> ScimitarParser::OpAddContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::OpAddContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

tree::TerminalNode* ScimitarParser::OpAddContext::ADD() {
  return getToken(ScimitarParser::ADD, 0);
}

ScimitarParser::OpAddContext::OpAddContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OpAddContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOpAdd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OpMulContext ------------------------------------------------------------------

std::vector<ScimitarParser::ExprContext *> ScimitarParser::OpMulContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::OpMulContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

tree::TerminalNode* ScimitarParser::OpMulContext::MUL() {
  return getToken(ScimitarParser::MUL, 0);
}

ScimitarParser::OpMulContext::OpMulContext(ExprContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::OpMulContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitOpMul(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::ExprContext* ScimitarParser::expr() {
   return expr(0);
}

ScimitarParser::ExprContext* ScimitarParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ScimitarParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  ScimitarParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 36;
  enterRecursionRule(_localctx, 36, ScimitarParser::RuleExpr, precedence);

    size_t _la = 0;

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 27, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParenthesisContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(237);
      match(ScimitarParser::T__10);
      setState(238);
      expr(0);
      setState(239);
      match(ScimitarParser::T__11);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NegateContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(241);
      match(ScimitarParser::SUB);
      setState(242);
      expr(4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<ExprFunctionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(243);
      match(ScimitarParser::IDENTIFIER);
      setState(244);
      match(ScimitarParser::T__10);
      setState(246);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ScimitarParser::T__10)
        | (1ULL << ScimitarParser::NEG_OP)
        | (1ULL << ScimitarParser::BOOL_LITERAL)
        | (1ULL << ScimitarParser::SUB)
        | (1ULL << ScimitarParser::NUMERIC)
        | (1ULL << ScimitarParser::IDENTIFIER)
        | (1ULL << ScimitarParser::WHITESPACE))) != 0)) {
        setState(245);
        userFunctionPassedArgList();
      }
      setState(248);
      match(ScimitarParser::T__11);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(249);
      match(ScimitarParser::NUMERIC);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<IdentifierContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(250);
      match(ScimitarParser::IDENTIFIER);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(275);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(273);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 28, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<OpPowContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(253);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(254);
          match(ScimitarParser::POW);
          setState(255);
          expr(10);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<OpMulContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(256);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(257);
          match(ScimitarParser::MUL);
          setState(258);
          expr(9);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<OpDivContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(259);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(260);
          match(ScimitarParser::DIV);
          setState(261);
          expr(8);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<OpAddContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(262);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(263);
          match(ScimitarParser::ADD);
          setState(264);
          expr(7);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<OpSubContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(265);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(266);
          match(ScimitarParser::SUB);
          setState(267);
          expr(6);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<ElementContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(268);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(269);
          match(ScimitarParser::T__5);
          setState(270);
          expr(0);
          setState(271);
          match(ScimitarParser::T__7);
          break;
        }

        } 
      }
      setState(277);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 29, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- RunContext ------------------------------------------------------------------

ScimitarParser::RunContext::RunContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::RunContext::RUN() {
  return getToken(ScimitarParser::RUN, 0);
}

std::vector<ScimitarParser::LoopStmtContext *> ScimitarParser::RunContext::loopStmt() {
  return getRuleContexts<ScimitarParser::LoopStmtContext>();
}

ScimitarParser::LoopStmtContext* ScimitarParser::RunContext::loopStmt(size_t i) {
  return getRuleContext<ScimitarParser::LoopStmtContext>(i);
}


size_t ScimitarParser::RunContext::getRuleIndex() const {
  return ScimitarParser::RuleRun;
}


antlrcpp::Any ScimitarParser::RunContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitRun(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::RunContext* ScimitarParser::run() {
  RunContext *_localctx = _tracker.createInstance<RunContext>(_ctx, getState());
  enterRule(_localctx, 38, ScimitarParser::RuleRun);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    match(ScimitarParser::RUN);
    setState(279);
    match(ScimitarParser::T__0);
    setState(283);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ScimitarParser::IF)
      | (1ULL << ScimitarParser::REMOVE)
      | (1ULL << ScimitarParser::IDENTIFIER)
      | (1ULL << ScimitarParser::COMMENT))) != 0)) {
      setState(280);
      loopStmt();
      setState(285);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(286);
    match(ScimitarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

ScimitarParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ScimitarParser::LoopStmtContext *> ScimitarParser::BlockContext::loopStmt() {
  return getRuleContexts<ScimitarParser::LoopStmtContext>();
}

ScimitarParser::LoopStmtContext* ScimitarParser::BlockContext::loopStmt(size_t i) {
  return getRuleContext<ScimitarParser::LoopStmtContext>(i);
}


size_t ScimitarParser::BlockContext::getRuleIndex() const {
  return ScimitarParser::RuleBlock;
}


antlrcpp::Any ScimitarParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::BlockContext* ScimitarParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 40, ScimitarParser::RuleBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(291);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ScimitarParser::IF)
      | (1ULL << ScimitarParser::REMOVE)
      | (1ULL << ScimitarParser::IDENTIFIER)
      | (1ULL << ScimitarParser::COMMENT))) != 0)) {
      setState(288);
      loopStmt();
      setState(293);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoopStmtContext ------------------------------------------------------------------

ScimitarParser::LoopStmtContext::LoopStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::LoopStmtContext::getRuleIndex() const {
  return ScimitarParser::RuleLoopStmt;
}

void ScimitarParser::LoopStmtContext::copyFrom(LoopStmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RemoveStmtContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::RemoveStmtContext::REMOVE() {
  return getToken(ScimitarParser::REMOVE, 0);
}

tree::TerminalNode* ScimitarParser::RemoveStmtContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::RemoveStmtContext::RemoveStmtContext(LoopStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::RemoveStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitRemoveStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LoopCommentContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::LoopCommentContext::COMMENT() {
  return getToken(ScimitarParser::COMMENT, 0);
}

ScimitarParser::LoopCommentContext::LoopCommentContext(LoopStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::LoopCommentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitLoopComment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfStmtContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::IfStmtContext::IF() {
  return getToken(ScimitarParser::IF, 0);
}

ScimitarParser::ConditionContext* ScimitarParser::IfStmtContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}

std::vector<ScimitarParser::LoopStmtContext *> ScimitarParser::IfStmtContext::loopStmt() {
  return getRuleContexts<ScimitarParser::LoopStmtContext>();
}

ScimitarParser::LoopStmtContext* ScimitarParser::IfStmtContext::loopStmt(size_t i) {
  return getRuleContext<ScimitarParser::LoopStmtContext>(i);
}

ScimitarParser::IfStmtContext::IfStmtContext(LoopStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::IfStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitIfStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IfElseStmtContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::IfElseStmtContext::IF() {
  return getToken(ScimitarParser::IF, 0);
}

ScimitarParser::ConditionContext* ScimitarParser::IfElseStmtContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}

std::vector<ScimitarParser::BlockContext *> ScimitarParser::IfElseStmtContext::block() {
  return getRuleContexts<ScimitarParser::BlockContext>();
}

ScimitarParser::BlockContext* ScimitarParser::IfElseStmtContext::block(size_t i) {
  return getRuleContext<ScimitarParser::BlockContext>(i);
}

tree::TerminalNode* ScimitarParser::IfElseStmtContext::ELSE() {
  return getToken(ScimitarParser::ELSE, 0);
}

ScimitarParser::IfElseStmtContext::IfElseStmtContext(LoopStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::IfElseStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitIfElseStmt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignmentStmtContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::AssignmentStmtContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::ExprContext* ScimitarParser::AssignmentStmtContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

tree::TerminalNode* ScimitarParser::AssignmentStmtContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::AssignmentStmtContext::AssignmentStmtContext(LoopStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::AssignmentStmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitAssignmentStmt(this);
  else
    return visitor->visitChildren(this);
}
ScimitarParser::LoopStmtContext* ScimitarParser::loopStmt() {
  LoopStmtContext *_localctx = _tracker.createInstance<LoopStmtContext>(_ctx, getState());
  enterRule(_localctx, 42, ScimitarParser::RuleLoopStmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(327);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<LoopStmtContext *>(_tracker.createInstance<ScimitarParser::IfStmtContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(294);
      match(ScimitarParser::IF);
      setState(295);
      match(ScimitarParser::T__10);
      setState(296);
      condition(0);
      setState(297);
      match(ScimitarParser::T__11);
      setState(298);
      match(ScimitarParser::T__0);
      setState(302);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << ScimitarParser::IF)
        | (1ULL << ScimitarParser::REMOVE)
        | (1ULL << ScimitarParser::IDENTIFIER)
        | (1ULL << ScimitarParser::COMMENT))) != 0)) {
        setState(299);
        loopStmt();
        setState(304);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(305);
      match(ScimitarParser::T__1);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<LoopStmtContext *>(_tracker.createInstance<ScimitarParser::IfElseStmtContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(307);
      match(ScimitarParser::IF);
      setState(308);
      match(ScimitarParser::T__10);
      setState(309);
      condition(0);
      setState(310);
      match(ScimitarParser::T__11);
      setState(311);
      match(ScimitarParser::T__0);
      setState(312);
      block();
      setState(313);
      match(ScimitarParser::T__1);
      setState(314);
      match(ScimitarParser::ELSE);
      setState(315);
      match(ScimitarParser::T__0);
      setState(316);
      block();
      setState(317);
      match(ScimitarParser::T__1);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<LoopStmtContext *>(_tracker.createInstance<ScimitarParser::RemoveStmtContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(319);
      match(ScimitarParser::REMOVE);
      setState(320);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<LoopStmtContext *>(_tracker.createInstance<ScimitarParser::AssignmentStmtContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(321);
      match(ScimitarParser::IDENTIFIER);
      setState(322);
      match(ScimitarParser::T__3);
      setState(323);
      expr(0);
      setState(324);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<LoopStmtContext *>(_tracker.createInstance<ScimitarParser::LoopCommentContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(326);
      match(ScimitarParser::COMMENT);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionContext ------------------------------------------------------------------

ScimitarParser::ConditionContext::ConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::ConditionContext::getRuleIndex() const {
  return ScimitarParser::RuleCondition;
}

void ScimitarParser::ConditionContext::copyFrom(ConditionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- NegateOpContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::NegateOpContext::NEG_OP() {
  return getToken(ScimitarParser::NEG_OP, 0);
}

ScimitarParser::ConditionContext* ScimitarParser::NegateOpContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}

ScimitarParser::NegateOpContext::NegateOpContext(ConditionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::NegateOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitNegateOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RelationContext ------------------------------------------------------------------

std::vector<ScimitarParser::ExprContext *> ScimitarParser::RelationContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::RelationContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

tree::TerminalNode* ScimitarParser::RelationContext::REL_OP() {
  return getToken(ScimitarParser::REL_OP, 0);
}

ScimitarParser::RelationContext::RelationContext(ConditionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::RelationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitRelation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanLiteralContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::BooleanLiteralContext::BOOL_LITERAL() {
  return getToken(ScimitarParser::BOOL_LITERAL, 0);
}

ScimitarParser::BooleanLiteralContext::BooleanLiteralContext(ConditionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::BooleanLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitBooleanLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanOpContext ------------------------------------------------------------------

std::vector<ScimitarParser::ConditionContext *> ScimitarParser::BooleanOpContext::condition() {
  return getRuleContexts<ScimitarParser::ConditionContext>();
}

ScimitarParser::ConditionContext* ScimitarParser::BooleanOpContext::condition(size_t i) {
  return getRuleContext<ScimitarParser::ConditionContext>(i);
}

tree::TerminalNode* ScimitarParser::BooleanOpContext::BOOL_OP() {
  return getToken(ScimitarParser::BOOL_OP, 0);
}

ScimitarParser::BooleanOpContext::BooleanOpContext(ConditionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::BooleanOpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitBooleanOp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConditionParenContext ------------------------------------------------------------------

ScimitarParser::ConditionContext* ScimitarParser::ConditionParenContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}

ScimitarParser::ConditionParenContext::ConditionParenContext(ConditionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::ConditionParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitConditionParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanIdentifierContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::BooleanIdentifierContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::BooleanIdentifierContext::BooleanIdentifierContext(ConditionContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::BooleanIdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitBooleanIdentifier(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::ConditionContext* ScimitarParser::condition() {
   return condition(0);
}

ScimitarParser::ConditionContext* ScimitarParser::condition(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ScimitarParser::ConditionContext *_localctx = _tracker.createInstance<ConditionContext>(_ctx, parentState);
  ScimitarParser::ConditionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 44;
  enterRecursionRule(_localctx, 44, ScimitarParser::RuleCondition, precedence);

    

  auto onExit = finally([=] {
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(342);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ConditionParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(330);
      match(ScimitarParser::T__10);
      setState(331);
      condition(0);
      setState(332);
      match(ScimitarParser::T__11);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NegateOpContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(334);
      match(ScimitarParser::NEG_OP);
      setState(335);
      condition(4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<RelationContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(336);
      expr(0);
      setState(337);
      match(ScimitarParser::REL_OP);
      setState(338);
      expr(0);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<BooleanLiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(340);
      match(ScimitarParser::BOOL_LITERAL);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<BooleanIdentifierContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(341);
      match(ScimitarParser::IDENTIFIER);
      break;
    }

    }
    _ctx->stop = _input->LT(-1);
    setState(349);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<BooleanOpContext>(_tracker.createInstance<ConditionContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleCondition);
        setState(344);

        if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
        setState(345);
        match(ScimitarParser::BOOL_OP);
        setState(346);
        condition(6); 
      }
      setState(351);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- EndContext ------------------------------------------------------------------

ScimitarParser::EndContext::EndContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::EndContext::END() {
  return getToken(ScimitarParser::END, 0);
}


size_t ScimitarParser::EndContext::getRuleIndex() const {
  return ScimitarParser::RuleEnd;
}


antlrcpp::Any ScimitarParser::EndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitEnd(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::EndContext* ScimitarParser::end() {
  EndContext *_localctx = _tracker.createInstance<EndContext>(_ctx, getState());
  enterRule(_localctx, 46, ScimitarParser::RuleEnd);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(352);
    match(ScimitarParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserFunctionContext ------------------------------------------------------------------

ScimitarParser::UserFunctionContext::UserFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::UserFunctionContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::UserFunctionArgListContext* ScimitarParser::UserFunctionContext::userFunctionArgList() {
  return getRuleContext<ScimitarParser::UserFunctionArgListContext>(0);
}

std::vector<ScimitarParser::UserFunctionStmtContext *> ScimitarParser::UserFunctionContext::userFunctionStmt() {
  return getRuleContexts<ScimitarParser::UserFunctionStmtContext>();
}

ScimitarParser::UserFunctionStmtContext* ScimitarParser::UserFunctionContext::userFunctionStmt(size_t i) {
  return getRuleContext<ScimitarParser::UserFunctionStmtContext>(i);
}


size_t ScimitarParser::UserFunctionContext::getRuleIndex() const {
  return ScimitarParser::RuleUserFunction;
}


antlrcpp::Any ScimitarParser::UserFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunction(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::UserFunctionContext* ScimitarParser::userFunction() {
  UserFunctionContext *_localctx = _tracker.createInstance<UserFunctionContext>(_ctx, getState());
  enterRule(_localctx, 48, ScimitarParser::RuleUserFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(354);
    match(ScimitarParser::T__12);
    setState(355);
    match(ScimitarParser::IDENTIFIER);
    setState(356);
    match(ScimitarParser::T__10);
    setState(358);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::TYPE

    || _la == ScimitarParser::WHITESPACE) {
      setState(357);
      userFunctionArgList();
    }
    setState(360);
    match(ScimitarParser::T__11);
    setState(361);
    match(ScimitarParser::T__0);
    setState(365);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ScimitarParser::RETURN)
      | (1ULL << ScimitarParser::TYPE)
      | (1ULL << ScimitarParser::IF)
      | (1ULL << ScimitarParser::FOR)
      | (1ULL << ScimitarParser::WHILE)
      | (1ULL << ScimitarParser::CONTINUE)
      | (1ULL << ScimitarParser::BREAK)
      | (1ULL << ScimitarParser::IDENTIFIER))) != 0)) {
      setState(362);
      userFunctionStmt();
      setState(367);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(368);
    match(ScimitarParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserFunctionArgListContext ------------------------------------------------------------------

ScimitarParser::UserFunctionArgListContext::UserFunctionArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ScimitarParser::UserFunctionArgumentContext *> ScimitarParser::UserFunctionArgListContext::userFunctionArgument() {
  return getRuleContexts<ScimitarParser::UserFunctionArgumentContext>();
}

ScimitarParser::UserFunctionArgumentContext* ScimitarParser::UserFunctionArgListContext::userFunctionArgument(size_t i) {
  return getRuleContext<ScimitarParser::UserFunctionArgumentContext>(i);
}

std::vector<tree::TerminalNode *> ScimitarParser::UserFunctionArgListContext::WHITESPACE() {
  return getTokens(ScimitarParser::WHITESPACE);
}

tree::TerminalNode* ScimitarParser::UserFunctionArgListContext::WHITESPACE(size_t i) {
  return getToken(ScimitarParser::WHITESPACE, i);
}


size_t ScimitarParser::UserFunctionArgListContext::getRuleIndex() const {
  return ScimitarParser::RuleUserFunctionArgList;
}


antlrcpp::Any ScimitarParser::UserFunctionArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionArgList(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::UserFunctionArgListContext* ScimitarParser::userFunctionArgList() {
  UserFunctionArgListContext *_localctx = _tracker.createInstance<UserFunctionArgListContext>(_ctx, getState());
  enterRule(_localctx, 50, ScimitarParser::RuleUserFunctionArgList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(383);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(371);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ScimitarParser::WHITESPACE) {
          setState(370);
          match(ScimitarParser::WHITESPACE);
        }
        setState(373);
        userFunctionArgument();
        setState(375);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ScimitarParser::WHITESPACE) {
          setState(374);
          match(ScimitarParser::WHITESPACE);
        }
        setState(377);
        match(ScimitarParser::T__6);
        setState(379);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx)) {
        case 1: {
          setState(378);
          match(ScimitarParser::WHITESPACE);
          break;
        }

        } 
      }
      setState(385);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 41, _ctx);
    }
    setState(387);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::WHITESPACE) {
      setState(386);
      match(ScimitarParser::WHITESPACE);
    }
    setState(389);
    userFunctionArgument();
    setState(391);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::WHITESPACE) {
      setState(390);
      match(ScimitarParser::WHITESPACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserFunctionPassedArgListContext ------------------------------------------------------------------

ScimitarParser::UserFunctionPassedArgListContext::UserFunctionPassedArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ScimitarParser::GenericExpressionContext *> ScimitarParser::UserFunctionPassedArgListContext::genericExpression() {
  return getRuleContexts<ScimitarParser::GenericExpressionContext>();
}

ScimitarParser::GenericExpressionContext* ScimitarParser::UserFunctionPassedArgListContext::genericExpression(size_t i) {
  return getRuleContext<ScimitarParser::GenericExpressionContext>(i);
}

std::vector<tree::TerminalNode *> ScimitarParser::UserFunctionPassedArgListContext::WHITESPACE() {
  return getTokens(ScimitarParser::WHITESPACE);
}

tree::TerminalNode* ScimitarParser::UserFunctionPassedArgListContext::WHITESPACE(size_t i) {
  return getToken(ScimitarParser::WHITESPACE, i);
}


size_t ScimitarParser::UserFunctionPassedArgListContext::getRuleIndex() const {
  return ScimitarParser::RuleUserFunctionPassedArgList;
}


antlrcpp::Any ScimitarParser::UserFunctionPassedArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionPassedArgList(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::UserFunctionPassedArgListContext* ScimitarParser::userFunctionPassedArgList() {
  UserFunctionPassedArgListContext *_localctx = _tracker.createInstance<UserFunctionPassedArgListContext>(_ctx, getState());
  enterRule(_localctx, 52, ScimitarParser::RuleUserFunctionPassedArgList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(406);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(394);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ScimitarParser::WHITESPACE) {
          setState(393);
          match(ScimitarParser::WHITESPACE);
        }
        setState(396);
        genericExpression();
        setState(398);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == ScimitarParser::WHITESPACE) {
          setState(397);
          match(ScimitarParser::WHITESPACE);
        }
        setState(400);
        match(ScimitarParser::T__6);
        setState(402);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 46, _ctx)) {
        case 1: {
          setState(401);
          match(ScimitarParser::WHITESPACE);
          break;
        }

        } 
      }
      setState(408);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 47, _ctx);
    }
    setState(410);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::WHITESPACE) {
      setState(409);
      match(ScimitarParser::WHITESPACE);
    }
    setState(412);
    genericExpression();
    setState(414);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ScimitarParser::WHITESPACE) {
      setState(413);
      match(ScimitarParser::WHITESPACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserFunctionArgumentContext ------------------------------------------------------------------

ScimitarParser::UserFunctionArgumentContext::UserFunctionArgumentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ScimitarParser::UserFunctionArgumentContext::TYPE() {
  return getToken(ScimitarParser::TYPE, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionArgumentContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}


size_t ScimitarParser::UserFunctionArgumentContext::getRuleIndex() const {
  return ScimitarParser::RuleUserFunctionArgument;
}


antlrcpp::Any ScimitarParser::UserFunctionArgumentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionArgument(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::UserFunctionArgumentContext* ScimitarParser::userFunctionArgument() {
  UserFunctionArgumentContext *_localctx = _tracker.createInstance<UserFunctionArgumentContext>(_ctx, getState());
  enterRule(_localctx, 54, ScimitarParser::RuleUserFunctionArgument);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(416);
    match(ScimitarParser::TYPE);
    setState(417);
    match(ScimitarParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserFunctionBlockContext ------------------------------------------------------------------

ScimitarParser::UserFunctionBlockContext::UserFunctionBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ScimitarParser::UserFunctionStmtContext *> ScimitarParser::UserFunctionBlockContext::userFunctionStmt() {
  return getRuleContexts<ScimitarParser::UserFunctionStmtContext>();
}

ScimitarParser::UserFunctionStmtContext* ScimitarParser::UserFunctionBlockContext::userFunctionStmt(size_t i) {
  return getRuleContext<ScimitarParser::UserFunctionStmtContext>(i);
}


size_t ScimitarParser::UserFunctionBlockContext::getRuleIndex() const {
  return ScimitarParser::RuleUserFunctionBlock;
}


antlrcpp::Any ScimitarParser::UserFunctionBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionBlock(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::UserFunctionBlockContext* ScimitarParser::userFunctionBlock() {
  UserFunctionBlockContext *_localctx = _tracker.createInstance<UserFunctionBlockContext>(_ctx, getState());
  enterRule(_localctx, 56, ScimitarParser::RuleUserFunctionBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(422);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << ScimitarParser::RETURN)
      | (1ULL << ScimitarParser::TYPE)
      | (1ULL << ScimitarParser::IF)
      | (1ULL << ScimitarParser::FOR)
      | (1ULL << ScimitarParser::WHILE)
      | (1ULL << ScimitarParser::CONTINUE)
      | (1ULL << ScimitarParser::BREAK)
      | (1ULL << ScimitarParser::IDENTIFIER))) != 0)) {
      setState(419);
      userFunctionStmt();
      setState(424);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GenericExpressionContext ------------------------------------------------------------------

ScimitarParser::GenericExpressionContext::GenericExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ScimitarParser::ExprContext* ScimitarParser::GenericExpressionContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

ScimitarParser::ConditionContext* ScimitarParser::GenericExpressionContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}


size_t ScimitarParser::GenericExpressionContext::getRuleIndex() const {
  return ScimitarParser::RuleGenericExpression;
}


antlrcpp::Any ScimitarParser::GenericExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitGenericExpression(this);
  else
    return visitor->visitChildren(this);
}

ScimitarParser::GenericExpressionContext* ScimitarParser::genericExpression() {
  GenericExpressionContext *_localctx = _tracker.createInstance<GenericExpressionContext>(_ctx, getState());
  enterRule(_localctx, 58, ScimitarParser::RuleGenericExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(427);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 51, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(425);
      expr(0);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(426);
      condition(0);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UserFunctionStmtContext ------------------------------------------------------------------

ScimitarParser::UserFunctionStmtContext::UserFunctionStmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ScimitarParser::UserFunctionStmtContext::getRuleIndex() const {
  return ScimitarParser::RuleUserFunctionStmt;
}

void ScimitarParser::UserFunctionStmtContext::copyFrom(UserFunctionStmtContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UserFunctionListRemoveContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionListRemoveContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionListRemoveContext::REMOVE() {
  return getToken(ScimitarParser::REMOVE, 0);
}

ScimitarParser::ExprContext* ScimitarParser::UserFunctionListRemoveContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

tree::TerminalNode* ScimitarParser::UserFunctionListRemoveContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::UserFunctionListRemoveContext::UserFunctionListRemoveContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionListRemoveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionListRemove(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionConditionalContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionConditionalContext::IF() {
  return getToken(ScimitarParser::IF, 0);
}

ScimitarParser::ConditionContext* ScimitarParser::UserFunctionConditionalContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}

std::vector<ScimitarParser::UserFunctionBlockContext *> ScimitarParser::UserFunctionConditionalContext::userFunctionBlock() {
  return getRuleContexts<ScimitarParser::UserFunctionBlockContext>();
}

ScimitarParser::UserFunctionBlockContext* ScimitarParser::UserFunctionConditionalContext::userFunctionBlock(size_t i) {
  return getRuleContext<ScimitarParser::UserFunctionBlockContext>(i);
}

tree::TerminalNode* ScimitarParser::UserFunctionConditionalContext::ELSE() {
  return getToken(ScimitarParser::ELSE, 0);
}

ScimitarParser::UserFunctionConditionalContext::UserFunctionConditionalContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionConditionalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionConditional(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionWhileLoopContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionWhileLoopContext::WHILE() {
  return getToken(ScimitarParser::WHILE, 0);
}

ScimitarParser::ConditionContext* ScimitarParser::UserFunctionWhileLoopContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}

ScimitarParser::UserFunctionBlockContext* ScimitarParser::UserFunctionWhileLoopContext::userFunctionBlock() {
  return getRuleContext<ScimitarParser::UserFunctionBlockContext>(0);
}

ScimitarParser::UserFunctionWhileLoopContext::UserFunctionWhileLoopContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionWhileLoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionWhileLoop(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionBreakContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionBreakContext::BREAK() {
  return getToken(ScimitarParser::BREAK, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionBreakContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::UserFunctionBreakContext::UserFunctionBreakContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionBreakContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionBreak(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionListAppendContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionListAppendContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionListAppendContext::TYPE() {
  return getToken(ScimitarParser::TYPE, 0);
}

ScimitarParser::GenericExpressionContext* ScimitarParser::UserFunctionListAppendContext::genericExpression() {
  return getRuleContext<ScimitarParser::GenericExpressionContext>(0);
}

tree::TerminalNode* ScimitarParser::UserFunctionListAppendContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::UserFunctionListAppendContext::UserFunctionListAppendContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionListAppendContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionListAppend(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionContinueContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionContinueContext::CONTINUE() {
  return getToken(ScimitarParser::CONTINUE, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionContinueContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::UserFunctionContinueContext::UserFunctionContinueContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionContinueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionContinue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionAssignmentContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionAssignmentContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

ScimitarParser::GenericExpressionContext* ScimitarParser::UserFunctionAssignmentContext::genericExpression() {
  return getRuleContext<ScimitarParser::GenericExpressionContext>(0);
}

tree::TerminalNode* ScimitarParser::UserFunctionAssignmentContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::UserFunctionAssignmentContext::UserFunctionAssignmentContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionAssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionAssignment(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionReturnContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionReturnContext::RETURN() {
  return getToken(ScimitarParser::RETURN, 0);
}

ScimitarParser::ExprContext* ScimitarParser::UserFunctionReturnContext::expr() {
  return getRuleContext<ScimitarParser::ExprContext>(0);
}

tree::TerminalNode* ScimitarParser::UserFunctionReturnContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::UserFunctionReturnContext::UserFunctionReturnContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionReturn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionForLoopContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionForLoopContext::FOR() {
  return getToken(ScimitarParser::FOR, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionForLoopContext::TYPE() {
  return getToken(ScimitarParser::TYPE, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionForLoopContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

std::vector<ScimitarParser::ExprContext *> ScimitarParser::UserFunctionForLoopContext::expr() {
  return getRuleContexts<ScimitarParser::ExprContext>();
}

ScimitarParser::ExprContext* ScimitarParser::UserFunctionForLoopContext::expr(size_t i) {
  return getRuleContext<ScimitarParser::ExprContext>(i);
}

ScimitarParser::ConditionContext* ScimitarParser::UserFunctionForLoopContext::condition() {
  return getRuleContext<ScimitarParser::ConditionContext>(0);
}

ScimitarParser::UserFunctionBlockContext* ScimitarParser::UserFunctionForLoopContext::userFunctionBlock() {
  return getRuleContext<ScimitarParser::UserFunctionBlockContext>(0);
}

ScimitarParser::UserFunctionForLoopContext::UserFunctionForLoopContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionForLoopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionForLoop(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserFunctionDeclarationContext ------------------------------------------------------------------

tree::TerminalNode* ScimitarParser::UserFunctionDeclarationContext::TYPE() {
  return getToken(ScimitarParser::TYPE, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionDeclarationContext::IDENTIFIER() {
  return getToken(ScimitarParser::IDENTIFIER, 0);
}

tree::TerminalNode* ScimitarParser::UserFunctionDeclarationContext::NEWLINE() {
  return getToken(ScimitarParser::NEWLINE, 0);
}

ScimitarParser::GenericExpressionContext* ScimitarParser::UserFunctionDeclarationContext::genericExpression() {
  return getRuleContext<ScimitarParser::GenericExpressionContext>(0);
}

ScimitarParser::UserFunctionDeclarationContext::UserFunctionDeclarationContext(UserFunctionStmtContext *ctx) { copyFrom(ctx); }


antlrcpp::Any ScimitarParser::UserFunctionDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ScimitarVisitor*>(visitor))
    return parserVisitor->visitUserFunctionDeclaration(this);
  else
    return visitor->visitChildren(this);
}
ScimitarParser::UserFunctionStmtContext* ScimitarParser::userFunctionStmt() {
  UserFunctionStmtContext *_localctx = _tracker.createInstance<UserFunctionStmtContext>(_ctx, getState());
  enterRule(_localctx, 60, ScimitarParser::RuleUserFunctionStmt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(501);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 54, _ctx)) {
    case 1: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionDeclarationContext>(_localctx));
      enterOuterAlt(_localctx, 1);
      setState(429);
      match(ScimitarParser::TYPE);
      setState(430);
      match(ScimitarParser::IDENTIFIER);
      setState(433);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ScimitarParser::T__3) {
        setState(431);
        match(ScimitarParser::T__3);
        setState(432);
        genericExpression();
      }
      setState(435);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 2: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionAssignmentContext>(_localctx));
      enterOuterAlt(_localctx, 2);
      setState(436);
      match(ScimitarParser::IDENTIFIER);
      setState(437);
      match(ScimitarParser::T__3);
      setState(438);
      genericExpression();
      setState(439);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 3: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionListAppendContext>(_localctx));
      enterOuterAlt(_localctx, 3);
      setState(441);
      match(ScimitarParser::IDENTIFIER);
      setState(442);
      match(ScimitarParser::T__4);
      setState(443);
      match(ScimitarParser::T__13);
      setState(444);
      match(ScimitarParser::TYPE);
      setState(445);
      match(ScimitarParser::T__10);
      setState(446);
      genericExpression();
      setState(447);
      match(ScimitarParser::T__11);
      setState(448);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 4: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionListRemoveContext>(_localctx));
      enterOuterAlt(_localctx, 4);
      setState(450);
      match(ScimitarParser::IDENTIFIER);
      setState(451);
      match(ScimitarParser::T__4);
      setState(452);
      match(ScimitarParser::REMOVE);
      setState(453);
      expr(0);
      setState(454);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 5: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionConditionalContext>(_localctx));
      enterOuterAlt(_localctx, 5);
      setState(456);
      match(ScimitarParser::IF);
      setState(457);
      match(ScimitarParser::T__10);
      setState(458);
      condition(0);
      setState(459);
      match(ScimitarParser::T__11);
      setState(460);
      match(ScimitarParser::T__0);
      setState(461);
      userFunctionBlock();
      setState(462);
      match(ScimitarParser::T__1);
      setState(468);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == ScimitarParser::ELSE) {
        setState(463);
        match(ScimitarParser::ELSE);
        setState(464);
        match(ScimitarParser::T__0);
        setState(465);
        userFunctionBlock();
        setState(466);
        match(ScimitarParser::T__1);
      }
      break;
    }

    case 6: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionReturnContext>(_localctx));
      enterOuterAlt(_localctx, 6);
      setState(470);
      match(ScimitarParser::RETURN);
      setState(471);
      expr(0);
      setState(472);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 7: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionForLoopContext>(_localctx));
      enterOuterAlt(_localctx, 7);
      setState(474);
      match(ScimitarParser::FOR);
      setState(475);
      match(ScimitarParser::T__10);
      setState(476);
      match(ScimitarParser::TYPE);
      setState(477);
      match(ScimitarParser::IDENTIFIER);
      setState(478);
      match(ScimitarParser::T__3);
      setState(479);
      expr(0);
      setState(480);
      match(ScimitarParser::T__6);
      setState(481);
      condition(0);
      setState(482);
      match(ScimitarParser::T__6);
      setState(483);
      expr(0);
      setState(484);
      match(ScimitarParser::T__11);
      setState(485);
      match(ScimitarParser::T__0);
      setState(486);
      userFunctionBlock();
      setState(487);
      match(ScimitarParser::T__1);
      break;
    }

    case 8: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionWhileLoopContext>(_localctx));
      enterOuterAlt(_localctx, 8);
      setState(489);
      match(ScimitarParser::WHILE);
      setState(490);
      match(ScimitarParser::T__10);
      setState(491);
      condition(0);
      setState(492);
      match(ScimitarParser::T__11);
      setState(493);
      match(ScimitarParser::T__0);
      setState(494);
      userFunctionBlock();
      setState(495);
      match(ScimitarParser::T__1);
      break;
    }

    case 9: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionContinueContext>(_localctx));
      enterOuterAlt(_localctx, 9);
      setState(497);
      match(ScimitarParser::CONTINUE);
      setState(498);
      match(ScimitarParser::NEWLINE);
      break;
    }

    case 10: {
      _localctx = dynamic_cast<UserFunctionStmtContext *>(_tracker.createInstance<ScimitarParser::UserFunctionBreakContext>(_localctx));
      enterOuterAlt(_localctx, 10);
      setState(499);
      match(ScimitarParser::BREAK);
      setState(500);
      match(ScimitarParser::NEWLINE);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool ScimitarParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 18: return exprSempred(dynamic_cast<ExprContext *>(context), predicateIndex);
    case 22: return conditionSempred(dynamic_cast<ConditionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ScimitarParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 9);
    case 1: return precpred(_ctx, 8);
    case 2: return precpred(_ctx, 7);
    case 3: return precpred(_ctx, 6);
    case 4: return precpred(_ctx, 5);
    case 5: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

bool ScimitarParser::conditionSempred(ConditionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 6: return precpred(_ctx, 5);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> ScimitarParser::_decisionToDFA;
atn::PredictionContextCache ScimitarParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN ScimitarParser::_atn;
std::vector<uint16_t> ScimitarParser::_serializedATN;

std::vector<std::string> ScimitarParser::_ruleNames = {
  "root", "action", "param", "function", "setParam", "setOption", "setFunction", 
  "group", "ungroup", "system", "parameterValue", "range", "list", "listElement", 
  "option", "optionValue", "scriptOption", "systemOption", "expr", "run", 
  "block", "loopStmt", "condition", "end", "userFunction", "userFunctionArgList", 
  "userFunctionPassedArgList", "userFunctionArgument", "userFunctionBlock", 
  "genericExpression", "userFunctionStmt"
};

std::vector<std::string> ScimitarParser::_literalNames = {
  "", "'{'", "'}'", "'function'", "'='", "':'", "'['", "','", "']'", "'hide'", 
  "'.'", "'('", "')'", "'def'", "'append'", "';'", "", "'option'", "'end'", 
  "'param'", "'set'", "'group'", "'ungroup'", "'run'", "'return'", "", "'if'", 
  "'for'", "'while'", "'continue'", "'break'", "'else'", "'system'", "", 
  "", "'not'", "'remove'", "", "'+'", "'-'", "'*'", "'/'", "'**'"
};

std::vector<std::string> ScimitarParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "NEWLINE", 
  "OPT", "OPTION", "END", "PARAM", "SET", "GROUP", "UNGROUP", "RUN", "RETURN", 
  "TYPE", "IF", "FOR", "WHILE", "CONTINUE", "BREAK", "ELSE", "SYSTEM", "REL_OP", 
  "BOOL_OP", "NEG_OP", "REMOVE", "BOOL_LITERAL", "ADD", "SUB", "MUL", "DIV", 
  "POW", "NUMERIC", "FORMAT", "IDENTIFIER", "STRING", "COMMENT", "BLOCK_COMMENT", 
  "WHITESPACE"
};

dfa::Vocabulary ScimitarParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> ScimitarParser::_tokenNames;

ScimitarParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x33, 0x1fa, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x3, 0x2, 0x7, 0x2, 0x42, 0xa, 
    0x2, 0xc, 0x2, 0xe, 0x2, 0x45, 0xb, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 
    0x50, 0xa, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 
    0x3, 0x57, 0xa, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x7, 0x4, 0x5f, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x62, 0xb, 0x4, 
    0x3, 0x4, 0x5, 0x4, 0x65, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x7, 0x5, 0x6d, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 
    0x70, 0xb, 0x5, 0x3, 0x5, 0x5, 0x5, 0x73, 0xa, 0x5, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x6, 0x6, 0x7a, 0xa, 0x6, 0xd, 0x6, 0xe, 
    0x6, 0x7b, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x6, 0x7, 0x86, 0xa, 0x7, 0xd, 0x7, 0xe, 0x7, 0x87, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x6, 0x8, 0x92, 0xa, 0x8, 0xd, 0x8, 0xe, 0x8, 0x93, 0x6, 0x8, 
    0x96, 0xa, 0x8, 0xd, 0x8, 0xe, 0x8, 0x97, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 
    0x3, 0x9, 0x6, 0x9, 0x9e, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 0x9f, 0x3, 0xa, 
    0x3, 0xa, 0x6, 0xa, 0xa4, 0xa, 0xa, 0xd, 0xa, 0xe, 0xa, 0xa5, 0x3, 0xb, 
    0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x6, 0xb, 0xac, 0xa, 0xb, 0xd, 0xb, 0xe, 
    0xb, 0xad, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0xb4, 0xa, 
    0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xe, 0x3, 0xe, 0x5, 0xe, 0xbe, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 
    0xc2, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xc6, 0xa, 0xe, 0x7, 0xe, 
    0xc8, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 0xcb, 0xb, 0xe, 0x3, 0xe, 0x5, 0xe, 
    0xce, 0xa, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0xd2, 0xa, 0xe, 0x3, 0xe, 
    0x3, 0xe, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0xd8, 0xa, 0xf, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0xde, 0xa, 0x10, 0x3, 0x11, 0x3, 
    0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0xe5, 0xa, 0x11, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xeb, 0xa, 0x12, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0xf9, 
    0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0xfe, 0xa, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 
    0x14, 0x7, 0x14, 0x114, 0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x117, 0xb, 
    0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 0x7, 0x15, 0x11c, 0xa, 0x15, 
    0xc, 0x15, 0xe, 0x15, 0x11f, 0xb, 0x15, 0x3, 0x15, 0x3, 0x15, 0x3, 0x16, 
    0x7, 0x16, 0x124, 0xa, 0x16, 0xc, 0x16, 0xe, 0x16, 0x127, 0xb, 0x16, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x7, 
    0x17, 0x12f, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0x132, 0xb, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 
    0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x14a, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 
    0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x159, 
    0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x7, 0x18, 0x15e, 0xa, 0x18, 
    0xc, 0x18, 0xe, 0x18, 0x161, 0xb, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x169, 0xa, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x3, 0x1a, 0x7, 0x1a, 0x16e, 0xa, 0x1a, 0xc, 0x1a, 0xe, 0x1a, 
    0x171, 0xb, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x5, 0x1b, 0x176, 
    0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x17a, 0xa, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x5, 0x1b, 0x17e, 0xa, 0x1b, 0x7, 0x1b, 0x180, 0xa, 0x1b, 
    0xc, 0x1b, 0xe, 0x1b, 0x183, 0xb, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x186, 
    0xa, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0x18a, 0xa, 0x1b, 0x3, 0x1c, 
    0x5, 0x1c, 0x18d, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x191, 
    0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x195, 0xa, 0x1c, 0x7, 0x1c, 
    0x197, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 0x19a, 0xb, 0x1c, 0x3, 0x1c, 
    0x5, 0x1c, 0x19d, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x1a1, 
    0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1e, 0x7, 0x1e, 0x1a7, 
    0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x1aa, 0xb, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 
    0x5, 0x1f, 0x1ae, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x5, 0x20, 0x1b4, 0xa, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x1d7, 0xa, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 
    0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 0x20, 0x1f8, 0xa, 0x20, 
    0x3, 0x20, 0x2, 0x4, 0x26, 0x2e, 0x21, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 
    0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 
    0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 
    0x3e, 0x2, 0x3, 0x4, 0x2, 0x2d, 0x2d, 0x30, 0x30, 0x2, 0x234, 0x2, 0x43, 
    0x3, 0x2, 0x2, 0x2, 0x4, 0x56, 0x3, 0x2, 0x2, 0x2, 0x6, 0x58, 0x3, 0x2, 
    0x2, 0x2, 0x8, 0x66, 0x3, 0x2, 0x2, 0x2, 0xa, 0x74, 0x3, 0x2, 0x2, 0x2, 
    0xc, 0x7f, 0x3, 0x2, 0x2, 0x2, 0xe, 0x89, 0x3, 0x2, 0x2, 0x2, 0x10, 
    0x9b, 0x3, 0x2, 0x2, 0x2, 0x12, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x14, 0xa7, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb5, 0x3, 
    0x2, 0x2, 0x2, 0x1a, 0xbb, 0x3, 0x2, 0x2, 0x2, 0x1c, 0xd7, 0x3, 0x2, 
    0x2, 0x2, 0x1e, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x20, 0xe4, 0x3, 0x2, 0x2, 
    0x2, 0x22, 0xea, 0x3, 0x2, 0x2, 0x2, 0x24, 0xec, 0x3, 0x2, 0x2, 0x2, 
    0x26, 0xfd, 0x3, 0x2, 0x2, 0x2, 0x28, 0x118, 0x3, 0x2, 0x2, 0x2, 0x2a, 
    0x125, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x149, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x158, 
    0x3, 0x2, 0x2, 0x2, 0x30, 0x162, 0x3, 0x2, 0x2, 0x2, 0x32, 0x164, 0x3, 
    0x2, 0x2, 0x2, 0x34, 0x181, 0x3, 0x2, 0x2, 0x2, 0x36, 0x198, 0x3, 0x2, 
    0x2, 0x2, 0x38, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x1a8, 0x3, 0x2, 0x2, 
    0x2, 0x3c, 0x1ad, 0x3, 0x2, 0x2, 0x2, 0x3e, 0x1f7, 0x3, 0x2, 0x2, 0x2, 
    0x40, 0x42, 0x5, 0x4, 0x3, 0x2, 0x41, 0x40, 0x3, 0x2, 0x2, 0x2, 0x42, 
    0x45, 0x3, 0x2, 0x2, 0x2, 0x43, 0x41, 0x3, 0x2, 0x2, 0x2, 0x43, 0x44, 
    0x3, 0x2, 0x2, 0x2, 0x44, 0x3, 0x3, 0x2, 0x2, 0x2, 0x45, 0x43, 0x3, 
    0x2, 0x2, 0x2, 0x46, 0x50, 0x5, 0x6, 0x4, 0x2, 0x47, 0x50, 0x5, 0x8, 
    0x5, 0x2, 0x48, 0x50, 0x5, 0xa, 0x6, 0x2, 0x49, 0x50, 0x5, 0xc, 0x7, 
    0x2, 0x4a, 0x50, 0x5, 0xe, 0x8, 0x2, 0x4b, 0x50, 0x5, 0x10, 0x9, 0x2, 
    0x4c, 0x50, 0x5, 0x12, 0xa, 0x2, 0x4d, 0x50, 0x5, 0x30, 0x19, 0x2, 0x4e, 
    0x50, 0x5, 0x14, 0xb, 0x2, 0x4f, 0x46, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x47, 
    0x3, 0x2, 0x2, 0x2, 0x4f, 0x48, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x49, 0x3, 
    0x2, 0x2, 0x2, 0x4f, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4b, 0x3, 0x2, 
    0x2, 0x2, 0x4f, 0x4c, 0x3, 0x2, 0x2, 0x2, 0x4f, 0x4d, 0x3, 0x2, 0x2, 
    0x2, 0x4f, 0x4e, 0x3, 0x2, 0x2, 0x2, 0x50, 0x51, 0x3, 0x2, 0x2, 0x2, 
    0x51, 0x52, 0x7, 0x11, 0x2, 0x2, 0x52, 0x57, 0x3, 0x2, 0x2, 0x2, 0x53, 
    0x57, 0x5, 0x28, 0x15, 0x2, 0x54, 0x57, 0x5, 0x32, 0x1a, 0x2, 0x55, 
    0x57, 0x7, 0x31, 0x2, 0x2, 0x56, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x56, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x56, 0x54, 0x3, 0x2, 0x2, 0x2, 0x56, 0x55, 0x3, 
    0x2, 0x2, 0x2, 0x57, 0x5, 0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x7, 0x15, 
    0x2, 0x2, 0x59, 0x5a, 0x7, 0x1b, 0x2, 0x2, 0x5a, 0x5b, 0x7, 0x2f, 0x2, 
    0x2, 0x5b, 0x64, 0x5, 0x16, 0xc, 0x2, 0x5c, 0x60, 0x7, 0x3, 0x2, 0x2, 
    0x5d, 0x5f, 0x5, 0x1e, 0x10, 0x2, 0x5e, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x5f, 
    0x62, 0x3, 0x2, 0x2, 0x2, 0x60, 0x5e, 0x3, 0x2, 0x2, 0x2, 0x60, 0x61, 
    0x3, 0x2, 0x2, 0x2, 0x61, 0x63, 0x3, 0x2, 0x2, 0x2, 0x62, 0x60, 0x3, 
    0x2, 0x2, 0x2, 0x63, 0x65, 0x7, 0x4, 0x2, 0x2, 0x64, 0x5c, 0x3, 0x2, 
    0x2, 0x2, 0x64, 0x65, 0x3, 0x2, 0x2, 0x2, 0x65, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0x66, 0x67, 0x7, 0x15, 0x2, 0x2, 0x67, 0x68, 0x7, 0x5, 0x2, 0x2, 
    0x68, 0x69, 0x7, 0x2f, 0x2, 0x2, 0x69, 0x72, 0x5, 0x26, 0x14, 0x2, 0x6a, 
    0x6e, 0x7, 0x3, 0x2, 0x2, 0x6b, 0x6d, 0x5, 0x1e, 0x10, 0x2, 0x6c, 0x6b, 
    0x3, 0x2, 0x2, 0x2, 0x6d, 0x70, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6c, 0x3, 
    0x2, 0x2, 0x2, 0x6e, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x71, 0x3, 0x2, 
    0x2, 0x2, 0x70, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x71, 0x73, 0x7, 0x4, 0x2, 
    0x2, 0x72, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x72, 0x73, 0x3, 0x2, 0x2, 0x2, 
    0x73, 0x9, 0x3, 0x2, 0x2, 0x2, 0x74, 0x75, 0x7, 0x16, 0x2, 0x2, 0x75, 
    0x76, 0x7, 0x15, 0x2, 0x2, 0x76, 0x77, 0x7, 0x2f, 0x2, 0x2, 0x77, 0x79, 
    0x7, 0x3, 0x2, 0x2, 0x78, 0x7a, 0x5, 0x1e, 0x10, 0x2, 0x79, 0x78, 0x3, 
    0x2, 0x2, 0x2, 0x7a, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x79, 0x3, 0x2, 
    0x2, 0x2, 0x7b, 0x7c, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x3, 0x2, 0x2, 
    0x2, 0x7d, 0x7e, 0x7, 0x4, 0x2, 0x2, 0x7e, 0xb, 0x3, 0x2, 0x2, 0x2, 
    0x7f, 0x80, 0x7, 0x16, 0x2, 0x2, 0x80, 0x85, 0x7, 0x13, 0x2, 0x2, 0x81, 
    0x82, 0x5, 0x22, 0x12, 0x2, 0x82, 0x83, 0x7, 0x6, 0x2, 0x2, 0x83, 0x84, 
    0x7, 0x30, 0x2, 0x2, 0x84, 0x86, 0x3, 0x2, 0x2, 0x2, 0x85, 0x81, 0x3, 
    0x2, 0x2, 0x2, 0x86, 0x87, 0x3, 0x2, 0x2, 0x2, 0x87, 0x85, 0x3, 0x2, 
    0x2, 0x2, 0x87, 0x88, 0x3, 0x2, 0x2, 0x2, 0x88, 0xd, 0x3, 0x2, 0x2, 
    0x2, 0x89, 0x8a, 0x7, 0x16, 0x2, 0x2, 0x8a, 0x8b, 0x7, 0x15, 0x2, 0x2, 
    0x8b, 0x8c, 0x7, 0x2f, 0x2, 0x2, 0x8c, 0x95, 0x7, 0x3, 0x2, 0x2, 0x8d, 
    0x8e, 0x7, 0x5, 0x2, 0x2, 0x8e, 0x8f, 0x7, 0x6, 0x2, 0x2, 0x8f, 0x96, 
    0x5, 0x26, 0x14, 0x2, 0x90, 0x92, 0x5, 0x1e, 0x10, 0x2, 0x91, 0x90, 
    0x3, 0x2, 0x2, 0x2, 0x92, 0x93, 0x3, 0x2, 0x2, 0x2, 0x93, 0x91, 0x3, 
    0x2, 0x2, 0x2, 0x93, 0x94, 0x3, 0x2, 0x2, 0x2, 0x94, 0x96, 0x3, 0x2, 
    0x2, 0x2, 0x95, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x95, 0x91, 0x3, 0x2, 0x2, 
    0x2, 0x96, 0x97, 0x3, 0x2, 0x2, 0x2, 0x97, 0x95, 0x3, 0x2, 0x2, 0x2, 
    0x97, 0x98, 0x3, 0x2, 0x2, 0x2, 0x98, 0x99, 0x3, 0x2, 0x2, 0x2, 0x99, 
    0x9a, 0x7, 0x4, 0x2, 0x2, 0x9a, 0xf, 0x3, 0x2, 0x2, 0x2, 0x9b, 0x9d, 
    0x7, 0x17, 0x2, 0x2, 0x9c, 0x9e, 0x7, 0x2f, 0x2, 0x2, 0x9d, 0x9c, 0x3, 
    0x2, 0x2, 0x2, 0x9e, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x9d, 0x3, 0x2, 
    0x2, 0x2, 0x9f, 0xa0, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x11, 0x3, 0x2, 0x2, 
    0x2, 0xa1, 0xa3, 0x7, 0x18, 0x2, 0x2, 0xa2, 0xa4, 0x7, 0x2f, 0x2, 0x2, 
    0xa3, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x3, 0x2, 0x2, 0x2, 0xa5, 
    0xa3, 0x3, 0x2, 0x2, 0x2, 0xa5, 0xa6, 0x3, 0x2, 0x2, 0x2, 0xa6, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0xa7, 0xab, 0x7, 0x22, 0x2, 0x2, 0xa8, 0xa9, 0x7, 
    0x2f, 0x2, 0x2, 0xa9, 0xaa, 0x7, 0x6, 0x2, 0x2, 0xaa, 0xac, 0x5, 0x24, 
    0x13, 0x2, 0xab, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xac, 0xad, 0x3, 0x2, 0x2, 
    0x2, 0xad, 0xab, 0x3, 0x2, 0x2, 0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 0x2, 
    0xae, 0x15, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xb4, 0x5, 0x26, 0x14, 0x2, 0xb0, 
    0xb4, 0x5, 0x18, 0xd, 0x2, 0xb1, 0xb4, 0x5, 0x1a, 0xe, 0x2, 0xb2, 0xb4, 
    0x7, 0x30, 0x2, 0x2, 0xb3, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb0, 0x3, 
    0x2, 0x2, 0x2, 0xb3, 0xb1, 0x3, 0x2, 0x2, 0x2, 0xb3, 0xb2, 0x3, 0x2, 
    0x2, 0x2, 0xb4, 0x17, 0x3, 0x2, 0x2, 0x2, 0xb5, 0xb6, 0x5, 0x26, 0x14, 
    0x2, 0xb6, 0xb7, 0x7, 0x7, 0x2, 0x2, 0xb7, 0xb8, 0x5, 0x26, 0x14, 0x2, 
    0xb8, 0xb9, 0x7, 0x7, 0x2, 0x2, 0xb9, 0xba, 0x5, 0x26, 0x14, 0x2, 0xba, 
    0x19, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xc9, 0x7, 0x8, 0x2, 0x2, 0xbc, 0xbe, 
    0x7, 0x33, 0x2, 0x2, 0xbd, 0xbc, 0x3, 0x2, 0x2, 0x2, 0xbd, 0xbe, 0x3, 
    0x2, 0x2, 0x2, 0xbe, 0xbf, 0x3, 0x2, 0x2, 0x2, 0xbf, 0xc1, 0x5, 0x1c, 
    0xf, 0x2, 0xc0, 0xc2, 0x7, 0x33, 0x2, 0x2, 0xc1, 0xc0, 0x3, 0x2, 0x2, 
    0x2, 0xc1, 0xc2, 0x3, 0x2, 0x2, 0x2, 0xc2, 0xc3, 0x3, 0x2, 0x2, 0x2, 
    0xc3, 0xc5, 0x7, 0x9, 0x2, 0x2, 0xc4, 0xc6, 0x7, 0x33, 0x2, 0x2, 0xc5, 
    0xc4, 0x3, 0x2, 0x2, 0x2, 0xc5, 0xc6, 0x3, 0x2, 0x2, 0x2, 0xc6, 0xc8, 
    0x3, 0x2, 0x2, 0x2, 0xc7, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xc8, 0xcb, 0x3, 
    0x2, 0x2, 0x2, 0xc9, 0xc7, 0x3, 0x2, 0x2, 0x2, 0xc9, 0xca, 0x3, 0x2, 
    0x2, 0x2, 0xca, 0xcd, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xc9, 0x3, 0x2, 0x2, 
    0x2, 0xcc, 0xce, 0x7, 0x33, 0x2, 0x2, 0xcd, 0xcc, 0x3, 0x2, 0x2, 0x2, 
    0xcd, 0xce, 0x3, 0x2, 0x2, 0x2, 0xce, 0xcf, 0x3, 0x2, 0x2, 0x2, 0xcf, 
    0xd1, 0x5, 0x1c, 0xf, 0x2, 0xd0, 0xd2, 0x7, 0x33, 0x2, 0x2, 0xd1, 0xd0, 
    0x3, 0x2, 0x2, 0x2, 0xd1, 0xd2, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 0x3, 
    0x2, 0x2, 0x2, 0xd3, 0xd4, 0x7, 0xa, 0x2, 0x2, 0xd4, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0xd5, 0xd8, 0x5, 0x26, 0x14, 0x2, 0xd6, 0xd8, 0x5, 0x18, 0xd, 
    0x2, 0xd7, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd7, 0xd6, 0x3, 0x2, 0x2, 0x2, 
    0xd8, 0x1d, 0x3, 0x2, 0x2, 0x2, 0xd9, 0xda, 0x7, 0x12, 0x2, 0x2, 0xda, 
    0xdb, 0x7, 0x6, 0x2, 0x2, 0xdb, 0xde, 0x5, 0x20, 0x11, 0x2, 0xdc, 0xde, 
    0x7, 0xb, 0x2, 0x2, 0xdd, 0xd9, 0x3, 0x2, 0x2, 0x2, 0xdd, 0xdc, 0x3, 
    0x2, 0x2, 0x2, 0xde, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xdf, 0xe5, 0x5, 0x26, 
    0x14, 0x2, 0xe0, 0xe5, 0x5, 0x18, 0xd, 0x2, 0xe1, 0xe5, 0x5, 0x1a, 0xe, 
    0x2, 0xe2, 0xe5, 0x7, 0x2e, 0x2, 0x2, 0xe3, 0xe5, 0x7, 0x30, 0x2, 0x2, 
    0xe4, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe0, 0x3, 0x2, 0x2, 0x2, 0xe4, 
    0xe1, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe2, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe3, 
    0x3, 0x2, 0x2, 0x2, 0xe5, 0x21, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xeb, 0x7, 
    0x2f, 0x2, 0x2, 0xe7, 0xe8, 0x7, 0x2f, 0x2, 0x2, 0xe8, 0xe9, 0x7, 0xc, 
    0x2, 0x2, 0xe9, 0xeb, 0x7, 0x2f, 0x2, 0x2, 0xea, 0xe6, 0x3, 0x2, 0x2, 
    0x2, 0xea, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xeb, 0x23, 0x3, 0x2, 0x2, 0x2, 
    0xec, 0xed, 0x9, 0x2, 0x2, 0x2, 0xed, 0x25, 0x3, 0x2, 0x2, 0x2, 0xee, 
    0xef, 0x8, 0x14, 0x1, 0x2, 0xef, 0xf0, 0x7, 0xd, 0x2, 0x2, 0xf0, 0xf1, 
    0x5, 0x26, 0x14, 0x2, 0xf1, 0xf2, 0x7, 0xe, 0x2, 0x2, 0xf2, 0xfe, 0x3, 
    0x2, 0x2, 0x2, 0xf3, 0xf4, 0x7, 0x29, 0x2, 0x2, 0xf4, 0xfe, 0x5, 0x26, 
    0x14, 0x6, 0xf5, 0xf6, 0x7, 0x2f, 0x2, 0x2, 0xf6, 0xf8, 0x7, 0xd, 0x2, 
    0x2, 0xf7, 0xf9, 0x5, 0x36, 0x1c, 0x2, 0xf8, 0xf7, 0x3, 0x2, 0x2, 0x2, 
    0xf8, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xf9, 0xfa, 0x3, 0x2, 0x2, 0x2, 0xfa, 
    0xfe, 0x7, 0xe, 0x2, 0x2, 0xfb, 0xfe, 0x7, 0x2d, 0x2, 0x2, 0xfc, 0xfe, 
    0x7, 0x2f, 0x2, 0x2, 0xfd, 0xee, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xf3, 0x3, 
    0x2, 0x2, 0x2, 0xfd, 0xf5, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xfb, 0x3, 0x2, 
    0x2, 0x2, 0xfd, 0xfc, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x115, 0x3, 0x2, 0x2, 
    0x2, 0xff, 0x100, 0xc, 0xb, 0x2, 0x2, 0x100, 0x101, 0x7, 0x2c, 0x2, 
    0x2, 0x101, 0x114, 0x5, 0x26, 0x14, 0xc, 0x102, 0x103, 0xc, 0xa, 0x2, 
    0x2, 0x103, 0x104, 0x7, 0x2a, 0x2, 0x2, 0x104, 0x114, 0x5, 0x26, 0x14, 
    0xb, 0x105, 0x106, 0xc, 0x9, 0x2, 0x2, 0x106, 0x107, 0x7, 0x2b, 0x2, 
    0x2, 0x107, 0x114, 0x5, 0x26, 0x14, 0xa, 0x108, 0x109, 0xc, 0x8, 0x2, 
    0x2, 0x109, 0x10a, 0x7, 0x28, 0x2, 0x2, 0x10a, 0x114, 0x5, 0x26, 0x14, 
    0x9, 0x10b, 0x10c, 0xc, 0x7, 0x2, 0x2, 0x10c, 0x10d, 0x7, 0x29, 0x2, 
    0x2, 0x10d, 0x114, 0x5, 0x26, 0x14, 0x8, 0x10e, 0x10f, 0xc, 0xc, 0x2, 
    0x2, 0x10f, 0x110, 0x7, 0x8, 0x2, 0x2, 0x110, 0x111, 0x5, 0x26, 0x14, 
    0x2, 0x111, 0x112, 0x7, 0xa, 0x2, 0x2, 0x112, 0x114, 0x3, 0x2, 0x2, 
    0x2, 0x113, 0xff, 0x3, 0x2, 0x2, 0x2, 0x113, 0x102, 0x3, 0x2, 0x2, 0x2, 
    0x113, 0x105, 0x3, 0x2, 0x2, 0x2, 0x113, 0x108, 0x3, 0x2, 0x2, 0x2, 
    0x113, 0x10b, 0x3, 0x2, 0x2, 0x2, 0x113, 0x10e, 0x3, 0x2, 0x2, 0x2, 
    0x114, 0x117, 0x3, 0x2, 0x2, 0x2, 0x115, 0x113, 0x3, 0x2, 0x2, 0x2, 
    0x115, 0x116, 0x3, 0x2, 0x2, 0x2, 0x116, 0x27, 0x3, 0x2, 0x2, 0x2, 0x117, 
    0x115, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x7, 0x19, 0x2, 0x2, 0x119, 
    0x11d, 0x7, 0x3, 0x2, 0x2, 0x11a, 0x11c, 0x5, 0x2c, 0x17, 0x2, 0x11b, 
    0x11a, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11f, 0x3, 0x2, 0x2, 0x2, 0x11d, 
    0x11b, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11e, 0x3, 0x2, 0x2, 0x2, 0x11e, 
    0x120, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x120, 
    0x121, 0x7, 0x4, 0x2, 0x2, 0x121, 0x29, 0x3, 0x2, 0x2, 0x2, 0x122, 0x124, 
    0x5, 0x2c, 0x17, 0x2, 0x123, 0x122, 0x3, 0x2, 0x2, 0x2, 0x124, 0x127, 
    0x3, 0x2, 0x2, 0x2, 0x125, 0x123, 0x3, 0x2, 0x2, 0x2, 0x125, 0x126, 
    0x3, 0x2, 0x2, 0x2, 0x126, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x127, 0x125, 0x3, 
    0x2, 0x2, 0x2, 0x128, 0x129, 0x7, 0x1c, 0x2, 0x2, 0x129, 0x12a, 0x7, 
    0xd, 0x2, 0x2, 0x12a, 0x12b, 0x5, 0x2e, 0x18, 0x2, 0x12b, 0x12c, 0x7, 
    0xe, 0x2, 0x2, 0x12c, 0x130, 0x7, 0x3, 0x2, 0x2, 0x12d, 0x12f, 0x5, 
    0x2c, 0x17, 0x2, 0x12e, 0x12d, 0x3, 0x2, 0x2, 0x2, 0x12f, 0x132, 0x3, 
    0x2, 0x2, 0x2, 0x130, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x130, 0x131, 0x3, 
    0x2, 0x2, 0x2, 0x131, 0x133, 0x3, 0x2, 0x2, 0x2, 0x132, 0x130, 0x3, 
    0x2, 0x2, 0x2, 0x133, 0x134, 0x7, 0x4, 0x2, 0x2, 0x134, 0x14a, 0x3, 
    0x2, 0x2, 0x2, 0x135, 0x136, 0x7, 0x1c, 0x2, 0x2, 0x136, 0x137, 0x7, 
    0xd, 0x2, 0x2, 0x137, 0x138, 0x5, 0x2e, 0x18, 0x2, 0x138, 0x139, 0x7, 
    0xe, 0x2, 0x2, 0x139, 0x13a, 0x7, 0x3, 0x2, 0x2, 0x13a, 0x13b, 0x5, 
    0x2a, 0x16, 0x2, 0x13b, 0x13c, 0x7, 0x4, 0x2, 0x2, 0x13c, 0x13d, 0x7, 
    0x21, 0x2, 0x2, 0x13d, 0x13e, 0x7, 0x3, 0x2, 0x2, 0x13e, 0x13f, 0x5, 
    0x2a, 0x16, 0x2, 0x13f, 0x140, 0x7, 0x4, 0x2, 0x2, 0x140, 0x14a, 0x3, 
    0x2, 0x2, 0x2, 0x141, 0x142, 0x7, 0x26, 0x2, 0x2, 0x142, 0x14a, 0x7, 
    0x11, 0x2, 0x2, 0x143, 0x144, 0x7, 0x2f, 0x2, 0x2, 0x144, 0x145, 0x7, 
    0x6, 0x2, 0x2, 0x145, 0x146, 0x5, 0x26, 0x14, 0x2, 0x146, 0x147, 0x7, 
    0x11, 0x2, 0x2, 0x147, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x148, 0x14a, 0x7, 
    0x31, 0x2, 0x2, 0x149, 0x128, 0x3, 0x2, 0x2, 0x2, 0x149, 0x135, 0x3, 
    0x2, 0x2, 0x2, 0x149, 0x141, 0x3, 0x2, 0x2, 0x2, 0x149, 0x143, 0x3, 
    0x2, 0x2, 0x2, 0x149, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x2d, 0x3, 0x2, 
    0x2, 0x2, 0x14b, 0x14c, 0x8, 0x18, 0x1, 0x2, 0x14c, 0x14d, 0x7, 0xd, 
    0x2, 0x2, 0x14d, 0x14e, 0x5, 0x2e, 0x18, 0x2, 0x14e, 0x14f, 0x7, 0xe, 
    0x2, 0x2, 0x14f, 0x159, 0x3, 0x2, 0x2, 0x2, 0x150, 0x151, 0x7, 0x25, 
    0x2, 0x2, 0x151, 0x159, 0x5, 0x2e, 0x18, 0x6, 0x152, 0x153, 0x5, 0x26, 
    0x14, 0x2, 0x153, 0x154, 0x7, 0x23, 0x2, 0x2, 0x154, 0x155, 0x5, 0x26, 
    0x14, 0x2, 0x155, 0x159, 0x3, 0x2, 0x2, 0x2, 0x156, 0x159, 0x7, 0x27, 
    0x2, 0x2, 0x157, 0x159, 0x7, 0x2f, 0x2, 0x2, 0x158, 0x14b, 0x3, 0x2, 
    0x2, 0x2, 0x158, 0x150, 0x3, 0x2, 0x2, 0x2, 0x158, 0x152, 0x3, 0x2, 
    0x2, 0x2, 0x158, 0x156, 0x3, 0x2, 0x2, 0x2, 0x158, 0x157, 0x3, 0x2, 
    0x2, 0x2, 0x159, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x15b, 0xc, 0x7, 
    0x2, 0x2, 0x15b, 0x15c, 0x7, 0x24, 0x2, 0x2, 0x15c, 0x15e, 0x5, 0x2e, 
    0x18, 0x8, 0x15d, 0x15a, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x161, 0x3, 0x2, 
    0x2, 0x2, 0x15f, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x15f, 0x160, 0x3, 0x2, 
    0x2, 0x2, 0x160, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x161, 0x15f, 0x3, 0x2, 0x2, 
    0x2, 0x162, 0x163, 0x7, 0x14, 0x2, 0x2, 0x163, 0x31, 0x3, 0x2, 0x2, 
    0x2, 0x164, 0x165, 0x7, 0xf, 0x2, 0x2, 0x165, 0x166, 0x7, 0x2f, 0x2, 
    0x2, 0x166, 0x168, 0x7, 0xd, 0x2, 0x2, 0x167, 0x169, 0x5, 0x34, 0x1b, 
    0x2, 0x168, 0x167, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x3, 0x2, 0x2, 
    0x2, 0x169, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x16b, 0x7, 0xe, 0x2, 
    0x2, 0x16b, 0x16f, 0x7, 0x3, 0x2, 0x2, 0x16c, 0x16e, 0x5, 0x3e, 0x20, 
    0x2, 0x16d, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x171, 0x3, 0x2, 0x2, 
    0x2, 0x16f, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16f, 0x170, 0x3, 0x2, 0x2, 
    0x2, 0x170, 0x172, 0x3, 0x2, 0x2, 0x2, 0x171, 0x16f, 0x3, 0x2, 0x2, 
    0x2, 0x172, 0x173, 0x7, 0x4, 0x2, 0x2, 0x173, 0x33, 0x3, 0x2, 0x2, 0x2, 
    0x174, 0x176, 0x7, 0x33, 0x2, 0x2, 0x175, 0x174, 0x3, 0x2, 0x2, 0x2, 
    0x175, 0x176, 0x3, 0x2, 0x2, 0x2, 0x176, 0x177, 0x3, 0x2, 0x2, 0x2, 
    0x177, 0x179, 0x5, 0x38, 0x1d, 0x2, 0x178, 0x17a, 0x7, 0x33, 0x2, 0x2, 
    0x179, 0x178, 0x3, 0x2, 0x2, 0x2, 0x179, 0x17a, 0x3, 0x2, 0x2, 0x2, 
    0x17a, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x17b, 0x17d, 0x7, 0x9, 0x2, 0x2, 
    0x17c, 0x17e, 0x7, 0x33, 0x2, 0x2, 0x17d, 0x17c, 0x3, 0x2, 0x2, 0x2, 
    0x17d, 0x17e, 0x3, 0x2, 0x2, 0x2, 0x17e, 0x180, 0x3, 0x2, 0x2, 0x2, 
    0x17f, 0x175, 0x3, 0x2, 0x2, 0x2, 0x180, 0x183, 0x3, 0x2, 0x2, 0x2, 
    0x181, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x181, 0x182, 0x3, 0x2, 0x2, 0x2, 
    0x182, 0x185, 0x3, 0x2, 0x2, 0x2, 0x183, 0x181, 0x3, 0x2, 0x2, 0x2, 
    0x184, 0x186, 0x7, 0x33, 0x2, 0x2, 0x185, 0x184, 0x3, 0x2, 0x2, 0x2, 
    0x185, 0x186, 0x3, 0x2, 0x2, 0x2, 0x186, 0x187, 0x3, 0x2, 0x2, 0x2, 
    0x187, 0x189, 0x5, 0x38, 0x1d, 0x2, 0x188, 0x18a, 0x7, 0x33, 0x2, 0x2, 
    0x189, 0x188, 0x3, 0x2, 0x2, 0x2, 0x189, 0x18a, 0x3, 0x2, 0x2, 0x2, 
    0x18a, 0x35, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x18d, 0x7, 0x33, 0x2, 0x2, 
    0x18c, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x18c, 0x18d, 0x3, 0x2, 0x2, 0x2, 
    0x18d, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x190, 0x5, 0x3c, 0x1f, 0x2, 
    0x18f, 0x191, 0x7, 0x33, 0x2, 0x2, 0x190, 0x18f, 0x3, 0x2, 0x2, 0x2, 
    0x190, 0x191, 0x3, 0x2, 0x2, 0x2, 0x191, 0x192, 0x3, 0x2, 0x2, 0x2, 
    0x192, 0x194, 0x7, 0x9, 0x2, 0x2, 0x193, 0x195, 0x7, 0x33, 0x2, 0x2, 
    0x194, 0x193, 0x3, 0x2, 0x2, 0x2, 0x194, 0x195, 0x3, 0x2, 0x2, 0x2, 
    0x195, 0x197, 0x3, 0x2, 0x2, 0x2, 0x196, 0x18c, 0x3, 0x2, 0x2, 0x2, 
    0x197, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x198, 0x196, 0x3, 0x2, 0x2, 0x2, 
    0x198, 0x199, 0x3, 0x2, 0x2, 0x2, 0x199, 0x19c, 0x3, 0x2, 0x2, 0x2, 
    0x19a, 0x198, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19d, 0x7, 0x33, 0x2, 0x2, 
    0x19c, 0x19b, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19d, 0x3, 0x2, 0x2, 0x2, 
    0x19d, 0x19e, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a0, 0x5, 0x3c, 0x1f, 0x2, 
    0x19f, 0x1a1, 0x7, 0x33, 0x2, 0x2, 0x1a0, 0x19f, 0x3, 0x2, 0x2, 0x2, 
    0x1a0, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x37, 0x3, 0x2, 0x2, 0x2, 0x1a2, 
    0x1a3, 0x7, 0x1b, 0x2, 0x2, 0x1a3, 0x1a4, 0x7, 0x2f, 0x2, 0x2, 0x1a4, 
    0x39, 0x3, 0x2, 0x2, 0x2, 0x1a5, 0x1a7, 0x5, 0x3e, 0x20, 0x2, 0x1a6, 
    0x1a5, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1a8, 
    0x1a6, 0x3, 0x2, 0x2, 0x2, 0x1a8, 0x1a9, 0x3, 0x2, 0x2, 0x2, 0x1a9, 
    0x3b, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ae, 
    0x5, 0x26, 0x14, 0x2, 0x1ac, 0x1ae, 0x5, 0x2e, 0x18, 0x2, 0x1ad, 0x1ab, 
    0x3, 0x2, 0x2, 0x2, 0x1ad, 0x1ac, 0x3, 0x2, 0x2, 0x2, 0x1ae, 0x3d, 0x3, 
    0x2, 0x2, 0x2, 0x1af, 0x1b0, 0x7, 0x1b, 0x2, 0x2, 0x1b0, 0x1b3, 0x7, 
    0x2f, 0x2, 0x2, 0x1b1, 0x1b2, 0x7, 0x6, 0x2, 0x2, 0x1b2, 0x1b4, 0x5, 
    0x3c, 0x1f, 0x2, 0x1b3, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b3, 0x1b4, 0x3, 
    0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b5, 0x1f8, 0x7, 
    0x11, 0x2, 0x2, 0x1b6, 0x1b7, 0x7, 0x2f, 0x2, 0x2, 0x1b7, 0x1b8, 0x7, 
    0x6, 0x2, 0x2, 0x1b8, 0x1b9, 0x5, 0x3c, 0x1f, 0x2, 0x1b9, 0x1ba, 0x7, 
    0x11, 0x2, 0x2, 0x1ba, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 0x7, 
    0x2f, 0x2, 0x2, 0x1bc, 0x1bd, 0x7, 0x7, 0x2, 0x2, 0x1bd, 0x1be, 0x7, 
    0x10, 0x2, 0x2, 0x1be, 0x1bf, 0x7, 0x1b, 0x2, 0x2, 0x1bf, 0x1c0, 0x7, 
    0xd, 0x2, 0x2, 0x1c0, 0x1c1, 0x5, 0x3c, 0x1f, 0x2, 0x1c1, 0x1c2, 0x7, 
    0xe, 0x2, 0x2, 0x1c2, 0x1c3, 0x7, 0x11, 0x2, 0x2, 0x1c3, 0x1f8, 0x3, 
    0x2, 0x2, 0x2, 0x1c4, 0x1c5, 0x7, 0x2f, 0x2, 0x2, 0x1c5, 0x1c6, 0x7, 
    0x7, 0x2, 0x2, 0x1c6, 0x1c7, 0x7, 0x26, 0x2, 0x2, 0x1c7, 0x1c8, 0x5, 
    0x26, 0x14, 0x2, 0x1c8, 0x1c9, 0x7, 0x11, 0x2, 0x2, 0x1c9, 0x1f8, 0x3, 
    0x2, 0x2, 0x2, 0x1ca, 0x1cb, 0x7, 0x1c, 0x2, 0x2, 0x1cb, 0x1cc, 0x7, 
    0xd, 0x2, 0x2, 0x1cc, 0x1cd, 0x5, 0x2e, 0x18, 0x2, 0x1cd, 0x1ce, 0x7, 
    0xe, 0x2, 0x2, 0x1ce, 0x1cf, 0x7, 0x3, 0x2, 0x2, 0x1cf, 0x1d0, 0x5, 
    0x3a, 0x1e, 0x2, 0x1d0, 0x1d6, 0x7, 0x4, 0x2, 0x2, 0x1d1, 0x1d2, 0x7, 
    0x21, 0x2, 0x2, 0x1d2, 0x1d3, 0x7, 0x3, 0x2, 0x2, 0x1d3, 0x1d4, 0x5, 
    0x3a, 0x1e, 0x2, 0x1d4, 0x1d5, 0x7, 0x4, 0x2, 0x2, 0x1d5, 0x1d7, 0x3, 
    0x2, 0x2, 0x2, 0x1d6, 0x1d1, 0x3, 0x2, 0x2, 0x2, 0x1d6, 0x1d7, 0x3, 
    0x2, 0x2, 0x2, 0x1d7, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1d8, 0x1d9, 0x7, 
    0x1a, 0x2, 0x2, 0x1d9, 0x1da, 0x5, 0x26, 0x14, 0x2, 0x1da, 0x1db, 0x7, 
    0x11, 0x2, 0x2, 0x1db, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1dc, 0x1dd, 0x7, 
    0x1d, 0x2, 0x2, 0x1dd, 0x1de, 0x7, 0xd, 0x2, 0x2, 0x1de, 0x1df, 0x7, 
    0x1b, 0x2, 0x2, 0x1df, 0x1e0, 0x7, 0x2f, 0x2, 0x2, 0x1e0, 0x1e1, 0x7, 
    0x6, 0x2, 0x2, 0x1e1, 0x1e2, 0x5, 0x26, 0x14, 0x2, 0x1e2, 0x1e3, 0x7, 
    0x9, 0x2, 0x2, 0x1e3, 0x1e4, 0x5, 0x2e, 0x18, 0x2, 0x1e4, 0x1e5, 0x7, 
    0x9, 0x2, 0x2, 0x1e5, 0x1e6, 0x5, 0x26, 0x14, 0x2, 0x1e6, 0x1e7, 0x7, 
    0xe, 0x2, 0x2, 0x1e7, 0x1e8, 0x7, 0x3, 0x2, 0x2, 0x1e8, 0x1e9, 0x5, 
    0x3a, 0x1e, 0x2, 0x1e9, 0x1ea, 0x7, 0x4, 0x2, 0x2, 0x1ea, 0x1f8, 0x3, 
    0x2, 0x2, 0x2, 0x1eb, 0x1ec, 0x7, 0x1e, 0x2, 0x2, 0x1ec, 0x1ed, 0x7, 
    0xd, 0x2, 0x2, 0x1ed, 0x1ee, 0x5, 0x2e, 0x18, 0x2, 0x1ee, 0x1ef, 0x7, 
    0xe, 0x2, 0x2, 0x1ef, 0x1f0, 0x7, 0x3, 0x2, 0x2, 0x1f0, 0x1f1, 0x5, 
    0x3a, 0x1e, 0x2, 0x1f1, 0x1f2, 0x7, 0x4, 0x2, 0x2, 0x1f2, 0x1f8, 0x3, 
    0x2, 0x2, 0x2, 0x1f3, 0x1f4, 0x7, 0x1f, 0x2, 0x2, 0x1f4, 0x1f8, 0x7, 
    0x11, 0x2, 0x2, 0x1f5, 0x1f6, 0x7, 0x20, 0x2, 0x2, 0x1f6, 0x1f8, 0x7, 
    0x11, 0x2, 0x2, 0x1f7, 0x1af, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1b6, 0x3, 
    0x2, 0x2, 0x2, 0x1f7, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1c4, 0x3, 
    0x2, 0x2, 0x2, 0x1f7, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1d8, 0x3, 
    0x2, 0x2, 0x2, 0x1f7, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1eb, 0x3, 
    0x2, 0x2, 0x2, 0x1f7, 0x1f3, 0x3, 0x2, 0x2, 0x2, 0x1f7, 0x1f5, 0x3, 
    0x2, 0x2, 0x2, 0x1f8, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x39, 0x43, 0x4f, 0x56, 
    0x60, 0x64, 0x6e, 0x72, 0x7b, 0x87, 0x93, 0x95, 0x97, 0x9f, 0xa5, 0xad, 
    0xb3, 0xbd, 0xc1, 0xc5, 0xc9, 0xcd, 0xd1, 0xd7, 0xdd, 0xe4, 0xea, 0xf8, 
    0xfd, 0x113, 0x115, 0x11d, 0x125, 0x130, 0x149, 0x158, 0x15f, 0x168, 
    0x16f, 0x175, 0x179, 0x17d, 0x181, 0x185, 0x189, 0x18c, 0x190, 0x194, 
    0x198, 0x19c, 0x1a0, 0x1a8, 0x1ad, 0x1b3, 0x1d6, 0x1f7, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

ScimitarParser::Initializer ScimitarParser::_init;
