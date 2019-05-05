#include <iostream>
#include "Blockchain.h"

using namespace std;

int main()
{
    cout << "RedRat Communication Node APP" << endl;

    Blockchain  blockchain;
    blockchain.AddBlock(Block(1,"01/05/2019", "data1"));
    blockchain.AddBlock(Block(2,"02/05/2019", "data2"));

    blockchain.ShowBlockchain();
    return 0;
}
