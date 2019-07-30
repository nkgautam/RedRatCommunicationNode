#ifndef BLOCK_H
#define BLOCK_H

#include <time.h>
#include <string>

using namespace std;

class Block
{
    public:
        string m_previousHash;
        string m_hash;
        Block(string data, string previousHash = " ");
        virtual ~Block();
        string calculateHash();
        string showBlock();
    protected:
    private:
        //int m_index;
        string m_timestamp;
        string m_data;
        //string sha256(const string str);

};

#endif // BLOCK_H
