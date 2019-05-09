#include <iostream>
#include "Blockchain.h"

using namespace std;

int main()
{
    cout << "RedRat Communication Node APP\n" << endl;

    BlockChain  blockChain;
    blockChain.addBlock(Block(1,"01/05/2019", "data1"));
    blockChain.addBlock(Block(2,"02/05/2019", "data2"));

    blockChain.showBlockChain();
    return 0;
}
