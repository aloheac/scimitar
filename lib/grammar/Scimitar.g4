grammar Scimitar;

/******************************************************************************
 * PARSER RULE DEFINITIONS
 *****************************************************************************/

/* Root-level parser rules. */

root : action*;

action : ( param | function | setParam | setOption | setFunction | group | ungroup | end | system ) NEWLINE  #  EngineAction
       | run  # RunBlock
       | userFunction  # UserFunctionDefinition
       | COMMENT  #  ExprComment;


/* Action statement parser rules. */

param : PARAM TYPE IDENTIFIER parameterValue ( '{' option* '}' )?;

function : PARAM 'function' IDENTIFIER  expr ( '{' option* '}' )?;

setParam : SET PARAM IDENTIFIER '{' option+ '}';

setOption : SET OPTION ( scriptOption '=' STRING )+;

setFunction : SET PARAM IDENTIFIER '{' ('function' '=' expr | option+ )+ '}';

group : GROUP IDENTIFIER+;

ungroup : UNGROUP IDENTIFIER+;

system : SYSTEM (IDENTIFIER '=' systemOption)+;


/* Parameter value parser rules. */

parameterValue : expr         #  ParameterValueExpr
               | range        #  ParameterValueRange
               | list         #  ParameterValueList
               | STRING       #  ParameterValueString;

range : expr ':' expr ':' expr;

list : '[' (WHITESPACE? listElement WHITESPACE? ',' WHITESPACE?)* WHITESPACE? listElement WHITESPACE? ']';

listElement : expr   #  ListElementExpr
            | range  #  ListElementRange;

option : OPT '=' optionValue  #  StandardOption
       | 'hide'  #  HideOption;

optionValue : expr    #  OptionValueExpr
            | range   #  OptionValueRange
            | list    #  OptionValueList
            | FORMAT  #  OptionValueFormat
            | STRING  #  OptionValueString;

scriptOption : IDENTIFIER | IDENTIFIER '.' IDENTIFIER;

systemOption : STRING | NUMERIC;


/* Mathematical expression parser rules. */

expr : '(' expr ')'       # Parenthesis
     | expr '[' expr ']'  # Element
     | expr POW expr      # OpPow
     | expr MUL expr      # OpMul
     | expr DIV expr      # OpDiv
     | expr ADD expr      # OpAdd
     | expr SUB expr      # OpSub
     | SUB expr           # Negate
     | IDENTIFIER '(' userFunctionPassedArgList? ')'  # ExprFunction
     | NUMERIC            # Literal
     | IDENTIFIER         # Identifier;


/* Run loop and block parser rules. */

run : RUN '{' loopStmt* '}';

block : loopStmt*;

loopStmt : IF '(' condition ')' '{' loopStmt* '}'  # IfStmt
         | IF '(' condition ')' '{' block '}' ELSE '{' block '}'  # IfElseStmt
         | REMOVE ';'                        # RemoveStmt
         | IDENTIFIER '=' expr ';'           # AssignmentStmt
         | COMMENT                           # LoopComment;

condition: '(' condition ')'                 # ConditionParen
         | condition BOOL_OP condition       # BooleanOp
         | NEG_OP condition                  # NegateOp
         | expr REL_OP expr                  # Relation
         | BOOL_LITERAL                      # BooleanLiteral
         | IDENTIFIER                        # BooleanIdentifier;

end : END;


/* User function definition and block parser rules. */

userFunction : 'def' IDENTIFIER '(' userFunctionArgList? ')' '{' userFunctionStmt* '}';

userFunctionArgList : (WHITESPACE? userFunctionArgument WHITESPACE? ',' WHITESPACE?)* WHITESPACE? userFunctionArgument WHITESPACE?;

userFunctionPassedArgList :  (WHITESPACE? genericExpression WHITESPACE? ',' WHITESPACE?)* WHITESPACE? genericExpression WHITESPACE?;

userFunctionArgument : TYPE IDENTIFIER;

userFunctionBlock : userFunctionStmt*;

genericExpression : expr | condition;

userFunctionStmt : TYPE IDENTIFIER ('=' genericExpression )? NEWLINE  # UserFunctionDeclaration
                 | IDENTIFIER '=' genericExpression ';'  # UserFunctionAssignment
                 | IDENTIFIER ':' 'append' TYPE '(' genericExpression ')' ';'  # UserFunctionListAppend
                 | IDENTIFIER ':' 'remove' expr ';'  # UserFunctionListRemove
                 | IF '(' condition ')' '{' userFunctionBlock '}' ( ELSE '{' userFunctionBlock '}' )?  # UserFunctionConditional
                 | RETURN expr ';' # UserFunctionReturn
                 | FOR '(' TYPE IDENTIFIER '=' expr ',' condition ',' expr ')' '{' userFunctionBlock '}'  # UserFunctionForLoop
                 | WHILE '(' condition ')' '{' userFunctionBlock '}'  # UserFunctionWhileLoop
                 | CONTINUE ';' # UserFunctionContinue
                 | BREAK ';' # UserFunctionBreak;

/******************************************************************************
 * LEXICAL RULES
 *****************************************************************************/

NEWLINE : ';';

OPT : 'dir' | 'format' | 'value';

OPTION : 'option';

END : 'end';

PARAM : 'param';

SET : 'set';

GROUP : 'group';

UNGROUP : 'ungroup';

RUN : 'run';

RETURN : 'return';

TYPE : 'real' | 'int' | 'string' | 'bool' | 'list';

IF : 'if';

FOR : 'for';

WHILE : 'while';

CONTINUE : 'continue';

BREAK : 'break';

ELSE : 'else';

SYSTEM : 'system';

REL_OP : '==' | '!=' | '>' | '<' | '>=' | '<=';

BOOL_OP : 'and' | 'or' | 'eq';

NEG_OP : 'not';

REMOVE : 'remove';

BOOL_LITERAL : 'true' | 'false';

ADD : '+';

SUB : '-';

MUL : '*';

DIV : '/';

POW : '**';

NUMERIC : INTEGER | SCIENTIFIC;

FORMAT : '%' [0-9]* '.'? [0-9]* [dfs];

IDENTIFIER : ( 'a'..'z' | 'A'..'Z' | '_' ) ( 'a'..'z' | 'A'..'Z' | '_' | '0'..'9' )*;

STRING : '"' ~["\r\n]* '"';

COMMENT : '//' ~[\r\n]* -> skip;

BLOCK_COMMENT : '/*' .*? '*/' -> skip;

WHITESPACE : [ \r\n\t]+ -> skip;

fragment INTEGER : ('0'..'9')+;

fragment FLOAT : ('0'..'9')+ ('.' ('0'..'9')+)?;

fragment SIGN : ('+' | '-' );

fragment SCIENTIFIC : FLOAT (('E' | 'e') SIGN? INTEGER)?;
