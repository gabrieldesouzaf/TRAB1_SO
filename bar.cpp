#include "bar.h"

semaforo Bar::mutex = 0;
int Bar::nClientes;
int Bar::cGarcom;
int Bar::nGarcom;
int Bar::rodadaAtual;
bool Bar::existemClientesNoBar;
bool Bar::fechouBar;
int Bar::maxRodadas;
queue<int> Bar::pedidoFeito;
int Bar::pedidoEntregue;
bool Garcom::atendeuMax;
bool Cliente::pedidoRealizado;
queue<int> Garcom::pedidosLocais;
vector<Cliente> Bar::todosCliente;
vector<Garcom> Bar::todosGarcom;

// Construtor padrão que inicializa os parâmetros
Bar::Bar(int nClientes, int nGarcom, int cGarcom, int maxRodadas)
{
    setNumeroMaxRodadas(maxRodadas);
    setNumeroClientes(nClientes);
    setNumeroGarcons(nGarcom);
    setNumeroLimitadoAtendimento(cGarcom);
    rodadaAtual = 1;
    pedidoEntregue = 0;
    if (nClientes > 0)
        setTemCliente(true);
    else
        setTemCliente(false);
    setFechouBar(false);
    preencheCliente(nClientes);
    preencheGarcom(nGarcom, cGarcom);
    cria_Thread();
}

// Destrutor padrão
Bar::~Bar() {}

// Métodos para alterar atributo dos objetos
void Bar::setNumeroMaxRodadas(int valor) { this->maxRodadas = valor; }
void Bar::setNumeroClientes(int valor) { this->nClientes = valor; }
void Bar::setNumeroGarcons(int valor) { this->nGarcom = valor; }
void Bar::setNumeroLimitadoAtendimento(int valor) { this->cGarcom = valor; }
void Bar::setTemCliente(bool status) { existemClientesNoBar = status; }
void Bar::setFechouBar(bool status) { fechouBar = status; }

// Métodos para mostrar atributo dos objetos
int Bar::getNumeroMaxRodadas() { return this->maxRodadas; }
int Bar::getNumeroClientes() { return this->nClientes; }
int Bar::getNumeroGarcons() { return this->nGarcom; }
int Bar::getNumeroLimitadoAtendimento() { return this->cGarcom; }
bool Bar::getTemCliente() { return this->existemClientesNoBar; }
bool Bar::getFechouBar() { return this->fechouBar; }

// Métodos para criar os Garçons e Clientes
void Bar::preencheCliente(int nClientes)
{
    for (int i = 0; i < nClientes; i++)
    {
        todosCliente.push_back(Cliente((i + 1001), (false)));
    }
}
void Bar::preencheGarcom(int nGarcom, int cGarcom)
{
    for (int i = 0; i < nGarcom; i++)
    {
        todosGarcom.push_back(Garcom((i + 101), (cGarcom), (false)));
    }
}

// Métodos para funcionamento do Bar
void Bar::incrementaRodada() { this->rodadaAtual++; }

// Imprimir os Dados dos clientes e Garçons
void Bar::imprimirBar()
{
    for (int i = 0; i < nClientes; i++)
    {
        todosCliente[i].imprimirCliente();
    }
    for (int i = 0; i < nGarcom; i++)
    {
        todosGarcom[i].imprimirGarcom();
    }
}

// Imprimir lista de pedidos
void Bar::imprimirPedidos()
{
    queue<int> listaTemporaria1(pedidoFeito);
    cout << "Lista de pedidos feitos ( ";
    while (!listaTemporaria1.empty())
    {
        //cout << pedidoFeito.size() << endl;
        if (pedidoFeito.size() > 1)
        {
            cout << listaTemporaria1.front() << "/";
        }
        else
        {
            cout << listaTemporaria1.front() << " )" << endl;
        }
        listaTemporaria1.pop();
    }
}

// Altera individualmente o status de atendimento
void Bar::alteraAtendimento(int idCliente)
{
    for (int i = 0; i < todosCliente.size(); i++)
    {
        if (todosCliente[i].getCodigoCliente() == idCliente)
        {
            if (todosCliente[i].getPedidoRealizado() == false)
            {
                todosCliente[i].setPedidoRealizado(true);
            }
            else
            {
                todosCliente[i].setPedidoRealizado(false);
            }
        }
    }
}

