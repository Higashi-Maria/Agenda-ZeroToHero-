//Agenda-ZeroToHero - Maria Luiza Higashi
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definindo o máximo de contatos, caracteres do nome e do telefone
#define MAX_Contatos 50
#define M_Nome 128
#define M_Telefone 15
#define ARQUIVO "agenda.csv"

// Definindo a struct com nome e telefone
typedef struct {
    char nome[M_Nome];
    char telefone[M_Telefone];
} contato;

// Vetor da struct agenda[50]
contato agenda[MAX_Contatos];
int totalcontatos = 0;

// Definindo as funções e os parâmetros que serão passados
void carregar_agenda(contato contatos[]);
void novo_contato(contato contatos[], int *numContatos);
void buscar_contato(contato contatos[], int numContatos);
void deletar_contato(contato contatos[], int *numContatos);
void salvar_contatos(contato contatos[], int numContatos);

void main(void) {
    //Função que carrega as informações da agenda (caso haja)
    carregar_agenda(agenda);  
    int registro;

    do {
        // Criação do MENU, chamando as funções
        printf("\n\n [MENU] \n\n");
        printf("[1]. Novo Contato\n");
        printf("[2]. Buscar Contato\n");
        printf("[3]. Deletar Contato\n");
        printf("[4]. Salvar Dados\n");
        printf("[0]. Sair\n");

        scanf("%d", &registro);
        getchar(); // Limpa o buffer do teclado após o scanf

        switch(registro) {
            case 1:
                novo_contato(agenda, &totalcontatos);  
                break;
            case 2:
                buscar_contato(agenda, totalcontatos);  
                break;
            case 3:
                deletar_contato(agenda, &totalcontatos);  
                break;
            case 4:
                salvar_contatos(agenda, totalcontatos);  
                break;
            case 0:
                break;
        }

    } while (registro != 0);
}

// Carrega contatos anteriores (caso haja)
// %127[^,] lê até 127 caracteres; %14[^\n]\n lê até 14 caracteres
void carregar_agenda(contato contatos[]) {
    FILE *arquivo = fopen(ARQUIVO, "r");
    if (!arquivo) return;

    while (fscanf(arquivo, "%127[^,], %14[^\n]\n", contatos[totalcontatos].nome, contatos[totalcontatos].telefone) == 2) {
        totalcontatos++;
        if (totalcontatos >= MAX_Contatos) break;
    }

    fclose(arquivo);
}

// Função que adiciona um novo contato
void novo_contato(contato contatos[], int *numContatos) {
    if (*numContatos >= MAX_Contatos) {
        printf("Agenda cheia!\n");
        return;
    }

    // Leitura do nome, incluindo espaços
    printf("Digite o nome\n");
    fgets(contatos[*numContatos].nome, M_Nome, stdin);
    contatos[*numContatos].nome[strcspn(contatos[*numContatos].nome, "\n")] = 0;  // Remove o \n do nome

    //Leitura do telefone, incluindo espaços
    printf("Digite o número de telefone. Exemplo: 63 99999-9999\n");
    fgets(contatos[*numContatos].telefone, M_Telefone, stdin);
    contatos[*numContatos].telefone[strcspn(contatos[*numContatos].telefone, "\n")] = 0; // Remove o \n do telefone

    (*numContatos)++;
    printf("Contato adicionado com sucesso\n");
}

void buscar_contato(contato contatos[], int numContatos) {
    char nomeBusca[M_Nome];
    printf("Digite o nome do contato a buscar: ");
    fgets(nomeBusca, M_Nome, stdin); // Lê a busca incluindo espaços
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Localiza a primeira ocorrência de um caractere

    int encontrado = 0;
    for (int i = 0; i < numContatos; i++) {
        if (strstr(contatos[i].nome, nomeBusca) != NULL) { // Devolve um ponteiro para a primeira ocorrência
            printf("Contato encontrado: %s - %s\n", contatos[i].nome, contatos[i].telefone);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }
}

void deletar_contato(contato contatos[], int *numContatos) {
    if (*numContatos == 0) {
        printf("Agenda telefônica vazia\n");
        return;
    }

    char nomeBusca[M_Nome];
    printf("Digite o nome do contato a deletar: ");
    fgets(nomeBusca, M_Nome, stdin); // Lê a busca incluindo espaços
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0'; // Remove o '\n' no final

    int i, encontrado = 0;
    for (i = 0; i < *numContatos; i++) {
        if (strcmp(contatos[i].nome, nomeBusca) == 0) { // Compara duas sequências
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        // Desloca os contatos restantes para preencher a vaga
        for (int j = i; j < *numContatos - 1; j++) {
            contatos[j] = contatos[j + 1];
        }
        (*numContatos)--; 
        printf("Contato deletado com sucesso.\n");
    } else {
        printf("Contato não encontrado.\n");
    }
}

void salvar_contatos(contato contatos[], int numContatos) {
    FILE *arquivo = fopen(ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar o arquivo.\n");
        return;
    }

    for (int i = 0; i < numContatos; i++) {
        fprintf(arquivo, "%s,%s\n", contatos[i].nome, contatos[i].telefone);
    }

    fclose(arquivo);
}
