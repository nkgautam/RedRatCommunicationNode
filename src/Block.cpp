#include "Block.h"

Block::Block(int index, string timestamp, string data, string previousHash = " ")
{
    //ctor
    this->m_index = index;
    this->m_timestamp = timestamp;
    this->m_data = data;
    this->m_previousHash = previousHash;
    this->m_hash = this->calculateHash();

}

Block::~Block()
{
    //dtor
}

string Block::calculateHash()
{
    string retHash = " ";
    return retHash;
}
