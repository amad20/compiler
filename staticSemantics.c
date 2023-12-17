#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"


#define MAX_VARIABLES 100

char *variableTable[MAX_VARIABLES];
int variableCount = 0;

void insertVariable(const char *varName) {
int i;
    for (i = 0; i < variableCount; i++) {
        if (strcmp(variableTable[i], varName) == 0) {
            fprintf(stderr, "Semantic Error: Variable %s already declared.\n", varName);
            exit(EXIT_FAILURE);
        }
    }
    if (variableCount < MAX_VARIABLES) {
        variableTable[variableCount++] = strdup(varName);
    } else {
        fprintf(stderr, "Semantic Error: Exceeded maximum variable limit.\n");
        exit(EXIT_FAILURE);
    }
}

bool verifyVariable(const char *varName) {
int i;
    for (i = 0; i < variableCount; i++) {
        if (strcmp(variableTable[i], varName) == 0) {
            return true;
        }
    }
    return false;
}
// Assuming Node is your tree node structure
// and it has a token field that includes the variable name (for identifiers)

void insertVariableDeclarations(Node *node) {
    if (!node) return;

    if (strcmp(node->name, "<varList>") == 0) {
        insertVariable(node->token.instance); // Assuming token.instance holds the variable name
    }

    // Recursively call on children
    insertVariableDeclarations(node->child1);
    insertVariableDeclarations(node->child2);
    insertVariableDeclarations(node->child3);
    insertVariableDeclarations(node->child4);
}

void verifyVariableUsage(Node *node) {
    if (!node) return;

    if (strcmp(node->name, "<identifier>") == 0) {
        if (!verifyVariable(node->token.instance)) {
            fprintf(stderr, "Semantic Error: Variable %s not declared.\n", node->token.instance);
            exit(EXIT_FAILURE);
        }
    }

    // Recursively call on children, skipping <vars> subtree
    if (strcmp(node->name, "<vars>") != 0) {
        verifyVariableUsage(node->child1);
        verifyVariableUsage(node->child2);
        verifyVariableUsage(node->child3);
        verifyVariableUsage(node->child4);
    }
}

void staticSemantics(Node *root) {
    insertVariableDeclarations(root); // First pass for insertion
    verifyVariableUsage(root); // Second pass for verification
printf("Static semantics checks passed.\n");
}
