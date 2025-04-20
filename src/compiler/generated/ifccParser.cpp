
// Generated from ifcc.g4 by ANTLR 4.13.2


#include "ifccVisitor.h"

#include "ifccParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct IfccParserStaticData final {
  IfccParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  IfccParserStaticData(const IfccParserStaticData&) = delete;
  IfccParserStaticData(IfccParserStaticData&&) = delete;
  IfccParserStaticData& operator=(const IfccParserStaticData&) = delete;
  IfccParserStaticData& operator=(IfccParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag ifccParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<IfccParserStaticData> ifccParserStaticData = nullptr;

void ifccParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (ifccParserStaticData != nullptr) {
    return;
  }
#else
  assert(ifccParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<IfccParserStaticData>(
    std::vector<std::string>{
      "axiom", "prog", "mainFunction", "functionDef", "functionDec", "parameter_list", 
      "parameter", "block", "stmt", "declaration", "assignment", "return_stmt", 
      "functionCall", "if_stmt", "while_stmt", "expr"
    },
    std::vector<std::string>{
      "", "'main'", "'('", "')'", "';'", "','", "'{'", "'}'", "'='", "'!'", 
      "'-'", "'*'", "'/'", "'%'", "'+'", "'<'", "'>'", "'<='", "'>='", "'=='", 
      "'!='", "'&'", "'^'", "'|'", "", "'return'", "'if'", "'else'", "'while'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "TYPE", "RETURN", "IF", "ELSE", "WHILE", 
      "ID", "CONST", "CHAR", "COMMENT", "DIRECTIVE", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,34,192,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,1,0,1,0,1,0,1,1,1,1,5,1,38,8,1,10,1,12,1,41,9,1,1,1,1,1,
  	1,1,5,1,46,8,1,10,1,12,1,49,9,1,1,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,1,
  	3,3,3,61,8,3,1,3,1,3,1,3,1,4,1,4,1,4,1,4,3,4,70,8,4,1,4,1,4,1,4,1,5,1,
  	5,1,5,5,5,78,8,5,10,5,12,5,81,9,5,1,6,1,6,1,6,1,7,1,7,5,7,88,8,7,10,7,
  	12,7,91,9,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,3,8,108,8,8,1,9,1,9,1,9,1,9,3,9,114,8,9,1,10,1,10,1,10,1,10,1,11,1,
  	11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,5,12,129,8,12,10,12,12,12,132,9,
  	12,3,12,134,8,12,1,12,1,12,1,13,1,13,1,13,1,13,1,13,1,13,1,13,3,13,145,
  	8,13,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,15,1,15,1,15,1,15,1,15,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,15,3,15,167,8,15,1,15,1,15,1,15,1,15,
  	1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,1,15,
  	5,15,187,8,15,10,15,12,15,190,9,15,1,15,0,1,30,16,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,0,3,1,0,11,13,2,0,10,10,14,14,1,0,15,20,206,0,
  	32,1,0,0,0,2,39,1,0,0,0,4,50,1,0,0,0,6,56,1,0,0,0,8,65,1,0,0,0,10,74,
  	1,0,0,0,12,82,1,0,0,0,14,85,1,0,0,0,16,107,1,0,0,0,18,109,1,0,0,0,20,
  	115,1,0,0,0,22,119,1,0,0,0,24,123,1,0,0,0,26,137,1,0,0,0,28,146,1,0,0,
  	0,30,166,1,0,0,0,32,33,3,2,1,0,33,34,5,0,0,1,34,1,1,0,0,0,35,38,3,6,3,
  	0,36,38,3,8,4,0,37,35,1,0,0,0,37,36,1,0,0,0,38,41,1,0,0,0,39,37,1,0,0,
  	0,39,40,1,0,0,0,40,42,1,0,0,0,41,39,1,0,0,0,42,47,3,4,2,0,43,46,3,6,3,
  	0,44,46,3,8,4,0,45,43,1,0,0,0,45,44,1,0,0,0,46,49,1,0,0,0,47,45,1,0,0,
  	0,47,48,1,0,0,0,48,3,1,0,0,0,49,47,1,0,0,0,50,51,5,24,0,0,51,52,5,1,0,
  	0,52,53,5,2,0,0,53,54,5,3,0,0,54,55,3,14,7,0,55,5,1,0,0,0,56,57,5,24,
  	0,0,57,58,5,29,0,0,58,60,5,2,0,0,59,61,3,10,5,0,60,59,1,0,0,0,60,61,1,
  	0,0,0,61,62,1,0,0,0,62,63,5,3,0,0,63,64,3,14,7,0,64,7,1,0,0,0,65,66,5,
  	24,0,0,66,67,5,29,0,0,67,69,5,2,0,0,68,70,3,10,5,0,69,68,1,0,0,0,69,70,
  	1,0,0,0,70,71,1,0,0,0,71,72,5,3,0,0,72,73,5,4,0,0,73,9,1,0,0,0,74,79,
  	3,12,6,0,75,76,5,5,0,0,76,78,3,12,6,0,77,75,1,0,0,0,78,81,1,0,0,0,79,
  	77,1,0,0,0,79,80,1,0,0,0,80,11,1,0,0,0,81,79,1,0,0,0,82,83,5,24,0,0,83,
  	84,5,29,0,0,84,13,1,0,0,0,85,89,5,6,0,0,86,88,3,16,8,0,87,86,1,0,0,0,
  	88,91,1,0,0,0,89,87,1,0,0,0,89,90,1,0,0,0,90,92,1,0,0,0,91,89,1,0,0,0,
  	92,93,5,7,0,0,93,15,1,0,0,0,94,95,3,18,9,0,95,96,5,4,0,0,96,108,1,0,0,
  	0,97,98,3,20,10,0,98,99,5,4,0,0,99,108,1,0,0,0,100,108,3,22,11,0,101,
  	102,3,24,12,0,102,103,5,4,0,0,103,108,1,0,0,0,104,108,3,26,13,0,105,108,
  	3,14,7,0,106,108,3,28,14,0,107,94,1,0,0,0,107,97,1,0,0,0,107,100,1,0,
  	0,0,107,101,1,0,0,0,107,104,1,0,0,0,107,105,1,0,0,0,107,106,1,0,0,0,108,
  	17,1,0,0,0,109,110,5,24,0,0,110,113,5,29,0,0,111,112,5,8,0,0,112,114,
  	3,30,15,0,113,111,1,0,0,0,113,114,1,0,0,0,114,19,1,0,0,0,115,116,5,29,
  	0,0,116,117,5,8,0,0,117,118,3,30,15,0,118,21,1,0,0,0,119,120,5,25,0,0,
  	120,121,3,30,15,0,121,122,5,4,0,0,122,23,1,0,0,0,123,124,5,29,0,0,124,
  	133,5,2,0,0,125,130,3,30,15,0,126,127,5,5,0,0,127,129,3,30,15,0,128,126,
  	1,0,0,0,129,132,1,0,0,0,130,128,1,0,0,0,130,131,1,0,0,0,131,134,1,0,0,
  	0,132,130,1,0,0,0,133,125,1,0,0,0,133,134,1,0,0,0,134,135,1,0,0,0,135,
  	136,5,3,0,0,136,25,1,0,0,0,137,138,5,26,0,0,138,139,5,2,0,0,139,140,3,
  	30,15,0,140,141,5,3,0,0,141,144,3,14,7,0,142,143,5,27,0,0,143,145,3,14,
  	7,0,144,142,1,0,0,0,144,145,1,0,0,0,145,27,1,0,0,0,146,147,5,28,0,0,147,
  	148,5,2,0,0,148,149,3,30,15,0,149,150,5,3,0,0,150,151,3,14,7,0,151,29,
  	1,0,0,0,152,153,6,15,-1,0,153,167,3,20,10,0,154,155,5,9,0,0,155,167,3,
  	30,15,13,156,157,5,10,0,0,157,167,3,30,15,12,158,159,5,2,0,0,159,160,
  	3,30,15,0,160,161,5,3,0,0,161,167,1,0,0,0,162,167,3,24,12,0,163,167,5,
  	29,0,0,164,167,5,30,0,0,165,167,5,31,0,0,166,152,1,0,0,0,166,154,1,0,
  	0,0,166,156,1,0,0,0,166,158,1,0,0,0,166,162,1,0,0,0,166,163,1,0,0,0,166,
  	164,1,0,0,0,166,165,1,0,0,0,167,188,1,0,0,0,168,169,10,11,0,0,169,170,
  	7,0,0,0,170,187,3,30,15,12,171,172,10,10,0,0,172,173,7,1,0,0,173,187,
  	3,30,15,11,174,175,10,9,0,0,175,176,7,2,0,0,176,187,3,30,15,10,177,178,
  	10,8,0,0,178,179,5,21,0,0,179,187,3,30,15,9,180,181,10,7,0,0,181,182,
  	5,22,0,0,182,187,3,30,15,8,183,184,10,6,0,0,184,185,5,23,0,0,185,187,
  	3,30,15,7,186,168,1,0,0,0,186,171,1,0,0,0,186,174,1,0,0,0,186,177,1,0,
  	0,0,186,180,1,0,0,0,186,183,1,0,0,0,187,190,1,0,0,0,188,186,1,0,0,0,188,
  	189,1,0,0,0,189,31,1,0,0,0,190,188,1,0,0,0,16,37,39,45,47,60,69,79,89,
  	107,113,130,133,144,166,186,188
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  ifccParserStaticData = std::move(staticData);
}

}

ifccParser::ifccParser(TokenStream *input) : ifccParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

ifccParser::ifccParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  ifccParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *ifccParserStaticData->atn, ifccParserStaticData->decisionToDFA, ifccParserStaticData->sharedContextCache, options);
}

