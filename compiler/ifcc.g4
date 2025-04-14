grammar ifcc;

axiom : prog EOF ;

prog : (functionDef|functionDec)* mainFunction (functionDef|functionDec)* ;

mainFunction : TYPE 'main' '(' ')' block ;

functionDef: TYPE ID '(' (parameter_list)? ')' block;

functionDec: TYPE ID'(' (parameter_list)? ')' ';';

parameter_list: parameter (',' parameter)*;

parameter: TYPE ID;

TYPE : 'int' | 'double' | 'void';

block : '{' stmt* '}';

stmt : declaration ';'
     | assignment ';'
     | return_stmt 
     | functionCall ';'  
     | if_stmt
     | block 
     | while_stmt;

declaration : TYPE ID ('=' expr)? ;

assignment: ID '=' expr ;

return_stmt : RETURN expr ';' ;

RETURN : 'return' ;

functionCall : ID '(' (expr (',' expr)*)? ')' ;

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
    | ID                               # IdExpr
    | CONST                             # ConstExpr
    | CHAR                              # CharConstExpr

    ;

IF : 'if';
ELSE: 'else';
WHILE : 'while';
ID : [a-zA-Z_][a-zA-Z_0-9]* ;
CONST
    : [0-9]+ ('.' [0-9]*)?     // 3 ou 3.14
    | '.' [0-9]+              // .42
    ;
CHAR : '\'' . '\'' ;



COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN);
