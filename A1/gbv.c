#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
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
        perror ("Erro ao criar arquivo");
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

    rewind(arq);
    fclose(arq);
    return 0;
}

int gbv_add(Library *lib, const char *archive, const char *docname) {

    // acessa o novo documento
    FILE* arq;

    arq = fopen(docname, "rb+");
    long doc_tam = arq_tam(docname);

    // calcula o offset do diretório
    int offset_dir = lib->docs[lib->count].offset + lib->docs[lib->count].size;

    // percorre a biblioteca para verificar se há algum documento de mesmo nome
    for (int i = 0; i < lib->count; i++) {

        // se há um arquivo com nome igual
        if (strcmp(lib->docs[i].name, docname) == 0) {

            strcpy (docname, (lib->docs[i].name));
            lib->docs[i].size = doc_tam;
            lib->docs[i].offset = offset_dir;
            lib->docs[i].date = time(&lib->docs[i].date);

        }
        // se não há arquivo com nome igual
        else if (i == lib->count - 1)
            

            lib->docs = realloc(lib->docs, (lib->count + 1) * sizeof(Document));
            
            lib->docs[lib->count] = 
            lib->count++;
            lib->docs[i+1] = 
    }

            lib->count++;

            fseek(lib, offset_dir, SEEK_SET);
            fwrite(docname, sizeof(const char), doc_tam, lib);

        }

    }

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