#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>



Veiculos* inserirVeiculos(Veiculos* inicio, int codigo, char tipo[], float bateria, float autonomia, char localizacao[]) {
    Veiculos* novoVeiculo = (Veiculos*)malloc(sizeof(Veiculos));
    if (novoVeiculo == NULL) {
        printf("Erro: n�o foi poss�vel alocar mem�ria\n");
        return inicio;
    }

    novoVeiculo->codigo = codigo;
    strncpy(novoVeiculo->tipo, tipo, sizeof(novoVeiculo->tipo) - 1);
    novoVeiculo->tipo[sizeof(novoVeiculo->tipo) - 1] = '\0';
    novoVeiculo->bateria = bateria;
    novoVeiculo->autonomia = autonomia;
    strncpy(novoVeiculo->localizacao, localizacao, sizeof(novoVeiculo->localizacao) - 1);
    novoVeiculo->localizacao[sizeof(novoVeiculo->localizacao) - 1] = '\0';
    novoVeiculo->seguinte = inicio;

    return novoVeiculo;
}

/*
void ordenarVeiculosPorAutonomia(Veiculos** inicio) {
    if (*inicio == NULL || (*inicio)->seguinte == NULL) {
        return;
    }

    Veiculos* anterior = NULL;
    Veiculos* atual = *inicio;
    Veiculos* proximo = (*inicio)->seguinte;
    int trocou = 1;

    while (trocou) {
        trocou = 0;
        while (atual != NULL && proximo != NULL) {
            if (atual->autonomia < proximo->autonomia) {
                if (anterior != NULL) {
                    anterior->seguinte = proximo;
                }
                else {
                    *inicio = proximo;
                }
                atual->seguinte = proximo->seguinte;
                proximo->seguinte = atual;
                trocou = 1;
            }

            anterior = atual;
            atual = atual->seguinte;
            proximo = (atual != NULL) ? atual->seguinte : NULL;
        }
        anterior = NULL;
        atual = *inicio;
        proximo = (*inicio)->seguinte;
    }
}

*/

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

// Fun��o para remover um ve�culo da lista encadeada
Veiculos* removerVeiculos(Veiculos* inicio, int cod)
{
    Veiculos* anterior = NULL;
    Veiculos* atual = inicio;

    while (atual != NULL) {
        if (atual->codigo == cod) {
            if (anterior == NULL) {
                inicio = atual->seguinte;
                free(atual);
                return inicio;
            }
            else {
                anterior->seguinte = atual->seguinte;
                free(atual);
                return inicio;
            }
        }
        anterior = atual;
        atual = atual->seguinte;
    }

    printf("N�o foi encontrado um registo com o c�digo %d.\n", cod);
    return inicio;
}


//Guardar Veiculos

int guardarVeiculos(Veiculos* inicio)
{
    FILE* ficheiro;
    ficheiro = fopen("veiculos.txt", "w");
    if (ficheiro == NULL) {
        printf("N�o foi poss�vel abrir o ficheiro.\n");
        return 0;
    }

    Veiculos* aux = inicio;

    while (aux != NULL)
    {
        fprintf(ficheiro, "%d %s %.2f %.2f %s\n", aux->codigo, aux->tipo, aux->bateria, aux->autonomia, aux->localizacao);
        aux = aux->seguinte;
    }

    fclose(ficheiro);
    return 1;
}

Veiculos* lerVeiculos()
{
    FILE* ficheiro;
    ficheiro = fopen("veiculos.txt", "r");
    if (ficheiro == NULL) {
        printf("N�o foi poss�vel abrir o ficheiro.\n");
        return NULL;
    }

    int codigo;
    char tipo[20];
    float bateria;
    float autonomia;
    char localizacao[50];

    Veiculos* inicio = NULL;

    while (fscanf(ficheiro, "%d %19s %f %f %49s", &codigo, tipo, &bateria, &autonomia, localizacao) != EOF)
    {
        inicio = inserirVeiculos(inicio, codigo, tipo, bateria, autonomia, localizacao);
    }

    fclose(ficheiro);
    return inicio;
}


