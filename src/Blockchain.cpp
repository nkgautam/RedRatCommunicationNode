#include "Blockchain.h"

Blockchain::Blockchain()
{
    this->m_chain.push_back(this.CreateGenesisBlock())
    //ctor
}

Blockchain::~Blockchain()
{
    //dtor
}

Block Blockchain::CreateGenesisBlock()
{
    return new Block(0,"05/05/2019","Genesis", "0")
}
