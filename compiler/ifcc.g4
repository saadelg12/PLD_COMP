grammar ifcc;

axiom : prog EOF ;

prog : (functionDef | functionDec)+ ;  // Support de plusieurs fonctions

functionDef : TYPE VAR '(' (parameter_list)? ')' block ;
functionDec : TYPE VAR '(' (parameter_list)? ')' ';' ;

parameter_list : parameter (',' parameter)* ;
parameter : TYPE VAR ;

TYPE : 'int' | 'double' | 'void' ;

block : '{' stmt* '}' ;

stmt : declaration ';'
     | assignment ';'
     | expr ';'
     | return_stmt 
     | block 
     | if_stmt
     | while_stmt;

declaration : TYPE VAR ('=' expr)? ;

assignment: VAR '=' expr ;

return_stmt : RETURN expr ';' ;

RETURN : 'return' ;
if_stmt : IF '(' expr ')' block (ELSE block)? ;
while_stmt : WHILE '(' expr ')' block;

IF : 'if';
ELSE: 'else';
WHILE : 'while';

expr
    : functionCall                     # FunctionCallExpr
    | assignment                       # AssignementExpr 
    | '!' expr                         # NotExpr
    | '-' expr                         # NegateExpr
    | expr OP=('*' | '/' | '%') expr   # MulDiv
    | expr OP=('+' | '-') expr         # AddSub
    | expr ('<' | '>' | '<=' | '>=' | '==' | '!=') expr   # CmpExpr
    | expr '&' expr                    # BitwiseAndExpr
    | expr '^' expr                    # BitwiseXorExpr
    | expr '|' expr                    # BitwiseOrExpr
    | '(' expr ')'                     # ParExpr
    | VAR                              # VarExpr
    | CONST                            # ConstExpr
    | CHAR                             # CharConstExpr
    ;

functionCall : VAR '(' (expr (',' expr)*)? ')' ;

VAR : [a-zA-Z_][a-zA-Z_0-9]* ;

CONST
    : [0-9]+ ('.' [0-9]*)?     // 3 ou 3.14
    | '.' [0-9]+              // .42
    ;

CHAR : '\'' . '\'' ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN);
