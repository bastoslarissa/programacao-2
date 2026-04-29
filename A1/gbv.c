#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>
#include "gbv.h"
#include "util.h"

struct superbloco {
    int docs_num;
    long offset_dir;
};

int gbv_create(const char *filename) {

    FILE* arq;

    arq = fopen(filename, "wb+");

    // verificacao
    if (!arq) {
        perror ("Erro ao criar arquivo em create");
        return -1;
    }

    // cria a biblioteca com um superbloco sem documentos
    struct superbloco sb;
    sb.docs_num = 0;
    sb.offset_dir = sizeof(struct superbloco);

    int escrita;

    escrita = fwrite(&sb, sizeof(struct superbloco), 1, arq);
    if (escrita != 1) {
        fclose(arq);
        return -1;
    }

    fclose(arq);
    return 0;
}

int gbv_open(Library *lib, const char *filename) {

    FILE* arq;

    arq = fopen(filename, "rb+");

    //verificacao
    if (!arq) {
        return -1;
    }

    // le o superbloco
    struct superbloco sb;

    if (fread(&sb, sizeof(struct superbloco), 1, arq) != 1) {
        perror ("Erro ao ler arquivo");
        fclose(arq);
        return -1;
    }

    // preenche a memoria da biblioteca
    lib->count = sb.docs_num;
    
    // se o numero de documentos for diferente de 0
    if (lib->count != 0) {
        lib->docs = malloc(sizeof(Document) * lib->count);  

        // se a memoria alocada para documentos for invalida
        if (!lib->docs) {
            perror ("Erro ao criar documento para arquivo");
            fclose(arq);
            return -1;
        }

        fseek(arq, sb.offset_dir, SEEK_SET);

        // verifica se a leitura da biblioteca ocorreu sem erros
        if (fread(&sb, sizeof(struct superbloco), lib->count, arq)) {

            free(lib->docs);
            perror ("Erro ao ler documentos do arquivo");
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

int gbv_add(Library *lib, const char *archive, const char *docname) {

    // verificacao
    if (!lib || !archive || !docname)
        return -1;

    // abre o arquivo do novo documento
    FILE* doc;

    doc = fopen(docname, "rb+");

     // verificacao
    if (!doc) {
        perror ("Erro ao abrir documento");
        return -1;
    }
   
    long doc_tam = arq_tam(doc);    // tamanho em bytes do documento

    // abre o arquivo da biblioteca
    FILE* biblioteca;

    biblioteca = fopen(archive, "rb+");

    if (!biblioteca) {
        perror ("Erro ao abrir biblioteca");
        return -1;
    }

    // acessa o offset da area de diretorio
    struct superbloco sb;
    fseek(biblioteca, 0, SEEK_SET);
    fread(&sb, sizeof(struct superbloco), 1, biblioteca);

    long offset_dir = sb.offset_dir;

    // percorre a biblioteca para verificar se há algum documento de mesmo nome
    for (int i = 0; i < lib->count; i++) {

        // se há um arquivo com nome igual
        if (strcmp(lib->docs[i].name, docname) == 0) {

            // substitui os dados do documento antigo pelo novo
            novo_documento(lib, i, docname, doc_tam, time(&lib->docs[i].date), offset_dir);
        }
    }

    // se não há arquivo com nome igual, aloca memoria para um novo elemento no vetor de documentos
    lib->docs = realloc(lib->docs, (lib->count + 1) * sizeof(Document));
    lib->docs[lib->count] = novo_documento(lib, lib->count, docname, doc_tam, time(&lib->docs[lib->count].date), offset_dir);
    lib->count++; 

    // reescreve a área de diretório no novo offset
    long novo_offset_dir = ftell(biblioteca);
    fseek(biblioteca, novo_offset_dir, SEEK_SET);
    fwrite(lib->docs, sizeof(Document), lib->count, doc);

    // escreve o arquivo no final do documento
    char buffer[BUFFER_SIZE];
    size_t lidos;

    fseek(biblioteca, offset_dir, SEEK_SET);   // ponteiro apontando para o início 

    // enquanto a quantidade de blocos lidos for maior do que 0, escreve os dados no buffer 
    while ((lidos = fread(buffer, 1, BUFFER_SIZE, doc)) > 0) {
        fwrite(buffer, 1, lidos, biblioteca);
    }

    // altera o superbloco
    sb.docs_num = lib->count;
    sb.offset_dir = novo_offset_dir;

    fseek(biblioteca, 0, SEEK_SET);
    fwrite(&sb, sizeof(struct superbloco), 1, biblioteca);

    // finaliza 
    rewind(doc);
    fclose(doc);
    return 0;
}


int gbv_remove(Library *lib, const char *docname) {

    // verificacao
    if (!lib || lib->count == 0 || !docname)
        return -1;

    // percorre o vetor de documentos procurando o arquivo a ser removido, se achar, remove, senão, retorna
    for (int i = 0; i < lib->count; i++) {

        if ((strcmp(lib->docs[i].name, docname)) == 0) {

            for (int j= i; j < (lib->count - 1); j++) {

                lib->docs[j] = lib->docs[j+1];
            }

            lib->count--;

        }
    }

    // ajusta a memória caso ela tenha ficado vazia
    if (lib->count == 0) {

        free(lib->docs);
        lib->docs = NULL;

    }

    return 0;
}

int gbv_list(const Library *lib) {

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

int gbv_view(const Library *lib, const char *docname) {

    // acesso a memória e verificacao
    FILE* biblioteca;

    biblioteca = fopen (lib, "rb");

    if(!biblioteca) {

        perror("Erro ao abrir arquivo para visualizar");
        return -1;
    }

    // encontra o documento dentro da biblioteca
    long doc_offset;
    long doc_size;

    for (int i = 0; i < lib->count; i++) {

        if (strcmp(docname, lib->docs[i].name)) {
            
            doc_offset = lib->docs[i].offset;
            doc_size = lib->docs[i].size;
        }
    }

    long posicao_atual = doc_offset;

    // impressao
    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];
    size_t lidos;
    char opcao = '\0';

    fseek(biblioteca, doc_offset, SEEK_SET);
    fread(buffer1, 1, BUFFER_SIZE, biblioteca);
    fwrite(buffer1, 1, BUFFER_SIZE, stdout);

    while (posicao_atual < (doc_offset + doc_size)) {

        scanf("%d", &opcao);

        if (strcmp(opcao, 'n') == 0)
            
        
        else if (strcmp(opcao, 'p') == 0)
    }
        

}