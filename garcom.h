#ifndef GARCOM_H
#define GARCOM_H

#include <iostream>
#include <queue>
#include <pthread.h>

using namespace std;

class Garcom
{
private:
    int codigoGarcom;                // Código do garçom
    int cGarcom;                     // Número máximo de Atendimentos por Garçom
    static bool atendeuMax;          // Se atendeu o máximo de clientes (true) else (false)
    static queue<int> pedidosLocais; // Lista de pedido local de cada garçom

public:
    // Construtor padrão que inicializa os parâmetros
    Garcom(int codigoGarcom, int cGarcom, bool atendeuMax);

    // Destrutor padrão
    ~Garcom();

    // Métodos para alterar atributo dos objetos
    void setCodigoGarcons(int);
    void setNumeroLimitadoAtendimento(int);
    void setAtendeuTodosClientes(bool);

    // Métodos para mostrar atributo dos objetos
    int getCodigoGarcons();
    int getNumeroLimitadoAtendimento();
    bool getAtendeuTodosClientes();

    // Método adiciona ou retira pedido
    void adicionaPedido(int);
    int getPedidoLocal();
    void retiraPedido();
    int retornaTamanho();

    // Imprimir os Dados do Garçom
    void imprimirGarcom();
};

#endif