void listarVeiculos(Veiculos* inicio) {
    if (inicio == NULL) {
        printf("A lista de ve�culos est� vazia.\n");
        return;
    }
    printf("Lista de ve�culos:\n");
    Veiculos* atual = inicio;
    while (atual != NULL) {
        printf("C�digo: %d\n", atual->codigo);
        printf("Tipo: %s\n", atual->tipo);
        printf("Bateria: %.2f\n", atual->bateria);
        printf("Autonomia: %.2f\n", atual->autonomia);
        printf("Localiza��o: %s\n", atual->localizacao);
        printf("\n");
        atual = atual->seguinte;
    }
}

Aluguer* alugarVeiculo(Aluguer* inicio, int codigo_veiculo, float valor, int distancia_km, float valor_km) {
    // Verifica se o ve�culo j� est� alugado
    Aluguer* aluguerAtual = inicio;
    while (aluguerAtual != NULL) {
        if (aluguerAtual->codigo_veiculo == codigo_veiculo) {
            printf("Erro: o ve�culo j� est� alugado\n");
            return inicio;
        }
        aluguerAtual = aluguerAtual->seguinte;
    }

    Aluguer* novoAluguer = (Aluguer*)malloc(sizeof(Aluguer));
    if (novoAluguer == NULL) {
        printf("Erro: n�o foi poss�vel alocar mem�ria\n");
        return inicio;
    }

    novoAluguer->codigo_veiculo = codigo_veiculo;
    novoAluguer->valor = valor;
    novoAluguer->distancia_km = distancia_km;
    novoAluguer->valor_km = valor_km; // Adicionado
    novoAluguer->seguinte = inicio;

    return novoAluguer;
}



// Fun��o para salvar os alugueres em um arquivo
void guardarAlugueres(Aluguer* inicio) {
    FILE* arquivo;
    Aluguer* aluguerAtual = inicio;

    arquivo = fopen("alugueres.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    while (aluguerAtual != NULL) {
        fprintf(arquivo, "%d %.2f %d\n", aluguerAtual->codigo_veiculo, aluguerAtual->valor, aluguerAtual->distancia_km);
        aluguerAtual = aluguerAtual->seguinte;
    }

    fclose(arquivo);
}

Aluguer* lerAlugueres() {
    FILE* arquivo;
    Aluguer* inicio = NULL;
    int codigo_veiculo, distancia_km;
    float valor, valor_km;

    arquivo = fopen("alugueres.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }

    while (fscanf(arquivo, "%d %f %d\n", &codigo_veiculo, &valor, &distancia_km) != EOF) {
        valor_km = obterValorKm(listarVeiculos, codigo_veiculo); // Obter o valor por quil�metro do ve�culo
        inicio = alugarVeiculo(inicio, codigo_veiculo, valor, distancia_km, valor_km);
    }

    fclose(arquivo);

    return inicio;
}


// Fun��o para verificar se um ve�culo est� alugado
bool veiculoEstaAlugado(Aluguer* listaAlugueres, int codigo_veiculo) {
    Aluguer* atual = listaAlugueres;
    while (atual != NULL) {
        if (atual->codigo_veiculo == codigo_veiculo) {
            return true; // O ve�culo est� alugado
        }
        atual = atual->seguinte;
    }
    return false; // O ve�culo n�o est� alugado
}

// Fun��o para listar os alugueres
void listarAluguer(Aluguer* inicio) {
    if (inicio == NULL) {
        printf("A lista de aluguer est� vazia.\n");
        return;
    }

    printf("Hist�rico de alugu�is:\n");
    Aluguer* atual = inicio;
    while (atual != NULL) {
        printf("C�digo do ve�culo: %d\n", atual->codigo_veiculo);
        printf("Dist�ncia percorrida: %d\n", atual->distancia_km);
        printf("Valor: %.2f\n", atual->valor);
        printf("\n");
        atual = atual->seguinte;
    }
}

// Fun��o para obter o valor por quil�metro de um ve�culo
float obterValorKm(Veiculos* listaVeiculos, int codigo_veiculo) {
    Veiculos* veiculoAtual = listaVeiculos;

    while (veiculoAtual != NULL) {
        if (veiculoAtual->codigo == codigo_veiculo) {
            return veiculoAtual->valor_km;
        }
        veiculoAtual = veiculoAtual->seguinte;
    }

    // Retornar um valor padr�o se o ve�culo n�o for encontrado
    return 0.0;
}

// CLIENTES


// Inserir clientes
 

Clientes* inserirClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]){
    Clientes* novoCliente = (Clientes*)malloc(sizeof(Clientes));
    if (novoCliente == NULL) {
        printf("Erro: n�o foi poss�vel alocar mem�ria\n");
        return inicio;
    }

    novoCliente->codigo = codigo;
    strncpy(novoCliente->nome, nome, sizeof(novoCliente->nome) - 1);
    novoCliente->nome[sizeof(novoCliente->nome) - 1] = '\0';
    strncpy(novoCliente->nif, nif, sizeof(novoCliente->nif) - 1);
    novoCliente->nif[sizeof(novoCliente->nif) - 1] = '\0';
    strncpy(novoCliente->email, email, sizeof(novoCliente->email) - 1);
    novoCliente->email[sizeof(novoCliente->email) - 1] = '\0';
    novoCliente->seguinte = inicio;

    return novoCliente;
}


