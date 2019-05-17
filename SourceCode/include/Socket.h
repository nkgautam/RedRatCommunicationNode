#ifndef SOCKET_H
#define SOCKET_H


#include <cstring>            // For string
#include <exception>         // For exception class
#include<string>
#include <sys/types.h>       // For data types
#include <sys/socket.h>      // For socket(), connect(), send(), and recv()
#include <netdb.h>           // For gethostbyname()
#include <arpa/inet.h>       // For inet_addr()
#include <unistd.h>          // For close()
#include <netinet/in.h>      // For sockaddr_in
#include<errno.h>
#include<climits>
using namespace std;


class RSocketException: public std::exception
{
public:

    RSocketException(const string &message, bool bSysMsg = false) throw();
    virtual ~RSocketException() throw ();
    virtual const char* what() const throw (){  return m_sMsg.c_str(); }
protected:
    std::string m_sMsg;
};


class RSocket
{
public:
    virtual ~RSocket();

    enum SocketType
    {
        TcpSocket = SOCK_STREAM,
        UdpSocket = SOCK_DGRAM,
        UnknownSocketType =-1
    };

    enum NetworkLayerProtocol
    {
        IPv4Protocol = AF_INET,
        IPv6Protocol = AF_INET6,
        UnknownNetworkLayerProtocol = -1
    };

    enum ReadResult
    {
       DATA_ARRIVED   = 0,
       DATA_TIMED_OUT = ETIMEDOUT,
       DATA_EXCEPTION = 255
    };

    string GetLocalAddress() throw(RSocketException);
    unsigned short GetLocalPort() throw(RSocketException);
    void BindLocalPort(unsigned short localPort) throw(RSocketException);
    void BindLocalAddressAndPort(const string &localAddress, unsigned short localPort = 0) throw(RSocketException);
    unsigned long int GetReadBufferSize ();
    void SetReadBufferSize(unsigned int nSize) throw(RSocketException);
    void SetNonBlocking(bool bBlocking) throw(RSocketException);
    void ConnectToHost(const string &foreignAddress, unsigned short foreignPort) throw(RSocketException);
    void Send(const void *buffer, int bufferLen) throw(RSocketException);
    int Recv(void *buffer, int bufferLen) throw(RSocketException);
    string GetPeerAddress() throw(RSocketException);
    unsigned short GetPeerPort() throw(RSocketException);
    RSocket& operator<<(const string& sStr );
    RSocket& operator>>(string& sStr);
    virtual int OnDataRead(unsigned long timeToWait = ULONG_MAX);
    void SetBindToDevice(const string& sInterface) throw(RSocketException);
protected:
    int m_sockDesc;
    RSocket(SocketType type, NetworkLayerProtocol protocol) throw(RSocketException);
    RSocket(int sockDesc);
    static void FillAddr( const string & localAddress, unsigned short localPort, sockaddr_in& localAddr );
private:
    // Prevent the user from trying to use Exact copy of this object
    RSocket(const RSocket &sock);
    void operator=(const RSocket &sock);
};



class UDPSocket : public RSocket
{
public:
    UDPSocket() throw(RSocketException);
    UDPSocket(unsigned short localPort) throw(RSocketException);
    UDPSocket(const string &localAddress, unsigned short localPort) throw(RSocketException);
    void DisconnectFromHost() throw(RSocketException);
    void SendDataGram(const void *buffer, int bufferLen, const string &foreignAddress,
        unsigned short foreignPort) throw(RSocketException);
    int RecvDataGram(void *buffer, int bufferLen, string &sourceAddress,
               unsigned short &sourcePort) throw(RSocketException);
    void SetMulticastTTL(unsigned char multicastTTL) throw(RSocketException);
    void JoinGroup(const string &multicastGroup) throw(RSocketException);
    void LeaveGroup(const string &multicastGroup) throw(RSocketException);
private:
    void SetBroadcast();
};
#endif // SOCKET_H
