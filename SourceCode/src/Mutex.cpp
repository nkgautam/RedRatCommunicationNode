#include "Mutex.h"

RMutex::RMutex()
{
    m_plock = PTHREAD_MUTEX_INITIALIZER;
}

RMutex::~RMutex()
{
    pthread_mutex_unlock(&m_plock);
}

int RMutex::Lock()
{
    return pthread_mutex_lock(&m_plock);
}

int RMutex::UnLock()
{
    return pthread_mutex_unlock(&m_plock);
}
