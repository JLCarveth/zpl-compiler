/*************************************************************
* COMPILERS COURSE - Algonquin College
* Code version: Summer, 2021
* This Code is EXCLUSIVE for professors (must not be shared)
* Author: Paulo Sousa - 1st May, 2020.
*************************************************************
* File name: compilers.c
* Compiler: MS Visual Studio 2019
* Author: Paulo Sousa
* Course: CST 8152 � Compilers, Lab Section: [011, 012, 013]
* Assignment: A21, A22, A23.
* Date: May 01 2021
* Professor: Paulo Sousa
* Purpose: This file is the main program of Compilers Project
* Function list: main().
*************************************************************/

#include <stdio.h>
#include <stdlib.h>

#ifndef COMPILERS_H_
#include "Compilers.h"
#endif

/************************************************************
* Function name: main
* Purpose: Main function
* Author: Paulo Sousa
* History/Versions: Ver 1.0
* Called functions: mainBuffer(), mainScanner(), mainParser()
* Parameters: Command line arguments - argc, argv
* Return value: Status
* Algorithm: -
**************************************************************/

zero_int main(int argc, char** argv) {
	zero_int i;
	if (DEBUG) {
		for (i = 0; i < argc; ++i)
			printf("argv[%d] = %s\n", i, argv[i]);
	}
	if (argc < 2) {
		printf("%s%s%c%s%c%s%c%s", argv[0], ": OPTIONS [",
			PGM_BUFFER, "] - Buffer, [",
			PGM_SCANNER, "] - Scanner, [",
			PGM_PARSER, "] - Parser\n");
	}
	zero_char option = argv[1][0];
	switch (option) {
	case PGM_BUFFER:
		break;
	case PGM_SCANNER:
		mainScanner(argc, argv);
		break;
	case PGM_PARSER:
		break;
	default:
		printf("%s%s%c%s%c%s%c%s", argv[0], ": OPTIONS [",
			PGM_BUFFER, "] - Buffer, [",
			PGM_SCANNER, "] - Scanner, [",
			PGM_PARSER, "] - Parser\n");
		break;
	}
	return EXIT_SUCCESS;
}
