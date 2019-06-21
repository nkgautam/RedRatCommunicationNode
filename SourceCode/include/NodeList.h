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

    protected:

    private:
    std::list<string> nodes;
    //bool AddNode(string ipSelfAddress);
    //string GetNodeList(string masterIpAddress);
};

#endif // NODELIST_H
