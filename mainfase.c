#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdio.h>
#include "data.h"

int main()
{

    int codigo; // código do cliente
    char nome[50];
    char nif[50];
    char email[50];
    char tipo[50];
    float bateria;
    float autonomia;
    int geo;

    Veiculos* listaVeiculos = NULL;
    Clientes* listaClientes = NULL;
    Gestores* listaGestores = NULL;

    listaVeiculos = lerVeiculos();
    //listaClientes = lerClientes();
    listaGestores = lerGestores();

    int escolha;


    while (1) {
        printf("\nMenu Principal:\n");
        printf("\n1. Adicionar veiculo\n");
        printf("2. Listar veiculos\n");
        printf("3. Remover veiculo\n");
        printf("4. Adicionar cliente\n");
        printf("5. Listar clientes\n");
        printf("6. Remover cliente\n");
        printf("7. Alterar dados do cliente\n");
        printf("8. Adicionar gestor\n");
        printf("9. Listar gestores\n");
        printf("10. Remover gestor\n");
        printf("11. Sair\n");
        printf("\nEscolha uma opcao:\n");

        scanf("%d", &escolha);
        switch (escolha) {
        case 1:
            printf("Digite o codigo do veiculo: ");
            scanf("%d", &codigo);
            // Verificar se o veículo já existe
            if (existeVeiculos(listaVeiculos, codigo)) {
                printf("O veiculo com o codigo %d ja existe na lista.\n", codigo);
                break;
            }
            printf("Digite o tipo do veiculo: ");
            scanf("%s", tipo);
            printf("Digite a capacidade da bateria: ");
            scanf("%f", &bateria);
            printf("Digite a autonomia do veiculo: ");
            scanf("%f", &autonomia);
            listaVeiculos = inserirVeiculos(listaVeiculos, codigo, tipo, bateria, autonomia);

            guardarVeiculos(listaVeiculos);
            break;

        case 2:
            listarVeiculos(listaVeiculos);
            break;
        case 3:
            printf("Digite o codigo do veiculo que deseja remover: ");
            scanf("%d", &codigo);
            listaVeiculos = removerVeiculos(listaVeiculos, codigo);
            guardarVeiculos(listaVeiculos);
            printf("Veiculo %d removido com sucesso.\n", codigo);
            break;
        }
        switch (escolha) {
        case 4:
            printf("Digite o código do cliente: ");
            scanf("%d", &codigo);
            if (existeClientes(listaClientes, codigo)) {
                printf("O cliente com o codigo %d ja existe na lista.\n", codigo);
                break;
            }
            printf("Digite o nome do cliente: ");
            scanf("%s", nome);
            printf("Digite o NIF do cliente: ");
            scanf("%s", nif);
            printf("Digite o email do cliente: ");
            scanf("%s", email);

            // call the inserirClientes function
            listaClientes = inserirClientes(listaClientes, codigo, nome, nif, email);
            guardarClientes(listaClientes);
            break;
        }
        switch (escolha) {
        case 5:
            listarClientes(listaClientes);
            break;
        }
        switch (escolha) {
        case 6:
            printf("Digite o codigo do cliente que deseja remover: ");
            scanf("%d", &codigo);
            listaClientes = removerClientes(listaClientes, codigo);
            guardarClientes(listaClientes);
            break;
        }

        switch (escolha) {
        case 7:
        {

            printf("Digite o código do cliente a ser alterado: ");
            scanf("%d", &codigo);
            printf("Digite o novo nome do cliente: ");
            scanf("%s", nome);
            printf("Digite o novo NIF do cliente: ");
            scanf("%s", nif);
            printf("Digite o novo email do cliente: ");
            scanf("%s", email);

            listaClientes = alterarClientes(listaClientes, codigo, nome, nif, email);
            break;
        }

        case 8:
            printf("Digite o codigo do gestor: ");
            scanf("%d", &codigo);
            // Verificar se o gestor já existe
            if (existeGestores(listaGestores, codigo)) {
                printf("O gestor com o codigo %d ja existe na lista.\n", codigo);
                break;
            }
            printf("Digite o nome do gestor: ");
            scanf("%s", nome);
            printf("Digite o email do gestor: ");
            scanf("%s", email);
            listaGestores = inserirGestores(listaGestores, codigo, nome, email);

            if (guardarGestores(listaGestores)) {
                printf("Gestor adicionado com sucesso!\n");
            }
            else {
                printf("Erro ao adicionar gestor.\n");
            }
            break;
        }
        switch (escolha) {
        case 9:

            listarGestores(listaGestores);
            break;
        }
        switch (escolha) {
        case 10:
            printf("Digite o codigo do gestor que deseja remover: ");
            scanf("%d", &codigo);
            listaGestores = removerGestores(listaGestores, codigo);
            guardarGestores(listaGestores);
            printf("Gestor com o %d removido com sucesso.\n", codigo);
            break;
        }
    }
    }