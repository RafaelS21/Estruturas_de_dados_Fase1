#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "data.h"
#include <stdlib.h>


// Inserir Veiculos:

Veiculos* inserirVeiculos(Veiculos* inicio, int codigo, char tipo[], float bateria, float autonomia) {
    // aloca memória para o novo veículo
    Veiculos* novoVeiculo = (Veiculos*)malloc(sizeof(Veiculos));
    if (novoVeiculo == NULL) {
        printf("Erro: não foi possível alocar memória\n");
        return inicio;
    }
    // preenche os campos do novo veículo
    novoVeiculo->codigo = codigo;
    strncpy(novoVeiculo->tipo, tipo, sizeof(novoVeiculo->tipo) - 1);
    novoVeiculo->tipo[sizeof(novoVeiculo->tipo) - 1] = '\0'; 
    novoVeiculo->bateria = bateria;
    novoVeiculo->autonomia = autonomia;
    novoVeiculo->geo = 0; // valor padrão para geo
    novoVeiculo->seguinte = inicio; // faz o novo veículo apontar para o início da lista
    return novoVeiculo; // retorna o novo início da lista
}


// Listar os veiculso adicionados:

void listarVeiculos(Veiculos* inicio) {
    if (inicio == NULL) {
        printf("A lista de veículos está vazia.\n");
        return;
    }
    printf("Lista de veículos:\n");
    while (inicio != NULL) {
        printf("%d %s %.2f %.2f\n", inicio->codigo, inicio->tipo, inicio->bateria, inicio->autonomia);
        inicio = inicio->seguinte;
    }
}

void ordenarVeiculosPorAutonomia(Veiculos* inicio) {
    if (inicio == NULL) {
        printf("A lista de veículos está vazia.\n");
        return;
    }
    int trocou = 0;
    do {
        trocou = 0;
        Veiculos* atual = inicio;
        Veiculos* anterior = NULL;
        while (atual->seguinte != NULL) {
            if (atual->autonomia < atual->seguinte->autonomia) {
                Veiculos* temp = atual->seguinte;
                atual->seguinte = atual->seguinte->seguinte;
                temp->seguinte = atual;
                if (anterior != NULL) {
                    anterior->seguinte = temp;
                }
                else {
                    inicio = temp;
                }
                anterior = temp;
                trocou = 1;
            }
            else {
                anterior = atual;
                atual = atual->seguinte;
            }
        }
    } while (trocou);
}

void alugar_veiculo(Veiculos* lista_veiculos, Clientes* lista_clientes) {
    int codigo_cliente, codigo_veiculo, tempo_aluguel;
    float valor_aluguel;
    Veiculos* veiculo_atual = lista_veiculos;
    Clientes* cliente_atual = lista_clientes;

    // pedir código do cliente e do veículo
    printf("Insira o código do cliente: ");
    scanf("%d", &codigo_cliente);
    printf("Insira o código do veículo: ");
    scanf("%d", &codigo_veiculo);

    // verificar se o código do cliente é válido
    while (cliente_atual != NULL) {
        if (cliente_atual->codigo == codigo_cliente) {
            break;
        }
        cliente_atual = cliente_atual->seguinte;
    }
    if (cliente_atual == NULL) {
        printf("Código de cliente inválido.\n");
        return;
    }

    // verificar se o código do veículo é válido
    while (veiculo_atual != NULL) {
        if (veiculo_atual->codigo == codigo_veiculo) {
            break;
        }
        veiculo_atual = veiculo_atual->seguinte;
    }
    if (veiculo_atual == NULL) {
        printf("Código de veículo inválido.\n");
        return;
    }

    // verificar se o veículo já está alugado
    if (veiculo_atual->alugado == 1) {
        printf("Veículo já está alugado.\n");
        return;
    }

    // pedir tempo de aluguel
    printf("Por quantas horas deseja alugar o veículo? ");
    scanf("%d", &tempo_aluguel);

    // calcular valor do aluguel
    valor_aluguel = veiculo_atual->autonomia * tempo_aluguel;

    // atualizar informações do veículo
    veiculo_atual->alugado = 1;
    veiculo_atual->cliente = codigo_cliente;
    veiculo_atual->tempo_aluguel = tempo_aluguel;
    // criar novo nó para a lista de alugueis
    Aluguel* novo_aluguel = (Aluguel*) malloc(sizeof(Aluguel));
    novo_aluguel->codigo_veiculo = codigo_veiculo;
    novo_aluguel->tempo = tempo_aluguel;
    novo_aluguel->valor = valor_aluguel;
    novo_aluguel->seguinte = NULL;

    // adicionar nó à lista de alugueis do cliente correspondente
    Aluguel* aluguel_atual = cliente_atual->alugueis;
    if (aluguel_atual == NULL) {
        cliente_atual->alugueis = novo_aluguel;
    } else {
        while (aluguel_atual->seguinte != NULL) {
            aluguel_atual = aluguel_atual->seguinte;
        }
        aluguel_atual->seguinte = novo_aluguel;
    }

    // informar sucesso e mostrar valor do aluguel
    printf("Veículo alugado com sucesso. Valor do aluguel: R$ %.2f\n", valor_aluguel);
}


