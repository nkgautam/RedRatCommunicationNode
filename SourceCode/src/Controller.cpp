#include <iostream>
#include "Controller.h"
#include "Chat.h"
#include "NodeList.h"
#include "ClientID.h"

Controller::Controller()
{
    //ctor
}

void
Controller::Run(string masterNodeIP)
{
    cout << "                                               "<<endl;
    cout << " **********************************************"<<endl;
    cout << "                    MENU                      "<<endl;
    cout << " **********************************************"<<endl;

    cout << " 1. For, Create and show ID"<<endl;
    cout << " 2. For, Send Temperature data to master node" <<endl;
    cout << " 3. For, Send Temperature data to all nodes" <<endl;
    cout << " 4. For, Chat with other node" << endl;
    cout << " 5. For, Send Add Me request to master node"<<endl;
    cout << " 6. For, Get All node list from the master node"<<endl;
    cout << " (Press 1-6 from above menu) "<<endl;
    cout << " Ctrl +x to exit" <<endl;
    cout << "                                               "<<endl;
    cout << " **********************************************"<<endl;

    int input;

    cin>> input;

    switch(input)
    {
        case 1:
        {
            ClientID clID;
            cout<< "Create ID:"<<clID.CreateID()<<endl;
            cout<< "Get ID:"<<clID.GetID()<<endl;
            cout << "                                               "<<endl;
        }
        break;

        case 2:
        {
            NodeList nodeList;

            while(1)
            {
               nodeList.SendTemperature(masterNodeIP);
                usleep( 10000 );
            }
        }
        break;

        case 3:
            cout<< "This is pending"<<endl;
        break;

        case 4:
        {
            Chat chat;
            chat.Run();
        }
        break;

        case 5:
        {
            NodeList nodeList;
            nodeList.SendAddNodeRequest(masterNodeIP);
        }
        break;

        case 6:
        {
            NodeList nodeList;
            nodeList.SendGetNodeListRequest(masterNodeIP);
        }
        break;

        default:
            cout << "That input isn’t valid\n";

    }


}
