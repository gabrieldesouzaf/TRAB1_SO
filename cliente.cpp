#include "cliente.h"

// Construtor padrão que inicializa os parâmetros
Cliente::Cliente(int codigoCliente, bool pedidoRealizado)
{
    setCodigoCliente(codigoCliente);
    setPedidoRealizado(pedidoRealizado);
    //cout << getPedidoRealizado() << endl;
}

// Destrutor padrão
Cliente::~Cliente() {}

// Métodos para mudar as variáveis
void Cliente::setCodigoCliente(int cod) { this->codigoCliente = cod; }
void Cliente::setPedidoRealizado(bool status) { this->pedidoRealizado = status; }

// Métodos para saber os valores das variáveis
int Cliente::getCodigoCliente() { return this->codigoCliente; }
bool Cliente::getPedidoRealizado() { return this->pedidoRealizado; }

// Imprimir os Dados do Garçom
void Cliente::imprimirCliente()
{
    cout << "Cliente (" << this->codigoCliente << ") - fez pedido (";
    if (pedidoRealizado == true)
    {
        cout << "sim)" << endl;
    }
    else
    {
        cout << "nao)" << endl;
    }
}