// Existe Veiculos:
int existeVeiculos(Veiculos* inicio, int codigo)
{
    Veiculos* atual = inicio;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return 1;
        }
        atual = atual->seguinte;
    }
    return 0;
}

//Remover veiculos:

Veiculos* removerVeiculos(Veiculos* inicio, int cod)
{
    Veiculos* anterior, * atual;
    anterior = NULL;
    atual = inicio;

    while (atual != NULL)
    {
        if (atual->codigo == cod)
        {
            if (anterior == NULL) // o código a remover é o primeiro da lista
            {
                inicio = atual->seguinte;
                free(atual);
                return inicio;
            }
            else // o código a remover está no meio ou no fim da lista
            {
                anterior->seguinte = atual->seguinte;
                free(atual);
                return inicio;
            }
        }
        anterior = atual;
        atual = atual->seguinte;
    }

    printf("Não foi encontrado um registo com o código %d.\n", cod);
    return inicio;
}

//Guardar Veiculos

int guardarVeiculos(Veiculos* inicio)
{
    FILE* ficheiro;
    ficheiro = fopen("veiculos.txt", "w");
    if (ficheiro == NULL) {
        printf("Não foi possível abrir o ficheiro.\n");
        return 0;
    }

    Veiculos* aux = inicio;
    while (aux != NULL)
    {
        fprintf(ficheiro, "%d %s %.2f %.2f\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia);
        aux = aux->seguinte;
    }

    fclose(ficheiro);
    return 1;
}


// Ler veiculos
Veiculos* lerVeiculos()
{
    FILE* ficheiro;
    ficheiro = fopen("veiculos.txt", "r");
    if (ficheiro == NULL) {
        printf("Não foi possível abrir o ficheiro.\n");
        return NULL;
    }

    int codigo;
    char tipo[20];
    float bateria;
    float autonomia;

    Veiculos* inicio = NULL;

    while (fscanf(ficheiro, "%d %s %.2f %.2f", &codigo, tipo, &bateria, &autonomia) != EOF)
    {
        inicio = inserirVeiculos(inicio, codigo, tipo, bateria, autonomia);
    }

    fclose(ficheiro);
    return inicio;
}




// Inserir Clientes

Clientes* inserirClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]) {
    // Verificar se já existe um cliente com o mesmo código
    if (existeClientes(inicio, codigo)) {
        printf("Já existe um cliente com o código %d\n", codigo);
        return inicio;
    }

    // Alocar memória para o novo cliente
    Clientes* novo = (Clientes*)malloc(sizeof(Clientes));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo cliente\n");
        return inicio;
    }

    // Preencher os dados do novo cliente
    novo->codigo = codigo;
    strcpy(novo->nome, nome);
    strcpy(novo->nif, nif);
    strcpy(novo->email, email);
    novo->seguinte = NULL;

    // Adicionar o novo cliente ao fim da lista
    if (inicio == NULL) {
        inicio = novo;
    }
    else {
        // Ler a lista existente do arquivo
        Clientes* atual = inicio;
        while (atual->seguinte != NULL) {
            atual = atual->seguinte;
        }
        atual->seguinte = novo;
    }

    // Escrever a lista completa de volta para o arquivo
    if (!guardarClientes(inicio)) {
        printf("Erro ao guardar a lista de clientes no arquivo\n");
        // Desfazer a inserção do novo cliente da lista
        if (inicio == novo) {
            inicio = NULL;
        }
        else {
            Clientes* atual = inicio;
            while (atual->seguinte != novo) {
                atual = atual->seguinte;
            }
            atual->seguinte = NULL;
        }
        free(novo);
        return inicio;
    }

    printf("Cliente com o código %d inserido com sucesso\n", codigo);
    return inicio;
}


