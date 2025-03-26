grammar ifcc;

axiom : function EOF ; // Replaced 'prog' with 'function'

function
    : type ID '(' ')' block ; // Updated function definition to use 'ID' and 'block'

block
    : '{' stmt* '}' ; // Defined 'block' as a sequence of statements enclosed in braces

stmt
    : declaration
    | assignment
    | return_stmt
    ;

declaration: 'int' ID ('=' expr)? ';' ; // Replaced 'VAR' with 'ID'
assignment: ID '=' expr ';' ; // Replaced 'VAR' with 'ID'
return_stmt: RETURN expr ';' ;

type
    : 'int'
    | 'void'
    ;

RETURN : 'return' ;

expr
    : '!' expr                  # NotExpr
    | '-' expr                  # NegateExpr
    | expr OP = ('*' | '/' | '%') expr   # MulDiv
    | expr OP = ('+' | '-') expr         # AddSub
    | expr ('<' | '>' | '<=' | '>=' | '==' | '!=') expr  # CmpExpr
    | expr ('&') expr                        # BitwiseAndExpr
    | expr ('^') expr                        # BitwiseXorExpr
    | expr ('|') expr                        # BitwiseOrExpr
    | '(' expr ')'                  # ParExpr
    | ID '(' (expr (',' expr)*)? ')' # FunctionCallExpr 
    | ID                           # VarExpr 
    | CONST                         # ConstExpr
    | CHAR                          # CharConstExpr
    ;

ID: [a-zA-Z_][a-zA-Z_0-9]* ; 
CONST : [0-9]+ ;
CHAR : '\'' . '\'' ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);