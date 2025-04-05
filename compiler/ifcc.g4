grammar ifcc;

axiom : prog EOF ;

prog : 'int' 'main' '(' ')' block ;

block : '{' stmt* '}' ;

stmt : declaration ';'
     | assignment ';'
     | expr ';'  // Permet d'écrire des expressions comme stmt
     | return_stmt 
     | block 
     | if_stmt
     | while_stmt;

declaration : 'int' VAR ('=' expr)? ;


assignment: VAR '=' expr ;

return_stmt : RETURN expr ';' ;


RETURN : 'return' ;
if_stmt : IF '(' expr ')' block (ELSE block)? ;
while_stmt : WHILE '(' expr ')' block;

IF : 'if';
ELSE: 'else';
WHILE : 'while';


expr
    : function_call                     # FunctionCallExpr
    |assignment                         # AssignementExpr 
    | '!' expr                          # NotExpr
    | '-' expr                          # NegateExpr
    | expr OP=('*' | '/' | '%') expr     # MulDiv
    | expr OP=('+' | '-') expr           # AddSub
    | expr ('<' | '>' | '<=' | '>=' | '==' | '!=') expr   # CmpExpr
    | expr ('&') expr                # BitwiseAndExpr
    | expr ('^') expr                # BitwiseXorExpr
    | expr ('|') expr                # BitwiseOrExpr
    | '(' expr ')'                       # ParExpr
    | VAR                               # VarExpr
    | CONST                             # ConstExpr
    | CHAR                              # CharConstExpr
    ;

function_call : FUNC '(' (expr)? ')' ;  // Appel de fonction avec ou sans argument

FUNC : 'putchar' | 'getchar' ;  // Définition des fonctions externes

VAR: [a-zA-Z_][a-zA-Z_0-9]* ;
CONST : [0-9]+ ;
CHAR : '\'' . '\'' ;

COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS : [ \t\r\n] -> channel(HIDDEN);

