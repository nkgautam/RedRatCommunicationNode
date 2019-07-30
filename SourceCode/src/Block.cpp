#include "Block.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <time.h>
#include "sha256.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace std;
using namespace rapidjson;

Block::Block(string data, string previousHash )
{
    //ctor
    time_t now;
    struct tm * timeinfo;
    time(&now);
    char buffer[80];
    timeinfo = localtime(&now);
    strftime(buffer,80,"%F %T",timeinfo);

    this->m_timestamp =strtok(buffer, "\n");

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
    ss << this->m_timestamp << this->m_data;

    return sha256(ss.str());

}

string
Block::showBlock(){
    string jsonStr = "{ \"TimeStamp\":\""+this->m_timestamp+
    "\",\"Data\":\""+this->m_data+
    "\",\"PreviousHash\":\""+this->m_previousHash+
    "\",\"Hash\":\""+this->m_hash+
    "\" }";

     const char* json =jsonStr.c_str();
     rapidjson::Document dom;
     dom.Parse(json);

     rapidjson::StringBuffer buffer;
     rapidjson::Writer<StringBuffer> writer(buffer);
     dom.Accept(writer);
    //std::cout << jsonStr << std::endl;
    // std::cout << buffer.GetString() << std::endl;
    // return buffer.GetString();
    return  jsonStr;

}