int existeClientes(Clientes* inicio, int codigo) {
    Clientes* atual = inicio;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return 1; // O cliente com o c�digo fornecido existe
        }
        atual = atual->seguinte;
    }
    return 0; // O cliente com o c�digo fornecido n�o existe
}


// Guardar Clientes
int guardarClientes(Clientes* inicio) {
    FILE* fp;
    char filename[] = "clientes.txt"; // Nome do ficheiro para guardar a lista de clientes
    fp = fopen(filename, "w"); // Abrir o ficheiro em modo escrita

    if (fp == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", filename);
        return 0;
    }

    // Escreve cada informa��o do cliente no ficheiro de texto
    while (inicio != NULL) {
        fprintf(fp, "%d %s %s %s\n", inicio->codigo, inicio->nome, inicio->nif, inicio->email);
        inicio = inicio->seguinte;
    }

    fclose(fp); // Fechar o ficheiro de texto
    return 1;
}

// Listar Clientes

void listarClientes(Clientes* inicio) {
    if (inicio == NULL) {
        printf("A lista de clientes est� vazia.\n");
        return;
    }

    printf("Lista de clientes:\n");
    Clientes* atual = inicio;
    while (atual != NULL) {
        printf("C�digo: %d\n", atual->codigo);
        printf("Nome: %s\n", atual->nome);
        printf("NIF: %s\n", atual->nif);
        printf("Email: %s\n", atual->email);
        printf("\n");
        atual = atual->seguinte;
    }
}

// Fun��o para remover um cliente da lista encadeada 
Clientes* removerClientes(Clientes* inicio, int codigo) {
    // Verificar se a lista est� vazia
    if (inicio == NULL) {
        printf("A lista de clientes est� vazia\n");
        return inicio;
    }

    // Inicializar ponteiros
    Clientes* atual = inicio;
    Clientes* anterior = NULL;

    // Procurar o cliente com o c�digo especificado
    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->seguinte;
    }

    // Se n�o encontrou o cliente com o c�digo especificado
    if (atual == NULL) {
        printf("N�o existe um cliente com o c�digo %d\n", codigo);
        return inicio;
    }

    // Se o cliente a remover � o primeiro da lista
    if (anterior == NULL) {
        inicio = atual->seguinte;
    }
    else {
        anterior->seguinte = atual->seguinte;
    }

    // Imprimir mensagem de sucesso e liberar mem�ria do cliente removido
    printf("Cliente com o c�digo %d removido com sucesso\n", codigo);
    free(atual);
    return inicio;

}


