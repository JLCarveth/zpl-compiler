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
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* CONSTANTS DEFINITION: GENERAL (NOT LANGUAGE DEPENDENT) .................................. */

/* Modes (used to create buffer) */
enum BUFFERMODES {
    MODE_FIXED = 'F',
    MODE_ADDIT = 'A',
    MODE_MULTI = 'M'
};

#define BUFFER_ERROR (-1)				/* General error message */

/* CONSTANTS DEFINITION: PREFIXED BY LANGUAGE NAME (ZIRO) */
#define ZIRO_DEFAULT_SIZE 100			/* default initial buffer capacity */
#define ZIRO_DEFAULT_INCREMENT 10		/* default increment factor */

/* You should add your own constant definitions here */
#define ZIRO_MAX_SIZE SHRT_MAX-1 /*maximum capacity*/ 
#define ZIRO_STR_NULL_TERM '\0' /* termination char indicating end of a string */

/* Add your bit-masks constant definitions here - Defined for ZIRO */
#define ZIRO_DEFAULT_FLAG 0x3F		/* 0011.1111 */
#define ZIRO_SET_FLAG_RLB 0x80		/* 1000.0000 */
#define ZIRO_RST_FLAG_RLB 0x7F		/* 0111.1111 */
#define ZIRO_CHK_FLAG_RLB 0x80		/* 1000.0000 */
#define ZIRO_SET_FLAG_EOB 0x40		/* 0100.0000 */
#define ZIRO_RST_FLAG_EOB 0xBF		/* 1011.1111 */
#define ZIRO_CHK_FLAG_EOB 0x01		/* 0100.0000 */

/* Logical constants - All booleans are by default false (0). Anything non-zero
is percieved as true
*/
#define ZIRO_TRUE 1
#define ZIRO_FALSE 0

/* STRUCTURES DEFINITION: SUFIXED BY LANGUAGE NAME (ZIRO) */
typedef int				ziro_int;
typedef short			ziro_short;
typedef char 			ziro_byte;
typedef char			ziro_char;
typedef long			ziro_long;
typedef float			ziro_float;
typedef double 			ziro_double;
typedef unsigned char	ziro_flag;
typedef char			ziro_bool;
typedef char* 			ziro_string;
typedef void*			ziro_array;

/* user data type declarations */
typedef struct OffsetZiro {
    ziro_int addC;      /* the offset (in chars) to the add-character location */
    ziro_int getC;      /* the offset (in chars) to the get-character location */
    ziro_int mark;      /* the offset (in chars) to the mark location */
} Offset;

/* user data type declarations */
typedef struct ZiroBuffer {
    ziro_char* string;         /* pointer to the beginning of character array (character buffer) */
    ziro_int size;            /* current dynamic memory size (in bytes) allocated to character buffer */
    ziro_int increment;       /* character array increment factor */
    ziro_int mode;            /* operational mode indicator*/
    ziro_flag flags;  /* contains character array reallocation flag and end-of-buffer flag */
    Offset offset;
} Buffer, * BufferPointer;

/* FUNCTIONS DECLARATION:  .................................. */

/* Function declarations */

BufferPointer bufferCreate(ziro_int, ziro_int, ziro_int);
BufferPointer bufferAddChar(BufferPointer const, ziro_char);
ziro_bool bufferRetract(BufferPointer const);
ziro_bool bufferRestore(BufferPointer const);
ziro_bool bufferRewind(BufferPointer const);
ziro_bool bufferClean(BufferPointer const);
ziro_bool bufferDestroy(BufferPointer const);

ziro_bool bufferSetOffsetMark(BufferPointer const, ziro_int);
ziro_int bufferPrint(BufferPointer const);
ziro_int bufferLoad(BufferPointer const, FILE* const);

ziro_bool bufferCheckFull(BufferPointer const);
ziro_bool bufferCheckEmpty(BufferPointer const);

ziro_int bufferGetSize(BufferPointer const);
ziro_int bufferGetOffsetAddC(BufferPointer const);
ziro_int bufferGetOffsetMark(BufferPointer const);
ziro_int bufferGetOffsetGetC(BufferPointer const);
ziro_int bufferGetIncrement(BufferPointer const);
ziro_int bufferGetMode(BufferPointer const);
ziro_char bufferGetChar(BufferPointer const);
ziro_char* bufferGetSubString(BufferPointer const, ziro_int);
ziro_flag bufferGetFlags(BufferPointer const);


#endif
