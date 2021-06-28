/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
*************************************************************
* File name: Scanner.h
* Compiler: MS Visual Studio 2019
* Author: Svillen Ranev - Paulo Sousa
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A2.
* Date: May 01 2021
* Purpose: This file is the main header for Scanner (.h)
* Function list: (...).
*************************************************************/

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

#ifndef SCANNER_H_
#define SCANNER_H_

#ifndef NULL
#include <_null.h> /* NULL pointer constant is defined there */
#endif

/*#pragma warning(1:4001) */	/*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*/	/* to enforce C89 comments - to make // comments an error */

/* Constants */
#define VID_LEN 8   /* variable identifier length */
#define ERR_LEN 20  /* error message length */
#define NUM_LEN 5   /* maximum number of digits for IL */

#define RTE_CODE 1   /* Value for run-time error */

/* TO_DO 2: Define Token codes - Create your token classes */
enum TOKENS {
    ERR_T,      /* Error token */
    ID_T,       /* Variable identifier token */
    INL_T,      /* Integer literal token */
    FPL_T,      /* Floating point literal token */
    CL_T,       /* Character literal token */
    STR_T,      /* String literal token */
    SCC_OP_T,   /* String concatenation operator token: (++) */
    ASS_OP_T,   /* Assignment operator token */
    ART_OP_T,   /* Arithmetic operator token (+,-,*,/)*/
    LOG_OP_T,   /* Logical operator token (AND, OR, NOT) */
    REL_OP_T,   /* Relational operator token ( < > <= >= != == )*/
    LPR_T,      /* Left parenthesis token */
    SEP_T,      /* Separator token */
    KW_T,       /* Keyword token */
    RTE_T,      /* Run-time error token */
    SEOF_T      /* Source end-of-file token */
};

/* CHECK: Operators token attributes */
typedef enum ArithmeticOperators { ADD, SUB, MUL, DIV } AriOperator;
typedef enum RelationalOperators { EQ, NE, GT, GTE, LT, LTE } RelOperator;
typedef enum LogicalOperators { AND, OR, NOT } LogOperator;
typedef enum Separators { LEFT_PARENS, RIGHT_PARENS, LEFT_CURLY, RIGHT_CURLY,
 LEFT_SQUARE, RIGHT_SQUARE, SEMICOLON, COMMA, PERIOD, COLON } Separator;
typedef enum SourceEndOfFile { SEOF_0, SEOF_EOF } EofOperator;

/* TO_DO 3A: Data structures for declaring the token and its attributes */
typedef union TokenAttribute {
    ziro_int codeType;                  /* integer attributes accessor */
    AriOperator arithmeticOperator;     /* arithmetic operator attribute code */
    RelOperator relationalOperator;     /* relational operator attribute code */
    LogOperator logicalOperator;        /* logical operator attribute code */
    EofOperator seofType;               /* source-end-of-file attribute code */
    Separator separatorType;            /* Type of separator */
    ziro_int intValue;                  /* integer literal attribute (value) */
    ziro_char charValue;                 /* Character literal attribute value */
    ziro_int keywordIndex;              /* keyword index in the keyword table */
    ziro_int contentString;             /* string literal offset from the beginning of the string literal buffer (stringLiteralTable->content) */
    ziro_float floatValue;              /* floating-point literal attribute (value) */
    ziro_char vidLexeme[VID_LEN + 1];   /* variable identifier token attribute */
    ziro_char errLexeme[ERR_LEN + 1];   /* error token attribite */
} TokenAttribute;

/* TO_DO 3B: Should be used if no symbol table is implemented */
typedef struct VidAttributes {
    ziro_flag flags;                     /* Flags information */
    union {
        ziro_int intValue;              /* Integer value */
        ziro_float floatValue;            /* Float value */
        ziro_string stringContent;        /* String value */
    } values;
} VidAttributes;

