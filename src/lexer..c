#include <string.h>
#include <ctype.h>
#include "../includes/tokens.h"
#include "../includes/utils.h"

//builtin lexer
int lexer(char *text, Token *token_buffer)
{
    // from the input text, create tokens
    
    int token_count = 0;


    while ((*text) != '\0')
    {
        if(*text == '\n' || *text == '\r' || *text == ' ' || *text == '\t')
        {
            text ++;
            continue;
        }

        // verifica se é um characere ou underline
        if(isalpha(*text) || *text == '_') {
            // buffer da linha, suporta ate 256 chars
            char buffer[256];
            int i = 0;
            // le enquanto for letra , numero ou undescore
            while(isalnum(*text) || *text == '_')
            {
                if (i < 255) 
                {
                    buffer[i++] = *text;
                }
                text++;
            }
            buffer[i] = '\0';
            

            // Cadeia de verificações para verificar tipo
            // Comparamos o conteúdo do buffer diretamente usando strcmp. 
            // strcmp retorna 0 quando as duas strings são exatamente iguais.
            char *type_found = is_type(buffer);
            if(type_found != NULL)
            {
                if (strcmp(buffer, "string") == 0)
                {
                    token_buffer[token_count].type = TYPE_STRING;
                }
                else if (strcmp(buffer, "int") == 0)
                {
                    token_buffer[token_count].type = TYPE_INT;
                }
                else if (strcmp(buffer, "float") == 0)
                {
                    token_buffer[token_count].type = TYPE_FLOAT;
                }
                else if (strcmp(buffer, "rune") == 0) 
                {
                    token_buffer[token_count].type = TYPE_RUNE;
                }
            }
            else 
            {
                token_buffer[token_count].type = IDENTIFIER;
            }

            strcpy(token_buffer[token_count].lexeme, buffer);
            token_count ++;
            continue;
        }
        
        if(isdigit(*text))
        {
            char buffer[256];

            int i = 0;

            while(isdigit(*text))
            {
                if(i < 255)
                {
                    buffer[i++] = *text;
                }
                text++;
            }
            buffer[i] = '\0';

            token_buffer[token_count].type = NUMBER;
            strcpy(token_buffer[token_count].lexeme, buffer);
            token_count++;
            continue;
        }
        
        // verifica se o proximo caractere também é um ASSINGMENT
        // caso seja, vira um EQUALS, um comparador
        if(*text == '=')
        {
            if (*(text + 1) == '=')
            {
                token_buffer[token_count].type = EQUALS;
                strcpy(token_buffer[token_count].lexeme, "==");
                token_count++;
                text += 2;
                continue;
            } else {
                token_buffer[token_count].type = ASSIGNMENT;
                strcpy(token_buffer[token_count].lexeme, "=");
                token_count++;
                text++;
                continue;
            }
        }

        TokenType type = char_to_token(*text);
        token_buffer[token_count].type = type;
        
        // Salva o caractere do operador como string no lexeme
        token_buffer[token_count].lexeme[0] = *text;
        token_buffer[token_count].lexeme[1] = '\0';
        
    
        token_count++;
        text++; // Avança o operador processados
    }
    return token_count;
}