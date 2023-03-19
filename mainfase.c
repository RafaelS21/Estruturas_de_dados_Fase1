#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "data.h"

int main()
{
    int utilizadorEscolha;
    int escolha;
    int codigo; // código do cliente
    char tipo[50];
    char tipo_utilizador;
    char password[50];
    char nome[50];
    char nif[10];
    char email[50];
    float bateria;
    float autonomia;
    int geo;
    Veiculos* listaVeiculos = NULL;
    Clientes* listaClientes = NULL;
    Gestores* listaGestores = NULL;
    Utilizadores* listaUtilizadores = NULL;
    listaVeiculos = lerVeiculos();
    listaClientes = lerClientes();
    listaGestores = lerGestores();
    listaUtilizadores = lerUtilizadores();

    int option;

start:
    printf("Selecione uma opção, por favor!\n");
    printf("1. Criar conta\n");
    printf("2. Login\n");
    printf("3. Sair do programa\n");
    scanf("%d", &option);

    switch (option) {
    case 1:
        printf("Digite o email do utilizador: ");
        scanf("%s", email);
        // Verificar se o utilizador já existe
        if (existeUtilizadores(listaUtilizadores, email)) {
            printf("O utilizador com o email %s já existe na lista.\n", email);
            goto start;
        }
        printf("Digite a password: ");
        scanf("%s", password);
        printf("Digite o tipo de utilizador: ");
        scanf(" %c", &tipo_utilizador);
        listaUtilizadores = inserirUtilizadores(listaUtilizadores, email, password, tipo_utilizador);
        guardarUtilizadores(listaUtilizadores);
        goto start;

        break;

    case 2:
        printf("Digite o email do utilizador: ");
        scanf("%s", email);

        // Verificar se o utilizador existe
        if (!existeUtilizadores(listaUtilizadores, email)) {
            printf("O utilizador com o email %s não existe na lista.\n", email);
            goto start;
        }

        printf("Digite a password: ");
        scanf("%s", password);

        // Fazer login do utilizador
        int tipo = loginUtilizador(listaUtilizadores, email, password);
        if (tipo == -1) {
            printf("Senha incorreta.\n");
            goto start;
        }

        // Verificar o tipo de utilizador
        if (tipo == '1') {
            printf("Bem-vindo, cliente %s!\n", email);
            int utilizadorEscolha;

            // loop principal do menu do cliente
            while (1) {
                printf("\nSelecione uma opção:\n");
                printf("1. Alugar um veiculo\n");
                printf("2. Verificar histórico de alugueres\n");
                printf("3. Sair do menu de cliente\n");
                scanf("%d", &utilizadorEscolha);

                switch (utilizadorEscolha) {
                case 1:
                    alugar_veiculo(email);
                    break;
                case 2:
                    
                    break;
                case 3:
                    // sair do menu do cliente
                    goto start;
                default:
                    printf("Opção inválida. Tente novamente.\n");
                }
            }
        }
        else if (tipo == '2') {
            printf("Bem-vindo, gestor!\n");
            int gestorEscolha;

            // loop principal do menu do gestor
            while (1) {
                printf("\nMenu Principal:\n");
                printf("1. Adicionar veiculo\n");
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
                scanf("%d", &gestorEscolha);

                switch (gestorEscolha) {
                case 1:
                    printf("Digite o codigo do veiculo: ");
                    scanf("%d", &codigo);
                    // Verificar se o veículo já existe
                    if (existeVeiculos(listaVeiculos, codigo)) {
                        printf("O veiculo com o codigo %d ja existe na lista.\n", codigo);
                    }
                    else {
                        char tipo[50]; // alteração: declaração do array de caracteres tipo aqui
                        float bateria, autonomia;
                        printf("Digite o tipo do veiculo: ");
                        scanf("%s", &tipo);
                        printf("Digite a bateria da bateria: ");
                        scanf("%f", &bateria);
                        printf("Digite a autonomia do veiculo: ");
                        scanf("%f", &autonomia);
                        listaVeiculos = inserirVeiculos(listaVeiculos, codigo, tipo, bateria, autonomia);
                        printf("Veiculo guardado com sucesso\n");

                        guardarVeiculos(listaVeiculos);



                    }
                    continue;
                    break;

                case 2:
                    ordenarVeiculosPorAutonomia(listaVeiculos);
                    listarVeiculos(listaVeiculos);
                    continue;

                case 3:
                    printf("Digite o codigo do veiculo que deseja remover: ");
                    scanf("%d", &codigo);
                    listaVeiculos = removerVeiculos(listaVeiculos, codigo);
                    guardarVeiculos(listaVeiculos);
                    printf("Veiculo %d removido com sucesso.\n", codigo);
                    continue;

                case 4:
                    printf("Digite o código do cliente: ");
                    scanf("%d", &codigo);
                    if (existeClientes(listaClientes, codigo)) {
                        printf("O cliente com o codigo %d ja existe na lista.\n", codigo);
                        continue;
                    }
                    printf("Digite o nome do cliente: ");
                    scanf("%s", nome);
                    printf("Digite o NIF do cliente: ");
                    scanf("%s", nif);
                    printf("Digite o email do cliente: ");
                    scanf("%s", email);

                    listaClientes = inserirClientes(listaClientes, codigo, nome, nif, email);
                    guardarClientes(listaClientes);
                    continue;

                case 5:
                    listarClientes(listaClientes);
                    continue;

                case 6:
                    printf("Digite o codigo do cliente que deseja remover: ");
                    scanf("%d", &codigo);
                    listaClientes = removerClientes(listaClientes, codigo);
                    guardarClientes(listaClientes);
                    continue;

                case 7:


                    printf("Digite o código do cliente a ser alterado: ");
                    scanf("%d", &codigo);
                    printf("Digite o novo nome do cliente: ");
                    scanf("%s", nome);
                    printf("Digite o novo NIF do cliente: ");
                    scanf("%s", nif);
                    printf("Digite o novo email do cliente: ");
                    scanf("%s", email);

                    listaClientes = alterarClientes(listaClientes, codigo, nome, nif, email);
                    continue;
                case 8:
                    printf("Digite o codigo do gestor: ");
                    scanf("%d", &codigo);
                    // Verificar se o gestor já existe
                    if (existeGestores(listaGestores, codigo)) {
                        printf("O gestor com o codigo %d ja existe na lista.\n", codigo);
                        continue;
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
                    continue;

                case 9:

                    listarGestores(listaGestores);
                    continue;

                case 10:
                    printf("Digite o codigo do gestor que deseja remover: ");
                    scanf("%d", &codigo);
                    listaGestores = removerGestores(listaGestores, codigo);
                    guardarGestores(listaGestores);
                    printf("Gestor com o %d removido com sucesso.\n", codigo);
                    continue;
                }


    case 110:
        printf("Exiting the application...\n");
        break;
            }

            while (option != 3);
        }
    }
}