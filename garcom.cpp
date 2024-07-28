#include "garcom.h"

// Construtor padrão que inicializa os parâmetros
Garcom::Garcom(int nGarcom, int cGarcom, bool atendeuMax)
{
    setCodigoGarcons(nGarcom);
    setNumeroLimitadoAtendimento(cGarcom);
    setAtendeuTodosClientes(atendeuMax);
}

// Destrutor padrão
Garcom::~Garcom() {}

// Métodos para alterar atributo dos objetos
void Garcom::setCodigoGarcons(int valor) { this->codigoGarcom = valor; }
void Garcom::setNumeroLimitadoAtendimento(int valor) { this->cGarcom = valor; }
void Garcom::setAtendeuTodosClientes(bool valor) { this->atendeuMax = valor; }

// Métodos para mostrar atributo dos objetos
int Garcom::getCodigoGarcons() { return this->codigoGarcom; }
int Garcom::getNumeroLimitadoAtendimento() { return this->cGarcom; }
bool Garcom::getAtendeuTodosClientes() { return this->atendeuMax; }

// Método adiciona ou retira pedido
void Garcom::adicionaPedido(int idCliente)
{
    pedidosLocais.push(idCliente);
}
int Garcom::getPedidoLocal()
{
    return pedidosLocais.front();
}
void Garcom::retiraPedido()
{
    pedidosLocais.pop();
}
int Garcom::retornaTamanho()
{
    return pedidosLocais.size();
}

// Imprimir os Dados dos clientes e Garçons
void Garcom::imprimirGarcom()
{
    cout << "Garcom (" << this->codigoGarcom << ") - esta cheio (";
    if (atendeuMax == true)
    {
        cout << "sim)" << endl;
    }
    else
    {
        cout << "nao)" << endl;
    }
}
