#include "Socket.h"
#include <errno.h>
#include <cstring>
#include <fcntl.h>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<pthread.h>
#include <unistd.h>
#include "Mutex.h"
#define BUF_SIZE 1024

RSocketException::RSocketException( const string &sMessage, bool blSysMsg /*= false*/ ) throw() :m_sMsg(sMessage)
{
    if (blSysMsg) {
        m_sMsg.append(": ");
        m_sMsg.append(strerror(errno));
    }
}

RSocketException::~RSocketException() throw ()
{

}

RSocket::~RSocket()
{
    ::close(m_sockDesc);
    m_sockDesc = -1;
}

RSocket::RSocket( SocketType type, NetworkLayerProtocol protocol ) throw(RSocketException):m_sockDesc(-1)
{
    m_sockDesc = socket(protocol, type, 0);
    if (m_sockDesc < 0)
    {
        throw RSocketException("Socket creation failed (socket())", true);
    }
}

RSocket::RSocket( int sockDesc )
{
    m_sockDesc = sockDesc;
}

RSocket::RSocket( const RSocket &sock )
{

}

void RSocket::operator=( const RSocket &sock )
{

}

std::string RSocket::GetLocalAddress() throw(RSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getsockname(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
        throw RSocketException("Fetch of local address failed (getsockname())", true);
    }
    return inet_ntoa(addr.sin_addr);
}

unsigned short RSocket::GetLocalPort() throw(RSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getsockname(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
        throw RSocketException("Fetch of local port failed (getsockname())", true);
    }
    return ntohs(addr.sin_port);
}

void RSocket::BindLocalPort( unsigned short localPort ) throw(RSocketException)
{
    // Bind the socket to its port
    sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(localPort);

    if (bind(m_sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
        throw RSocketException("Set of local port failed (bind())", true);
    }
}

void RSocket::BindLocalAddressAndPort( const string &localAddress, unsigned short localPort /*= 0*/ )
    throw(RSocketException)
{
    // Get the address of the requested host
    sockaddr_in localAddr;
    FillAddr(localAddress, localPort, localAddr);

    if (bind(m_sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
        throw RSocketException("Set of local address and port failed (bind())", true);
    }
}

void RSocket::FillAddr( const string & localAddress, unsigned short localPort, sockaddr_in& localAddr )
{
    ////cout<<"\n Inside Fille addr:"<<localAddress <<" port:"<<localPort;
    memset(&localAddr, 0, sizeof(localAddr));  // Zero out address structure
    localAddr.sin_family = AF_INET;       // Internet address

    hostent *host;  // Resolve name
    if ((host = gethostbyname(localAddress.c_str())) == NULL) {
        // strerror() will not work for gethostbyname() and hstrerror()
        // is supposedly obsolete
        throw RSocketException("Failed to resolve name (gethostbyname())");
    }
    localAddr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);

    localAddr.sin_port = htons(localPort);
}

unsigned long int RSocket::GetReadBufferSize()
{
    unsigned long int nSize;
    socklen_t n = sizeof(nSize);
    getsockopt(m_sockDesc,SOL_SOCKET,SO_RCVBUF,(void *)&nSize, (&n));

    return nSize;
}

void RSocket::SetReadBufferSize( unsigned int nSize ) throw(RSocketException)
{
    if (setsockopt(m_sockDesc, SOL_SOCKET, SO_RCVBUF, &nSize, sizeof(nSize)) == -1)
    {
        throw RSocketException("Error in setting socket buffer size ", true);
    }
}

void RSocket::SetNonBlocking( bool bBlocking ) throw(RSocketException)
{
    int opts;

    opts = fcntl ( m_sockDesc, F_GETFL );

    if ( opts < 0 )
    {
        return;
    }

    if ( bBlocking )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );

    fcntl ( m_sockDesc, F_SETFL,opts );
}

void RSocket::ConnectToHost( const string &foreignAddress, unsigned short foreignPort ) throw(RSocketException)
{

    sockaddr_in destAddr;

    FillAddr(foreignAddress, foreignPort, destAddr);


    if (::connect(m_sockDesc, (sockaddr *) &destAddr, sizeof(destAddr)) < 0) {
        throw RSocketException("Connect failed (connect())", true);
    }


}

void RSocket::Send( const void *buffer, int bufferLen ) throw(RSocketException)
{
    if (::send(m_sockDesc, (void *) buffer, bufferLen, 0) < 0) {
        throw RSocketException("Send failed (send())", true);
    }
}

int RSocket::Recv( void *buffer, int bufferLen ) throw(RSocketException)
{
    int nBytes;
    if ((nBytes = ::recv(m_sockDesc, (void *) buffer, bufferLen, 0)) < 0) {
        throw RSocketException("Received failed (recv())", true);
    }
    char* sData = static_cast<char *>(buffer);
    sData[nBytes] = '\0';
    return nBytes;
}

std::string RSocket::GetPeerAddress() throw(RSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getpeername(m_sockDesc, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0) {
        throw RSocketException("Fetch of foreign address failed (getpeername())", true);
    }
    return inet_ntoa(addr.sin_addr);
}

unsigned short RSocket::GetPeerPort() throw(RSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);

    if (getpeername(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
        throw RSocketException("Fetch of foreign port failed (getpeername())", true);
    }
    return ntohs(addr.sin_port);
}

RSocket& RSocket::operator<<(const string& sStr )
{
     Send(sStr.c_str(), sStr.length());
     return *this;
}

RSocket& RSocket::operator>>( string& sStr )
{
    char *buff = new char[GetReadBufferSize()];
    Recv(buff, GetReadBufferSize());
    sStr.append(buff);
    delete [] buff;
    return *this;
}

