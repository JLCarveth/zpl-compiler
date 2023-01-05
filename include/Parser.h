/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
*************************************************************
* File name: Parser.h
* Compiler: MS Visual Studio 2019
* Author: Svillen Ranev - Paulo Sousa
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A3.
* Date: May 01 2021
* Purpose: This file is the main header for Parser (.h)
* Function list: (...).
*************************************************************/

#ifndef PARSER_H_
#define PARSER_H_

/* Inclusion section */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif
#ifndef BUFFER_H_
#include "Buffer.h"
#endif
#ifndef SCANNER_H_
#include "Scanner.h"
#endif

/* Global vars */
static Token lookahead;
zero_int syntaxErrorNumber = 0;
extern Buffer* stringLiteralTable;
extern zero_int line;
extern Token tokenizer();
extern zero_char* keywordTable[];

/* TO_DO: Define the name of your language */
#define STR_LANGNAME "Zero"

/* TO_DO: Create ALL constants for keywords (sequence given in table.h) */
/* Constants */
enum KEYWORDS
{
	NO_ATTR = -1,
	BYTE,
	SHORT,
	INT,
	LONG,
	FLOAT,
	DOUBLE,
	CHAR,
	STRING,
	VOID,
	ENUM,
	CLASS,
	NEW,
	IF,
	ELSE,
	DO,
	WHILE,
	FOR,
	FOREACH,
	SWITCH,
	CASE,
	BREAK,
	CONTINUE,
	DEFAULT,
	PROGRAM,
	WRITE,
	READ,
  IN
	/* TO_DO: Continue with your keywords */
};

/* Function definitions */
zero_null startParser();
zero_null matchToken(zero_int, zero_int);
zero_null syncErrorHandler(zero_int);
zero_null printError();

/* TODO: Place ALL non-terminal function declarations */
zero_null additiveArithmeticExpression();
zero_null additiveArithmeticExpressionPrime();
zero_null arithmeticExpression();
zero_null assignmentExpression();
zero_null assignmentStatement();
zero_null codeSession();
zero_null conditionalExpression();
zero_null dataSession();
zero_null fltVariableIdentifier();
zero_null fltVarList();
zero_null fltVarListPrime();
zero_null inputStatement();
zero_null intVariableIdentifier();
zero_null intVarList();
zero_null intVarListPrime();
zero_null iterationStatement();
zero_null logicalAndExpression();
zero_null logicalAndExpressionPrime();
zero_null logicalNotExpression();
zero_null logicalOrExpression();
zero_null logicalOrExpressionPrime();
zero_null multiplicativeArithmeticExpression();
zero_null multiplicativeArithmeticExpressionPrime();
zero_null fltVarListDeclaration();
zero_null intVarListDeclaration();
zero_null strVarListDeclaration();
zero_null optVarListDeclarations();
zero_null optionalStatements();
zero_null outputStatement();
zero_null outputVariableList();
zero_null primaryArithmeticExpression();
zero_null primaryRelationalArithmeticExpression();
zero_null primaryRelationalStringExpression();
zero_null primaryStringExpression();
zero_null program();
zero_null relationalArithmeticExpression();
zero_null relationalArithmeticOperator();
zero_null relationalExpression();
zero_null relationalStringExpression();
zero_null relationalStringOperator();
zero_null selectionStatement();
zero_null ifStatement();
zero_null elseStatement();
zero_null ifElseStatement();
zero_null ifElseStatements();
zero_null switchStatement();
zero_null switchBlock();
zero_null caseBlocks();
zero_null caseBlock();
zero_null statement();
zero_null statements();
zero_null statementsPrime();
zero_null stringExpression();
zero_null stringExpressionPrime();
zero_null strVariableIdentifier();
zero_null strVarList();
zero_null strVarListPrime();
zero_null variableIdentifier();
zero_null variableList();
zero_null variableListPrime();
zero_null varListDeclarations();
zero_null varListDeclaration();
zero_null varListDeclarationsPrime();

zero_null datatype();
zero_null varlist();
zero_null varlistPrime();
zero_null whileStatement();
zero_null doWhileStatement();
zero_null forStatement();
zero_null forEachStatement();
zero_null listGroup();
zero_null expression();
zero_null expressionPrime();
zero_null term();
zero_null termPrime();
zero_null factor();
//zero_null preCondition();

#endif
