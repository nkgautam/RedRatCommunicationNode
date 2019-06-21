#include "NodeList.h"
#include <future>
#include <iostream>

using namespace std;

NodeList::NodeList()
{

}

UDPSocket sock2(PORTMASTER);

int ReceiveMsg1(string sourceAddress)
{
    char str1[256] ={0};
    unsigned short sport = PORTMASTER;
    try{
        cout << "Recv Start\n " ;
        int ret = sock2.RecvDataGram(str1,256 ,sourceAddress,sport);
        if(ret > 0)
        {
            cout << "Recv end\n" ;
            str1[ret] = '\0';
            cout << endl<<"Peer : " << str1 << endl;
            cout << endl<<"Peer Address: " << sourceAddress << endl;

            //cout<<"response sent\n";
            if(str1 == "AddMe"){

            }
            if(str1 == "GetNodeList"){
                string message = "NodeList";
                sock2.SendDataGram(message.c_str(),message.length(),sourceAddress,sport);
            }
        }
        return ret;
    }
    catch(RSocketException e){
         cout<< "RSocketException \n";
        return 0;
    }
}

void SendMsg1(string ip)
{
    string message = "192.168.29.197";
    //cout << "Me : " ;
    //std::getline (std::cin , message);
    sock2.SendDataGram(message.c_str(),message.length(),ip,PORTMASTER);
}

void
NodeList::ListenRequest()
{

    while(true){
        cout<<"While() starts\n";
        string peerIPAddress = "0.0.0.0";
        std::future<int> recvMsg = std::async (ReceiveMsg1,peerIPAddress);
        //int ret = recvMsg.get();
        //cout<<"ret = "<<ret<<"\n";

    }
}
