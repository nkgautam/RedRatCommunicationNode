#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H
#include <vector>
#include "Block.h"
using namespace std;

class BlockChain
{
    public:
        BlockChain();
        virtual ~BlockChain();
        void showBlockChain();
        void addBlock(Block block);
    protected:
    private:
    vector <Block> m_chain;
    Block createGenesisBlock();
    Block getLatestBlock();

};

#endif // BLOCKCHAIN_H
