#include <iostream>
#include <future>
//#include <stdio.h>
//#include <sqlite3.h>
#include "Blockchain.h"
#include "Socket.h"
#include "Chat.h"
#include "SqliteDataBase.h"
#include "NodeList.h"
#include "SensorDS18B20.h"
#include "Identity.h"
#include "ClientID.h"
#include "Controller.h"

using namespace std;


int main(int argc, char* argv[])
{

    if (argc < 2) {
        cout << "RedRat Communication Master Node APP\n" << endl;
        NodeList nodeList;
        nodeList.ListenRequest();
    }
    else
    {
        cout << "RedRat Communication Node APP\n" << endl;

        Controller ctrl;
        while(1)
        {
            ctrl.Run(argv[1]);

        }


        //Identity identity;
        //identity.CreateID("user","password");


        //string masterNode = argv[1];

        //NodeList nodeList;
        //nodeList.SendAddNodeRequest(masterNode);
        //nodeList.SendGetNodeListRequest(masterNode);


        //while(1)
        //{
        //   nodeList.SendTemperature(masterNode);
        //    usleep( 10000 );
        //}

        /*

        BlockChain  blockChain;
        blockChain.addBlock(Block("data1"));
        blockChain.addBlock(Block("data2"));

        blockChain.showBlockChain();

        */

        //Chat chat;
        //chat.Run();

        /*

        SqliteDataBase sqlitedb;

        char* sql = "INSERT INTO NODEMSG (SENDER,JSON) "  \
             "VALUES ('192.168.43.121', '{json:yes}' ); " ;

        sqlitedb.InsertRecord(sql);

        char* sql2 = "SELECT * FROM NODEMSG";
        sqlitedb.SelectRecord(sql2);

        //  char* sql3 = "DELETE from NODEMSG where SENDER='sender';";
        //  sqlitedb.DeleteRecord(sql3);

        */

    }

    return 0;
}