// Vê a variável de atendimento
int Bar::verificaAtendimento(int idCliente)
{
    for (int i = 0; i < todosCliente.size(); i++)
    {
        if (todosCliente[i].getCodigoCliente() == idCliente)
        {
            return (todosCliente[i].getPedidoRealizado());
        }
    }
    return 0;
}

// Threads
void *Bar::rotinaGarcom(void *arg)
{
    Garcom *idGarcom = (Garcom *)arg;

    while (existemClientesNoBar)
    {
        
        //imprimirPedidos();
        if (pedidoFeito.size() > 0 && !mutex)
        {
            usleep(2000);
            mutex = 1;
            cout << "(" << idGarcom->getCodigoGarcons() << ") - entregou o pedido de (" << pedidoFeito.front() << ")" << endl;
            idGarcom->adicionaPedido(pedidoFeito.front());
            pedidoFeito.pop();
            pedidoEntregue++;
            if(pedidoEntregue > nClientes){
                rodadaAtual++;
                pedidoEntregue = 0;
                for(int i=0; i<nClientes; i++){
                    todosCliente[i].setPedidoRealizado(false);
                }
            }    
            mutex = 0;
                
        }

        if (rodadaAtual >= maxRodadas && !mutex)
        {
            mutex = 1;
            existemClientesNoBar = false;
            fechouBar = true;
            mutex = 0;
        }
    }
    pthread_exit(NULL);
}
void *Bar::rotinaCliente(void *arg)
{
    Cliente *idCliente = (Cliente *)arg;

    while (!fechouBar)
    {
        
        if (!idCliente->getPedidoRealizado() && !mutex)
        {   
            mutex = 1;
            usleep(2000);
            pedidoFeito.push(idCliente->getCodigoCliente());
            cout << "(" << idCliente->getCodigoCliente() << ") - fez o pedido" << endl;
            idCliente->setPedidoRealizado(true);
            mutex = 0;
        }
    }
    pthread_exit(NULL);
}

// Criando Threads
void Bar::cria_Thread()
{
    int garcom[nGarcom];
    int cliente[nClientes];
    vector<pthread_t> idGarcom(nGarcom);
    vector<pthread_t> idCliente(nClientes);

    for (int i = 0; i < nGarcom; i++)
    {
        garcom[i] = pthread_create(&idGarcom[i], NULL, rotinaGarcom, &todosGarcom[i]);
        //usleep(1000);
    }
    for (int i = 0; i < nClientes; i++)
    {
        cliente[i] = pthread_create(&idCliente[i], NULL, rotinaCliente, &todosCliente[i]);
        //usleep(1000);
    }
    for (int i = 0; i < nGarcom; i++)
    {
        pthread_join(idGarcom[i], NULL);
        //usleep(1000);
    }
    for (int i = 0; i < nClientes; i++)
    {
        pthread_join(idCliente[i], NULL);
        //usleep(1000);
    }
}

void Bar::cria_Thread_Garcom()
{
    int garcom[nGarcom];
    vector<pthread_t> idGarcom(nGarcom);

    for (int i = 0; i < nGarcom; i++)
    {
        garcom[i] = pthread_create(&idGarcom[i], NULL, rotinaGarcom, &todosGarcom[i]);
        //usleep(1000);
    }
    for (int i = 0; i < nGarcom; i++)
    {
        pthread_join(idGarcom[i], NULL);
        //usleep(1000);
    }
}

void Bar::cria_Thread_Cliente()
{
    int cliente[nClientes];
    vector<pthread_t> idCliente(nClientes);

    for (int i = 0; i < nClientes; i++)
    {
        cliente[i] = pthread_create(&idCliente[i], NULL, rotinaCliente, &todosCliente[i]);
        //usleep(1000);
    }
    for (int i = 0; i < nClientes; i++)
    {
        pthread_join(idCliente[i], NULL);
        //usleep(1000);
    }
}

// Verifica se todos os clientes foram atendidos
bool Bar::verificaAtendimento()
{
    int contador = 0;
    for (int i = 0; i < nClientes; i++)
    {
        if (todosCliente[i].getPedidoRealizado() == true)
        {
            contador++;
        }
    }
    if (contador == nClientes && pedidoEntregue == nClientes)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Assim que todos os clientes forem atendidos podem pedir novamente
void Bar::zeraStatusPedido()
{
    for (int i = 0; i < nClientes; i++)
    {
        todosCliente[i].setPedidoRealizado(false);
    }
}
