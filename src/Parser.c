/*************************************************************
 * COMPILERS COURSE - Algonquin College
 * Code version: Summer, 2021
 * Author: Svillen Ranev - Paulo Sousa.
 *************************************************************
 * File name: Parser.c
 * Compiler: MS Visual Studio 2019
 * Course: CST 8152 – Compilers, Lab Section: [011, 012, 013]
 * Assignment: A3.
 * Date: May 01 2021
 * Professor: Paulo Sousa
 * Purpose: This file contains all functionalities from Parser.
 * Function list: (...).
 *************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef PARSER_H_
#include "Parser.h"
#endif

/*************************************************************
 * Process Parser
 ************************************************************/
zero_null startParser()
{
    lookahead = tokenizer();
    program();
    matchToken(SEOF_T, NO_ATTR);
    printf("%s%s\n", STR_LANGNAME, ": Source file parsed");
}

/*************************************************************
 * Match Token
 ************************************************************/
/* TODO: This is the main code for match - check your definition */
zero_null matchToken(zero_int tokenCode, zero_int tokenAttribute)
{
    zero_int matchFlag = 1;
    switch (lookahead.code)
    {
    case KW_T:
        // TO_DO: Include the other cases
        if (lookahead.attribute.codeType != tokenAttribute)
            matchFlag = 0;
    default:
        if (lookahead.code != tokenCode)
            matchFlag = 0;
    }
    if (matchFlag && lookahead.code == SEOF_T)
        return;
    if (matchFlag)
    {
        lookahead = tokenizer();
        if (lookahead.code == ERR_T)
        {
            printError();
            lookahead = tokenizer();
            syntaxErrorNumber++;
        }
    }
    else
        syncErrorHandler(tokenCode);
}

/*************************************************************
 * Syncronize Error Handler
 ************************************************************/
zero_null syncErrorHandler(zero_int syncTokenCode)
{
    printError();
    syntaxErrorNumber++;
    while (lookahead.code != syncTokenCode)
    {
        if (lookahead.code == SEOF_T)
            exit(syntaxErrorNumber);
        lookahead = tokenizer();
    }
    if (lookahead.code != SEOF_T)
        lookahead = tokenizer();
}

/*************************************************************
 * Print Error
 ************************************************************/
/* TODO: This is the function to error printing - adjust basically datatypes */
zero_null printError()
{
    Token t = lookahead;
    printf("%s%s%3d\n", STR_LANGNAME, ": Syntax error:  Line:", line);
    printf("*****  Token code:%3d Attribute: ", t.code);
    switch (t.code)
    {
    case ERR_T:
        printf("%s\n", t.attribute.errLexeme);
        break;
    case SEOF_T:
        printf("SEOF_T\t\t%d\t\n", t.attribute.seofType);
        break;
    case STR_T:
        printf("%s\n", bufferGetSubString(stringLiteralTable, t.attribute.contentString));
        break;
    case KW_T:
        printf("%s\n", keywordTable[t.attribute.codeType]);
        break;
    case ASS_OP_T:
    case LPR_T:
    case SEP_T:
        printf("NA\n");
        break;
    // TO_DO: Adjust the other cases
    default:
        printf("%s%s%d\n", STR_LANGNAME, ": Scanner error: invalid token code: ", t.code);
    }
}

/*************************************************************
 * Program statement
 * BNF: <program> -> PLATYPUS { <opt_statements> }
 * FIRST(<program>)= {KW_T (MAIN)}.
 ************************************************************/
zero_null program()
{
    switch (lookahead.code)
    {
    case KW_T:
        if (lookahead.attribute.codeType == PROGRAM)
        {
            matchToken(KW_T, PROGRAM);
            matchToken(ID_T, NO_ATTR);
            matchToken(SEP_T, LEFT_CURLY);
            statements();
            matchToken(SEP_T, RIGHT_CURLY);
            break;
        }
        else
        {
            printError();
        }
    case SEOF_T:; // Empty: for optional
        break;
    default:
        printError();
    }
    printf("%s%s\n", STR_LANGNAME, ": Program parsed");
}

/**
 * Variable Declaration
 * BNF: <variableDeclaration> -> <datatype> <varlist>
 * FIRST(<variableDeclaration>) = {KW_T(int, short, ...), ID_T};
 */
zero_null variableDeclaration()
{
    datatype();
    varlist();
    printf("%s%s\n", STR_LANGNAME, ": Variable declaration parsed.");
}

/**
 * @brief Matches the <datatype> non-terminal
 * BNF: <datatype> -> short | int | long | float | double | String | char | ID_T
 *      FIRST(<datatype>) = { KW_T(int, short, ...), ID_T }
 * @return zero_null
 */