int RSocket::OnDataRead(unsigned long timeToWait)
{

    fd_set master;
    struct timeval      *ptimeout = NULL;


    fd_set read_fds;


    int fdmax;


    FD_ZERO(&master);
    FD_ZERO(&read_fds);


    FD_SET(m_sockDesc, &master);

    fdmax = m_sockDesc;


    read_fds = master;
    //cout<<"Waiting for select";
    int nRet;
    if (timeToWait == ULONG_MAX)
    {
        nRet  = select(fdmax+1, &read_fds, NULL, NULL, NULL);
        if (nRet == -1)
            nRet = DATA_EXCEPTION;
        else if (nRet > 0)
            nRet = DATA_ARRIVED;
    }
    else
    {
        struct timeval       timeout;
        timeout.tv_sec  = timeToWait;
        timeout.tv_usec = 0;
        nRet = select(fdmax+1, &read_fds, NULL, NULL, &timeout);
        if (nRet == -1)
            nRet = DATA_EXCEPTION;
        else if (nRet > 0)
            nRet = DATA_ARRIVED;
        else if(nRet == 0)
            nRet = DATA_TIMED_OUT;
    }

    return nRet;
}

void RSocket::SetBindToDevice( const string& sInterface ) throw(RSocketException)
{
    //struct ifreq ifr;
    //memset(&ifr, 0, sizeof(ifr));
    //snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), sInterface.c_str());
    //Todo:SO_BINDTODEVICE not declared error comes in CygWin, need to compile in Linux.
    /*int nRet = ::setsockopt(m_sockDesc, SOL_SOCKET, SO_BINDTODEVICE, (void*)&ifr, sizeof(ifr));

    if (nRet < 0)
    {
        throw RSocketException("Error in binding to device ", true);
    }*/
}

UDPSocket::UDPSocket() throw(RSocketException):RSocket(UdpSocket,IPv4Protocol)
{
    SetBroadcast();
}

UDPSocket::UDPSocket( unsigned short localPort ) throw(RSocketException):
RSocket(UdpSocket,IPv4Protocol)
{
    BindLocalPort(localPort);
    SetBroadcast();
}

UDPSocket::UDPSocket( const string &localAddress, unsigned short localPort ) throw(RSocketException):
RSocket(UdpSocket,IPv4Protocol)
{
    BindLocalAddressAndPort(localAddress, localPort);
    SetBroadcast();
}

void UDPSocket::DisconnectFromHost() throw(RSocketException)
{
    sockaddr_in nullAddr;
    memset(&nullAddr, 0, sizeof(nullAddr));
    nullAddr.sin_family = AF_UNSPEC;
    // Try to disconnect
    if (::connect(m_sockDesc, (sockaddr *) &nullAddr, sizeof(nullAddr)) < 0)
    {
        if (errno != EAFNOSUPPORT)
        {
            throw RSocketException("Disconnect failed (connect())", true);
        }
    }
}

void UDPSocket::SendDataGram( const void *buffer, int bufferLen, const string &foreignAddress,
    unsigned short foreignPort )  throw(RSocketException)
{

    sockaddr_in destAddr;
    FillAddr(foreignAddress, foreignPort, destAddr);

    if (sendto(m_sockDesc, (void *) buffer, bufferLen, 0,(sockaddr *) &destAddr, sizeof(destAddr)) != bufferLen)
    {
        throw RSocketException("Send failed (sendto())", true);
    }

}

int UDPSocket::RecvDataGram( void *buffer, int bufferLen, string &sourceAddress, unsigned short &sourcePort )
    throw(RSocketException)
{
    sockaddr_in clntAddr;
    socklen_t addrLen = sizeof(clntAddr);
    int nBytes;
    if ((nBytes = recvfrom(m_sockDesc, (void *) buffer, bufferLen, 0, (sockaddr *) &clntAddr,
        (socklen_t *) &addrLen)) < 0)
    {
        throw RSocketException("Receive failed (recvfrom())", true);
    }
    sourceAddress = inet_ntoa(clntAddr.sin_addr);
    sourcePort    = ntohs(clntAddr.sin_port);
    char* sData = static_cast<char *>(buffer);
    sData[nBytes] = '\0';
    return nBytes;
}

void UDPSocket::SetMulticastTTL( unsigned char multicastTTL ) throw(RSocketException)
{
    if (setsockopt(m_sockDesc, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &multicastTTL, sizeof(multicastTTL)) < 0)
    {
        throw RSocketException("Multicast TTL set failed (setsockopt())", true);
    }
}

void UDPSocket::JoinGroup( const string &multicastGroup ) throw(RSocketException)
{
    struct ip_mreq multicastRequest;

    multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastGroup.c_str());
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(m_sockDesc, IPPROTO_IP, IP_ADD_MEMBERSHIP,
        (void *) &multicastRequest,
        sizeof(multicastRequest)) < 0)
    {
        throw RSocketException("Multicast group join failed (setsockopt())", true);
    }

}

void UDPSocket::LeaveGroup( const string &multicastGroup ) throw(RSocketException)
{
    struct ip_mreq multicastRequest;

    multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastGroup.c_str());
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(m_sockDesc, IPPROTO_IP, IP_DROP_MEMBERSHIP,
        (void *) &multicastRequest,
        sizeof(multicastRequest)) < 0)
    {
        throw RSocketException("Multicast group leave failed (setsockopt())", true);
    }

}

void UDPSocket::SetBroadcast()
{

    int broadcastPermission = 1;
    setsockopt(m_sockDesc, SOL_SOCKET, SO_BROADCAST,
        (void *) &broadcastPermission, sizeof(broadcastPermission));

}
