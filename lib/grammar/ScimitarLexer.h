
// Generated from Scimitar.g4 by ANTLR 4.8; unmodified.

#pragma once


#include "antlr4-runtime.h"




class  ScimitarLexer : public antlr4::Lexer {
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

  ScimitarLexer(antlr4::CharStream *input);
  ~ScimitarLexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getChannelNames() const override;
  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _channelNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

