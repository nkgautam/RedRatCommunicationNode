#ifndef MUTEX_H
#define MUTEX_H


extern "C" {
#include <pthread.h>
}

class RMutex
{
public:

    RMutex();


    virtual ~RMutex();

    int Lock();

    int UnLock();

private:


    pthread_mutex_t m_plock;
};

#endif // MUTEX_H