// Existe Clientes

int existeClientes(Clientes* inicio, int codigo) {
    Clientes* atual = inicio;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return 1; // O código já existe na lista ligada
        }
        atual = atual->seguinte;
    }
    return 0; // O código não existe na lista ligada
}

// Guardar
int guardarClientes(Clientes* inicio) {
    FILE* fp;
    char filename[] = "clientes.txt"; // file name to save the clients list
    fp = fopen(filename, "w"); // open the file in write mode

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return 0;
    }

    // write each client's information to the file
    while (inicio != NULL) {
        fprintf(fp, "%d %s %s %s\n", inicio->codigo, inicio->nome, inicio->nif, inicio->email);
        inicio = inicio->seguinte;
    }

    fclose(fp); // close the file
    return 1;
}

// listar

void listarClientes(Clientes* inicio) {
    if (inicio == NULL) {
        printf("A lista de clientes está vazia.\n");
    }
    else {
        printf("Lista de clientes:\n");
        while (inicio != NULL) {
            printf("Código: %d\n", inicio->codigo);
            printf("Nome: %s\n", inicio->nome);
            printf("NIF: %s\n", inicio->nif);
            printf("Email: %s\n", inicio->email);
            printf("\n");
            inicio = inicio->seguinte;
        }

    }
}
Clientes* removerClientes(Clientes* inicio, int codigo) {
    if (inicio == NULL) {
        printf("A lista de clientes está vazia\n");
        return inicio;
    }

    Clientes* atual = inicio;
    Clientes* anterior = NULL;

    // Procurar o cliente com o código especificado
    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->seguinte;
    }

    // Se não encontrou o cliente com o código especificado
    if (atual == NULL) {
        printf("Não existe um cliente com o código %d\n", codigo);
        return inicio;
    }

    // Se o cliente a remover é o primeiro da lista
    if (anterior == NULL) {
        inicio = atual->seguinte;
    }
    else {
        anterior->seguinte = atual->seguinte;
    }

    printf("Cliente com o código %d removido com sucesso\n", codigo);
    free(atual);
    return inicio;
}


Clientes* alterarClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]) {
    // Verificar se o cliente existe
    if (!existeClientes(inicio, codigo)) {
        printf("Não existe um cliente com o código %d\n", codigo);
        return inicio;
    }

    // Procurar o cliente a ser alterado
    Clientes* atual = inicio;
    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->seguinte;
    }

    // Alterar os dados do cliente
    strcpy(atual->nome, nome);
    strcpy(atual->nif, nif);
    strcpy(atual->email, email);

    // Escrever a lista completa de volta para o arquivo
    if (!guardarClientes(inicio)) {
        printf("Erro ao guardar a lista de clientes no arquivo\n");
        // Desfazer a alteração dos dados do cliente
        strcpy(atual->nome, "");
        strcpy(atual->nif, "");
        strcpy(atual->email, "");
    }

    printf("Dados do cliente com o código %d alterados com sucesso\n", codigo);
    return inicio;
}

Gestores* inserirGestores(Gestores* inicio, int codigo, char nome[], char email[]) {
    Gestores* novoGestor = (Gestores*)malloc(sizeof(Gestores));
    if (novoGestor == NULL) { // Verificar se foi possível alocar memória
        printf("Erro: nao foi possivel alocar memoria para um novo gestor.\n");
        return inicio;
    }
    novoGestor->codigo = codigo;
    strcpy(novoGestor->nome, nome);
    strcpy(novoGestor->email, email);
    novoGestor->seguinte = NULL;

    Gestores* gestorAtual = NULL;
    if (inicio == NULL) { // Se a lista estiver vazia, o novo gestor é o primeiro
        return novoGestor;
    }
    else {
        gestorAtual = inicio;
        while (gestorAtual->seguinte != NULL) { // Percorrer a lista até chegar ao último gestor
            gestorAtual = gestorAtual->seguinte;
        }
        gestorAtual->seguinte = novoGestor; // O último gestor passa a apontar para o novo gestor
        return inicio;
    }
}



