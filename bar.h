#ifndef BAR_H
#define BAR_H

#include <unistd.h>
#include <vector>
#include <queue>
#include <iostream>
#include "garcom.h"
#include "cliente.h"
#include <semaphore.h>

typedef int semaforo;

using namespace std;

class Bar
{
private:
    static semaforo mutex;
    static int nClientes;                // Número de Clientes no Bar
    static int nGarcom;                  // Número de Garçons no Bar
    static int cGarcom;                  // Número máximo de Atendimentos por Garcom
    static int maxRodadas;               // Número máximo de Rodadas
    static int rodadaAtual;              // Número da rodada atual
    static vector<Cliente> todosCliente; // Código do cliente (Lista dos Clientes)
    static vector<Garcom> todosGarcom;   // Código do Garçom (Lista dos Garçons)
    static bool existemClientesNoBar;    // Indica se há clientes no bar
    static bool fechouBar;               // Informa se o bar está aberto ou fechado
    static queue<int> pedidoFeito;       // Todos os pedidos feitos
    static int pedidoEntregue;           // Todos os pedidos entregues

public:
    // Construtor padrão que inicializa os parâmetros
    Bar(int nClientes, int nGarcom, int cGarcom, int maxRodadas);

    // Destrutor padrão
    ~Bar();

    // Métodos para alterar atributo dos objetos
    void setNumeroMaxRodadas(int);
    void setNumeroClientes(int);
    void setNumeroGarcons(int);
    void setNumeroLimitadoAtendimento(int);
    static void setTemCliente(bool);
    static void setFechouBar(bool);

    // Métodos para mostrar atributo dos objetos
    int getNumeroMaxRodadas();
    int getNumeroClientes();
    int getNumeroGarcons();
    int getNumeroLimitadoAtendimento();
    bool getTemCliente();
    bool getFechouBar();

    // Métodos para criar os Garçons e Clientes
    void preencheCliente(int);
    void preencheGarcom(int, int);

    // Métodos para funcionamento do Bar
    void incrementaRodada(); // Incrementa Rodadas

    // Imprimir os Dados dos clientes e Garçons
    static void imprimirBar();

    // Imprimi lista de pedidos
    static void imprimirPedidos();

    // Altera individualmente o status de atendimento
    static void alteraAtendimento(int);

    // Vê a variável de atendimento
    static int verificaAtendimento(int);

    // Threads
    static void *rotinaGarcom(void *arg);
    static void *rotinaCliente(void *arg);

    // Criando Threads
    void cria_Thread();
    void cria_Thread_Garcom();
    void cria_Thread_Cliente();

    // Verifica se todos os clientes foram atendidos e retorna true ou false
    static bool verificaAtendimento();

    // Assim que todos os clientes forem atendidos podem pedir novamente
    static void zeraStatusPedido();
};

#endif
