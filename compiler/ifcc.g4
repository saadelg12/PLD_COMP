grammar ifcc;

axiom : prog EOF ;

prog : 'int' 'main' '(' ')' '{' stmt* '}' ;

block : '{' stmt* '}' ;

stmt : declaration
     | assignment
     | return_stmt
     | block ;

declaration : 'int' VAR ('=' expr)? ';' ;

assignment : VAR '=' expr ';' ;

return_stmt : RETURN expr ';' ;

RETURN : 'return' ;

expr
    : '!' expr                          # NotExpr
    | '-' expr                          # NegateExpr
    | expr OP=('*' | '/' | '%') expr     # MulDiv
    | expr OP=('+' | '-') expr           # AddSub
    | expr ('<' | '>' | '<=' | '>=' | '==' | '!=') expr   # CmpExpr
    | expr ('&' | '|' | '^') expr        # BitwiseExpr
    | '(' expr ')'                       # ParExpr
    | VAR                               # VarExpr
    | CONST                             # ConstExpr
    | CHAR                              # CharConstExpr
    ;

VAR: [a-zA-Z_][a-zA-Z_0-9]* ;
CONST : [0-9]+ ;
CHAR : '\'' . '\'' ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN);
