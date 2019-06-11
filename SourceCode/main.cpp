#include <iostream>
#include <future>

#include "Blockchain.h"
#include "Socket.h"
#include "Chat.h"

using namespace std;



int main()
{
    cout << "RedRat Communication Node APP\n" << endl;

    /*
    BlockChain  blockChain;
    blockChain.addBlock(Block(1,"01/05/2019", "data1"));
    blockChain.addBlock(Block(2,"02/05/2019", "data2"));

    blockChain.showBlockChain();
    */

    Chat chat;
    chat.Run();

    return 0;
}
