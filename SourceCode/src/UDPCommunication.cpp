#include "UDPCommunication.h"

UDPCommunication::UDPCommunication()
{
    //ctor
    socket = new UdpSocket(this);
    socket->BindLocalAddressAndPort("localhost",8080);

}

UDPCommunication::Recv()
{

}

UDPCommunication::Send()
{

}
