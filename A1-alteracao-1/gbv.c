#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>
#include "gbv.h"
#include "util.h"

// variável global de chave 
char chave[4] = "pass";

struct superbloco {
    int docs_num;
    long offset_dir;
};

int gbv_create(const char *filename) {

    FILE* arq;

    arq = fopen(filename, "wb+");

    // verificacao
    if (!arq) {
        return -1;
    }

    int escrita_chave;

    escrita_chave = fwrite(&chave, sizeof(chave), 1, arq);
    if (escrita_chave != 1) {
        fclose(arq);
        return -1;
    }

    // cria a biblioteca com um superbloco sem documentos
    struct superbloco sb;
    sb.docs_num = 0;
    sb.offset_dir = sizeof(chave) + sizeof(struct superbloco);

    int escrita_superbloco;

    fseek(arq, sizeof(chave), SEEK_SET);    // seta o ponteiro 4 bytes depois do inicio da biblioteca

    escrita_superbloco = fwrite(&sb, sizeof(struct superbloco), 1, arq);
    if (escrita_superbloco != 1) {
        fclose(arq);
        return -1;
    }

    fclose(arq);
    return 0;
}

int gbv_open(Library *lib, const char *filename, const char *key) {

    FILE* arq;

    arq = fopen(filename, "rb+");

    //verificacao
    if (!arq) {
        gbv_create(filename);
        arq = fopen(filename, "rb+");

        if (!arq) {
            return -1;
        }
    }

    // le o superbloco
    struct superbloco sb;
    
    fseek(arq, sizeof(chave), SEEK_SET);
    if (fread(&sb, sizeof(struct superbloco), 1, arq) != 1) {
        fclose(arq);
        return -1;
    }
    
    // preenche a memoria da biblioteca
    lib->count = sb.docs_num;
    
    // se o numero de documentos for diferente de 0
    if (lib->count > 0) {
        lib->docs = malloc(sizeof(Document) * lib->count);  

        // se a memoria alocada para documentos for invalida
        if (!lib->docs) {
            fclose(arq);
            return -1;
        }

        fseek(arq, sb.offset_dir, SEEK_SET);

        // verifica se a leitura da biblioteca ocorreu sem erros
        size_t lidos = (fread(lib->docs, sizeof(Document), lib->count, arq));

        if (lidos != (size_t)(lib->count)) {
            free(lib->docs);
            fclose(arq);
            return -1;
        }
    }

    else {

        lib->docs = NULL;
    } 

    rewind(arq);
    fclose(arq);
    return 0;
}


/* Função Auxiliar de GBV_ADD */
Document novo_documento (Library *lib, int indice, const char *name, long size, time_t date, long offset) {

    strcpy(lib->docs[indice].name, name);
    lib->docs[indice].size = size;
    lib->docs[indice].date = date;
    lib->docs[indice].offset = offset;
    
    return lib->docs[indice];
}

