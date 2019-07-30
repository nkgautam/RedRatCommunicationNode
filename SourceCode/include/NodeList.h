#ifndef NODELIST_H
#define NODELIST_H

#include <vector>
#include "Socket.h"
#include <future>
#include <string>
#include <time.h>

#define PORTMASTER       9003

class NodeList
{
    public:
        NodeList();

    void ListenRequest();
    void SendAddNodeRequest(string masterNodeIP);
    void SendGetNodeListRequest(string masterNodeIP);
    void SendTemperature(string masterNodeIP);
    static vector <string> nodes;

    protected:

    private:
        clock_t tClock;
};

#endif // NODELIST_H