ifccParser::~ifccParser() {
  delete _interpreter;
}

const atn::ATN& ifccParser::getATN() const {
  return *ifccParserStaticData->atn;
}

std::string ifccParser::getGrammarFileName() const {
  return "ifcc.g4";
}

const std::vector<std::string>& ifccParser::getRuleNames() const {
  return ifccParserStaticData->ruleNames;
}

const dfa::Vocabulary& ifccParser::getVocabulary() const {
  return ifccParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView ifccParser::getSerializedATN() const {
  return ifccParserStaticData->serializedATN;
}


//----------------- AxiomContext ------------------------------------------------------------------

ifccParser::AxiomContext::AxiomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::ProgContext* ifccParser::AxiomContext::prog() {
  return getRuleContext<ifccParser::ProgContext>(0);
}

tree::TerminalNode* ifccParser::AxiomContext::EOF() {
  return getToken(ifccParser::EOF, 0);
}


size_t ifccParser::AxiomContext::getRuleIndex() const {
  return ifccParser::RuleAxiom;
}


std::any ifccParser::AxiomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAxiom(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::AxiomContext* ifccParser::axiom() {
  AxiomContext *_localctx = _tracker.createInstance<AxiomContext>(_ctx, getState());
  enterRule(_localctx, 0, ifccParser::RuleAxiom);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(32);
    prog();
    setState(33);
    match(ifccParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ProgContext ------------------------------------------------------------------

ifccParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::MainFunctionContext* ifccParser::ProgContext::mainFunction() {
  return getRuleContext<ifccParser::MainFunctionContext>(0);
}

std::vector<ifccParser::FunctionDefContext *> ifccParser::ProgContext::functionDef() {
  return getRuleContexts<ifccParser::FunctionDefContext>();
}

ifccParser::FunctionDefContext* ifccParser::ProgContext::functionDef(size_t i) {
  return getRuleContext<ifccParser::FunctionDefContext>(i);
}

std::vector<ifccParser::FunctionDecContext *> ifccParser::ProgContext::functionDec() {
  return getRuleContexts<ifccParser::FunctionDecContext>();
}

ifccParser::FunctionDecContext* ifccParser::ProgContext::functionDec(size_t i) {
  return getRuleContext<ifccParser::FunctionDecContext>(i);
}


size_t ifccParser::ProgContext::getRuleIndex() const {
  return ifccParser::RuleProg;
}


std::any ifccParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ProgContext* ifccParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 2, ifccParser::RuleProg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(39);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(37);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
        case 1: {
          setState(35);
          functionDef();
          break;
        }

        case 2: {
          setState(36);
          functionDec();
          break;
        }

        default:
          break;
        } 
      }
      setState(41);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx);
    }
    setState(42);
    mainFunction();
    setState(47);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ifccParser::TYPE) {
      setState(45);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
      case 1: {
        setState(43);
        functionDef();
        break;
      }

      case 2: {
        setState(44);
        functionDec();
        break;
      }

      default:
        break;
      }
      setState(49);
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