int gbv_add(Library *lib, const char *archive, const char *docname, const char *key) {

    // verificação de chave 
    if (strcmp(key, chave) != 0) {
        printf("Acesso Negado\n");
        exit(0);
    }

    // verificação de chave 
    if (strcmp(key, chave) != 0) {
        printf("Acesso Negado\n");
        exit(0);
    }

    // verificacao
    if (!lib || !archive || !docname)
        return -1;

    // abre o arquivo do novo documento
    FILE* doc;

    doc = fopen(docname, "rb+");

     // verificacao
    if (!doc) {
        return -1;
    }
   
    long doc_tam = arq_tam(doc);    // tamanho em bytes do documento

    // abre o arquivo da biblioteca
    FILE* biblioteca;

    biblioteca = fopen(archive, "rb+");

    if (!biblioteca) {
        return -1;
    }

    // acessa o offset da area de diretorio
    struct superbloco sb;
    fseek(biblioteca, 0, SEEK_SET);
    fread(&sb, sizeof(struct superbloco), 1, biblioteca);
    long offset_dir = sb.offset_dir;

    int posicao = -1;

    // percorre a biblioteca para verificar se há algum documento de mesmo nome
    for (int i = 0; i < lib->count; i++) {

        // se há um arquivo com nome igual
        if (strcmp(lib->docs[i].name, docname) == 0) {
            posicao = i;
        }
    }

    if (posicao != - 1) {
        lib->docs[posicao] = novo_documento(lib, posicao, docname, doc_tam, time(&lib->docs[posicao].date), offset_dir);
    }

    // se não há arquivo com nome igual, aloca memoria para um novo elemento no vetor de documentos
    else {   
        lib->docs = realloc(lib->docs, (lib->count + 1) * sizeof(Document));
        lib->docs[lib->count] = novo_documento(lib, lib->count, docname, doc_tam, time(&lib->docs[lib->count].date), offset_dir);
        lib->count++;
    } 

    // escreve o arquivo no final do documento
    char buffer[BUFFER_SIZE];
    size_t lidos;

    fseek(biblioteca, offset_dir, SEEK_SET);   // ponteiro apontando para o início 

    // enquanto a quantidade de blocos lidos for maior do que 0, escreve os dados do buffer 
    while ((lidos = fread(buffer, 1, BUFFER_SIZE, doc)) > 0) {
        fwrite(buffer, 1, lidos, biblioteca);
    }

    // reescreve a área de diretório no novo offset
    long novo_offset_dir = ftell(biblioteca);
    fseek(biblioteca, novo_offset_dir, SEEK_SET);
    fwrite(lib->docs, sizeof(Document), lib->count, biblioteca);


    // altera o superbloco
    sb.docs_num = lib->count;
    sb.offset_dir = novo_offset_dir;

    fseek(biblioteca, 0, SEEK_SET);
    fwrite(&sb, sizeof(struct superbloco), 1, biblioteca);

    // finaliza 
    rewind(doc);
    fclose(doc);
    rewind(biblioteca);
    fclose(biblioteca);
    return 0;
}


int gbv_remove(Library *lib, const char *docname, const char* archive, const char *key) {

    // verificação de chave 
    if (strcmp(key, chave) != 0) {
        printf("Acesso Negado\n");
        exit(0);
    }

    // verificacao
    if (!lib || lib->count == 0 || !docname)
        return -1;

    // le a biblioteca
    FILE* biblioteca;

    biblioteca =  fopen(archive, "rb+");

    if(!biblioteca) {
        return -1;
    }

    // le o superbloco
    struct superbloco sb;

    fseek(biblioteca, 0, SEEK_SET);
    fwrite(&sb, sizeof(struct superbloco), 1, biblioteca);

    // percorre o vetor de documentos procurando o arquivo a ser removido, se achar, remove, senão, retorna
    for (int i = 0; i < lib->count; i++) {

        if ((strcmp(lib->docs[i].name, docname)) == 0) {

            for (int j= i; j < lib->count - 1; j++) {
                lib->docs[j] = lib->docs[j+1];
            }

            lib->count = lib->count - 1;
        }
    }

    // reescreve a área de diretório
    fseek(biblioteca, sb.offset_dir, SEEK_SET);
    fwrite(lib->docs, sizeof(Document), lib->count, biblioteca); 

    // altera o superbloco
    sb.docs_num = lib->count;

    fseek(biblioteca, 0, SEEK_SET);
    fwrite(&sb, sizeof(struct superbloco), 1, biblioteca);

    // ajusta a memória caso ela tenha ficado vazia
    if (lib->count == 0) {
        free(lib->docs);
        lib->docs = NULL;
    }

    fclose(biblioteca);
    return 0;
}

int gbv_list(const Library *lib, const char *key) {

    // verificação de chave 
    if (strcmp(key, chave) != 0) {
        printf("Acesso Negado\n");
        exit(0);
    }

    char data_str[64];

    for (int i = 0; i < lib->count; i++) {
        printf("Name: %s\n", lib->docs[i].name);
        printf("Size: %ld\n", lib->docs[i].size);

        format_date(lib->docs[i].date, data_str, sizeof(data_str));
        printf("Data: %s\n", data_str);

        printf("Offset: %ld\n", lib->docs[i].offset);

        if (i < lib->count -1)
            printf("\n");
    }

    return 0;

}

