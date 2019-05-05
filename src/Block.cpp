#include "Block.h"
#include<iostream>

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

string Block::calculateHash()
{
    string retHash = "0000aadnv";
    return retHash;
}

void Block::ShowBlock(){
 cout<< this->m_index << "\n ";
 cout<< this->m_timestamp << "\n ";
 cout<< this->m_data << "\n ";
 cout<< this->m_hash << "\n ";
}
