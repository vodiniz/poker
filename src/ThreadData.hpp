#ifndef THREADDATA_HPP_
#define THREADDATA_HPP_
#include <pthread.h>    /* POSIX Threads */ 
#include <bits/pthreadtypes.h>

using namespace std;

class ThreadData
{
private:
    pthread_t thread;
    int sock;
    int threadNumber;
    bool activeThread;
public:
    ThreadData(int sock, int threadNumber, bool activeThread = true); 
    ~ThreadData();

    pthread_t* getThread();
    bool setThread(pthread_t thread);

    int getSock() const;
    bool setSock(int sock);

    const int getThreadNumber() const;
    bool setThreadNumber(int threadNumber);

    const bool getActiveThread() const;
    bool setActiveThread(bool activeThread);

};



#endif