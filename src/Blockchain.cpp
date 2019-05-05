#include "Blockchain.h"
#include <iostream>

Blockchain::Blockchain()
{
    //ctor
    this->m_chain.push_back(this->CreateGenesisBlock());
}

Blockchain::~Blockchain()
{
    //dtor
}

Block Blockchain::CreateGenesisBlock()
{
    return Block(0,"05/05/2019","Genesis", "0");
}

Block Blockchain::GetLatestBlock()
{
    int size = this->m_chain.size();
    return this->m_chain[size-1];
}

void Blockchain::AddBlock(Block newBlock)
{
    newBlock.m_previousHash = this->GetLatestBlock().m_hash;
    newBlock.m_hash = newBlock.calculateHash();
    this->m_chain.push_back(newBlock);
}

void Blockchain::ShowBlockchain()
{
cout << "\nBlockchain elements are: ";

    for (int i = 0; i < this->m_chain.size(); i++)
    {
        Block block = this->m_chain.at(i);
        block.ShowBlock();
    }

}
