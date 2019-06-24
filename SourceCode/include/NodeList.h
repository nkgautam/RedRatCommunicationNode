#ifndef NODELIST_H
#define NODELIST_H

#include <vector>
#include "Socket.h"
#include <future>
#include <string>

#define PORTMASTER       9003

class NodeList
{
    public:
        NodeList();

    void ListenRequest();
    void SendAddNodeRequest(string masterNodeIP);
    void SendGetNodeListRequest(string masterNodeIP);
    static vector <string> nodes;
   // string NodeListJson();
    protected:

    private:
    //std::list<string> nodes;

    //bool AddNode(string ipSelfAddress);
    //string GetNodeList(string masterIpAddress);
};

#endif // NODELIST_H
