// token.h

#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    EOFTk,
    KeywordTk,
    IdentifierTk,
    OperatorTk,
    IntLiteralTk,
    ErrorTk
} TokenType;

typedef struct {
    TokenType type;
    const char *instance;
    int line;
} Token;

#endif

