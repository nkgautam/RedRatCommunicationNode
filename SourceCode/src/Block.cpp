#include "Block.h"
#include <iostream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "sha256.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

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
    string jsonStr = "{\"TimeStamp\":\""+this->m_timestamp+
    "\",\"Data\":\""+this->m_data+
    "\",\"PreviousHash\":\""+this->m_previousHash+
    "\",\"Hash\":\""+this->m_hash+
    "\"}";

     const char* json =jsonStr.c_str();
     Document dom;
     dom.Parse(json);

     StringBuffer buffer;
     Writer<StringBuffer> writer(buffer);
     dom.Accept(writer);


     std::cout << buffer.GetString() << std::endl;

}
