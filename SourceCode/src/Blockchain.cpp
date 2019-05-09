#include "Blockchain.h"
#include <iostream>

BlockChain::BlockChain()
{
    //ctor
    this->m_chain.push_back(this->createGenesisBlock());
}

BlockChain::~BlockChain()
{
    //dtor
}

Block BlockChain::createGenesisBlock()
{
    return Block(0,"05/05/2019","Genesis", "0");
}

Block BlockChain::getLatestBlock()
{
    int size = this->m_chain.size();
    return this->m_chain[size-1];
}

void BlockChain::addBlock(Block block)
{
    block.m_previousHash = this->getLatestBlock().m_hash;
    block.m_hash = block.calculateHash();
    this->m_chain.push_back(block);
}

void BlockChain::showBlockChain()
{
cout << "\nBlockchain elements are: ";

    for (int i = 0; i < this->m_chain.size(); i++)
    {
        Block block = this->m_chain.at(i);
        block.showBlock();
    }

}