Clientes* alterarClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]) {
    // Verificar se o cliente existe
    if (!existeClientes(inicio, codigo)) {
        printf("N�o existe um cliente com o c�digo %d\n", codigo);
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
        // Desfazer a altera��o dos dados do cliente
        strcpy(atual->nome, "");
        strcpy(atual->nif, "");
        strcpy(atual->email, "");
    }

    printf("Dados do cliente com o c�digo %d alterados com sucesso\n", codigo);
    return inicio;

}

// Fun��o para ler clientes a partir de um arquivo e criar uma lista encadeada de clientes
Clientes* lerClientes() {
    // Abre o arquivo "clientes.txt" para leitura
    FILE* fp;
    fp = fopen("clientes.txt", "r");
    // Verifica se ocorreu algum erro ao abrir o arquivo
    if (fp == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return NULL;
    }
    // Inicializa a lista encadeada de clientes como vazia
    Clientes* inicio = NULL;
    // Cria uma string para armazenar cada linha lida do arquivo
    char linha[200];
    // Loop para ler cada linha do arquivo
    while (fgets(linha, 200, fp) != NULL) {
        // Vari�veis para armazenar os dados de cada cliente lido
        int codigo;
        char nome[50];
        char nif[50];
        char email[50];
        // Verifica se a linha cont�m os 4 campos esperados e armazena os dados em vari�veis locais
        if (sscanf(linha, "%d %49[^ ] %49[^ ] %49[^\n]", &codigo, nome, nif, email) == 4) {
            // Insere um novo cliente na lista encadeada usando a fun��o inserirClientes()
            inicio = inserirClientes(inicio, codigo, nome, nif, email);
        }
        else {
            // Erro de formata��o na linha
            printf("Erro de formata��o na linha: %s", linha);
        }
    }
    // Fecha o arquivo
    fclose(fp);
    // Retorna o ponteiro para o in�cio da lista encadeada de clientes
    return inicio;
}
Clientes* carregarSaldo(Clientes* inicio, int codigo, float valor) {
    Clientes* cliente = inicio;
    Clientes* clienteEncontrado = NULL;

    // Procurar o cliente na lista
    while (cliente != NULL) {
        if (cliente->codigo == codigo) {
            clienteEncontrado = cliente;
            break;
        }
        cliente = cliente->seguinte;
    }

    // Verificar se o cliente foi encontrado
    if (clienteEncontrado == NULL) {
        printf("Cliente n�o encontrado.\n");
        return inicio;
    }

    // Atualizar o saldo do cliente
    clienteEncontrado->saldo += valor;

    // Abrir o arquivo em modo de escrita
    FILE* arquivo = fopen("saldo.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de saldo.\n");
        return inicio;
    }

    // Percorrer a lista de clientes e salvar os saldos no arquivo
    cliente = inicio;
    while (cliente != NULL) {
        fprintf(arquivo, "%d %.2f\n", cliente->codigo, cliente->saldo);
        cliente = cliente->seguinte;
    }

    fclose(arquivo);

    printf("Saldo carregado com sucesso.\n");
    return inicio;
}



// GESTORES

Gestores* inserirGestores(Gestores* inicio, int codigo, char nome[], char email[]) {
    Gestores* novoGestor = (Gestores*)malloc(sizeof(Gestores));
    if (novoGestor == NULL) { // Verificar se foi poss�vel alocar mem�ria
        printf("Erro: nao foi possivel alocar memoria para um novo gestor.\n");
        return inicio;
    }
    novoGestor->codigo = codigo;
    strcpy(novoGestor->nome, nome);
    strcpy(novoGestor->email, email);
    novoGestor->seguinte = NULL;

    Gestores* gestorAtual = NULL;
    if (inicio == NULL) { // Se a lista estiver vazia, o novo gestor � o primeiro
        return novoGestor;
    }
    else {
        gestorAtual = inicio;
        while (gestorAtual->seguinte != NULL) { // Percorrer a lista at� chegar ao �ltimo gestor
            gestorAtual = gestorAtual->seguinte;
        }
        gestorAtual->seguinte = novoGestor; // O �ltimo gestor passa a apontar para o novo gestor
        return inicio;
    }
}

