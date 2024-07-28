#ifndef CLIENTE_H
#define CLIENTE_H

#include <iostream>

using namespace std;

class Cliente
{

private:
    int codigoCliente;           // Código dos clientes
    static bool pedidoRealizado; // Variável para controle de consumo

public:
    // Construtor padrão que inicializa os parâmetros
    Cliente(int codigoCliente, bool pedidoRealizado);

    // Destrutor padrão
    ~Cliente();

    // Métodos para mudar as variáveis
    void setCodigoCliente(int);
    void setPedidoRealizado(bool);

    // Métodos para saber os valores das variáveis
    int getCodigoCliente();
    bool getPedidoRealizado();

    // Imprimir os Dados do Cliente
    void imprimirCliente();
};

#endif
