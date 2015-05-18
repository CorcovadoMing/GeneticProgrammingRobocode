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

	expression -> expression, operator, expression
	expression := value

	operator := +
	operator := -
	operator := *
	operator := /

	value := constant
	value := variable

	constant -> null (random real-number)
	variable -> null (random choose from table)

	+ -> null
	- -> null
	* -> null
	/ -> null

	confitionalExpression := value, compareOperator, value
	
	compareOperator := >
	compareOperator := <
	compareOperator := ==
	compareOperator := !=

	> -> null
	< -> null
	== -> null
	!= -> null

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

	expression := value

	operator := +
	operator := -
	operator := *
	operator := /

	value := constant
	value := variable

	constant -> null (random real-number)
	variable -> null (random choose from table)

	+ -> null
	- -> null
	* -> null
	/ -> null

	confitionalExpression := value, compareOperator, value
	
	compareOperator := >
	compareOperator := <
	compareOperator := ==
	compareOperator := !=

	> -> null
	< -> null
	== -> null
	!= -> null