void listarGestores(Gestores* inicio) {
    // Inicializa um ponteiro para percorrer a lista de gestores a partir do in�cio
    Gestores* gestorAtual = inicio;

    // Enquanto o gestorAtual n�o for NULL, ou seja, ainda h� gestores a serem percorridos
    while (gestorAtual != NULL) {
        // Imprime o c�digo do gestor
        printf("C�digo: %d\n", gestorAtual->codigo);

        // Imprime o nome do gestor
        printf("Nome: %s\n", gestorAtual->nome);

        // Imprime o email do gestor
        printf("Email: %s\n", gestorAtual->email);

        // Imprime uma quebra de linha para separar os gestores
        printf("\n");

        // Atualiza o ponteiro para o pr�ximo gestor na lista
        gestorAtual = gestorAtual->seguinte;
    }
}

int existeGestores(Gestores* inicio, int codigo) {
    // Inicializa um ponteiro para percorrer a lista de gestores a partir do in�cio
    Gestores* gestorAtual = inicio;

    // Enquanto o gestorAtual n�o for NULL, ou seja, ainda h� gestores a serem percorridos
    while (gestorAtual != NULL) {
        // Verifica se o c�digo do gestor atual � igual ao c�digo fornecido
        if (gestorAtual->codigo == codigo) {
            // Se for igual, retorna 1 para indicar que o gestor existe
            return 1;
        }

        // Atualiza o ponteiro para o pr�ximo gestor na lista
        gestorAtual = gestorAtual->seguinte;
    }

    // Se o gestor n�o foi encontrado, retorna 0 para indicar que n�o existe
    return 0;
}

int guardarGestores(Gestores* inicio) {
    // Declara��o de vari�veis locais
    FILE* arquivo; // Ponteiro para o arquivo
    Gestores* gestorAtual; // Ponteiro para percorrer a lista de gestores

    // Abrir o arquivo "gestores.txt" para escrita
    arquivo = fopen("gestores.txt", "w");

    // Verifica se houve erro ao abrir o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo para escrita.\n");
        return 0; // Retorna 0 para indicar falha na opera��o
    }

    // Inicializa o ponteiro para percorrer a lista de gestores a partir do in�cio
    gestorAtual = inicio;

    // TODO: Implementar a escrita dos gestores no arquivo

    // Fecha o arquivo
    fclose(arquivo);

    return 1; // Retorna 1 para indicar sucesso na opera��o
}


Gestores* lerGestores() {
    FILE* arquivo;
    Gestores* inicio = NULL;
    Gestores* gestorAtual = NULL; // Inicializa a vari�vel gestorAtual com NULL

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
            break; // Se a leitura n�o for bem sucedida, sair do loop
        }

        Gestores* novoGestor = (Gestores*)malloc(sizeof(Gestores));
        if (novoGestor == NULL) { // Verificar se foi poss�vel alocar mem�ria
            printf("Erro: nao foi possivel alocar memoria para um novo gestor.\n");
            break; // Se n�o foi poss�vel alocar mem�ria, sair do loop
        }
        novoGestor->codigo = codigo;
        strcpy(novoGestor->nome, nome);
        strcpy(novoGestor->email, email);
        novoGestor->seguinte = NULL;

        if (inicio == NULL) { // Se a lista estiver vazia, o novo gestor � o primeiro
            inicio = novoGestor;
            gestorAtual = novoGestor;
        }
        else {
            gestorAtual->seguinte = novoGestor; // O �ltimo gestor passa a apontar para o novo gestor
            gestorAtual = gestorAtual->seguinte; // Atualizar o ponteiro para o �ltimo gestor
        }
    }

    // Fechar o arquivo
    fclose(arquivo);
    
    return inicio;
}