//----------------- MainFunctionContext ------------------------------------------------------------------

ifccParser::MainFunctionContext::MainFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::MainFunctionContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

ifccParser::BlockContext* ifccParser::MainFunctionContext::block() {
  return getRuleContext<ifccParser::BlockContext>(0);
}


size_t ifccParser::MainFunctionContext::getRuleIndex() const {
  return ifccParser::RuleMainFunction;
}


std::any ifccParser::MainFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitMainFunction(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::MainFunctionContext* ifccParser::mainFunction() {
  MainFunctionContext *_localctx = _tracker.createInstance<MainFunctionContext>(_ctx, getState());
  enterRule(_localctx, 4, ifccParser::RuleMainFunction);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(50);
    match(ifccParser::TYPE);
    setState(51);
    match(ifccParser::T__0);
    setState(52);
    match(ifccParser::T__1);
    setState(53);
    match(ifccParser::T__2);
    setState(54);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDefContext ------------------------------------------------------------------

ifccParser::FunctionDefContext::FunctionDefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::FunctionDefContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::FunctionDefContext::ID() {
  return getToken(ifccParser::ID, 0);
}

ifccParser::BlockContext* ifccParser::FunctionDefContext::block() {
  return getRuleContext<ifccParser::BlockContext>(0);
}

ifccParser::Parameter_listContext* ifccParser::FunctionDefContext::parameter_list() {
  return getRuleContext<ifccParser::Parameter_listContext>(0);
}


size_t ifccParser::FunctionDefContext::getRuleIndex() const {
  return ifccParser::RuleFunctionDef;
}


std::any ifccParser::FunctionDefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFunctionDef(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::FunctionDefContext* ifccParser::functionDef() {
  FunctionDefContext *_localctx = _tracker.createInstance<FunctionDefContext>(_ctx, getState());
  enterRule(_localctx, 6, ifccParser::RuleFunctionDef);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(56);
    match(ifccParser::TYPE);
    setState(57);
    match(ifccParser::ID);
    setState(58);
    match(ifccParser::T__1);
    setState(60);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ifccParser::TYPE) {
      setState(59);
      parameter_list();
    }
    setState(62);
    match(ifccParser::T__2);
    setState(63);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionDecContext ------------------------------------------------------------------

ifccParser::FunctionDecContext::FunctionDecContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::FunctionDecContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::FunctionDecContext::ID() {
  return getToken(ifccParser::ID, 0);
}

ifccParser::Parameter_listContext* ifccParser::FunctionDecContext::parameter_list() {
  return getRuleContext<ifccParser::Parameter_listContext>(0);
}


size_t ifccParser::FunctionDecContext::getRuleIndex() const {
  return ifccParser::RuleFunctionDec;
}


std::any ifccParser::FunctionDecContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFunctionDec(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::FunctionDecContext* ifccParser::functionDec() {
  FunctionDecContext *_localctx = _tracker.createInstance<FunctionDecContext>(_ctx, getState());
  enterRule(_localctx, 8, ifccParser::RuleFunctionDec);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    match(ifccParser::TYPE);
    setState(66);
    match(ifccParser::ID);
    setState(67);
    match(ifccParser::T__1);
    setState(69);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ifccParser::TYPE) {
      setState(68);
      parameter_list();
    }
    setState(71);
    match(ifccParser::T__2);
    setState(72);
    match(ifccParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Parameter_listContext ------------------------------------------------------------------

ifccParser::Parameter_listContext::Parameter_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ifccParser::ParameterContext *> ifccParser::Parameter_listContext::parameter() {
  return getRuleContexts<ifccParser::ParameterContext>();
}

ifccParser::ParameterContext* ifccParser::Parameter_listContext::parameter(size_t i) {
  return getRuleContext<ifccParser::ParameterContext>(i);
}


size_t ifccParser::Parameter_listContext::getRuleIndex() const {
  return ifccParser::RuleParameter_list;
}


std::any ifccParser::Parameter_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitParameter_list(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::Parameter_listContext* ifccParser::parameter_list() {
  Parameter_listContext *_localctx = _tracker.createInstance<Parameter_listContext>(_ctx, getState());
  enterRule(_localctx, 10, ifccParser::RuleParameter_list);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(74);
    parameter();
    setState(79);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == ifccParser::T__4) {
      setState(75);
      match(ifccParser::T__4);
      setState(76);
      parameter();
      setState(81);
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

//----------------- ParameterContext ------------------------------------------------------------------

ifccParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::ParameterContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::ParameterContext::ID() {
  return getToken(ifccParser::ID, 0);
}


size_t ifccParser::ParameterContext::getRuleIndex() const {
  return ifccParser::RuleParameter;
}


std::any ifccParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ParameterContext* ifccParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 12, ifccParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(82);
    match(ifccParser::TYPE);
    setState(83);
    match(ifccParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlockContext ------------------------------------------------------------------

ifccParser::BlockContext::BlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<ifccParser::StmtContext *> ifccParser::BlockContext::stmt() {
  return getRuleContexts<ifccParser::StmtContext>();
}

ifccParser::StmtContext* ifccParser::BlockContext::stmt(size_t i) {
  return getRuleContext<ifccParser::StmtContext>(i);
}


size_t ifccParser::BlockContext::getRuleIndex() const {
  return ifccParser::RuleBlock;
}


std::any ifccParser::BlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitBlock(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::BlockContext* ifccParser::block() {
  BlockContext *_localctx = _tracker.createInstance<BlockContext>(_ctx, getState());
  enterRule(_localctx, 14, ifccParser::RuleBlock);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(ifccParser::T__5);
    setState(89);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 922746944) != 0)) {
      setState(86);
      stmt();
      setState(91);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(92);
    match(ifccParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StmtContext ------------------------------------------------------------------

ifccParser::StmtContext::StmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

ifccParser::DeclarationContext* ifccParser::StmtContext::declaration() {
  return getRuleContext<ifccParser::DeclarationContext>(0);
}

ifccParser::AssignmentContext* ifccParser::StmtContext::assignment() {
  return getRuleContext<ifccParser::AssignmentContext>(0);
}

ifccParser::Return_stmtContext* ifccParser::StmtContext::return_stmt() {
  return getRuleContext<ifccParser::Return_stmtContext>(0);
}

ifccParser::FunctionCallContext* ifccParser::StmtContext::functionCall() {
  return getRuleContext<ifccParser::FunctionCallContext>(0);
}

ifccParser::If_stmtContext* ifccParser::StmtContext::if_stmt() {
  return getRuleContext<ifccParser::If_stmtContext>(0);
}

ifccParser::BlockContext* ifccParser::StmtContext::block() {
  return getRuleContext<ifccParser::BlockContext>(0);
}

ifccParser::While_stmtContext* ifccParser::StmtContext::while_stmt() {
  return getRuleContext<ifccParser::While_stmtContext>(0);
}


size_t ifccParser::StmtContext::getRuleIndex() const {
  return ifccParser::RuleStmt;
}


std::any ifccParser::StmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitStmt(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::StmtContext* ifccParser::stmt() {
  StmtContext *_localctx = _tracker.createInstance<StmtContext>(_ctx, getState());
  enterRule(_localctx, 16, ifccParser::RuleStmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(107);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(94);
      declaration();
      setState(95);
      match(ifccParser::T__3);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(97);
      assignment();
      setState(98);
      match(ifccParser::T__3);
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(100);
      return_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(101);
      functionCall();
      setState(102);
      match(ifccParser::T__3);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(104);
      if_stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(105);
      block();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(106);
      while_stmt();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

ifccParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::DeclarationContext::TYPE() {
  return getToken(ifccParser::TYPE, 0);
}

tree::TerminalNode* ifccParser::DeclarationContext::ID() {
  return getToken(ifccParser::ID, 0);
}

ifccParser::ExprContext* ifccParser::DeclarationContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}


size_t ifccParser::DeclarationContext::getRuleIndex() const {
  return ifccParser::RuleDeclaration;
}


std::any ifccParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::DeclarationContext* ifccParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 18, ifccParser::RuleDeclaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(109);
    match(ifccParser::TYPE);
    setState(110);
    match(ifccParser::ID);
    setState(113);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ifccParser::T__7) {
      setState(111);
      match(ifccParser::T__7);
      setState(112);
      expr(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

ifccParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::AssignmentContext::ID() {
  return getToken(ifccParser::ID, 0);
}

ifccParser::ExprContext* ifccParser::AssignmentContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}


size_t ifccParser::AssignmentContext::getRuleIndex() const {
  return ifccParser::RuleAssignment;
}


std::any ifccParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::AssignmentContext* ifccParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 20, ifccParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(115);
    match(ifccParser::ID);
    setState(116);
    match(ifccParser::T__7);
    setState(117);
    expr(0);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Return_stmtContext ------------------------------------------------------------------

ifccParser::Return_stmtContext::Return_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::Return_stmtContext::RETURN() {
  return getToken(ifccParser::RETURN, 0);
}

ifccParser::ExprContext* ifccParser::Return_stmtContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}


size_t ifccParser::Return_stmtContext::getRuleIndex() const {
  return ifccParser::RuleReturn_stmt;
}


std::any ifccParser::Return_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitReturn_stmt(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::Return_stmtContext* ifccParser::return_stmt() {
  Return_stmtContext *_localctx = _tracker.createInstance<Return_stmtContext>(_ctx, getState());
  enterRule(_localctx, 22, ifccParser::RuleReturn_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(119);
    match(ifccParser::RETURN);
    setState(120);
    expr(0);
    setState(121);
    match(ifccParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

ifccParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::FunctionCallContext::ID() {
  return getToken(ifccParser::ID, 0);
}

std::vector<ifccParser::ExprContext *> ifccParser::FunctionCallContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::FunctionCallContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}


size_t ifccParser::FunctionCallContext::getRuleIndex() const {
  return ifccParser::RuleFunctionCall;
}


std::any ifccParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::FunctionCallContext* ifccParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 24, ifccParser::RuleFunctionCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(123);
    match(ifccParser::ID);
    setState(124);
    match(ifccParser::T__1);
    setState(133);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 3758097924) != 0)) {
      setState(125);
      expr(0);
      setState(130);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == ifccParser::T__4) {
        setState(126);
        match(ifccParser::T__4);
        setState(127);
        expr(0);
        setState(132);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(135);
    match(ifccParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- If_stmtContext ------------------------------------------------------------------

ifccParser::If_stmtContext::If_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::If_stmtContext::IF() {
  return getToken(ifccParser::IF, 0);
}

ifccParser::ExprContext* ifccParser::If_stmtContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

std::vector<ifccParser::BlockContext *> ifccParser::If_stmtContext::block() {
  return getRuleContexts<ifccParser::BlockContext>();
}

ifccParser::BlockContext* ifccParser::If_stmtContext::block(size_t i) {
  return getRuleContext<ifccParser::BlockContext>(i);
}

tree::TerminalNode* ifccParser::If_stmtContext::ELSE() {
  return getToken(ifccParser::ELSE, 0);
}


size_t ifccParser::If_stmtContext::getRuleIndex() const {
  return ifccParser::RuleIf_stmt;
}


std::any ifccParser::If_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitIf_stmt(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::If_stmtContext* ifccParser::if_stmt() {
  If_stmtContext *_localctx = _tracker.createInstance<If_stmtContext>(_ctx, getState());
  enterRule(_localctx, 26, ifccParser::RuleIf_stmt);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(137);
    match(ifccParser::IF);
    setState(138);
    match(ifccParser::T__1);
    setState(139);
    expr(0);
    setState(140);
    match(ifccParser::T__2);
    setState(141);
    block();
    setState(144);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == ifccParser::ELSE) {
      setState(142);
      match(ifccParser::ELSE);
      setState(143);
      block();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- While_stmtContext ------------------------------------------------------------------

ifccParser::While_stmtContext::While_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* ifccParser::While_stmtContext::WHILE() {
  return getToken(ifccParser::WHILE, 0);
}

ifccParser::ExprContext* ifccParser::While_stmtContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::BlockContext* ifccParser::While_stmtContext::block() {
  return getRuleContext<ifccParser::BlockContext>(0);
}


size_t ifccParser::While_stmtContext::getRuleIndex() const {
  return ifccParser::RuleWhile_stmt;
}


std::any ifccParser::While_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitWhile_stmt(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::While_stmtContext* ifccParser::while_stmt() {
  While_stmtContext *_localctx = _tracker.createInstance<While_stmtContext>(_ctx, getState());
  enterRule(_localctx, 28, ifccParser::RuleWhile_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(146);
    match(ifccParser::WHILE);
    setState(147);
    match(ifccParser::T__1);
    setState(148);
    expr(0);
    setState(149);
    match(ifccParser::T__2);
    setState(150);
    block();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

ifccParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t ifccParser::ExprContext::getRuleIndex() const {
  return ifccParser::RuleExpr;
}

void ifccParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BitwiseAndExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::BitwiseAndExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::BitwiseAndExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::BitwiseAndExprContext::BitwiseAndExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::BitwiseAndExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitBitwiseAndExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConstExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::ConstExprContext::CONST() {
  return getToken(ifccParser::CONST, 0);
}

ifccParser::ConstExprContext::ConstExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::ConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitConstExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::IdExprContext::ID() {
  return getToken(ifccParser::ID, 0);
}

ifccParser::IdExprContext::IdExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::IdExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitIdExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitwiseOrExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::BitwiseOrExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::BitwiseOrExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::BitwiseOrExprContext::BitwiseOrExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::BitwiseOrExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitBitwiseOrExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MulDivContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::MulDivContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::MulDivContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::MulDivContext::MulDivContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::MulDivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitMulDiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddSubContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::AddSubContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::AddSubContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::AddSubContext::AddSubContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::AddSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAddSub(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CharConstExprContext ------------------------------------------------------------------

tree::TerminalNode* ifccParser::CharConstExprContext::CHAR() {
  return getToken(ifccParser::CHAR, 0);
}

ifccParser::CharConstExprContext::CharConstExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::CharConstExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitCharConstExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegateExprContext ------------------------------------------------------------------

ifccParser::ExprContext* ifccParser::NegateExprContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::NegateExprContext::NegateExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::NegateExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitNegateExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallExprContext ------------------------------------------------------------------

ifccParser::FunctionCallContext* ifccParser::FunctionCallExprContext::functionCall() {
  return getRuleContext<ifccParser::FunctionCallContext>(0);
}

ifccParser::FunctionCallExprContext::FunctionCallExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::FunctionCallExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitFunctionCallExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParExprContext ------------------------------------------------------------------

ifccParser::ExprContext* ifccParser::ParExprContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::ParExprContext::ParExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::ParExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitParExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CmpExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::CmpExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::CmpExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::CmpExprContext::CmpExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::CmpExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitCmpExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AssignementExprContext ------------------------------------------------------------------

ifccParser::AssignmentContext* ifccParser::AssignementExprContext::assignment() {
  return getRuleContext<ifccParser::AssignmentContext>(0);
}

ifccParser::AssignementExprContext::AssignementExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::AssignementExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitAssignementExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotExprContext ------------------------------------------------------------------

ifccParser::ExprContext* ifccParser::NotExprContext::expr() {
  return getRuleContext<ifccParser::ExprContext>(0);
}

ifccParser::NotExprContext::NotExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::NotExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitNotExpr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BitwiseXorExprContext ------------------------------------------------------------------

std::vector<ifccParser::ExprContext *> ifccParser::BitwiseXorExprContext::expr() {
  return getRuleContexts<ifccParser::ExprContext>();
}

ifccParser::ExprContext* ifccParser::BitwiseXorExprContext::expr(size_t i) {
  return getRuleContext<ifccParser::ExprContext>(i);
}

ifccParser::BitwiseXorExprContext::BitwiseXorExprContext(ExprContext *ctx) { copyFrom(ctx); }


std::any ifccParser::BitwiseXorExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<ifccVisitor*>(visitor))
    return parserVisitor->visitBitwiseXorExpr(this);
  else
    return visitor->visitChildren(this);
}

ifccParser::ExprContext* ifccParser::expr() {
   return expr(0);
}

ifccParser::ExprContext* ifccParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  ifccParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  ifccParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 30;
  enterRecursionRule(_localctx, 30, ifccParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(166);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<AssignementExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(153);
      assignment();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<NotExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(154);
      match(ifccParser::T__8);
      setState(155);
      expr(13);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<NegateExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(156);
      match(ifccParser::T__9);
      setState(157);
      expr(12);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<ParExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(158);
      match(ifccParser::T__1);
      setState(159);
      expr(0);
      setState(160);
      match(ifccParser::T__2);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<FunctionCallExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(162);
      functionCall();
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<IdExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(163);
      match(ifccParser::ID);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<ConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(164);
      match(ifccParser::CONST);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<CharConstExprContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(165);
      match(ifccParser::CHAR);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(188);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(186);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MulDivContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(168);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(169);
          antlrcpp::downCast<MulDivContext *>(_localctx)->OP = _input->LT(1);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 14336) != 0))) {
            antlrcpp::downCast<MulDivContext *>(_localctx)->OP = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(170);
          expr(12);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<AddSubContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(171);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(172);
          antlrcpp::downCast<AddSubContext *>(_localctx)->OP = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == ifccParser::T__9

          || _la == ifccParser::T__13)) {
            antlrcpp::downCast<AddSubContext *>(_localctx)->OP = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(173);
          expr(11);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<CmpExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(174);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(175);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 2064384) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(176);
          expr(10);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<BitwiseAndExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(177);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");

          setState(178);
          match(ifccParser::T__20);
          setState(179);
          expr(9);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<BitwiseXorExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(180);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");

          setState(181);
          match(ifccParser::T__21);
          setState(182);
          expr(8);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<BitwiseOrExprContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(183);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");

          setState(184);
          match(ifccParser::T__22);
          setState(185);
          expr(7);
          break;
        }

        default:
          break;
        } 
      }
      setState(190);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool ifccParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 15: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool ifccParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 11);
    case 1: return precpred(_ctx, 10);
    case 2: return precpred(_ctx, 9);
    case 3: return precpred(_ctx, 8);
    case 4: return precpred(_ctx, 7);
    case 5: return precpred(_ctx, 6);

  default:
    break;
  }
  return true;
}

void ifccParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  ifccParserInitialize();
#else
  ::antlr4::internal::call_once(ifccParserOnceFlag, ifccParserInitialize);
#endif
}
