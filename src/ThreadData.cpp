#include "ThreadData.hpp"

    ThreadData::ThreadData(int sock, int threadNumber, bool activeThread = true):
        sock(sock), threadNumber(threadNumber), activeThread(activeThread){}

ThreadData::~ThreadData(){}

pthread_t* ThreadData::getThread(){
    return &this->thread;
}

bool ThreadData::setThread(pthread_t thread)
{

    this->thread = thread;
    if(this->thread != thread)
        return false;
    return true;
}

int ThreadData::getSock() const{
    return sock;
}

bool ThreadData::setSock(int sock){
    this->sock = sock;
    if(this->sock != sock)
        return false;
    return true;
}

const int ThreadData::getThreadNumber() const{
    return threadNumber;
}

bool ThreadData::setThreadNumber(int threadNumber){

    this->threadNumber = threadNumber;
    if(this->threadNumber != threadNumber)
        return false;
    return true;
}

const bool ThreadData::getActiveThread() const{
    return activeThread;
}

bool ThreadData::setActiveThread(bool activeThread){
    this->activeThread = activeThread;
    if(this->activeThread != activeThread)
        return false;
    return true;
}
