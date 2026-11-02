#ifndef TOKENS_H
#define TOKENS_H


typedef enum 
    {
        // Literais e Identificadores
        TYPE_INT, // para inteiros
        TYPE_STRING, // para strings
        TYPE_FLOAT, // para ponto flutuante
        TYPE_RUNE, // para characteres
        IDENTIFIER ,         // x, y, nomeVariavel
        NUMBER,             // 3, 5, 24.2, 5.5
        TYPE_BOOL, // para booleanos

        // Operadores de Atribuição e Comparação
        ASSIGNMENT,         // '=' (para inicializar: int x = 10)
        EQUALS,             // '==' (retorna true/false: 3 + 4 == 7)

        // Operadores Matemáticos
        PLUS,               // '+'
        MINUS,              // '-'
        MULTIPLY,           // '*'
        DIVIDE,             // '/'

        // Delimitadores e Agrupadores
        LPAREN,             // '('
        RPAREN,             // ')'
        SEMICOLON,          // ';'
        KEYWORD,
        RBRACE,
        LBRACE,
        // Controle do Lexer
        END_OF_FILE,        // Fim do arquivo/texto
        UNKNOWN             // Para caracteres inválidos detectados
    } TokenType;


    typedef union {
        int integer;
        float decimal;
        char *string;
    } TokenValue;
    //
    typedef struct {
        TokenType type;
        char    lexeme[256];
        TokenValue value;
        int line; // for error handling
        int column; // for error handling
    } Token;

    TokenType char_to_token(char c);
    const char *token_to_string(TokenType type);
    
#endif