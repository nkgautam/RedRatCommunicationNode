#include "Chat.h"
#include <iostream>
#include <future>

using namespace std;

Chat::Chat()
{
    //
}

UDPSocket sock1(PORTCHAT);

int ReceiveMsg(string ip)
{
    char str1[256] ={0};
    unsigned short sport = PORTCHAT;

    int ret = sock1.RecvDataGram(str1,256 ,ip,sport);
    if(ret > 0)
    {
        //cout << "Ret : " << ret << endl;
        str1[ret] = '\0';
        cout << endl<<"Peer : " << str1 << endl;
    }

    return ret;
}

void SendMsg(string ip)
{
    string message;
    //cout << "Me : " ;
    std::getline (std::cin , message);
    sock1.SendDataGram(message.c_str(),message.length(),ip,PORTCHAT);
}

void Chat::Run()
{
    string peerIPAddress;
    cout << "Enter peer IP address:";
    cin>> peerIPAddress;

    int isChat;
    cout << "Enter 1 to start chat with the peer:";
    cin>> isChat;
    // comment
    if(isChat == 1)
    {
        while(true)
        {
            std::future<int> recvMsg = std::async (ReceiveMsg,peerIPAddress);
            std::future<void> sendMsg = std::async (SendMsg,peerIPAddress);
        }
        cout << "Chat session end... " ;
    }
}
