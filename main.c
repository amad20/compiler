#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scanner.h"
#include "parser.h"
#include "testTree.h"
#include "staticSemantics.h"
#include "codegen.h"

int main(int argc, char *argv[]) {

    FILE *inputFile;
FILE *outputFile;
char outputFileName[256];

    // Check command-line arguments
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input_file>\n", argv[0]);
        return 1;
    }
    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        perror("Error opening file");
        return 1;
    }

// Extract the base name and create the output file name
    strcpy(outputFileName, argv[1]);
    char *dot = strrchr(outputFileName, '.');
    if (dot != NULL) {
        *dot = '\0'; // Remove the extension
    }
    strcat(outputFileName, ".asm"); // Append .asm extension

    // Open the output file for writing assembly code
    outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile); // Close the input file before returning
        return 1;
    }


// Initialize the scanner
    initializeScanner(inputFile);

    // Start the parsing process
    Node *parseTree = parser();

    // Print the parse tree
 // printf("Parse Tree:\n");
 //  printTree(parseTree, 0);



// Call the static semantic checker
staticSemantics(parseTree);


 // Generate code based on the parse tree
    generateAssembly(parseTree, outputFile );

    // Clean up
    freeParseTree(parseTree);
    fclose(inputFile);
fclose(outputFile);
    return 0;
}