/* CHECK: Token declaration */
typedef struct Token {
    ziro_int code;                  /* token code */
    TokenAttribute attribute;       /* token attribute */
    VidAttributes   vidAttribute;    /* not used in this scanner implementation - for further use */
} Token;

///////////////////////////////////////////////////////////////////////////////////////////////////////

/* CHECK: EOF definitions */
#define CHARSEOF0 '\0'
#define CHARSEOF255 0xFF
#define BUFFER_EOF CHARSEOF0

/*  Special case tokens processed separately one by one in the token-driven part of the scanner
 *  '=' , ' ' , '(' , ')' , '{' , '}' , == , <> , '>' , '<' , ';', 
 *  white space, comments , ',' , ';' , '-' , '+' , '*' , '/', ## , 
 *  .&., .|. , .!. , SEOF.
 */

/* TO_DO 4: Error states and illegal state */
#define ER  17      /* Error state  with retract */
#define ES  18      /* Error state  with no retract */
#define IS -1       /* Illegal state */

/* TO_DO 5: State transition table definition */
#define TABLE_COLUMNS 9

/* TO_DO 6: Define lexeme FIXED classes */
/* These constants will be used on nextClass */
#define CHRCOL2 '.'
#define CHRCOL3 '\"'
#define CHRCOL4 '\''
#define CHRCOL5 'e'
#define CHRCOL8 '-'

/* These constants will be used on VID function */
/* These are irrelevant to the ZPL */
#define IVIDPREFIX '#'
#define FVIDPREFIX '%'
#define SVIDPREFIX '$'

/* TO_DO 7: Transition table - type of states defined in separate table */
static ziro_int transitionTable[][TABLE_COLUMNS] = {
    /*          [A-z],  [0-9],  .,      ",      ',      E|e,    SOEF,   other,  -                       */
    /*          L(0)    D(1)    P(2)    Q(3)    C(4)    X(5)    E(6)    O(7)    M(8)                    */
    /* S00 */	{10,    1,      ES,     12,     14,     ES,     ER,     ES,     2},     /* NOAS */
    /* S01 */	{3,     1,      4,      3,      3,      3,      ER,     3,      3},     /* NOAS */
    /* S02 */	{ES,    1,      4,      ES,     ES,     ES,     ER,     ES,     ES},    /* NOAS */
    /* S03 */	{IS     IS,     IS,     IS,     IS,     IS,     IS,     IS,     IS},    /* ASWR (IL) */
    /* S04 */	{ES,    5,      ES,     ES,     ES,     ES,     ER,     ES,     ES},    /* NOAS */
    /* S05 */	{9,     5,      9,      9,      9,      6,      ER,      9,     9},     /* NOAS */
    /* S06 */	{ES,    8,      ES,     ES,     ES,     ES,     ER,     ES,     7},     /* NOAS */
    /* S07 */	{ES,    8,      ES,     ES,     ES,     ES,     ER,     ES,     ES},    /* NOAS */
    /* S08 */	{9,     8,      9,      9,      9,      9,      ER,     9,      9},     /* NOAS */
    /* S09 */	{IS     IS,     IS,     IS,     IS,     IS,     IS,     IS,     IS},    /* ASWR (FPL) */
    /* S10 */	{10,    10,     11,     11,     11,     11,     ER,     11,     11},    /* NOAS */
    /* S11 */	{IS     IS,     IS,     IS,     IS,     IS,     IS,     IS,     IS},    /* ASWR (ID)  */
    /* S12 */	{12,    12,     12,     13,     12,     12,     ER,     12,     12},    /* NOAS */
    /* S13 */	{IS     IS,     IS,     IS,     IS,     IS,     IS,     IS,     IS},    /* ASNR (SL)   */
    /* S14 */	{15,    15,     15,     15,     ES,     15,     ER,     15,     15},    /* NOAS */
    /* S15 */	{ES,    ES,     ES,     ES,     16,     ES,     ER,     ES,     ES},    /* NOAS */
    /* S16 */	{IS,    IS,     IS,     IS,     IS,     IS,     IS,     IS,     IS},    /* ASWR (CL)) */
    /* S17 */	{IS,    IS,     IS,     IS,     IS,     IS,     IS,     IS,     IS},    /* ASWR (Err1) */ 
    /* S18 */	{IS,    IS,     IS,     IS,     IS,     IS,     IS,     IS,     IS}     /* ASNR (Err2) */};

