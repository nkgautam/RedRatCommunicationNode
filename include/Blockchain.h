#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <vector>
#include "Block.h"
using namespace std;

class Blockchain
{
    public:
        Blockchain();
        virtual ~Blockchain();
        void ShowBlockchain();
        void AddBlock(Block newBlock);
    protected:
    private:
    vector <Block> m_chain;
    Block CreateGenesisBlock();
    Block GetLatestBlock();

};

#endif // BLOCKCHAIN_H
