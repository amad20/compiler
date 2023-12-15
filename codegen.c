#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "codegen.h"

static int labelCounter = 0;
static char* generateLabel() {
  char label[10];
    snprintf(label, sizeof(label), "label%d", labelCounter++);
    return strdup(label);
}

void generateAssembly(Node *node, FILE *outputFile) {
    if (node == NULL) {
        return;
    }

    if (strcmp(node->name, "<program>") == 0) {
        // Initialize the stack pointer (TOS)
       // fprintf(outputFile, "PUSH\n");
        generateAssembly(node->child1, outputFile); // Generate code for <vars>
        generateAssembly(node->child2, outputFile); // Generate code for <stats>
        fprintf(outputFile, "STOP\n");
return;
    }

    if (strcmp(node->name, "<vars>") == 0) {
        // Handle variable declarations here
        // Iterate through the varList and generate code to allocate storage
        generateAssembly(node->child1, outputFile);
    }

    if (strcmp(node->name, "<varList>") == 0) {
        // Handle individual variable declarations here
        // Generate code to reserve storage for the variable
        fprintf(outputFile, "PUSH\n");
    }

    if (strcmp(node->name, "<assign>") == 0) {
        // Handle assignment statements
        // Generate code to load the value of the expression into ACC
        generateAssembly(node->child1, outputFile);
        // Generate code to store ACC into the variable
        fprintf(outputFile, "STORE %s\n", node->token.instance);
    }

if (strcmp(node->name, "<in>") == 0) {
    // Handle input statements
    // Generate code to read an integer and store it in the variable
    fprintf(outputFile, "READ %s\n", node->token.instance);
}



if (strcmp(node->name, "<out>") == 0) {
        // Assembly code for output
        generateAssembly(node->child1, outputFile); // Generate code for expression
        fprintf(outputFile, "WRITE %s\n", node->child1->token.instance);
    }


if (strcmp(node->name, "<R>") == 0) {
    if (node->child1 != NULL) {
        generateAssembly(node->child1, outputFile); // Generate code for <expr>
    } else if (node->token.type == IntLiteralTk) {
        // If the node represents an integer literal
        fprintf(outputFile, "LOAD %s\n", node->token.instance); // Load the literal value
    } else if (node->token.type == IdentifierTk) {
        // If the node represents a variable
        fprintf(outputFile, "LOAD %s\n", node->token.instance); // Load the variable
    }
return;
}


    if (strcmp(node->name, "<if>") == 0) {
        char* label1 = generateLabel();
        char* label2 = generateLabel();

        // Generate code to evaluate arg2
        generateAssembly(node->child1, outputFile);
        // Store the result in result2
        fprintf(outputFile, "STORE result2\n");
        // Generate code to evaluate arg1
        generateAssembly(node->child2, outputFile);
        // Subtract result2 from ACC (arg1 - arg2)
        fprintf(outputFile, "SUB result2\n");
        // Branch to label1 if the condition is false
        fprintf(outputFile, "BRZNEG %s\n", label1);
        // Generate code for Stat1 (true branch)
        // Unconditionally jump to label2 (skip Stat2)
        fprintf(outputFile, "BR %s\n", label2);
        // Label1: Statement 2
        fprintf(outputFile, "%s: NOOP\n", label1);
        // Generate code for Stat2 (false branch)
        generateAssembly(node->child4, outputFile);
        // Label2: End of if statement
        fprintf(outputFile, "%s: NOOP\n", label2);
    }

    if (strcmp(node->name, "<loop>") == 0) {
        char* label1 = generateLabel();
        char* label2 = generateLabel();

        // Label1: Condition evaluation
        fprintf(outputFile, "%s: NOOP\n", label1);
        // Generate code to evaluate arg2
        generateAssembly(node->child1, outputFile);
        // Store the result in result2
        fprintf(outputFile, "STORE result2\n");
        // Generate code to evaluate arg1
        generateAssembly(node->child2, outputFile);
        // Subtract result2 from ACC (arg1 - arg2)
        fprintf(outputFile, "SUB result2\n");
        // Branch to label2 if the condition is false
        fprintf(outputFile, "BRZNEG %s\n", label2);
        // Generate code for Stat1 (loop body)
        generateAssembly(node->child3, outputFile);
        // Unconditionally jump back to label1 (re-evaluate condition)
        fprintf(outputFile, "BR %s\n", label1);
        // Label2: End of loop
        fprintf(outputFile, "%s: NOOP\n", label2);
    }


if (strcmp(node->name, "<N>") == 0) {
    generateAssembly(node->child1, outputFile); // Generate code for <R>

    if (node->token.type == OperatorTk && strcmp(node->token.instance, "/") == 0) {
        generateAssembly(node->child2, outputFile); // Generate code for <N>
        fprintf(outputFile, "DIV\n"); // Output DIV instruction
    }
}
if (strcmp(node->name, "<M>") == 0) {
        generateAssembly(node->child1, outputFile); // Generate code for <N>

        if (node->token.type == OperatorTk) {
            if (strcmp(node->token.instance, "*") == 0) {
                generateAssembly(node->child2, outputFile); // Generate code for <M>
                fprintf(outputFile, "MULT\n");
        }
    }
}

    if (strcmp(node->name, "<expr>") == 0) {
        // Handle expression evaluation here
        generateAssembly(node->child1, outputFile);
        if (node->child2 != NULL) {
            // Binary operation (+ or -)
            generateAssembly(node->child2, outputFile);
            if (strcmp(node->token.instance, "+") == 0) {
                fprintf(outputFile, "ADD\n");
            } else if (strcmp(node->token.instance, "-") == 0) {
                fprintf(outputFile, "SUB\n");
            }
        }
    }

    // Handle other instructions, storage directives, and expressions here

    // Recursively process children
    generateAssembly(node->child1, outputFile);
    generateAssembly(node->child2, outputFile);
    generateAssembly(node->child3, outputFile);
    generateAssembly(node->child4, outputFile);
}
