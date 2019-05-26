#ifndef UDPCOMMUNICATION_H
#define UDPCOMMUNICATION_H

#include "Socket.h"

class UDPCommunication
{
    public:
        UDPCommunication();
    void Send();
    void Recv();
    protected:
    private:
    UDPSocket *socket;
};

#endif // UDPCOMMUNICATION_H
