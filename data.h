#include <stdbool.h>
#include <stdio.h>

typedef struct Veiculos {
	int codigo;
	char tipo[20];
	float bateria;
	float autonomia;
	char localizacao[50];
	float valor_km;
	struct Veiculos* seguinte;
} Veiculos;


Veiculos* inserirVeiculos(Veiculos* inicio, int cod, char tipo[], float bateria, float autonomia, char localizacao[]); // Inserção de um novo registo
void listarVeiculos(Veiculos* inicio); // listar na consola o conteúdo da lista ligada
int existeVeiculos(Veiculos* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
Veiculos* removerVeiculos(Veiculos* inicio, int cod); // Remover um meio a partir do seu código

int guardarVeiculos(Veiculos* inicio);
Veiculos* lerVeiculos();



// CLIENTES


typedef struct Clientes {
	int codigo; // código do cliente
	char nome[50];
	char nif[10];
	char email[50];
	float saldo;
	struct Clientes* seguinte;
	
} Clientes;

Clientes* inserirClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]); // Inserção de um novo registo
void listarClientes(Clientes* inicio); // listar na consola o conteúdo da lista ligada
int existeClientes(Clientes* inicio, int codigo); // Determinar existência do 'codigo' na lista ligada 'inicio'
Clientes* removerClientes(Clientes* inicio, int codigo); // Remover um cliente a partir do seu código
Clientes* alterarClientes(Clientes* inicio, int codigo, char nome[], char nif[], char email[]);

int guardarClientes(Clientes* inicio);
Clientes* lerClientes();


typedef struct Aluguer {
	int codigo_veiculo; // código do veículo alugado
	float valor; // valor do aluguel
	int distancia_km;
	float valor_km;
	struct Aluguer* seguinte;
} Aluguer;

bool veiculoEstaAlugado(Aluguer* listaAlugueres, int codigo_veiculo);
void listarAluguer(Aluguer* inicio);
float obterValorKm(Veiculos * listaVeiculos, int codigo_veiculo);
Aluguer* lerAlugueres();
void guardarAlugueres(Aluguer* inicio);
Aluguer* alugarVeiculo(Aluguer* inicio, int codigo_veiculo, float valor, int distancia_km, float valor_km);





// GESTORES

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


// UTILIZADORES 

typedef struct Utilizadores {
    char email[50];
    char password[50];
    char tipo_utilizador; // 1 = cliente, 2 = gestor
    struct Utilizadores* seguinte;
} Utilizadores;

Utilizadores* inserirUtilizadores(Utilizadores* inicio, char* email, char* password, char tipo_utilizador);
void listarUtilizadores(Utilizadores* inicio);
int existeUtilizadores(Utilizadores* inicio, char* email);
Utilizadores* removerUtilizadores(Utilizadores* inicio, char* email);
int loginUtilizador(Utilizadores* inicio, char* email, char* password);

int guardarUtilizadores(Utilizadores* inicio);
Utilizadores* lerUtilizadores();


// Definição da estrutura de um vértice do grafo
typedef struct {
	int id;
	float vertice_inicial;
	float vertice_final;	
} Vertice;

// Definição da estrutura de uma aresta do grafo
typedef struct {
	Vertice* origem;
	Vertice* destino;
	float distancia;
} Aresta;

// Definição da estrutura do grafo
typedef struct {
	int numVertices;
	int numArestas;
	Vertice** vertices;
	Aresta** arestas;
} Grafo;
