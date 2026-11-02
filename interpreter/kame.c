#include <stdio.h>
#include <stdlib.h>
#include "../includes/tokens.h"
#include "../includes/lexer.h"
#include "../library/klex.c"
#include "../library/kutilib.c"
#include <string.h>
#define MAX_TOKENS 1024
#define INPUT_LENGTH 1000
#define INITIAL_TOKEN_CAPACITY 128



extern const char* token_to_string(TokenType type);


#if _WIN32
    #define PHRASE "Kame | Pre-Alpha Version.: 0.0.0.1-PA on Windows\n"
#elif __linux__ || __APPLE__
    #define PHRASE "Kame | Pre-Alpha Version.: 0.0.0.1-PA on Unix.\n"
#else 
    #define PHRASE "Kame | Pre-Alpha Version.: 0.0.01-PA\n"
#endif

void run_repl() {
    char s[MAX_TOKENS];
    Token tokens_da_linha[MAX_TOKENS]; // Buffer temporário para até MAX_TOKENS tokens por linha
    printf("%s", PHRASE);

    while(1)
    {
        char  passed_line[MAX_TOKENS];
        passed_line[0] = '\0'; // inicializa a string como vazia
        printf("> ");
        // define a entrada padrão para o usuario digitar o codigo
        if (fgets(s, INPUT_LENGTH, stdin) == NULL) break;
        printf("%s", s);
        s[strcspn(s, "\n")] = '\0';
        
        if(strcmp(s, "exit") == 0) {
            printf("Goodbye!\n");
            break;
        }

        int qtd_tokens =  lexer(s, tokens_da_linha);
        
        // Debug
        for(int i = 0; i < qtd_tokens; i++) {

            //printf("%s : %s     ", token_to_string(tokens_da_linha[i].type),(tokens_da_linha[i].lexeme));
            printf("%s, %s\n", tokens_da_linha[i].lexeme, token_to_string(tokens_da_linha[i].type));
            
        }
        printf("\n");

    }
}


// roda o arquivo
// se o arquivo for maior que MAX_TOKENS, expande mais
void run_file(const char *filepath)
{
    // 1. Abre o arquivo em modo binário para medir o tamanho exato em bytes
    FILE *file = fopen(filepath, "rb");
    if (file == NULL) {
        printf("Erro: Não foi possível abrir o arquivo %s\n", filepath);
        return;
    }

  
    fseek(file, 0L, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

  
    char *source_code = (char *)malloc((file_size + 1) * sizeof(char));
    if (source_code == NULL) {
        printf("Erro de memória: Não foi possível alocar o buffer do arquivo.\n");
        fclose(file);
        return;
    }


    size_t bytes_read = fread(source_code, sizeof(char), file_size, file);
    source_code[bytes_read] = '\0';
    fclose(file); 

    
    int token_capacity = INITIAL_TOKEN_CAPACITY;
    Token *token_buffer = (Token *)malloc(token_capacity * sizeof(Token));
    if (token_buffer == NULL) {
        printf("Erro de memória ao alocar buffer de tokens.\n");
        free(source_code);
        return;
    }

    while (token_capacity < file_size) {
        token_capacity *= 2;
    }
    
    Token *new_buffer = (Token *)realloc(token_buffer, token_capacity * sizeof(Token));
    if (new_buffer == NULL) {
        printf("Erro de memória ao expandir buffer de tokens.\n");
        free(source_code);
        free(token_buffer);
        return;
    }
    token_buffer = new_buffer;

    // 5. Executa seu Lexer passando o texto completo
    printf("Analisando %ld bytes de código com capacidade para %d tokens...\n", file_size, token_capacity);
    int total_tokens = lexer(source_code, token_buffer);

    // 6. Printa os tokens gerados para debugar
    for (int i = 0; i < total_tokens; i++) {
       const char *type_name = token_to_string(token_buffer[i].type);
       printf("%s | %s\n", type_name, token_buffer[i].lexeme);
    }

    // 7. Limpeza total de memória
    free(source_code);
    free(token_buffer);
}

int main(int argc, char **argv)
{
    if (argc > 1) {
        printf("Modo Arquivo: Lendo %s (Futura implementação)...\n", argv[1]);
        run_file(argv[1]);
        return 0;
    }


    // Se nenhum argumento foi passado, roda o REPL builtin
    run_repl();
    return 0;
}
