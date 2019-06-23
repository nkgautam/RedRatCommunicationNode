#ifndef NODELIST_H
#define NODELIST_H

#include <list>
#include "Socket.h"
#include <future>
#include <string>

#define PORTMASTER       9003

class NodeList
{
    public:
        NodeList();

    void ListenRequest();
    void SendAddNodeRequest();
    void SendGetNodeListRequest();

    protected:

    private:
    //std::list<string> nodes;
    vector <string> nodes;
    string NodeListJson();
    //bool AddNode(string ipSelfAddress);
    //string GetNodeList(string masterIpAddress);
};

#endif // NODELIST_H
