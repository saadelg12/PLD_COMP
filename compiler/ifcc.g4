grammar ifcc;

axiom : prog EOF ;

prog : 'int' 'main' '(' ')' '{' stmt*'}' ;
stmt: declaration | assignment | return_stmt ;

declaration: 'int' VAR ('=' expr)? ';' ;
assignment: VAR '=' expr ';' ;
return_stmt: RETURN expr ';' ;

RETURN : 'return' ;

expr
    : CONST                  # ConstExpr
    | VAR                    # VarExpr
    | expr ('*' | '/') expr   # MulDiv
    | expr ('+' | '-') expr   # AddSub
    | '(' expr ')'            # Parenthesized
    ;

VAR: [a-zA-Z_][a-zA-Z_0-9]* ;
CONST : [0-9]+ ;



COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);