#include "block.h"

block::block(int index, string timestamp, string data, string previousHash)
{
    //ctor
    this->m_index = index;
    this->m_timestamp = timestamp;
    this->m_data = data;
    this->m_previousHash = previousHash;
    this->m_hash = "";
}

string block::calculateHash()
{
    //use SHA 256
    string retHash = "Hashvalue";
    return retHash;
}
