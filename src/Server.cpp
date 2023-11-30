#include "Server.hpp"

using namespace std;

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


//variável global para controlar acesso a região de memória
pthread_mutex_t mutex;

//wrapper para ponteiro de função
// ESSA LÓGICA TÁ ERRADA. TODA CONEXÃO EU TO CRIANDO UMA MESA E UM PLAYER NESSE THREAD.
//PRECISO ENTRAR NO THREAD E ADICIONAR O PLAYER QUE PRECISAR
// ESSA PARTE TÁ UM POUCO COMPLICADA
void *conexao(void *param){
    
    thdata *data = (thdata *) param; /* type cast to a pointer to thdata */
    
    Table* table = data->table;
    table->addPlayer();
    table->start();
}


Server::Server(int port, int portRange, int maxTablePlayers, int numThreads) :
    port(port), portRange(portRange), maxTablePlayers(maxTablePlayers), numThreads(numThreads){

    //inicializando o número de threads no meu server
    socketsThreadsIds = new int[numThreads];

}

Server::~Server(){
    delete socketsThreadsIds;
}



bool Server::start(){

    //socket para receber as comunicações iniciais
    int welcomeSocket;

    //novo socket para delegar a comunicação
    int newSocket;

    //Structure describing an Internet socket address
    struct sockaddr_in serverAddr;

    //tamanho do endereço armazenado pelo Socket
    socklen_t addr_size;

    //array de identificação dos threads
    pthread_t threads[this->numThreads];

    //atributos/caracteristicas do thread. Você pode definiar algumas scoisas como flags
    //tamanho do stack, endereço do stack, etc.
    pthread_attr_t attr;

    //inicia os atributods do phtread.
    pthread_attr_init(&attr);

    //The pthread_detach() function shall indicate to the implementation that storage
    //for the thread thread can be reclaimed when that thread terminates. 
    //If thread has not terminated, pthread_detach() shall not cause it to terminate. 
    //The effect of multiple pthread_detach() calls on the same target thread is unspecified.
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


    //struct para guardar o numero do thread e o socket.
    thdata data[this->numThreads];

    //inicializando o socket para receber as conexões
    welcomeSocket = socket(PF_INET, SOCK_STREAM, 0);

    //inicializando campos da struct endereço
    serverAddr.sin_family = AF_INET;

    //definindo a porta do meu endereço
    serverAddr.sin_port = htons(this->port);


    // lembrar de alterar se o servidor e cliente estiverem em máquinas diferentes. Nesse caso, colocar o IP da máquina que será servidora
    // o IP 127.0.0.1 só funciona se cliente e servidor estiverem na mesma máquina
    // porque é o localhost
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 

    //copiando o conteúdo de um endereço para o outro
    // ?????
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

    //adiciona o endereço local definido para utilizar no meu socket.
    bind(welcomeSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    //inicializando o mutex para controle de acesso em região crítica da memória
    pthread_mutex_init(&mutex, NULL);

    // informando que o socket irá ouvir até NUM_THREADS conexões
    if(listen(welcomeSocket,this->numThreads) == 0)
        printf("Listening\n");
    else
        printf("Error\n");



    // inicializando o vetor que conterá as referências para as threads. -1 indica que não existe thread associada.
    int i;
    for (i = 0; i < this->numThreads; i++){
        socketsThreadsIds[i] = -1;
    }


    i = 0;
    //loop para esperar as conexões. 
    //idealmente mudar para enquanto houver 1 cliente conectado seria interessante.
    while (i < this->numThreads){

        printf("esperando conexao do jogador.... \n");

        //caso haja uma conexão nova, definimos o newSocket como o socket
        //para essa nova conexão.
        newSocket = accept(welcomeSocket, (struct sockaddr *) NULL, NULL);

        //travando o semáforo por causa de acesso em região crítica
        pthread_mutex_lock(&mutex);

        //salvando o Id do newSocket, que é gerado pelo Sistema Operacional.
        socketsThreadsIds[i] = newSocket;

        //salvando os dados do thread e socket na minha estrutura de data para controle
        data[i].thread_no = i;
        data[i].sock = newSocket;




        /*
         Se o número total de jogadores for um múltiplo do número máximo de mesas
         siginifica que todas as minhas mesas estão cheias, e eu tenho que criar um thread com uma mesa nova.
        */
        if(this->totalPlayers() % this->maxTablePlayers == 0){
            createTable((void*) &data[i]);

        }

        pthread_create (&threads[i], &attr, conexao, (void *) &data[i]);

        printf ("Jogador conectou.\n");
        i++;
        pthread_mutex_unlock(&mutex);
    }


    printf("Abriu todas as threads. Esperando a thread terminar para fechar o servidor.\n");

    //Itera sobre as threads, e espera elas terminarem.
    for (i = 0; i < this->numThreads; i++){
        //Mecanismo para esperar a thread terminar.
        pthread_join(threads[i], NULL);
    }


  /* Clean up and exit */
   pthread_attr_destroy(&attr);
   pthread_mutex_destroy(&mutex);

}


const int Server::tablesSize() const{
    return tables.size();
}


Table* Server::tableBack(){
    return tables.back();
}

int Server::totalPlayers(){
    int totalPlayers = 0;
    for(TableIterator it = tablesBegin(); it < tablesEnd(); it++)
        totalPlayers += (*it)->playersSize();

    return totalPlayers;
}

    bool newPlayer();

Table* Server::createTable(void* param){

    thdata *data = (thdata *) param; /* type cast to a pointer to thdata */

    Table *table = new Table(data->thread_no, data->sock);
    data->table = table;
    tables.push_back(table);

    return table;

}