Gestores* removerGestores(Gestores* inicio, int codigo) {
    Gestores* gestorAnterior = NULL;
    Gestores* gestorAtual = inicio;

    // Percorrer a lista at� encontrar o gestor com o c�digo especificado
    while (gestorAtual != NULL && gestorAtual->codigo != codigo) {
        gestorAnterior = gestorAtual;
        gestorAtual = gestorAtual->seguinte;
    }

    // Se n�o encontrou o gestor com o c�digo especificado, retornar a lista original
    if (gestorAtual == NULL) {
        return inicio;
    }

    // Se o gestor a ser removido � o primeiro da lista
    if (gestorAnterior == NULL) {
        inicio = gestorAtual->seguinte;
    }
    // Se o gestor a ser removido n�o � o primeiro da lista
    else {
        gestorAnterior->seguinte = gestorAtual->seguinte;
    }

    // Libertar a mem�ria alocada pelo gestor removido
    free(gestorAtual);

    return inicio;
}

// Fun��o que insere um novo utilizador em uma lista ligada de utilizador
Utilizadores* inserirUtilizadores(Utilizadores* inicio, char* email, char* password, char tipo_utilizador) {
    // Aloca mem�ria para o novo usu�rio
    Utilizadores* novo_utilizador = (Utilizadores*)malloc(sizeof(Utilizadores));
    // Copia o email e a senha do novo utilizador para a estrutura
    strcpy(novo_utilizador->email, email);
    strcpy(novo_utilizador->password, password);
    // Define o tipo de utilizador
    novo_utilizador->tipo_utilizador = tipo_utilizador;
    // Define o pr�ximo n� da lista ligada como NULL
    novo_utilizador->seguinte = NULL;
    // Se a lista est� vazia, o novo utilizador � o in�cio da lista
    if (inicio == NULL) {
        inicio = novo_utilizador;
    }
    // Se a lista j� tem elementos, encontra o �ltimo n� e adiciona o novo utilizador
    else {
        Utilizadores* ultimo = inicio;
        while (ultimo->seguinte != NULL) {
            ultimo = ultimo->seguinte;
        }
        ultimo->seguinte = novo_utilizador;
    }

    // Retorna o in�cio da lista ligada de utilizadores
    return inicio;

}
// Fun��o que lista todos os utilizadores da lista ligada
void listarUtilizadores(Utilizadores* inicio) {
    Utilizadores* atual = inicio;

    while (atual != NULL) {
        printf("Email: %s\n", atual->email);
        printf("Tipo de utilizador: %s\n", atual->tipo_utilizador == '1' ? "cliente" : "gestor");
        printf("----------------------\n");
        atual = atual->seguinte;
    }
}

// Fun��o que verifica se um utilizador com um determinado email existe na lista ligada
int existeUtilizadores(Utilizadores* inicio, char* email) {
    Utilizadores* atual = inicio;

    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            return 1; // encontrado
        }
        atual = atual->seguinte;
    }

    return 0; // n�o encontrado
}

// Fun��o que remove um utilizador da lista ligada com base no email
Utilizadores* removerUtilizadores(Utilizadores* inicio, char* email) {
    Utilizadores* atual = inicio;
    Utilizadores* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0) {
            if (anterior == NULL) {
                inicio = atual->seguinte; // primeiro n�
            }
            else {
                anterior->seguinte = atual->seguinte;
            }
            free(atual);
            return inicio;
        }
        anterior = atual;
        atual = atual->seguinte;
    }

    return inicio;
}

// Fun��o que verifica se um utilizador com um determinado email e senha existe na lista ligada
int loginUtilizador(Utilizadores* inicio, char* email, char* password) {
    Utilizadores* atual = inicio;

    while (atual != NULL) {
        if (strcmp(atual->email, email) == 0 && strcmp(atual->password, password) == 0) {
            return atual->tipo_utilizador; // encontrado
        }
        atual = atual->seguinte;
    }

    return 0; // n�o encontrado
}

// Fun��o que grava os dados dos utilizadores em um arquivo de texto
int guardarUtilizadores(Utilizadores* inicio) {
    FILE* arquivo;
    arquivo = fopen("utilizadores.txt", "w");
    if (arquivo == NULL) {
        return 0; // erro ao abrir arquivo
    }

    Utilizadores* atual = inicio;
    while (atual != NULL) {
        fprintf(arquivo, "%s;%s;%c\n", atual->email, atual->password, atual->tipo_utilizador);
        atual = atual->seguinte;
    }

    fclose(arquivo);
    return 1; // sucesso
}