/* CHECK: Define accepting states types */
#define NOAS    0       /* not accepting state */
#define ASNR    1       /* accepting state with no retract */
#define ASWR    2       /* accepting state with retract */

/* TO_DO 8: Define list of acceptable states */
static ziro_int stateType[] = {
    NOAS, /* 00 */
    NOAS, /* 01 */
    NOAS, /* 02 */
    ASWR, /* 03 (IL) */
    NOAS, /* 04 */
    NOAS, /* 05 */
    NOAS, /* 06 */
    NOAS, /* 07 */
    NOAS, /* 08 */
    ASWR, /* 09 (FPL) */
    NOAS, /* 10 */
    ASWR, /* 11 (ID) */
    NOAS, /* 12 */
    ASNR, /* 13 (SL) */
    NOAS, /* 14 */
    NOAS, /* 15 */
    ASWR, /* 16 (CL) */
    ASWR, /* 17 (ERR) */
    ASNR  /* 18 (ERR) */
};

/*
-------------------------------------------------
TO_DO 9: Adjust your functions'definitions
-------------------------------------------------
*/

/* Static (local) function  prototypes */
ziro_int startScanner(BufferPointer psc_buf);
ziro_int nextClass(ziro_flag c);         /* character class function */
ziro_int nextState(ziro_int state, ziro_char c); /* state machine function */

/*
-------------------------------------------------
Automata definitions
-------------------------------------------------
*/

/* TO_DO_10A: Pointer to function (of one char * argument) returning Token */
typedef Token(*PTR_ACCFUN)(ziro_char* lexeme);

/* Declare accepting states functions */
Token funcID    (ziro_char* lexeme);
Token funcIL    (ziro_char* lexeme);
Token funcFPL   (ziro_char* lexeme);
Token funcSL    (ziro_char* lexeme);
Token funcCL    (ziro_char* lexeme);
Token funcKEY   (ziro_char* lexeme);
Token funcErr   (ziro_char* lexeme);

/* 
 * Accepting function (action) callback table (array) definition 
 * If you do not want to use the typedef, the equvalent declaration is:
 */

/* TO_DO_10B: Define final state table */
static PTR_ACCFUN finalStateTable[] = {
    NULL,       /* 00 */
    NULL,       /* 01 */
    NULL,       /* 02 */
    funcIL,     /* 03 */
    NULL,       /* 04 */
    NULL,       /* 05 */
    NULL,       /* 06 */
    NULL,       /* 07 */
    NULL,       /* 08 */
    funcFPL,    /* 09 */
    NULL,       /* 10 */
    funcID,     /* 11 */
    NULL,       /* 12 */
    funcSL,     /* 13 */
    NULL,       /* 14 */
    NULL,       /* 15 */
    funcCL,     /* 16 */
    funcErr,    /* 17 */
    funcErr     /* 18*/
};

/*
-------------------------------------------------
Language keywords
-------------------------------------------------
*/

/* TO_DO 11A: Define the number of Keywords from the language */
#define KWT_SIZE 25

/* TO_DO 11B: Define the list of keywords */
static ziro_char* keywordTable[KWT_SIZE] = {
    "byte",
    "short",
    "int",
    "long",
    "float",
    "double",
    "char",
    "String",
    "void",
    "enum",     /* Reserved for future use */
    "class",    /* Reserved for future use */
    "new",      /* Reserved for future use */
    "if",
    "else",
    "do",
    "while",
    "for",
    "foreach",
    "switch",
    "case",
    "break",
    "continue",
    "default",
    "program",
    "write"
};

#endif
