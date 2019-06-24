#include <iostream>
#include <future>
//#include <stdio.h>
//#include <sqlite3.h>
#include "Blockchain.h"
#include "Socket.h"
#include "Chat.h"
#include "SqliteDataBase.h"
#include "NodeList.h"

using namespace std;

int main(int argc, char* argv[])
{
    cout << "RedRat Communication Node APP\n" << endl;
    if (argc < 2) {

      NodeList nodeList;
      nodeList.ListenRequest();

    }
    else
    {
        string masterNode = argv[1];
        NodeList nodeList;
        nodeList.SendAddNodeRequest(masterNode);

        nodeList.SendGetNodeListRequest(masterNode);
        /*
        BlockChain  blockChain;
        blockChain.addBlock(Block(1,"01/05/2019", "data1"));
        blockChain.addBlock(Block(2,"02/05/2019", "data2"));

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
