#include "Client.hpp"
#include <pthread.h>    
#include <sys/socket.h>
#include <arpa/inet.h>    // htons(), inet_addr()
#include <sys/types.h>    // AF_INET, SOCK_STREAM
#include <netinet/in.h>

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 

#include "../poker/Player.hpp"
#include "../messages/ServerClientJson.hpp"
#include "../messages/ClientServerJson.hpp"

#include "../jsonMapping/json_struct.h"


using namespace std;

Player player;
ServerClientJson serverJson;


//variável global para controlar acesso a região de memória
pthread_mutex_t mutex;



typedef struct str_thdata{
    int sock;
    pthread_t thread;
} thdata;


void *threadRecv(void *param){

    thdata *data;
    data = (thdata *) param;
    
    char buffer[1024];

    int s = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    if (s != 0) {
        printf("Erro.");
        exit(0);
    }

    while (1){
        //cout << "Recebendo o json do servidor (sock " << data->sock << " )" << endl;
        recv(data->sock, buffer, sizeof(buffer), 0);
        //cout << "Recebeu o json do servidor" << endl;
        
        //usando parser para preencher a struct
        JS::ParseContext context(buffer);
        JS::Error erro = context.parseTo(serverJson);
    
        //travando o semáforo por causa de acesso em região crítica
        pthread_mutex_lock(&mutex);

        
        player.setState(static_cast<PlayerState>(serverJson.playerState));
        player.setMoney(serverJson.newMoneyValue);
        player.setMoneyOnTable(serverJson.playerMoneyOnTable);
        //
        pthread_mutex_unlock(&mutex);

        printf("%s\n",buffer); 
    }

}


void *threadSend(void *param){

    thdata *data;
    data = (thdata *)param;

    char buffer[1024];
    string nome;
    printf("Digite seu nome: \n");
    cin >> nome;

    cout << "Lembrando que você pode digitar quit a qualquer momento para encerrar o jogo" << endl;
    pthread_mutex_lock(&mutex);
    player.setName(nome);
    player.setState(PlayerState::Fold);
    pthread_mutex_unlock(&mutex);

    send(data->sock, nome.c_str(), sizeof(nome.c_str()),0);  
    

    do {

        if(player.getState() == PlayerState::WaitingPlayers || player.getState() == PlayerState::Fold || player.getState() == PlayerState::In){
            continue;
        }
        else if (player.getState() == PlayerState::WaitingBet){
            cout << "A mesa tem uma nova aposta de " << 
                serverJson.currentTableBet - player.getMoneyOnTable() << endl; 

            cout << "Digite 1 para apostar, 2 para aumentar o valor e 3 para correr." << endl;

            string input;
            cin >> input;

            double playerCurrentMoney = player.getMoney();
            
            if (input == "1"){
                
                pthread_mutex_lock(&mutex);

                if((serverJson.currentTableBet - player.getMoneyOnTable() > playerCurrentMoney))
                    player.setMoney(0);

                else
                    player.setMoney(playerCurrentMoney - (serverJson.currentTableBet - player.getMoneyOnTable()));
                
                player.setState(PlayerState::In);
                pthread_mutex_unlock(&mutex);
            }

            else if(input == "2"){

                

                double bet; 
                cin >> bet;

                while(bet < playerCurrentMoney || bet != 0){
                    cout << "Dinheiro insuficiente para aposta. Tente novamente" << endl;
                    cin >> bet;

                }

                pthread_mutex_lock(&mutex);
                
                player.setMoney(playerCurrentMoney - bet);
                player.setMoneyOnTable(player.getMoneyOnTable() + bet);
                player.setState(PlayerState::In);
    
                pthread_mutex_unlock(&mutex); 
            }

            else if (input == "3"){
                pthread_mutex_lock(&mutex);
                player.setState(PlayerState::Fold);
                pthread_mutex_unlock(&mutex);
            }

            else if (input == "quit"){
                pthread_mutex_lock(&mutex);
                player.setState(PlayerState::Quit);
                pthread_mutex_unlock(&mutex);
            }



        }


        
        ClientServerJson clientJson;

        clientJson.playerState = static_cast<int>(player.getState());
        clientJson.newMoneyValue = player.getMoney();
        clientJson.playerMoneyOnTable = player.getMoneyOnTable();

        std::string pretty_json = JS::serializeStruct(clientJson);

        send(data->sock,pretty_json.c_str(), sizeof(pretty_json.c_str()),0);  


    } while (player.getState() != PlayerState::Quit);

    printf("Fechando Conexao e encerrando o programa...\n"); 
    pthread_cancel(data->thread);
    sleep(5);
    shutdown(data->sock, 2);
    pthread_exit(NULL);


}

int main(){

    


    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addr_size;
    pthread_t threadSendId, threadRecvId;
    thdata dataRecv, dataSend;
    pthread_attr_t attr;

    //inicializando o mutex para controle de acesso em região crítica da memória
    pthread_mutex_init(&mutex, NULL);


    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    clientSocket = socket(PF_INET, SOCK_STREAM, 0);
    
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(25557);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  


    addr_size = sizeof serverAddr;
    connect(clientSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

    player.setSock(clientSocket);

    printf("criando thread recv...\n");
    dataRecv.sock = clientSocket;
    pthread_create (&threadRecvId, &attr, threadRecv, (void *) &dataRecv);

    printf("criando thread send...\n");
    dataSend.sock = clientSocket;
    dataSend.thread = threadRecvId;
    pthread_create (&threadSendId, &attr, threadSend, (void *) &dataSend);

    
    pthread_join(threadSendId, NULL);
    pthread_join(threadRecvId, NULL);
    

    pthread_attr_destroy(&attr);

    printf("Todas as threads terminaram. Fechando cliente.\n");


    return 0;
}
