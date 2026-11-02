#include "../includes/utils.h"
#include <string.h>
#include <stdbool.h>

// define o tamanho do array keywords
#define ARR_KEYWORDS_SIZE sizeof(keywords) / sizeof(keywords[0])
#define TYPES_ARR_SIZE sizeof(kame_types) / sizeof(kame_types[0])
const char* token_to_string(TokenType type) {



    
    switch (type) {
        case PLUS:       return "PLUS";
        case EQUALS:    return "EQUALS";
        case NUMBER:    return "NUMBER";
        // primitive types
        case TYPE_INT:       return "TYPE_INT";
        case TYPE_RUNE:     return "TYPE_RUNE";
        case TYPE_STRING:   return "TYPE_STRING";
        case TYPE_FLOAT:    return "TYPE_FLOAT";
        case TYPE_BOOL:     return "TYPE_BOOL";
        //ctypes
        case IDENTIFIER: return "IDENTIFIER";
        case MINUS:      return "MINUS";
        case MULTIPLY:   return "MULTIPLY";
        case DIVIDE:     return "DIVIDE";
        case ASSIGNMENT: return "ASSIGNMENT";
        case SEMICOLON:  return "SEMICOLON";
        case LPAREN:     return "LPAREN";
        case RPAREN:     return "RPAREN";
        case END_OF_FILE:  return "EOF";
        case KEYWORD:   return "KEYWORD";
        case UNKNOWN:    return "UNKNOWN";
        case RBRACE:     return "RBRACE";
        case LBRACE:     return "LBRACE";
        default:         return "UNKNOWN";
    }
}

TokenType char_to_token(char c) {
    switch(c) {
        case '+': return PLUS;
        case '-': return MINUS;
        case '*': return MULTIPLY;
        case '/': return DIVIDE;
        case '=': return ASSIGNMENT;
        case ';': return SEMICOLON;
        case '(': return LPAREN;
        case ')': return RPAREN;
        case '}': return RBRACE;
        case '{': return LBRACE;
        default:  return UNKNOWN;
    }
}

char  *is_type(const char *lexame)
{
    for(int i = 0; i < TYPES_ARR_SIZE; i++){
        if(strcmp(lexame, kame_types[i]) == 0)
        {
            if(strcmp(lexame, "int") == 0) {
                return "int";
            } else if(strcmp(lexame, "string") == 0) {
                return "string";
            } else if(strcmp(lexame, "rune") == 0) {
                return "rune";
            } else if(strcmp(lexame, "float") == 0) {
                return "float";
            } else if(strcmp(lexame, "bool") == 0) {
                return "bool";
            }
        }
    }
    return NULL; // false
}

bool is_keyword(const char *buff)
{
    for(int i =0; i < ARR_KEYWORDS_SIZE; i++)
    {
        if(strcmp(buff, keywords[i]) == 0) {
            return true;
        }
    } 
    return false;
}