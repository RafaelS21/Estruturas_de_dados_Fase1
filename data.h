
#include <stdio.h>

typedef struct Veiculos
{
	int codigo; // código do veiculo de mobilidade elétrica
	char tipo[50];
	float bateria;
	float autonomia;
	int geo;
	int alugado; // flag que indica se o veículo está alugado ou não (0 = não alugado, 1 = alugado)
	int cliente; // código do cliente que alugou o veículo (apenas válido se o veículo estiver alugado)
	int tempo_aluguel; // tempo de aluguel em horas (apenas válido se o veículo estiver alugado)
	struct Veiculos* seguinte;
}Veiculos;


Veiculos* inserirVeiculos(Veiculos* inicio, int cod, char tipo[], float bateria, float autonomia); // Inserção de um novo registo
void listarVeiculos(Veiculos* inicio); // listar na consola o conteúdo da lista ligada
int existeVeiculos(Veiculos* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
Veiculos* removerVeiculos(Veiculos* inicio, int cod); // Remover um meio a partir do seu código

int guardarVeiculos(Veiculos* inicio);
Veiculos* lerVeiculos();

typedef struct Clientes {
	int codigo; // código do cliente
	char nome[50];
	char nif[10];
	char email[50];
	struct Aluguel* alugueis; // lista de alugueis realizados pelo cliente
	struct Clientes* seguinte;
	
} Clientes;

Clientes* inserirClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]); // Inserção de um novo registo
void listarClientes(Clientes* inicio); // listar na consola o conteúdo da lista ligada
int existeClientes(Clientes* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
Clientes* removerClientes(Clientes* inicio, int codigo); // Remover um cliente a partir do seu código
Clientes* alterarClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]);



int guardarClientes(Clientes* inicio);
Clientes* lerClientes();

typedef struct Gestores {
	int codigo; // código do gestor
	char nome[50];
	char email[50];
	struct Gestores* seguinte;
} Gestores;

Gestores* inserirGestores(Gestores* inicio, int codigo, char nome[], char email[]); // Inserção de um novo registo
void listarGestores(Gestores* inicio); // listar na consola o conteúdo da lista ligada
int existeGestores(Gestores* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
Gestores* removerGestores(Gestores* inicio, int codigo); // Remover um gestor a partir do seu código

int guardarGestores(Gestores* inicio);
Gestores* lerGestores();

typedef struct Utilizadores {
    char email[50];
    char password[50];
    char tipo_utilizador; // 1 = cliente, 2 = gestor
    struct Utilizadores* proximo;
} Utilizadores;

Utilizadores* inserirUtilizadores(Utilizadores* inicio, char* email, char* password, char tipo_utilizador);
void listarUtilizadores(Utilizadores* inicio);
int existeUtilizadores(Utilizadores* inicio, char* email);
Utilizadores* removerUtilizadores(Utilizadores* inicio, char* email);
int loginUtilizador(Utilizadores* inicio, char* email, char* password);

int guardarUtilizadores(Utilizadores* inicio);
Utilizadores* lerUtilizadores();

typedef struct Aluguel {
	int codigo_veiculo; // código do veículo alugado
	int tempo; // tempo de aluguel em horas
	float valor; // valor do aluguel
	struct Aluguel* seguinte;
} Aluguel;

