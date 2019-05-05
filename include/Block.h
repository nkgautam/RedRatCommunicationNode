#ifndef BLOCK_H
#define BLOCK_H
#include<string>
using namespace std;

class Block
{
    public:
        Block(int index, string timestamp, string data, string previousHash = " ");
        virtual ~Block();
    protected:
    private:
    int m_index;
    string m_timestamp;
    string m_data;
    string m_previousHash;
    string m_hash;
    string calculateHash();
};

#endif // BLOCK_H
