#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h" // Include the parser header for access to the parse tree

// Function to generate assembly code based on the parse tree
void generateAssembly(Node *parseTree, FILE *outputFile);

// Function to emit assembly code instructions
void emit(const char *instruction);

#endif /* CODEGEN_H */

