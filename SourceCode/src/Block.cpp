#include "Block.h"
#include <iostream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "sha256.h"
using namespace std;

Block::Block(int index, string timestamp, string data, string previousHash )
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

string
Block::calculateHash()
{
    std::ostringstream ss;
    ss << this->m_index << this->m_timestamp << this->m_data;

    return sha256(ss.str());

}

void
Block::showBlock(){
 cout<< this->m_index << "\n ";
 cout<< this->m_timestamp << "\n ";
 cout<< this->m_data << "\n ";
 cout<< this->m_previousHash << "\n ";
 cout<< this->m_hash << "\n ";
}