void listarGestores(Gestores* inicio) {
    Gestores* gestorAtual = inicio;
    while (gestorAtual != NULL) {
        printf("Código: %d\n", gestorAtual->codigo);
        printf("Nome: %s\n", gestorAtual->nome);
        printf("Email: %s\n", gestorAtual->email);
        printf("\n");
        gestorAtual = gestorAtual->seguinte;
    }
}

int existeGestores(Gestores* inicio, int codigo) {
    Gestores* gestorAtual = inicio;
    while (gestorAtual != NULL) {
        if (gestorAtual->codigo == codigo) {
            return 1;
        }
        gestorAtual = gestorAtual->seguinte;
    }
    return 0;
}
int guardarGestores(Gestores* inicio) {
    FILE* arquivo;
    Gestores* gestorAtual;

    // Abrir o arquivo para escrita
    arquivo = fopen("gestores.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return 0;
    }

    // Percorrer a lista de gestores e escrever cada registro no arquivo
    gestorAtual = inicio;
    while (gestorAtual != NULL) {
        fprintf(arquivo, "%d,%s,%s\n", gestorAtual->codigo, gestorAtual->nome, gestorAtual->email);
        gestorAtual = gestorAtual->seguinte;
    }

    // Fechar o arquivo
    fclose(arquivo);
    return 1;
}
Gestores* lerGestores() {
    FILE* arquivo;
    Gestores* inicio = NULL;
    Gestores* gestorAtual = NULL; // Inicializa a variável gestorAtual com NULL

    // Abrir o arquivo para leitura
    arquivo = fopen("gestores.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para leitura.\n");
        return NULL;
    }

    // Ler cada linha do arquivo e criar um novo gestor com os dados lidos
    while (!feof(arquivo)) {
        int codigo;
        char nome[50];
        char email[50];

        if (fscanf(arquivo, "%d,%[^,],%s\n", &codigo, nome, email) != 3) {
            break; // Se a leitura não for bem sucedida, sair do loop
        }

        Gestores* novoGestor = (Gestores*)malloc(sizeof(Gestores));
        if (novoGestor == NULL) { // Verificar se foi possível alocar memória
            printf("Erro: nao foi possivel alocar memoria para um novo gestor.\n");
            break; // Se não foi possível alocar memória, sair do loop
        }
        novoGestor->codigo = codigo;
        strcpy(novoGestor->nome, nome);
        strcpy(novoGestor->email, email);
        novoGestor->seguinte = NULL;

        if (inicio == NULL) { // Se a lista estiver vazia, o novo gestor é o primeiro
            inicio = novoGestor;
            gestorAtual = novoGestor;
        }
        else {
            gestorAtual->seguinte = novoGestor; // O último gestor passa a apontar para o novo gestor
            gestorAtual = gestorAtual->seguinte; // Atualizar o ponteiro para o último gestor
        }
    }

    // Fechar o arquivo
    fclose(arquivo);
    
    return inicio;
}

Gestores* removerGestores(Gestores* inicio, int codigo) {
    Gestores* gestorAnterior = NULL;
    Gestores* gestorAtual = inicio;

    // Percorrer a lista até encontrar o gestor com o código especificado
    while (gestorAtual != NULL && gestorAtual->codigo != codigo) {
        gestorAnterior = gestorAtual;
        gestorAtual = gestorAtual->seguinte;
    }

    // Se não encontrou o gestor com o código especificado, retornar a lista original
    if (gestorAtual == NULL) {
        return inicio;
    }

    // Se o gestor a ser removido é o primeiro da lista
    if (gestorAnterior == NULL) {
        inicio = gestorAtual->seguinte;
    }
    // Se o gestor a ser removido não é o primeiro da lista
    else {
        gestorAnterior->seguinte = gestorAtual->seguinte;
    }

    // Liberar a memória alocada pelo gestor removido
    free(gestorAtual);

    return inicio;
}

