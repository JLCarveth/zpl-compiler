/*************************************************************
* REPLACE the file header below with your file header (see CST8152_ASSAMG.pdf for details).
* File Name: buffer.h
* Version: 1.20.1
* Author: S^R
* Date: 1 January 2020
* Preprocessor directives, type declarations and prototypes necessary for buffer implementation
* as required for CST8152-Assignment #1.
* The file is not completed.
* You must add your function declarations (prototypes).
* You must also add your constant definitions and macros,if any.
*/

#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <stdlib.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
    MODE_FIXED = 'F',
    MODE_ADDIT = 'A',
    MODE_MULTI = 'M'
};

#define BUFFER_ERROR (-1)				/* General error message */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (ZERO) */
#define ZERO_DEFAULT_SIZE 100			/* default initial buffer capacity */
#define ZERO_DEFAULT_INCREMENT 10		/* default increment factor */

/* You should add your own constant definitions here */
#define ZERO_MAX_SIZE SHRT_MAX-1 /*maximum capacity*/ 
#define ZERO_STR_NULL_TERM '\0' /* termination char indicating end of a string */

/* Add your bit-masks constant definitions here - Defined for ZERO */
#define ZERO_DEFAULT_FLAG 0x3F		/* 0011.1111 */
#define ZERO_SET_FLAG_RLB 0x80		/* 1000.0000 */
#define ZERO_RST_FLAG_RLB 0x7F		/* 0111.1111 */
#define ZERO_CHK_FLAG_RLB 0x80		/* 1000.0000 */
#define ZERO_SET_FLAG_EOB 0x40		/* 0100.0000 */
#define ZERO_RST_FLAG_EOB 0xBF		/* 1011.1111 */
#define ZERO_CHK_FLAG_EOB 0x01		/* 0100.0000 */

/* Logical constants - All booleans are by default false (0). Anything non-zero
is percieved as true
*/
#define ZERO_TRUE 1
#define ZERO_FALSE 0

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (ZERO) */
typedef int				zero_int;
typedef short			zero_short;
typedef char 			zero_byte;
typedef char			zero_char;
typedef long			zero_long;
typedef float			zero_float;
typedef double 			zero_double;
typedef unsigned char	zero_flag;
typedef char			zero_bool;
typedef char* 			zero_string;
typedef void*			zero_array;

/* user data type declarations */
typedef struct OffsetZero {
    zero_int addC;      /* the offset (in chars) to the add-character location */
    zero_int getC;      /* the offset (in chars) to the get-character location */
    zero_int mark;      /* the offset (in chars) to the mark location */
} Offset;

/* user data type declarations */
typedef struct ZeroBuffer {
    zero_char* string;         /* pointer to the beginning of character array (character buffer) */
    zero_int size;            /* current dynamic memory size (in bytes) allocated to character buffer */
    zero_int increment;       /* character array increment factor */
    zero_int mode;            /* operational mode indicator*/
    zero_flag flags;  /* contains character array reallocation flag and end-of-buffer flag */
    Offset offset;
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */

/* Function declarations */

BufferPointer bufferCreate(zero_int, zero_int, zero_int);
BufferPointer bufferAddChar(BufferPointer const, zero_char);
zero_bool bufferRetract(BufferPointer const);
zero_bool bufferRestore(BufferPointer const);
zero_bool bufferRewind(BufferPointer const);
zero_bool bufferClean(BufferPointer const);
zero_bool bufferDestroy(BufferPointer const);

zero_bool bufferSetOffsetMark(BufferPointer const, zero_int);
zero_int bufferPrint(BufferPointer const);
zero_int bufferLoad(BufferPointer const, FILE* const);

zero_bool bufferCheckFull(BufferPointer const);
zero_bool bufferCheckEmpty(BufferPointer const);

zero_int bufferGetSize(BufferPointer const);
zero_int bufferGetOffsetAddC(BufferPointer const);
zero_int bufferGetOffsetMark(BufferPointer const);
zero_int bufferGetOffsetGetC(BufferPointer const);
zero_int bufferGetIncrement(BufferPointer const);
zero_int bufferGetMode(BufferPointer const);
zero_char bufferGetChar(BufferPointer const);
zero_char* bufferGetSubString(BufferPointer const, zero_int);
zero_flag bufferGetFlags(BufferPointer const);


#endif