// Esta fun��o l� os utilizadores a partir do arquivo "utilizadores.txt"
Utilizadores* lerUtilizadores() {
    Utilizadores* inicio = NULL;
    Utilizadores* atual = NULL;
    Utilizadores* novo = NULL;
    char linha[150];
    char* token;
    // Abrir o arquivo em modo leitura
    FILE* arquivo;
    arquivo = fopen("utilizadores.txt", "r");
    if (arquivo == NULL) {
        return NULL; // retorna NULL se houver um erro ao abrir o arquivo
    }
    // Ler as linhas do arquivo, separar as informa��es usando o delimitador ';' e criar um novo n� para cada utilizador
    while (fgets(linha, 150, arquivo)) {
        // Alocar mem�ria para o novo n� da lista
        novo = (Utilizadores*)malloc(sizeof(Utilizadores));
        novo->seguinte = NULL;

        // Separar as informa��es da linha usando strtok e copi�-las para o n�
        token = strtok(linha, ";");
        strcpy(novo->email, token);

        token = strtok(NULL, ";");
        strcpy(novo->password, token);

        token = strtok(NULL, ";");
        novo->tipo_utilizador = token[0];

        // Adicionar o novo n� � lista de utilizadores
        if (inicio == NULL) {
            inicio = novo;
            atual = novo;
        }
        else {
            atual->seguinte = novo;
            atual = novo;
        }
    }

    /// Fechar o arquivo e retornar o ponteiro para o in�cio da lista de utilizadores
    fclose(arquivo);
    return inicio;
}

Vertice* criarVertice(float vertice_inicial, float vertice_final) {
    // Aloca mem�ria para um novo v�rtice
    Vertice* vertice = (Vertice*)malloc(sizeof(Vertice));

    // Define as coordenadas do v�rtice
    vertice->vertice_inicial = vertice_inicial;
    vertice->vertice_final = vertice_final;

    return vertice;
}

Aresta* criarAresta(float distancia) {
    // Aloca mem�ria para uma nova aresta
    Aresta* aresta = (Aresta*)malloc(sizeof(Aresta));

    // Inicializa os ponteiros de origem e destino como nulos
    aresta->origem = NULL;
    aresta->destino = NULL;

    // Define a dist�ncia da aresta
    aresta->distancia = distancia;

    return aresta;
}

Grafo* criarGrafo() {
    // Aloca mem�ria para um novo grafo
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));

    // Inicializa a lista de v�rtices e o n�mero de v�rtices como vazios
    grafo->vertices = NULL;
    grafo->numVertices = 0;

    // Inicializa a lista de arestas e o n�mero de arestas como vazios
    grafo->arestas = NULL;
    grafo->numArestas = 0;

    return grafo;
}

void adicionarVertice(Grafo* grafo, Vertice* vertice) {
    // Verifica se o grafo � nulo
    if (grafo == NULL) {
        return;
    }

    // Incrementa o n�mero de v�rtices no grafo
    grafo->numVertices++;

    // Realoca a mem�ria para a lista de v�rtices com o tamanho atualizado
    grafo->vertices = (Vertice**)realloc(grafo->vertices, grafo->numVertices * sizeof(Vertice*));

    // Adiciona o v�rtice � lista de v�rtices no �ltimo �ndice
    grafo->vertices[grafo->numVertices - 1] = vertice;
}

void adicionarAresta(Grafo* grafo, Aresta* aresta) {
    // Verifica se o grafo � nulo
    if (grafo == NULL) {
        printf("Grafo n�o inicializado.\n");
        return;
    }

    // Incrementa o n�mero de arestas no grafo
    grafo->numArestas++;

    // Realoca a mem�ria para a lista de arestas com o tamanho atualizado
    grafo->arestas = (Aresta**)realloc(grafo->arestas, grafo->numArestas * sizeof(Aresta*));

    // Adiciona a aresta � lista de arestas no �ltimo �ndice
    grafo->arestas[grafo->numArestas - 1] = aresta;
}

