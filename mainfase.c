#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "data.h"
#include <stdbool.h>

int main()
{
    int utilizadorEscolha;
    int escolha;
    int codigo; // c�digo do cliente
    char tipo[50];
    char tipo_utilizador;
    char password[50];
    char nome[50];
    char nif[10];
    char email[50];
    float bateria;
    float valor;
    float autonomia;
    char localizacao[50];
    Veiculos* listaVeiculos = NULL;
    Clientes* listaClientes = NULL;
    Gestores* listaGestores = NULL;
    Clientes* inicio = NULL;// Inicializa a lista vazia
    Utilizadores* listaUtilizadores = NULL;
    Aluguer* listaAlugueres = NULL;
    listaVeiculos = lerVeiculos();
    listaClientes = lerClientes();
    listaGestores = lerGestores();
    listaUtilizadores = lerUtilizadores();
    float taxa_aluguel = 10.0;
    int option;
    Grafo* grafo = NULL;



start:
    printf("Selecione uma op��o, por favor!\n");
    printf("1. Criar conta\n");
    printf("2. Login\n");
    printf("3. Sair do programa\n");
    scanf("%d", &option);

    switch (option) {
    case 1:
        printf("Digite o email do utilizador: ");
        scanf("%s", email);
        // Verificar se o utilizador j� existe
        if (existeUtilizadores(listaUtilizadores, email)) {
            printf("O utilizador com o email %s j� existe na lista.\n", email);
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
            printf("O utilizador com o email %s n�o existe na lista.\n", email);
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
                printf("\nSelecione uma op��o:\n");
                printf("1. Alugar um veiculo\n");
                printf("2. Carregar conta\n");
                printf("3. Verificar hist�rico de alugueres\n");
                printf("4. Sair do menu de cliente\n");
                scanf("%d", &utilizadorEscolha);

                switch (utilizadorEscolha) {
                case 1:
                {
                    int codigo_veiculo;
                    float valor_km = 0.5; // Exemplo de valor por quil�metro fixo
                    int distancia_km = 50; // Exemplo de dist�ncia percorrida fixa

                    printf("Insira o c�digo do ve�culo: ");
                    scanf("%d", &codigo_veiculo);

                    // Verificar se o ve�culo existe
                    if (!existeVeiculos(listaVeiculos, codigo_veiculo)) {
                        printf("Ve�culo n�o encontrado.\n");
                        break;
                    }

                    // Verificar se o ve�culo j� est� alugado
                    if (veiculoEstaAlugado(listaAlugueres, codigo_veiculo)) {
                        printf("O ve�culo j� est� alugado. Por favor, escolha outro ve�culo.\n");
                        break;
                    }

                    // Obter o valor por quil�metro do ve�culo
                    if (valor_km == 0.0) {
                        printf("Valor por quil�metro n�o encontrado para o ve�culo.\n");
                        break;
                    }

                    printf("Insira a dist�ncia percorrida em quil�metros: ");
                    scanf("%d", &distancia_km);

                    float valor = valor_km * distancia_km;

                    printf("Valor a pagar: %.2f\n", valor);

                    // Alugar o ve�culo
                    listaAlugueres = alugarVeiculo(listaAlugueres, codigo_veiculo, distancia_km, valor, valor_km);
                    printf("Ve�culo alugado com sucesso.\n");

                    // Abrir o arquivo em modo de escrita (append)
                    FILE* arquivo = fopen("alugueres.txt", "a");
                    if (arquivo == NULL) {
                        printf("Erro ao abrir o arquivo de hist�rico.\n");
                        break;
                    }

                    // Escrever os detalhes do aluguel no arquivo
                    fprintf(arquivo, "C�digo do ve�culo: %d\n", codigo_veiculo);
                    fprintf(arquivo, "Dist�ncia percorrida: %d\n", distancia_km);
                    fprintf(arquivo, "Valor: %.2f\n\n", valor);

                    // Fechar o arquivo
                    fclose(arquivo);

                    break;
                }
                case 2:
                {
                    int codigo;
                    printf("Digite o c�digo do cliente: ");
                    scanf("%d", &codigo);

                    // Verificar se o cliente existe na lista de clientes
                    int clienteExiste = existeClientes(listaClientes, codigo);
                    if (clienteExiste == 0) {
                        printf("Cliente n�o encontrado.\n");
                        break;
                    }

                    float saldo;
                    char valor_str[100];
                    printf("Digite o valor a ser carregado: ");
                    scanf("%s", valor_str);

                    if (sscanf(valor_str, "%f", &saldo) != 1) {
                        printf("Valor inv�lido.\n");
                        break;
                    }

                    // Carregar o saldo do cliente
                    listaClientes = carregarSaldo(listaClientes, codigo, saldo);
                    break;
                }


                case 3:

                {
                    // Abrir o arquivo em modo de leitura
                    FILE* arquivo = fopen("alugueres.txt", "r");
                    if (arquivo == NULL) {
                        printf("Nenhum hist�rico de aluguer encontrado.\n");
                        break;
                    }

                    // Ler e exibir o conte�do do arquivo
                    char linha[100];
                    printf("Hist�rico de aluguer:\n");
                    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                        printf("%s", linha);
                    }

                    // Fechar o arquivo
                    fclose(arquivo);

                    break;
                }

                case 4:
                    printf("Digite o c�digo do cliente: ");
                    scanf("%d", &codigo);

                    printf("Digite o valor a ser carregado: ");
                    scanf("%f", &valor);

                    listaClientes = carregarSaldo(listaClientes, codigo, valor);
                    guardarClientes(listaClientes);

                    printf("Saldo carregado com sucesso.\n");
                    continue;


                case 5:
                    // sair do menu do cliente
                    goto start;
                default:
                    printf("Op��o inv�lida. Tente novamente.\n");
                }
            }
        }
        else if (tipo == '2') {
            printf("Bem-vindo, gestor!\n");
            int gestorEscolha;

            system("CLS");

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
                printf("11. Gerir localizacao\n");
                printf("12. Sair\n");
                printf("\nEscolha uma opcao:\n");
                scanf("%d", &gestorEscolha);

                switch (gestorEscolha) {
                case 1:
                {
                    int codigo;
                    printf("Digite o c�digo do ve�culo: ");
                    scanf("%d", &codigo);

                    // Verificar se o ve�culo j� existe
                    if (existeVeiculos(listaVeiculos, codigo)) {
                        printf("O ve�culo com o c�digo %d j� existe na lista.\n", codigo);
                    }
                    else {
                        char tipo[50];
                        float bateria, autonomia;
                        printf("Digite o tipo do ve�culo: ");
                        scanf("%s", tipo);
                        printf("Digite a bateria do ve�culo: ");
                        scanf("%f", &bateria);
                        printf("Digite a autonomia do ve�culo: ");
                        scanf("%f", &autonomia);

                        // Adicionar a funcionalidade de inserir uma localiza��o usando o what3words
                        char localizacao[50];
                        printf("Digite a localiza��o do ve�culo (what3words): ");
                        scanf("%s", localizacao);

                        // Criar o novo ve�culo com os dados fornecidos
                        listaVeiculos = inserirVeiculos(listaVeiculos, codigo, tipo, bateria, autonomia, localizacao); // O �ltimo argumento '0' representa que o ve�culo n�o est� alugado
                        printf("Ve�culo guardado com sucesso.\n");
                        guardarVeiculos(listaVeiculos);
                    }

                    continue;
                    break;
                }


                case 2:
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
                    printf("Digite o c�digo do cliente: ");
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


                    printf("Digite o c�digo do cliente a ser alterado: ");
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
                    // Verificar se o gestor j� existe
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
                system("CLS");



    case 11:
    {
        int escolha_menu = 0;
        while (escolha_menu != 2) {

            printf("\nMenu de Gerenciamento de Localizacao:\n");
            printf("1. Listar Grafos\n");
            printf("2. Alterar vertice a partir do ID\n");
            printf("3. Alterar arestas a partir do ID\n");
            printf("4. Sair do Menu de Gerenciamento de Localizacao\n");
            printf("\nEscolha uma opcao:\n");
            scanf("%d", &escolha_menu);


            switch (escolha_menu) {

                {
            case 1:
            {
                lerVerticesDeArquivo(grafo, "grafos.txt");
                listarGrafoDeArquivo("grafos.txt");

                break;

            }

            case 2:
            {
                int id_vertice;
                printf("ID do v�rtice a ser alterado: ");
                scanf("%d", &id_vertice);
                alterarVerticePorID(grafo, id_vertice);
                break;
            }
            case 3:
            {
                int id_vertice;
                printf("ID do v�rtice para alterar as arestas: ");
                scanf("%d", &id_vertice);
                alterarArestasPorID(grafo, id_vertice);
                break;
            }
            default:
                printf("Op��o inv�lida.\n");
                }

                break;
            }

        }
    }
            }
        }
    }
}