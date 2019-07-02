#include "NodeList.h"
#include <future>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <sstream>
#include "SensorDS18B20.h"

using namespace std;
using namespace rapidjson;

vector<string> NodeList::nodes = {""};

NodeList::NodeList()
{

}

UDPSocket sock2(PORTMASTER);

int ReceiveMsg1(string sourceAddress)
{
    char str1[256] ={0};
    unsigned short sport = PORTMASTER;
    //NodeList nodeList;
    try{
        cout << "Recv Start\n " ;
        int ret = sock2.RecvDataGram(str1,256 ,sourceAddress,sport);
        if(ret > 0)
        {
            //cout << "Recv end\n" ;
            str1[ret] = '\0';
            //cout << endl<<"Peer : " << str1 << endl;
            //cout << endl<<"Peer Address: " << sourceAddress << endl;

            //cout<<"response sent\n";
            string temp = string(str1);
            if(temp.compare("AddMe") == 0){
                NodeList::nodes.push_back(sourceAddress);
                cout <<"Node Added: " << sourceAddress << endl;
            }
            else if(temp.compare("GetNodeList") == 0){
                string jsonNodes = "{\"Nodes\":[";

            for (int i=0; i< NodeList::nodes.size(); i++)
            {
                //cout << nodes[i] << "\n";
                if (i < (NodeList::nodes.size() - 1))
                    jsonNodes += "\""+NodeList::nodes[i]+"\" ," ;
                else
                    jsonNodes += "\""+NodeList::nodes[i]+"\" " ;

            }

            jsonNodes += "] }";

            const char* json =jsonNodes.c_str();
            Document dom;
            dom.Parse(json);

            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            dom.Accept(writer);

             //std::cout << buffer.GetString() << std::endl;
            //return buffer.GetString();
            string retNodeList = buffer.GetString();
            sock2.SendDataGram(retNodeList.c_str(),retNodeList.length(),sourceAddress,sport);
            cout <<"Node list sent to: " << sourceAddress << endl;
            }
            else
            {
                cout <<"Temperature of Node : " << sourceAddress << " is " << temp <<"deg C"<<endl;
            }
        }
        return ret;
    }
    catch(RSocketException e){
         cout<< "RSocketException \n";
        return 0;
    }
}


void
NodeList::ListenRequest()
{

    while(true){
        //cout<<"While() starts\n";
        string peerIPAddress = "0.0.0.0";
        std::future<int> recvMsg = std::async (ReceiveMsg1,peerIPAddress);
        //int ret = recvMsg.get();
        //cout<<"ret = "<<ret<<"\n";

    }
}

void
NodeList::SendAddNodeRequest(string masterNodeIP)
{
    string request = "AddMe";
    unsigned short sport = PORTMASTER;
    sock2.SendDataGram(request.c_str(),request.length(),masterNodeIP,sport);

}

void
NodeList::SendGetNodeListRequest(string masterNodeIP)
{
    string request = "GetNodeList";
    unsigned short sport = PORTMASTER;
    sock2.SendDataGram(request.c_str(),request.length(),masterNodeIP,sport);

    char str1[256] ={0};
    int ret = sock2.RecvDataGram(str1,256 ,masterNodeIP,sport);
        if(ret > 0)
        {
            //cout << "Recv end\n" ;
            str1[ret] = '\0';
            cout << endl<<"Master node sent node list : " << str1 << endl;

        }

}

void
NodeList::SendTemperature(string masterNodeIP)
{
    SensorDS18B20 temperature;
    //cout<< "temp = " << temperature.GetReading() <<endl;
    stringstream ss (stringstream::in | stringstream::out);
    ss << temperature.GetReading();

    string request = ss.str();
    unsigned short sport = PORTMASTER;
    cout <<"Temperature : " << request << " Deg C"<< endl;
    sock2.SendDataGram(request.c_str(),request.length(),masterNodeIP,sport);

}