void listarVertices(Grafo* grafo) {
    // Verifica se o grafo � nulo ou se a lista de v�rtices � nula
    if (grafo == NULL || grafo->vertices == NULL) {
        printf("Grafo vazio.\n");
        return;
    }

    printf("Lista de V�rtices:\n");
    // Percorre a lista de v�rtices e exibe suas informa��es
    for (int i = 0; i < grafo->numVertices; i++) {
        Vertice* vertice = grafo->vertices[i];
        printf("ID: %d, Latitude: %.2f, Longitude: %.2f\n", vertice->id, vertice->vertice_inicial, vertice->vertice_final);
    }
}

void listarArestas(Grafo* grafo) {
    // Verifica se o grafo � nulo ou se a lista de arestas � nula
    if (grafo == NULL || grafo->arestas == NULL) {
        printf("Grafo vazio.\n");
        return;
    }

    printf("Lista de Arestas:\n");
    // Percorre a lista de arestas e exibe suas informa��es
    for (int i = 0; i < grafo->numArestas; i++) {
        Aresta* aresta = grafo->arestas[i];
        printf("Dist�ncia: %.2f\n", aresta->distancia);
    }
}

void listarGrafoDeArquivo(const char* nomeArquivo) {
    // Abre o arquivo em modo de leitura
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int id;
    float origem, destino;

    // L� as informa��es do arquivo enquanto houver dados a serem lidos
    while (fscanf(arquivo, "%d %f %f", &id, &origem, &destino) == 3) {
        // Calcula a dist�ncia com base nas informa��es lidas
        float distancia = destino - origem;
        printf("ID: %d, Origem: %.2f, Destino: %.2f, Dist�ncia: %.2f\n", id, origem, destino, distancia);
    }

    // Fecha o arquivo
    fclose(arquivo);
}


void lerVerticesDeArquivo(Grafo* grafo, const char* nomeArquivo) {
    // Abre o arquivo em modo de leitura
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int id;
    float origem, destino;
    // L� as informa��es do arquivo enquanto houver dados a serem lidos
    while (fscanf(arquivo, "%d %f %f", &id, &origem, &destino) == 3) {
        // Cria um novo v�rtice com as informa��es lidas
        Vertice* vertice = criarVertice(id, origem, destino);
        // Adiciona o v�rtice ao grafo
        adicionarVertice(grafo, vertice);
    }

    // Fecha o arquivo
    fclose(arquivo);
}

void alterarVerticePorID(Grafo* grafo, int id) {
    // Verificar se o ponteiro grafo � nulo
    if (grafo == NULL) {
        printf("O grafo fornecido � inv�lido.\n");
        return;
    }

    // Percorrer a lista de v�rtices do grafo e encontrar o v�rtice com o ID fornecido
    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->vertices[i]->id == id) {
            float novaOrigem, novaDestino;
            printf("Novas coordenadas de origem e destino (separadas por espa�o): ");
            scanf("%f %f", &novaOrigem, &novaDestino);
            // Atualizar as coordenadas do v�rtice encontrado
            grafo->vertices[i]->vertice_inicial = novaOrigem;
            grafo->vertices[i]->vertice_final = novaDestino;
            printf("V�rtice com ID %d alterado com sucesso.\n", id);
            return;
        }
    }
    // Se nenhum v�rtice com o ID fornecido for encontrado
    printf("N�o foi encontrado um v�rtice com o ID %d.\n", id);
}

void alterarArestasPorID(Grafo* grafo, int id) {
    // Percorrer a lista de v�rtices do grafo e encontrar o v�rtice com o ID fornecido
    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->vertices[i]->id == id) {
            printf("N�o � poss�vel alterar as arestas do v�rtice com ID %d, pois a estrutura Vertice n�o possui informa��es de arestas.\n", id);
            return;
        }
    }
    // Se nenhum v�rtice com o ID fornecido for encontrado
    printf("N�o foi encontrado um v�rtice com o ID %d.\n", id);
}




