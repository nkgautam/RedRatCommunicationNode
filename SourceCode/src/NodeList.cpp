#include "NodeList.h"
#include "Block.h"
#include <time.h>
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
            time_t tNow;
            time(&tNow);

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
            std::cout <<"Node list sent to: " << sourceAddress << endl;
            }
            else
            {
                std::cout <<"Json from Node : " << sourceAddress << " is " << temp <<endl;
                const char* jsonRecv =temp.c_str();
                Document domRecv;
                domRecv.Parse(jsonRecv);
                assert(domRecv.IsObject());
                assert(domRecv.HasMember("TimeStamp"));
                assert(domRecv["TimeStamp"].IsString());
                string strTime = domRecv["TimeStamp"].GetString();
                time_t tRecv;
                int yy, month, dd, hh, mm, ss;
                struct tm timeInfo;
                const char *zStart = strTime.c_str();

                sscanf(zStart, "%d-%d-%d %d:%d:%d ", &yy, &month, &dd, &hh, &mm, &ss);
                timeInfo.tm_year = yy - 1900;
                timeInfo.tm_mon = month - 1;
                timeInfo.tm_mday = dd;
                timeInfo.tm_hour = hh;
                timeInfo.tm_min = mm;
                timeInfo.tm_sec = ss;
                timeInfo.tm_isdst = -1;

                tRecv = mktime(&timeInfo);

                double seconds;
                seconds = difftime(tNow,tRecv);

                std::cout << "Time when remote node sent data   : "<< ctime(&tRecv) << std::endl;
                std::cout << "Time when local node recevied data: " << ctime(&tNow) << std::endl;
                std::cout << "Time to recev json                : " << seconds << " seconds\n" <<std::endl;



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
    cout << endl<<"Add me request sent to master node " << endl;

}

void
NodeList::SendGetNodeListRequest(string masterNodeIP)
{
    string request = "GetNodeList";
    unsigned short sport = PORTMASTER;
    tClock = clock();
    sock2.SendDataGram(request.c_str(),request.length(),masterNodeIP,sport);

    char str1[256] ={0};

    int ret = sock2.RecvDataGram(str1,256 ,masterNodeIP,sport);
        if(ret > 0)
        {
            tClock = clock() - tClock;
            float seconds = ((float)tClock)/CLOCKS_PER_SEC;
            //
            str1[ret] = '\0';
            cout << endl<<"Master node sent node list : " << str1 << endl;
            cout << "It took " << tClock << " clicks " << " ( "<< seconds<<" seconds) to send & receive the nodelist."<<endl;

        }

}

void
NodeList::SendTemperature(string masterNodeIP)
{
    SensorDS18B20 temperature;
    //cout<< "temp = " << temperature.GetReading() <<endl;
    stringstream ss (stringstream::in | stringstream::out);
    ss << temperature.GetReading();

    string temp = ss.str();
    Block jsonblock(temp,"0");
    string jsonBuffer = jsonblock.showBlock();

    unsigned short sport = PORTMASTER;
    cout <<"Local Temperature : " << temp << " Deg C"<< " sent."<<endl;
    sock2.SendDataGram(jsonBuffer.c_str(),jsonBuffer.length(),masterNodeIP,sport);

}

