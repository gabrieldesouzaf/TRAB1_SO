#include <iostream>
#include "bar.h"
#include "cliente.h"
#include "garcom.h"

using namespace std;

int main()
{
    int nClientes, nGarcom, cGarcom, maxRodadas;

    cout << "Digite o numero de clientes:" << endl;
    cin >> nClientes;
    // Para facilitar os testes se o usuário digitar -1 executa com entradas pré-estipuladas
    if (nClientes != -1)
    {
        cout << "Digite o numero de garçons:" << endl;
        cin >> nGarcom;
        cout << "Digite o numero capacidade dos garçons:" << endl;
        cin >> cGarcom;
        cout << "Digite o numero máximo de rodadas:" << endl;
        cin >> maxRodadas;

        Bar novoBar(nClientes, nGarcom, cGarcom, maxRodadas);
    }
    else
    {
        Bar novoBar(3, 3, 2, 3);
        // novoBar.imprimirBar();
        // novoBar.imprimirPedidos();
    }
    return 0;
}
