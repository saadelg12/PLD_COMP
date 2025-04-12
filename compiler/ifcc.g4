grammar ifcc;

axiom : prog EOF ;

prog : (functionDef|functionDec)+;

functionDef: TYPE VAR '(' (parameter_list)? ')' block;

functionDec: TYPE VAR'(' (parameter_list)? ')' ';';

parameter_list: parameter (',' parameter)*;

parameter: TYPE VAR;

TYPE : 'int' | 'void';

block : '{' stmt* '}';

stmt : declaration ';'
     | assignment ';'
     | return_stmt 
     | functionCall ';'  
     | if_stmt
     | block 
     | while_stmt;

declaration : TYPE VAR ('=' expr)? ;

assignment: VAR '=' expr ;

return_stmt : RETURN expr ';' ;

RETURN : 'return' ;

functionCall : VAR '(' (expr (',' expr)*)? ')' ;

if_stmt : IF '(' expr ')' block(ELSE block)? ;
while_stmt : WHILE '(' expr ')' block;

expr
    : assignment                       # AssignementExpr 
    | '!' expr                          # NotExpr
    | '-' expr                          # NegateExpr
    | expr OP=('*' | '/' | '%') expr     # MulDiv
    | expr OP=('+' | '-') expr           # AddSub
    | expr ('<' | '>' | '<=' | '>=' | '==' | '!=') expr   # CmpExpr
    | expr ('&') expr                # BitwiseAndExpr
    | expr ('^') expr                # BitwiseXorExpr
    | expr ('|') expr                # BitwiseOrExpr
    | '(' expr ')'                       # ParExpr
    | functionCall                      # FunctionCallExpr
    | VAR                               # VarExpr
    | CONST                             # ConstExpr
    | CHAR                              # CharConstExpr
    ;

IF : 'if';
ELSE: 'else';
WHILE : 'while';
VAR: [a-zA-Z_][a-zA-Z_0-9]* ;
CONST : [0-9]+ ;
CHAR : '\'' . '\'' ;



COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN);
