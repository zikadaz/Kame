#ifndef UTILFILE_H
#define UTILFILE_H

#include "tokens.h"
#include <stdbool.h>

const char* token_to_string(TokenType type);

TokenType char_to_token(char c);

const char *kame_types[] = {
    "int",
    "string",
    "rune",
    "float",
    "bool"
};

char *is_type(const char *lexame);

// add: keywords
char *keywords[] = {
        "function",
        "do",
        "end", // identifier
        "while", // identifier
        "if",
        "elif",
        "else",
        "switch",
        "case",
        "return",
        "class",
        "method",
        "var",
        "const",
        "expand",
        "using"
    };
bool is_keyword(const char *buff);

#endif
