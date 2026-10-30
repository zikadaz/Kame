#include "../includes/utils.h"
#include <string.h>
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
        case UNKNOWN:    return "UNKNOWN";
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
        default:  return UNKNOWN;
    }
}

const char *kame_types[] = {
    "int",
    "string",
    "rune",
    "float",
    "bool"
};

char* is_type(const char *buffer)
{
    
    if(strcmp(buffer, "string") == 0) return "string";
    if(strcmp(buffer, "int") == 0) return "int";
    if(strcmp(buffer, "float") == 0) return "float";
    if(strcmp(buffer, "rune") == 0) return "rune";
    return NULL;
}