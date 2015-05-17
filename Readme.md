# Evolved a Robocode tank using genetic programming

------------

###**RuleSet**:

`:=` Means `Transform`

`->` Means `Expand`

#### Growth Rules

    statements := statement, statements, controlStatement
    statements := statement

    statement := controlStatement    
    statement := argumentRequiring0   
    statement := argumentRequiring1
    
    controlStatement := flowStatement
    
    flowStatement := whileStatement   
    flowStatement := ifStatement
    
    ifStatement := ifStatement, elseIfStatement   
    ifStatement -> conditionalExpresiion, statement

	elseIfStatement := elseIfStatement, elseIfStatement
	elseIfStatement := ElseIfStatement, elseStatement
	elseIfStatement -> confitionalExpression, statements

	whileStatement -> confitionalExpression, statements

	argumentRequiring0 -> null

	elseStatement -> statements

	argumentRequiring1 -> expression

	expression := operator
	expression := value

	operator := plus
	operator := minus
	operator := multiple
	operator := divide

	value := constant
	value := variable

	constant -> null (random real-number)
	variable -> null (random choose from table)

	plus -> value, value
	minus -> value, value
	multiple -> value, value
	divide -> value, value

	confitionalExpression -> null //[UNDONE]



#### Terminal Rules

    statements := statement
  
    statement := argumentRequiring0   
    statement := argumentRequiring1
    
    controlStatement := flowStatement
    
    flowStatement := whileStatement   
    flowStatement := ifStatement
    
    ifStatement -> conditionalExpresiion, statement

	elseIfStatement -> confitionalExpression, statements

	whileStatement -> confitionalExpression, statements

	argumentRequiring0 -> null

	elseStatement -> statements

	argumentRequiring1 -> expression

	expression := operator
	expression := value

	operator := plus
	operator := minus
	operator := multiple
	operator := divide

	value := constant
	value := variable

	constant -> null (random real-number)
	variable -> null (random choose from table)

	plus -> value, value
	minus -> value, value
	multiple -> value, value
	divide -> value, value

	confitionalExpression -> null //[UNDONE]