Clientes* lerClientes() {
    FILE* fp;
    fp = fopen("clientes.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }
    Clientes* inicio = NULL;
    char linha[200];
    while (fgets(linha, 200, fp) != NULL) {
        char* token;
        token = strtok(linha, ";");
        int codigo = atoi(token);
        token = strtok(NULL, ";");
        char nome[50];
        strcpy(nome, token);
        token = strtok(NULL, ";");
        char nif[50];
        strcpy(nif, token);
        token = strtok(NULL, ";");
        char email[50];
        strcpy(email, token);
        inicio = inserirClientes(inicio, codigo, nome, nif, email);
    }
    fclose(fp);
    return inicio;
}

/*
int fazerLogin(Utilizadores* inicio) {
    char email[50];
    char password[50];

    printf("Digite seu email: ");
    scanf("%s", email);
    printf("Digite sua password: ");
    scanf("%s",password);

    Utilizadores* atual = inicio;
    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0 && strcmp(atual->password, password) == 0) {
            if (atual->tipo == 1) {
                menuCliente();
            }
            else if (atual->tipo == 2) {
                menuGestor();
            }
            return 1;
        }
        atual = atual->proximo;
    }

    printf("Email ou password incorretos.\n");
    return 0;
}

*/

Utilizadores* inserirUtilizadores(Utilizadores* inicio, char* email, char* password, char tipo_utilizador) {
    Utilizadores* novo_utilizador = (Utilizadores*)malloc(sizeof(Utilizadores));
    strcpy(novo_utilizador->email, email);
    strcpy(novo_utilizador->password, password);
    novo_utilizador->tipo_utilizador = tipo_utilizador;
    novo_utilizador->proximo = NULL;

    if (inicio == NULL) {
        inicio = novo_utilizador;
    }
    else {
        Utilizadores* ultimo = inicio;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novo_utilizador;
    }

    return inicio;
}
// Função que lista todos os utilizadores da lista ligada
void listarUtilizadores(Utilizadores* inicio) {
    Utilizadores* atual = inicio;

    while (atual != NULL) {
        printf("Email: %s\n", atual->email);
        printf("Tipo de utilizador: %s\n", atual->tipo_utilizador == '1' ? "cliente" : "gestor");
        printf("----------------------\n");
        atual = atual->proximo;
    }
}

// Função que verifica se um utilizador com um determinado email existe na lista ligada
int existeUtilizadores(Utilizadores* inicio, char* email) {
    Utilizadores* atual = inicio;

    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            return 1; // encontrado
        }
        atual = atual->proximo;
    }

    return 0; // não encontrado
}

// Função que remove um utilizador da lista ligada com base no email
Utilizadores* removerUtilizadores(Utilizadores* inicio, char* email) {
    Utilizadores* atual = inicio;
    Utilizadores* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            if (anterior == NULL) {
                inicio = atual->proximo; // primeiro nó
            }
            else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            return inicio;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    return inicio;
}

// Função que verifica se um utilizador com um determinado email e senha existe na lista ligada
int loginUtilizador(Utilizadores* inicio, char* email, char* password) {
    Utilizadores* atual = inicio;

    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0 && strcmp(atual->password, password) == 0) {
            return atual->tipo_utilizador; // encontrado
        }
        atual = atual->proximo;
    }

    return 0; // não encontrado
}

// Função que grava os dados dos utilizadores em um arquivo de texto
int guardarUtilizadores(Utilizadores* inicio) {
    FILE* arquivo;
    arquivo = fopen("utilizadores.txt", "w");
    if (arquivo == NULL) {
        return 0; // erro ao abrir arquivo
    }

    Utilizadores* atual = inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%c\n", atual->email, atual->password, atual->tipo_utilizador);
        atual = atual->proximo;
    }

    fclose(arquivo);
    return 1; // sucesso
}



// Função que lê os dados dos utilizadores de um arquivo de texto e os retorna como uma lista ligada
Utilizadores* lerUtilizadores() {
    FILE* arquivo;
    arquivo = fopen("utilizadores.txt", "r");
    if (arquivo == NULL) {
        return NULL; // erro ao abrir arquivo
    }

    Utilizadores* inicio = NULL;
    Utilizadores* atual = NULL;
    Utilizadores* novo = NULL;
    char linha[150];
    char* token;

    while (fgets(linha, 150, arquivo)) {
        novo = (Utilizadores*)malloc(sizeof(Utilizadores));
        novo->proximo = NULL;

        token = strtok(linha, ";");
        strcpy(novo->email, token);

        token = strtok(NULL, ";");
        strcpy(novo->password, token);

        token = strtok(NULL, ";");
        novo->tipo_utilizador = token[0];

        if (inicio == NULL) {
            inicio = novo;
            atual = novo;
        }
        else {
            atual->proximo = novo;
            atual = novo;
        }
    }

    fclose(arquivo);
    return inicio;
}
