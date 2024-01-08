#include "Server.hpp"


#include <vector>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h> // memset()
#include <time.h>
#include <pthread.h>    /* POSIX Threads */ 
#include <stdlib.h>

#include <fcntl.h> // for open
#include <unistd.h> // for close
#include <arpa/inet.h>    // htons(), inet_addr()
#include <sys/types.h>    // AF_INET, SOCK_STREAM


vector<Table*> Server::tables;
vector<Player*> Server::players;
bool Server::firstConnection;
int Server::totalConnections;

using namespace std;


//variável global para controlar acesso a região de memória
pthread_mutex_t mutex;

//variável global para o ID dos threads
#define NUM_THREADS 30

//wrapper para ponteiro de função
void *tableStart(void* param){
    cout << "Criando uma mesa nova." << endl;
    Table* table = (Table*) param;
    table->start(&mutex);
    return NULL;
}

void *newPlayerHandle(void* param){
    Server::firstConnection = true;
    tuple<int,Table*>* tupleSocketTable = (tuple<int,Table*>*) param;

    //extraindo os valores da tupla para usar posteriormente.
    int sock = get<0>(*tupleSocketTable);
    Table *table = get<1>(*tupleSocketTable);
3
    char buffer[1024];
    recv(sock, buffer, sizeof(buffer), 0);
    
    Player player(buffer, sock, Server::totalConnections);

    table->addPlayer(&player);
    Server::newPlayer(&player);

    cout << "O Player: " << player.getName() << "conectou" << endl;

    pthread_exit(NULL);
}

bool Server::newPlayer(Player *player){
    players.push_back(player);
    return true;
}

int Server::totalPlayers(){
    return players.size();
}

int Server::tablesSize(){
    return this->tables.size();
}


Table* Server::tableBack(){
    return tables.back();
}



Server::Server(int port, int portRange, int maxTablePlayers) :
    port(port), portRange(portRange), maxTablePlayers(maxTablePlayers){}

Server::~Server(){}

bool Server::checkAvailableTable(Table *table){
    for(TableIterator it = tablesBegin(); it < tablesEnd(); it++){
        if((*it)->playersSize() < this->maxTablePlayers){
            table = (*it);
            return true;
        }
    }
    return false;
}


bool Server::start(){

    //socket para receber as comunicações iniciais
    int welcomeSocket;

    //novo socket para delegar a comunicação
    int newSocket;

    //Structure describing an Internet socket address
    //necessária para passar como parâmetro no ponteiro de função do thread. 
    struct sockaddr_in serverAddr;

    //tamanho do endereço armazenado pelo Socket
    socklen_t addr_size;


    //atributos/caracteristicas do thread. Você pode definiar algumas scoisas como flags
    //tamanho do stack, endereço do stack, etc.
    pthread_attr_t attr;

    //inicia os atributos do phtread.
    pthread_attr_init(&attr);

    //The pthread_detach() function shall indicate to the implementation that storage
    //for the thread thread can be reclaimed when that thread terminates. 
    //If thread has not terminated, pthread_detach() shall not cause it to terminate. 
    //The effect of multiple pthread_detach() calls on the same target thread is unspecified.
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    //inicializando o socket para receber as conexões
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    //inicializando campos da struct endereço
    serverAddr.sin_family = AF_INET;

    //definindo a porta do meu endereço
    serverAddr.sin_port = htons(this->port);


    // lembrar de alterar se o servidor e cliente estiverem em máquinas diferentes. Nesse caso, colocar o IP da máquina que será servidora
    // o IP 127.0.0.1 só funciona se cliente e servidor estiverem na mesma máquina
    // porque é o localhost
    serverAddr.sin_addr.s_addr = inet_addr(this->ip); 

    //copiando o conteúdo de um endereço para o outro
    // ?????
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    //adiciona o endereço local definido para utilizar no meu socket.
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    //inicializando o mutex para controle de acesso em região crítica da memória
    pthread_mutex_init(&mutex, NULL);

    // informando que o socket irá ouvir até NUM_THREADS conexões
    if(listen(welcomeSocket,NUM_THREADS) == 0)
        printf("Listening\n");
    else
        printf("Error\n");



    // inicializando o vetor que conterá as referências para as threads. -1 indica que não existe thread associada.

    //loop para esperar as conexões. 
    // caso eu já tenha 30 threads, ou 

    while (tablesSize() > 0 || !firstConnection || totalPlayers() > 0){

        printf("esperando conexao do jogador.... \n");


        //caso haja uma conexão nova, definimos o newSocket como o socket
        //para essa nova conexão.
        newSocket = accept(welcomeSocket, (struct sockaddr *) NULL, NULL);

        //travando o semáforo por causa de acesso em região crítica
        pthread_mutex_lock(&mutex);

        // //salvando os dados do thread e socket na minha estrutura de data para controle;
        // Não faz sentido salvar isso.
        // this->threadData.push_back(new ThreadData(newSocket, i));

        Table *possibleTable;
        

        if(!checkAvailableTable(possibleTable)){
            possibleTable = Server::createTable();
            pthread_create (possibleTable->getThread(), &attr, tableStart, (void *) possibleTable);
        }

        tuple<int,Table*> tupleSocketTable(welcomeSocket, possibleTable);

        //criando thread para adicionar um player novo.
        pthread_t newPlayerThread;
        pthread_create (&newPlayerThread, &attr, newPlayerHandle, (void *) &tupleSocketTable);


    }


  /* Clean up and exit */
   pthread_attr_destroy(&attr);
   pthread_mutex_destroy(&mutex);

    return true;

}

Table* Server::createTable(){
    Table *table = new Table(&mutex); 
    tables.push_back(table);
    return table;
}


Server::TableIterator Server::tablesBegin(){
    return tables.begin();
}
Server::TableIterator Server::tablesEnd(){
    return tables.end();
}

int main(void){

    Server *server = new Server(25555, 10, 30);
    server->start();


    return 0;
}