zero_null datatype()
{
    switch (lookahead.code)
    {
    case KW_T:
        if (lookahead.attribute.codeType == SHORT)
        {
            matchToken(KW_T, SHORT);
            break;
        }
        if (lookahead.attribute.codeType == INT)
        {
            matchToken(KW_T, INT);
        }
        if (lookahead.attribute.codeType == LONG)
        {
            matchToken(KW_T, LONG);
        }
        if (lookahead.attribute.codeType == FLOAT)
        {
            matchToken(KW_T, FLOAT);
        }
        if (lookahead.attribute.codeType == DOUBLE)
        {
            matchToken(KW_T, DOUBLE);
        }
        if (lookahead.attribute.codeType == STRING)
        {
            matchToken(KW_T, STRING);
        }
        if (lookahead.attribute.codeType == CHAR)
        {
            matchToken(KW_T, CHAR);
        }
    case ID_T:
        matchToken(ID_T, NO_ATTR);
        break;
    default:
        printError();
    }
    printf("%s%s\n", STR_LANGNAME, ": Datatype parsed");
}

/**
 * @brief Matches the <varlist> non-terminal
 * BNF: <varlist> -> <identifier> <varlistPrime>
 * @return zero_null
 */
zero_null varlist()
{
    matchToken(ID_T, NO_ATTR);
    varlistPrime();
    printf("%s%s\n", STR_LANGNAME, ": Varlist parsed.");
}

/*************************************************************
 * Optional Var List Declarations
 * BNF: <opt_varlist_declarations> -> <varlist_declarations> | e
 * FIRST(<opt_varlist_declarations>) = { e, KW_T (INT), KW_T (FLOAT), KW_T (STRING)}.
 ************************************************************/
zero_null optVarListDeclarations()
{
    // TO_DO: Basic implementation
    ; // Empty
    printf("%s%s\n", STR_LANGNAME, ": Optional Variable List Declarations parsed");
}

/* TODO_205: Continue the development (all non-terminal functions) */

/*************************************************************
 * Optional statement
 * BNF: <opt_statements> -> <statements> | ϵ
 * FIRST(<opt_statements>) = { ϵ , IVID_T, FVID_T, SVID_T, KW_T(IF),
 *				KW_T(WHILE), KW_T(READ), KW_T(WRITE) }
 ************************************************************/
zero_null optionalStatements()
{ // TO_DO: Basic implementation
    switch (lookahead.code)
    {
    case KW_T:
    case ID_T:
        statements();
        break;
    default:; // Empty
    }
    printf("%s%s\n", STR_LANGNAME, ": Optional statements parsed");
}

/*************************************************************
 * Statements
 * BNF: <statements> -> <statement><statementsPrime>
 * FIRST(<statements>) = { IVID_T, FVID_T, SVID_T, KW_T(IF),
 *		KW_T(WHILE), KW_T(READ), KW_T(WRITE) }
 ************************************************************/
zero_null statements()
{
    statement();
    statementsPrime();
    printf("%s%s\n", STR_LANGNAME, ": Statements parsed");
}

/*************************************************************
 * Statements Prime
 * BNF: <statementsPrime> -> <statement><statementsPrime> | ϵ
 * FIRST(<statementsPrime>) = { ϵ , IVID_T, FVID_T, SVID_T,
 *		KW_T(IF), KW_T(WHILE), KW_T(READ), KW_T(WRITE) }
 ************************************************************/
zero_null statementsPrime()
{
    switch (lookahead.code)
    {
    case KW_T:
        if (lookahead.attribute.codeType == WRITE ||
            lookahead.attribute.codeType == READ ||
            lookahead.attribute.codeType == IF ||
            lookahead.attribute.codeType == ELSE ||
            lookahead.attribute.codeType == WHILE ||
            lookahead.attribute.codeType == SWITCH)
        {
            statement();
            statementsPrime();
            break;
        }
    default:; // empty string
    }
}

/*************************************************************
 * Single statement
 * BNF: <statement> ->  <assignment statement> | <selection statement> |
 *	<iteration statement> | <input statement> | <output statement>
 * FIRST(<statement>) = { ID_T, KW_T(IF), KW_T(WHILE),
 *			KW_T(READ), KW_T(WRITE) }
 ************************************************************/
zero_null statement()
{
    switch (lookahead.code)
    {
    case KW_T:
        switch (lookahead.attribute.codeType)
        {
        case WRITE:
            outputStatement();
            break;
        case READ:
            inputStatement();
            break;
        case IF:
        case ELSE:
            selectionStatement();
            break;
        case FOR:
        case FOREACH:
        case WHILE:
            iterationStatement();
        default:
            printError();
        }
        break;
    case ID_T:
        assignmentStatement();
    default:
        printError();
    }
    printf("%s%s\n", STR_LANGNAME, ": Statement parsed");
}

