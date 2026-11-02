#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "../includes/tokens.h"


extern const char *kame_types[];
extern char *keywords[];
extern bool is_keyword(const char *buff);
extern char *is_type(const char *lexame);

#define MAX_TOKENS 1024
//builtin lexer
int lexer(char *text, Token *token_buffer)
{
    // from the input text, create tokens
    
    int token_count = 0;


    while ((*text) != '\0')
    {
        // trata de quebra de linhas, espacos etc.
        if(*text == '\n' || *text == '\r' || *text == ' ' || *text == '\t')
        {
            text ++;
            continue;
        }

        // verifica se é um characere ou underline
        if(isalpha(*text) || *text == '_') {
            // buffer da linha, suporta ate 256 chars
            char buffer[MAX_TOKENS];
            int i = 0;
            // le enquanto for letra , numero ou undescore
            while(isalnum(*text) || *text == '_')
            {
                if (i < MAX_TOKENS - 1) // Limita o tamanho do buffer para evitar overflow 
                {
                    buffer[i++] = *text;
                }
                text++;
            }
            buffer[i] = '\0'; // Finaliza a string com o caractere nulo
            

            //verifica se o buffer é uma palavra reservada
            if(is_keyword(buffer))
            {
                token_buffer[token_count].type = KEYWORD;
                strcpy(token_buffer[token_count].lexeme, buffer);
                token_count++;
                continue;
            }

            // Cadeia de verificações para verificar tipo
            // Comparamos o conteúdo do buffer diretamente usando strcmp. 
            // strcmp retorna 0 quando as duas strings são exatamente iguais.
            bool type_found = is_type(buffer);
            if(type_found)
            {
                token_buffer[token_count].type = TYPE_INT;;
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
            char buffer[MAX_TOKENS];

            int i = 0;

            while(isdigit(*text))
            {
                if(i < MAX_TOKENS - 1)
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
            // Verifica se o proximo caractere é '=' para diferenciar entre ASSIGMENT e EQUALS
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
        size_t buff_size = sizeof token_buffer / sizeof (token_buffer[0]);
        token_count++;
        text++; // Avança o operador processados
    }
    return token_count;
}