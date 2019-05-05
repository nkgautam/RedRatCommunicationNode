#ifndef BLOCK_H
#define BLOCK_H

#include <string>

using namespace std;

class block
{
    public:
        block(int index, string timestamp, string data, string previousHash);

    private:
    int m_index;
    string m_timestamp;
    string m_data;
    string m_previousHash;
    string m_hash;
    string calculateHash();
};

#endif // BLOCK_H