zero_null iterationStatement()
{
    switch (lookahead.code)
    {
    case KW_T:
        switch (lookahead.attribute.codeType)
        {
        case WHILE:
            whileStatement();
            break;
        case DO:
            doWhileStatement();
            break;
        case FOR:
            forStatement();
            break;
        case FOREACH:
            forEachStatement();
            break;
        default:
            printError();
            break;
        }
    default:
        printError();
        break;
    }
}

zero_null whileStatement()
{
    matchToken(KW_T, WHILE);
    matchToken(SEP_T, LEFT_PARENS);
    conditionalExpression();
    matchToken(SEP_T, RIGHT_PARENS);
    matchToken(SEP_T, LEFT_CURLY);
    optionalStatements();
    matchToken(SEP_T, RIGHT_CURLY);
}

zero_null doWhileStatement()
{
    matchToken(KW_T, DO);
    matchToken(SEP_T, LEFT_CURLY);
    optionalStatements();
    matchToken(SEP_T, RIGHT_CURLY);
    matchToken(KW_T, WHILE);
    matchToken(SEP_T, LEFT_PARENS);
    conditionalExpression();
    matchToken(SEP_T, RIGHT_PARENS);
}

zero_null forStatement()
{
    matchToken(KW_T, FOR);
    matchToken(SEP_T, LEFT_PARENS);
    assignmentExpression();
    matchToken(SEP_T, SEMICOLON);
    conditionalExpression();
    matchToken(SEP_T, SEMICOLON);
    arithmeticExpression();
    matchToken(SEP_T, RIGHT_PARENS);
    matchToken(SEP_T, LEFT_CURLY);
    optionalStatements();
    matchToken(SEP_T, RIGHT_CURLY);
}

zero_null forEachStatement()
{
    matchToken(KW_T, FOREACH);
    matchToken(SEP_T, LEFT_PARENS);
    matchToken(ID_T, NO_ATTR);
    matchToken(KW_T, IN);
    listGroup();
    matchToken(SEP_T, LEFT_CURLY);
    optionalStatements();
    matchToken(SEP_T, RIGHT_CURLY);
}

zero_null listGroup()
{
}
/*************************************************************
 * Output Statement
 * BNF: <output statement> -> WRITE (<output statementPrime>);
 * FIRST(<output statement>) = { KW_T(WRITE) }
 ************************************************************/
zero_null outputStatement()
{
    matchToken(KW_T, WRITE);
    matchToken(SEP_T, LEFT_PARENS);
    switch (lookahead.code)
    {
    case STR_T:
        matchToken(STR_T, NO_ATTR);
        break;
    case ID_T:
        matchToken(ID_T, NO_ATTR);
        break;
    }
    matchToken(SEP_T, RIGHT_PARENS);
    printf("%s%s\n", STR_LANGNAME, ": Output statement parsed");
}

zero_null inputStatement()
{
    matchToken(KW_T, READ);
    matchToken(SEP_T, LEFT_PARENS);
    switch (lookahead.code)
    {
    case STR_T:
        matchToken(STR_T, NO_ATTR);
        break;
    case ID_T:
        matchToken(ID_T, NO_ATTR);
        break;
    }
    matchToken(SEP_T, RIGHT_PARENS);
    printf("%s%s\n", STR_LANGNAME, ": Input statement parsed");
}

zero_null selectionStatement()
{
    if (lookahead.code == KW_T)
    {
        switch (lookahead.attribute.codeType)
        {
        case IF:
            matchToken(KW_T, IF);
            break;
        case WHILE: // Should BE IF, IF ELSE, SWITCH... NOT WHILE
            matchToken(KW_T, WHILE);
            break;
        }
    }
    printf("%s%s\n", STR_LANGNAME, ": Selection statement parsed");
}

zero_null ifStatement()
{
    matchToken(KW_T, IF);
    matchToken(SEP_T, LEFT_PARENS);
    conditionalExpression();
    matchToken(SEP_T, RIGHT_PARENS);
    matchToken(SEP_T, LEFT_CURLY);
    optionalStatements();
    matchToken(SEP_T, RIGHT_CURLY);
    printf("%s%s\n", STR_LANGNAME, ": If statement parsed");
}

zero_null elseStatement()
{
    matchToken(KW_T, ELSE);
    matchToken(SEP_T, LEFT_CURLY);
    optionalStatements();
    matchToken(SEP_T, RIGHT_CURLY);
    printf("%s%s\n", STR_LANGNAME, ": Else statement parsed");
}

zero_null ifElseStatement()
{
    ifStatement();
    elseStatement();
    printf("%s%s\n", STR_LANGNAME, ": If else statement parsed");
}

zero_null ifElseStatements()
{
}

