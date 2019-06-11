#ifndef CHAT_H
#define CHAT_H

#include "Socket.h"
#include <future>
#include <string>

#define PORTCHAT       9002

using namespace std;

class Chat
{
    public:
        Chat();
    void Run();
    protected:

    private:
    //int ReceiveMsg(string ip);
    //void SendMsg(string ip);
    //UDPSocket sock1;
};

#endif // CHAT_H
