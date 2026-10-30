#ifndef UTILFILE_H
#define UTILFILE_H

#include "tokens.h"


const char* token_to_string(TokenType type);

TokenType char_to_token(char c);

char* is_type(const char *lexame);

#endif