zero_null switchStatement()
{
    matchToken(KW_T, SWITCH);
    matchToken(SEP_T, LEFT_PARENS);
    matchToken(ID_T, NO_ATTR);
    matchToken(SEP_T, RIGHT_PARENS);
    switchBlock();
    printf("%s%s\n", STR_LANGNAME, ": Switch statement parsed");
}

zero_null switchBlock()
{
    matchToken(SEP_T, LEFT_CURLY);
    caseBlocks();
    matchToken(SEP_T, RIGHT_CURLY);
    printf("%s%s\n", STR_LANGNAME, ": Switch block parsed");
}

zero_null caseBlocks()
{
    statement();
    statementsPrime();
    printf("%s%s\n", STR_LANGNAME, ": Case blocks parsed");
}

zero_null caseBlockPrime()
{
    switch (lookahead.code)
    {
    case KW_T:
        if (lookahead.attribute.codeType == CASE)
        {
            caseBlock();
            caseBlockPrime();
            break;
        }
    default:
        printError();
    }
}

zero_null caseBlock()
{
    if (lookahead.code == KW_T)
    {
        switch (lookahead.attribute.codeType)
        {
        case CASE:
            matchToken(KW_T, CASE);
            matchToken(ID_T, NO_ATTR);
            matchToken(SEP_T, COLON);
            optionalStatements();
            break;
        case DEFAULT:
            matchToken(KW_T, CASE);
            matchToken(SEP_T, COLON);
            optionalStatements();
            break;
        default:
            printError();
        }
    }
    printf("%s%s\n", STR_LANGNAME, ": Case block parsed");
}

zero_null assignmentStatement()
{
    assignmentExpression();
    printf("%s%s\n", STR_LANGNAME, ": Assignment statement parsed");
}

zero_null assignmentExpression()
{
    matchToken(ID_T, NO_ATTR);
    matchToken(ASS_OP_T, NO_ATTR);
    expression();
    printf("%s%s\n", STR_LANGNAME, ": Assignment expression parsed");
}

zero_null conditionalExpression()
{
}

zero_null logicalOrExpression()
{
}

zero_null logicalNotExpression()
{
    matchToken(LOG_OP_T, NOT);
    relationalExpression();
}

zero_null logicalAndExpression()
{
}

zero_null relationalExpression()
{
}
/*************************************************************
 * Expression
 * BNF: <expression> -> <term> <expressionPrime>
 * FIRST(<expression>) = { KW_T(...) }
 ************************************************************/
zero_null expression()
{
    term();
    expressionPrime();
}

/*************************************************************
 * ExpressionPrime
 * BNF: <expressionPrime> -> + <term> <expressionPrime>
 *                          | - <term> <expressionPrime>
 *                          | ε
 * FIRST(<output statement>) = { KW_T(...) }
 ************************************************************/
zero_null expressionPrime()
{
    switch (lookahead.code)
    {
    case ART_OP_T:
        switch (lookahead.attribute.arithmeticOperator)
        {
        case ADD:
        case SUB:
            term();
            expressionPrime();
        }
        break;
    default: // empty
        break;
    }
}

/*************************************************************
 * Term
 * BNF: <term> -> <term><factorPrime>
 * FIRST(<output statement>) = { KW_T(...) }
 ************************************************************/
zero_null term()
{
    factor();
    termPrime();
}

/**
 * @brief Matches the <termPrime> non-terminal
 * BNF: <termPrime> -> * <factor> <termPrime>
 *                   | / <factor> <termPrime>
 *                   | ε
 * @return zero_null
 */
zero_null termPrime()
{
    switch (lookahead.code)
    {
    case ART_OP_T:
        switch (lookahead.attribute.arithmeticOperator)
        {
        case MUL:
        case DIV:
            factor();
            termPrime();
        }
        break;
    default: // empty
        break;
    }
}

/**
 * @brief Matches the <factor> non-terminal
 * BNF: <factor> -> ( <expression> ) | - <expression> | ϵ
 * @return zero_null
 */
zero_null factor()
{
    switch (lookahead.code)
    {
    case SEP_T:
        if (lookahead.attribute.separatorType == LEFT_PARENS)
        {
            matchToken(SEP_T, LEFT_PARENS);
            expression();
            matchToken(SEP_T, RIGHT_PARENS);
        }
        break;
    /* is it really right to use an artihmetic substitution, rather than
     separate unary negative operator?
     TODO: Implement unary operators (+,-,++,--,~) */
    case ART_OP_T:
        if (lookahead.attribute.arithmeticOperator == SUB)
        {
            expression();
        }
        break;
    default:
        printError();
    }
}

zero_null literal()
{
    switch (lookahead.code)
    {
    case INL_T:
        matchToken(INL_T, lookahead.attribute.intValue);
        break;
    case FPL_T:
        matchToken(FPL_T, lookahead.attribute.floatValue);
        break;
    default:
        printError();
    }
}
