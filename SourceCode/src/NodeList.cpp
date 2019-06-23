#include "NodeList.h"
#include <future>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

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
            if(str1 == "AddMe"){
                //NodeList::nodes.push_back(sourceAddress);
                cout <<"Node Added: " << sourceAddress << endl;
            }
            if(str1 == "GetNodeList"){
                string message = "{\"nodes\":[ \"192.168.29.122\" , \"192.168.29.133\"}";//NodeList::NodeListJson();
                sock2.SendDataGram(message.c_str(),message.length(),sourceAddress,sport);
                cout <<"Node list sent to: " << sourceAddress << endl;
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
    string message = "AddMe";
    unsigned short sport = PORTMASTER;
    sock2.SendDataGram(message.c_str(),message.length(),masterNodeIP,sport);

}

void
NodeList::SendGetNodeListRequest(string masterNodeIP)
{
    string message = "GetNodeList";
    unsigned short sport = PORTMASTER;
    sock2.SendDataGram(message.c_str(),message.length(),masterNodeIP,sport);

    char str1[256] ={0};
    int ret = sock2.RecvDataGram(str1,256 ,masterNodeIP,sport);
        if(ret > 0)
        {
            //cout << "Recv end\n" ;
            str1[ret] = '\0';
            cout << endl<<"Master node sent node list : " << str1 << endl;

        }

}


string
NodeList::NodeListJson(){


    string jsonNodes = "{\"Nodes\":[";

    /*for (int i=0; i< this.nodes.size(); i++)
    {
        //cout << nodes[i] << "\n";
        if (i < (nodes.size() - 1))
            jsonNodes += "\""+nodes[i]+"\" ," ;
        else
            jsonNodes += "\""+nodes[i]+"\" " ;

    }*/

    jsonNodes += "] }";

    const char* json =jsonNodes.c_str();
    Document dom;
    dom.Parse(json);

    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    dom.Accept(writer);

     //std::cout << buffer.GetString() << std::endl;
    return buffer.GetString();

}