int gbv_view(const Library *lib, const char *docname, const char* archive, const char *key) {

    // verificação de chave 
    if (strcmp(key, chave) != 0) {
        printf("Acesso Negado\n");
        exit(0);
    }

    // acesso a memória e verificacao
    FILE* biblioteca;

    biblioteca = fopen (archive, "rb");

    if(!biblioteca) {
        return -1;
    }

    // encontra o documento dentro da biblioteca
    long doc_offset = -1;
    long doc_size = -1;

    for (int i = 0; i < lib->count; i++) {

        if (strcmp(docname, lib->docs[i].name) == 0) {
            doc_offset = lib->docs[i].offset;
            doc_size = lib->docs[i].size;
        }
    }

    // se o documento não está na biblioteca
    if (doc_offset == -1 || doc_size == -1) {
        fclose(biblioteca);
        return -1;
    }

    
    long inicio = doc_offset;
    long posicao_atual = doc_offset;
    long fim = doc_offset + doc_size;

    // impressao
    char buffer[BUFFER_SIZE];
    char opcao;

    // imprime a primeira vez
    fseek(biblioteca, doc_offset, SEEK_SET);

    // caso em que o doc é maior do que buffer_size
    if (doc_size > BUFFER_SIZE) {
        fread(buffer, 1, BUFFER_SIZE, biblioteca);
        fwrite(buffer, 1, BUFFER_SIZE, stdout);
        printf("\n");
        posicao_atual += BUFFER_SIZE;
    }

    // caso em que o doc é menor do que o buffer_size
    else {
        fread(buffer, 1, doc_size, biblioteca);
        fwrite(buffer, 1, doc_size, stdout);
        printf("\n");
        posicao_atual = fim;    
    }


   // loop de impressao 
    while (1) {
        scanf(" %c", &opcao);

        // usuario digitou 'n'
        if (opcao == 'n') {

            if(posicao_atual < fim && (posicao_atual + BUFFER_SIZE) < fim) {
                fseek(biblioteca, posicao_atual, SEEK_SET);
                fread(buffer, 1, BUFFER_SIZE, biblioteca);
                fwrite(buffer, 1, BUFFER_SIZE, stdout);
                printf("\n");
                posicao_atual += BUFFER_SIZE;
            }
            else if (posicao_atual < fim && (posicao_atual + BUFFER_SIZE) > fim) {
                fread(buffer, 1, (fim - posicao_atual), biblioteca);
                fwrite(buffer, 1, (fim - posicao_atual), stdout);
                printf("\n");
                posicao_atual = fim;
            }
        }
            
        // usuario digitou 'p'
        else if (opcao == 'p') {

            if ((posicao_atual - (BUFFER_SIZE * 2)) > inicio) {
                posicao_atual -= BUFFER_SIZE * 2;
                fseek(biblioteca, posicao_atual, SEEK_SET);
                fread(buffer, 1, BUFFER_SIZE, biblioteca);
                fwrite(buffer, 1, BUFFER_SIZE, stdout);
                printf("\n");
            }
            else if ((posicao_atual - (BUFFER_SIZE * 2)) < inicio) {

                if (posicao_atual - BUFFER_SIZE > inicio) {
                    posicao_atual -= BUFFER_SIZE;
                    fseek(biblioteca, posicao_atual, SEEK_SET);
                    fread(buffer, 1, BUFFER_SIZE, biblioteca);
                    fwrite(buffer, 1, BUFFER_SIZE, stdout);
                    printf("\n");
                }
                else if ((posicao_atual - BUFFER_SIZE) < inicio) {
                    fseek(biblioteca, inicio, SEEK_SET);
                    fread(buffer, 1, (posicao_atual - inicio), biblioteca);
                    fwrite(buffer, 1, (posicao_atual - inicio), stdout);
                    printf("\n");
                    posicao_atual = inicio;
                }
            }
        }

        // usuario digitou 'q'
        else if (opcao == 'q') {
            fclose(biblioteca);
            return 0;
        }
    }
        
    return -1;
}